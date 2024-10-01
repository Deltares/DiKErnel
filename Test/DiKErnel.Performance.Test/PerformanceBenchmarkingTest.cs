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
using DiKErnel.Integration.Data.AsphaltWaveImpact;
using DiKErnel.Integration.Data.Grass;
using DiKErnel.Integration.Data.GrassWaveImpact;
using DiKErnel.Integration.Data.GrassWaveOvertopping;
using DiKErnel.Integration.Data.GrassWaveRunup;
using DiKErnel.Integration.Data.NaturalStoneWaveImpact;
using DiKErnel.Util;
using NUnit.Framework;

namespace DiKErnel.Performance.Test
{
    [TestFixture]
    public class PerformanceBenchmarkingTest
    {
        [Test]
        [TestCaseSource(nameof(LocationCases))]
        public void PerformanceBenchmarking(Action<CalculationInputBuilder> addLocationAction)
        {
            var builder = new CalculationInputBuilder(10);

            AddDikeProfile(builder);

            AddTimeSteps(builder);

            addLocationAction(builder);

            DataResult<ICalculationInput> result = builder.Build();

            if (!result.Successful)
            {
                Console.WriteLine($"Validation error: {result.Events.First(e => e.Type == EventType.Error).Message}");
                return;
            }

            CalculateAndWriteOutput(result.Data);
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

            double[] waveDirections = Resources.WDir_12h.Split(',')
                                               .Select(s => double.Parse(s, CultureInfo.InvariantCulture))
                                               .ToArray();

            double[] times = Enumerable.Range(0, waterLevels.Length + 1)
                                       .Select(i => 12 * 3600d * i)
                                       .ToArray();

            for (var i = 0; i <= waterLevels.Length - 1; i++)
            {
                builder.AddTimeStep(times[i], times[i + 1], waterLevels[i], waveHeights[i], wavePeriods[i], waveDirections[i]);
            }
        }

        private static IEnumerable<TestCaseData> LocationCases()
        {
            yield return new TestCaseData(
                    (Action<CalculationInputBuilder>) (builder => builder.AddGrassWaveImpactLocation(
                                                              new GrassWaveImpactLocationConstructionProperties(
                                                                  10, GrassTopLayerType.OpenSod))))
                .SetName("GrassWaveImpact");

            yield return new TestCaseData(
                    (Action<CalculationInputBuilder>) (builder => builder.AddGrassWaveOvertoppingRayleighAnalyticalLocation(
                                                              new GrassWaveOvertoppingRayleighLocationConstructionProperties(
                                                                  26, GrassTopLayerType.OpenSod)
                                                              {
                                                                  DikeHeight = 11
                                                              })))
                .SetName("GrassWaveOvertoppingRayleighAnalytical");

            yield return new TestCaseData(
                    (Action<CalculationInputBuilder>) (builder => builder.AddGrassWaveOvertoppingRayleighDiscreteLocation(
                                                              new GrassWaveOvertoppingRayleighDiscreteLocationConstructionProperties(
                                                                  26, GrassTopLayerType.OpenSod)
                                                              {
                                                                  DikeHeight = 11
                                                              })))
                .SetName("GrassWaveOvertoppingRayleighDiscrete");

            yield return new TestCaseData(
                    (Action<CalculationInputBuilder>) (builder => builder.AddGrassWaveRunupBattjesGroenendijkAnalyticalLocation(
                                                              new GrassWaveRunupBattjesGroenendijkAnalyticalLocationConstructionProperties(
                                                                  10, GrassTopLayerType.OpenSod))))
                .SetName("GrassWaveRunupBattjesGroenendijkAnalytical");

            yield return new TestCaseData(
                    (Action<CalculationInputBuilder>) (builder => builder.AddGrassWaveRunupRayleighDiscreteLocation(
                                                              new GrassWaveRunupRayleighDiscreteLocationConstructionProperties(
                                                                  10, GrassTopLayerType.OpenSod))))
                .SetName("GrassWaveRunupRayleighDiscrete");

            yield return new TestCaseData(
                    (Action<CalculationInputBuilder>) (builder => builder.AddNaturalStoneWaveImpactLocation(
                                                              new NaturalStoneWaveImpactLocationConstructionProperties(
                                                                  10, NaturalStoneWaveImpactTopLayerType.NordicStone, 0.4, 1.65))))
                .SetName("NaturalStoneWaveImpact");

            yield return new TestCaseData(
                    (Action<CalculationInputBuilder>) (builder => builder.AddAsphaltWaveImpactLocation(
                                                              new AsphaltWaveImpactLocationConstructionProperties(
                                                                  10, AsphaltWaveImpactTopLayerType.HydraulicAsphaltConcrete, 1.75, 60, 0.3,
                                                                  16000))))
                .SetName("AsphaltWaveImpact");
        }

        private static void CalculateAndWriteOutput(ICalculationInput calculationInput)
        {
            var stopWatch = new Stopwatch();

            stopWatch.Start();

            DataResult<CalculationOutput> result = Calculator.Calculate(calculationInput);

            stopWatch.Stop();

            string outputMessage = $"{calculationInput.LocationDependentInputItems.Count,4};" +
                                   $"{calculationInput.TimeDependentInputItems.Count,8};" +
                                   $"{Math.Round(stopWatch.Elapsed.TotalSeconds, 2).ToString(CultureInfo.InvariantCulture),7};";

            for (var i = 0; i < result.Data.LocationDependentOutputItems.Count; i++)
            {
                IReadOnlyList<double> cumulativeDamages =
                    result.Data.LocationDependentOutputItems[i]
                          .GetCumulativeDamages(calculationInput.LocationDependentInputItems[i].InitialDamage);

                var x = Math.Round(calculationInput.LocationDependentInputItems[i].X, 2).ToString(CultureInfo.InvariantCulture);
                var damage = Math.Round(cumulativeDamages[cumulativeDamages.Count - 1], 2).ToString(CultureInfo.InvariantCulture);

                outputMessage += $" {x,5}; {damage,8};";
            }

            Console.Write(outputMessage.Remove(outputMessage.Length - 1, 1));
        }
    }
}