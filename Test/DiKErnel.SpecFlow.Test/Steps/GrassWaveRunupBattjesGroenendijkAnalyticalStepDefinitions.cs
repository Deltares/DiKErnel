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

using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using DiKErnel.Core;
using DiKErnel.Core.Data;
using DiKErnel.Core.Extensions;
using DiKErnel.Integration;
using DiKErnel.Integration.Data.Grass;
using DiKErnel.Integration.Data.GrassWaveRunup;
using DiKErnel.Util;
using NUnit.Framework;
using TechTalk.SpecFlow;
using TechTalk.SpecFlow.Assist;

namespace DiKErnel.SpecFlow.Test.Steps
{
    [Binding]
    public class GrassWaveRunupBattjesGroenendijkAnalyticalStepDefinitions
    {
        private const string timeStepsKey = "Time step";
        private const string waterLevelsKey = "Water level";
        private const string waveHeightsHm0Key = "Wave height Hm0";
        private const string wavePeriodsTm10Key = "Wave period Tm10";
        private const string waveDirectionsKey = "Wave directions";

        private const string dikeOrientationKey = "dijkorientatie";
        private const string outerToePositionKey = "Outer toe";
        private const string outerCrestPositionKey = "Outer crest";

        private const string locationXCoordinateKey = "positie";
        private const string grassTopLayerTypeKey = "typeToplaag";

        private const string xCoordinatesKey = "X";
        private const string zCoordinatesKey = "Z";
        private const string roughnessCoefficientsKey = "Roughness coefficient";

        private const string foreshoreSlopeKey = "tanAvl";
        private const string bottomZForeshoreKey = "bodemVoorlandZ";

        private const string damageKey = "faalgetal";
        private const string initialDamageKey = "beginschade";
        private const string averageNumberOfWavesCtmKey = "factorCtm";
        private const string criticalFrontVelocityKey = "kritiekeFrontsnelheid";
        private const string frontVelocityCuKey = "frontsnelheid";
        private const string criticalCumulativeOverloadKey = "kritiekeCumulatieveOverbelasting";
        private const string increasedLoadTransitionAlfaMKey = "verhogingBelastingOvergangAlfaM";
        private const string reducedStrengthTransitionAlphaSKey = "verlagingSterkteOvergangAlfaS";
        private const double tolerance = 1e-14;

        private readonly ScenarioContext context;

        private IReadOnlyList<LocationDependentOutput> outputs;

        public GrassWaveRunupBattjesGroenendijkAnalyticalStepDefinitions(ScenarioContext context)
        {
            this.context = context;
        }

        [Given(@"the following dike profile and a dike orientation of (.*):")]
        public void GivenTheFollowingDikeProfile(string dikeOrientation, Table table)
        {
            context[dikeOrientationKey] = dikeOrientation;

            context[xCoordinatesKey] = table.Rows.Select(row => row.GetString(xCoordinatesKey)).ToArray();
            context[zCoordinatesKey] = table.Rows.Select(row => row.GetString(zCoordinatesKey)).ToArray();
            context[roughnessCoefficientsKey] = table.Rows.Select(row => row.GetString(roughnessCoefficientsKey)).ToArray();
        }

        [Given(@"the following time steps and hydraulic loads:")]
        [Given(@"the following series are adjusted:")]
        public void GivenTheFollowingCollectionsAreAdjusted(Table table)
        {
            foreach (string property in table.Header)
            {
                context[property] = table.Rows.Select(r => r.GetString(property)).ToArray();
            }
        }

        [Given(@"the following dike profile points:")]
        public void GivenTheFollowingValuesAreAdjusted(Table table)
        {
            foreach (string property in table.Header)
            {
                context[property] = table.Rows[0].GetString(property);
            }
        }

        [Given(@"the following rekeninstellingen:")]
        [Given(@"the following (?:(?!series).)* are adjusted:")]
        public void GivenTheFollowingCalculationSettingsAreAdjusted(Table table)
        {
            foreach (TableRow row in table.Rows)
            {
                context[row.Id()] = row.Value();
            }
        }

        [When(@"I change the property (\w*) to a value of (.*)")]
        public void WhenIChangeTheValueOf(string propertyName, string value)
        {
            context[propertyName] = value;
        }

        [When(@"I run the grass wave run-up Battjes-Groenendijk analytical calculation")]
        public void WhenIRunTheBattjesGroenendijkWaveRunupCalculation()
        {
            var builder = new CalculationInputBuilder(GetDouble(dikeOrientationKey));
            AddTimeSteps(builder);
            AddDikeProfile(builder);
            AddProfilePoints(builder);
            AddForeshore(builder);
            AddLocation(builder);

            DataResult<ICalculationInput> result = builder.Build();
            var calculator = new Calculator(result.Data);
            calculator.WaitForCompletion();

            outputs = calculator.Result.Data.LocationDependentOutputItems;
        }

        [Then(@"the schadegetal is (.*)")]
        public void ThenTheDamageIs(double expectedDamage)
        {
            IReadOnlyList<double> damages = outputs[0].GetDamages();
            double actualDamage = damages[damages.Count - 1];
            Assert.That(actualDamage, Is.EqualTo(expectedDamage).Within(tolerance));
        }

        [Then(@"the output values for (.*) and (.*) are")]
        public void ThenTheDamageAndCumulativeOverloadAre(double expectedDamage, double? expectedCumulativeOverload)
        {
            LocationDependentOutput locationDependentOutput = outputs[0];

            GrassCumulativeOverloadTimeDependentOutput[] cumulativeOverLoadOutputs =
                locationDependentOutput.TimeDependentOutputItems.Cast<GrassCumulativeOverloadTimeDependentOutput>().ToArray();
            Assert.That(cumulativeOverLoadOutputs[cumulativeOverLoadOutputs.Length - 1].CumulativeOverload,
                        Is.EqualTo(expectedCumulativeOverload).Within(tolerance));

            IReadOnlyList<double> damages = locationDependentOutput.GetDamages();
            double actualDamage = damages[damages.Count - 1];

            Assert.That(actualDamage, Is.EqualTo(expectedDamage).Within(tolerance));
        }

        private GrassTopLayerType GetGrassTopLayerType(string id)
        {
            return GetString(id) == "grasOpenZode" ? GrassTopLayerType.OpenSod : GrassTopLayerType.ClosedSod;
        }

        private string GetString(string id)
        {
            return (string) context[id];
        }

        private double GetDouble(string id)
        {
            return double.Parse(GetString(id), CultureInfo.InvariantCulture);
        }

        private double? GetNullableDouble(string id)
        {
            if (context.TryGetValue(id, out object retrievedValue))
            {
                var value = (string) retrievedValue;
                return string.IsNullOrWhiteSpace(value) ? (double?) null : double.Parse(value, CultureInfo.InvariantCulture);
            }

            return null;
        }

        private double[] GetDoubleCollection(string id)
        {
            var values = (IReadOnlyList<string>) context[id];
            return values.Select(double.Parse).ToArray();
        }

        private List<double?> GetNullableDoubleCollection(string id)
        {
            var values = (IReadOnlyList<string>) context[id];
            var parsedValues = new List<double?>();
            foreach (string value in values)
            {
                if (string.IsNullOrWhiteSpace(value))
                {
                    parsedValues.Add(null);
                }
                else
                {
                    parsedValues.Add(double.Parse(value, CultureInfo.InvariantCulture));
                }
            }

            return parsedValues;
        }

        private void AddTimeSteps(CalculationInputBuilder builder)
        {
            IReadOnlyList<double> times = GetDoubleCollection(timeStepsKey);
            IReadOnlyList<double> waterLevels =
                GetNullableDoubleCollection(waterLevelsKey).TakeWhile(d => d.HasValue).Cast<double>().ToArray();
            IReadOnlyList<double> waveHeightsHm0 =
                GetNullableDoubleCollection(waveHeightsHm0Key).TakeWhile(d => d.HasValue).Cast<double>().ToArray();
            IReadOnlyList<double> wavePeriodsTm10 =
                GetNullableDoubleCollection(wavePeriodsTm10Key).TakeWhile(d => d.HasValue).Cast<double>().ToArray();
            IReadOnlyList<double> waveDirections =
                GetNullableDoubleCollection(waveDirectionsKey).TakeWhile(d => d.HasValue).Cast<double>().ToArray();

            for (var i = 0; i < times.Count - 1; i++)
            {
                builder.AddTimeStep(times[i], times[i + 1], waterLevels[i], waveHeightsHm0[i], wavePeriodsTm10[i],
                                    waveDirections[i]);
            }
        }

        private void AddDikeProfile(CalculationInputBuilder builder)
        {
            IReadOnlyList<double> xLocations = GetDoubleCollection(xCoordinatesKey);
            IReadOnlyList<double> zLocations = GetDoubleCollection(zCoordinatesKey);
            IReadOnlyList<double?> roughnessCoefficients = GetNullableDoubleCollection(roughnessCoefficientsKey);

            for (var i = 0; i < xLocations.Count - 1; i++)
            {
                double startPointX = xLocations[i];
                double startPointZ = zLocations[i];
                double endPointX = xLocations[i + 1];
                double endPointZ = zLocations[i + 1];

                double? roughnessCoefficient = roughnessCoefficients[i];
                if (roughnessCoefficient.HasValue)
                {
                    builder.AddDikeProfileSegment(startPointX, startPointZ, endPointX, endPointZ, roughnessCoefficient.Value);
                }
                else
                {
                    builder.AddDikeProfileSegment(startPointX, startPointZ, endPointX, endPointZ);
                }
            }
        }

        private void AddProfilePoints(CalculationInputBuilder builder)
        {
            builder.AddDikeProfilePoint(GetDouble(outerToePositionKey), CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(GetDouble(outerCrestPositionKey), CharacteristicPointType.OuterCrest);
        }

        private void AddForeshore(CalculationInputBuilder builder)
        {
            double foreshoreSlope = GetDouble(foreshoreSlopeKey);
            double bottomForeshoreZ = GetDouble(bottomZForeshoreKey);

            builder.AddForeshore(foreshoreSlope, bottomForeshoreZ);
        }

        private void AddLocation(CalculationInputBuilder builder)
        {
            GrassTopLayerType topLayerType = GetGrassTopLayerType(grassTopLayerTypeKey);

            var constructionProperties = new GrassWaveRunupBattjesGroenendijkAnalyticalLocationConstructionProperties(
                GetDouble(locationXCoordinateKey), topLayerType)
            {
                FailureNumber = GetNullableDouble(damageKey),
                InitialDamage = GetNullableDouble(initialDamageKey),
                AverageNumberOfWavesCtm = GetNullableDouble(averageNumberOfWavesCtmKey),
                CriticalFrontVelocity = GetNullableDouble(criticalFrontVelocityKey),
                FrontVelocityCu = GetNullableDouble(frontVelocityCuKey),
                CriticalCumulativeOverload = GetNullableDouble(criticalCumulativeOverloadKey),
                IncreasedLoadTransitionAlphaM = GetNullableDouble(increasedLoadTransitionAlfaMKey),
                ReducedStrengthTransitionAlphaS = GetNullableDouble(reducedStrengthTransitionAlphaSKey)
            };

            builder.AddGrassWaveRunupBattjesGroenendijkAnalyticalLocation(constructionProperties);
        }
    }
}