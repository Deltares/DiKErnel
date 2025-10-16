// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
//
// This file is part of DiKErnel.
//
// This program is free software; you can redistribute it and/or modify it under the terms of
// the GNU Lesser General Public License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with this
// program; if not, see <https://www.gnu.org/licenses/>.
//
// All names, logos, and references to "Deltares" are registered trademarks of Stichting
// Deltares and remain full property of Stichting Deltares at all times. All rights reserved.

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Globalization;
using System.Linq;
using DiKErnel.Core;
using DiKErnel.Core.Data;
using DiKErnel.Integration;
using NUnit.Framework;

namespace DiKErnel.Performance.Test
{
    [TestFixture]
    public abstract class PerformanceTestBase
    {
        private CalculationInputBuilder builder;

        protected abstract double ExpectedDamage { get; }

        protected abstract Action<CalculationInputBuilder> AddLocationForFailureMechanismAction { get; }

        [SetUp]
        public void Arrange()
        {
            builder = new CalculationInputBuilder(0);

            AddDikeProfile(builder);

            AddTimeSteps(builder);
        }

        [Test]
        [TestCaseSource(nameof(ParallelizationCases))]
        public void PerformanceTest(CalculatorSettings calculatorSettings)
        {
            int numberOfLocations = calculatorSettings.CalculateLocationsInParallel ? 20 : 1;

            for (var i = 0; i < numberOfLocations; i++)
            {
                AddLocationForFailureMechanismAction(builder);
            }

            ICalculationInput calculationInput = builder.Build().Data;

            SuccessResult result = PerformCalculationAndWriteDuration(calculatorSettings, calculationInput);

            for (var i = 0; i < numberOfLocations; i++)
            {
                AssertDamage(result.CalculationOutput.LocationDependentOutputItems[i]);
            }
        }

        private static void AddDikeProfile(CalculationInputBuilder builder)
        {
            builder.AddForeshore(0.004, -4);

            builder.AddDikeProfileSegment(0, 7.09, 18.39, 13.22, 1);
            builder.AddDikeProfileSegment(18.39, 13.22, 23.39, 13.22, 1);
            builder.AddDikeProfileSegment(23.39, 13.22, 33.05, 0, 1);

            builder.AddDikeProfilePoint(0, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(18.39, CharacteristicPointType.OuterCrest);
            builder.AddDikeProfilePoint(23.39, CharacteristicPointType.InnerCrest);
            builder.AddDikeProfilePoint(33.05, CharacteristicPointType.InnerToe);
        }

        private static void AddTimeSteps(CalculationInputBuilder builder)
        {
            double[] waterLevels = Resources.htime_12h.Split(',')
                                            .Select(s => double.Parse(s, CultureInfo.InvariantCulture))
                                            .ToArray();

            double[] waveHeights = Resources.Hm0_12h.Split(',')
                                            .Select(s => double.Parse(s, CultureInfo.InvariantCulture))
                                            .ToArray();

            double[] wavePeriods = Resources.Tmm10_12h.Split(',')
                                            .Select(s => double.Parse(s, CultureInfo.InvariantCulture))
                                            .ToArray();

            double[] times = Enumerable.Range(0, waterLevels.Length + 1)
                                       .Select(i => 12 * 3600d * i)
                                       .ToArray();

            for (var i = 0; i <= waterLevels.Length - 1; i++)
            {
                builder.AddTimeStep(times[i], times[i + 1], waterLevels[i], waveHeights[i], wavePeriods[i], 0);
            }
        }

        private static IEnumerable<TestCaseData> ParallelizationCases()
        {
            yield return new TestCaseData(new CalculatorSettings())
                .SetName("WithoutParallelization");

            yield return new TestCaseData(new CalculatorSettings
            {
                CalculateLocationsInParallel = true
            }).SetName("LocationsInParallel");

            yield return new TestCaseData(new CalculatorSettings
            {
                CalculateTimeStepsInParallel = true
            }).SetName("TimeStepsInParallel");

            yield return new TestCaseData(new CalculatorSettings
            {
                CalculateLocationsInParallel = true,
                CalculateTimeStepsInParallel = true
            }).SetName("FullParallelization");
        }

        private static SuccessResult PerformCalculationAndWriteDuration(CalculatorSettings calculatorSettings,
                                                                        ICalculationInput calculationInput)
        {
            var stopWatch = new Stopwatch();

            stopWatch.Start();

            var result = (SuccessResult) Calculator.Calculate(calculationInput, calculatorSettings);

            stopWatch.Stop();

            double durationPerLocation = stopWatch.Elapsed.TotalSeconds / calculationInput.LocationDependentInputItems.Count;

            Console.WriteLine($"##teamcity[buildStatisticValue key='{TestContext.CurrentContext.Test.Name}' " +
                              $"value='{Math.Round(durationPerLocation, 2)}']", CultureInfo.InvariantCulture);

            return result;
        }

        private void AssertDamage(LocationDependentOutput locationDependentOutput)
        {
            double damage = Math.Round(locationDependentOutput.CumulativeDamages[^1], 2);

            Assert.That(damage, Is.EqualTo(ExpectedDamage));
        }
    }
}