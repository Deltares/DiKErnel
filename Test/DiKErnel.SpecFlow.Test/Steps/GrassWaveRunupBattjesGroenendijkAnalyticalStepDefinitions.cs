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
        private const string timesKey = "tijdstippen";
        private const string waterLevelsKey = "waterstanden";
        private const string waveHeightsHm0Key = "golfhoogtenHm0";
        private const string wavePeriodsTm10Key = "golfperiodenTm10";
        private const string waveDirectionsKey = "golfrichtingen";

        private const string dikeOrientationKey = "dijkorientatie";
        private const string outerToePositionKey = "teenBuitenzijde";
        private const string outerCrestPositionKey = "kruinBuitenzijde";

        private const string locationXCoordinateKey = "positie";
        private const string grassTopLayerTypeKey = "typeToplaag";

        private const string xCoordinatesKey = "posities";
        private const string zCoordinatesKey = "hoogten";
        private const string roughnessCoefficientsKey = "ruwheidscoefficienten";

        private const string foreshoreSlopeKey = "tanAvl";
        private const string bottomZForeshoreKey = "bodemVoorlandZ";

        private const string failureNumberKey = "faalgetal";
        private const string initialDamageKey = "beginschade";
        private const string averageNumberOfWavesCtmKey = "factorCtm";
        private const string criticalFrontVelocityKey = "kritiekeFrontsnelheid";
        private const string frontVelocityCuKey = "frontsnelheid";
        private const string criticalCumulativeOverloadKey = "kritiekeCumulatieveOverbelasting";
        private const string increasedLoadTransitionAlfaMKey = "verhogingBelastingOvergangAlfaM";
        private const string reducedStrengthTransitionAlphaSKey = "verlagingSterkteOvergangAlfaS";

        private const string damageKey = "damage";

        private readonly ScenarioContext context;

        public GrassWaveRunupBattjesGroenendijkAnalyticalStepDefinitions(ScenarioContext context)
        {
            this.context = context;
        }

        [Given(@"the following dijkprofiel and a dijkorientatie of (.*):")]
        public void GivenTheFollowingDijkprofiel(string dikeOrientation, Table table)
        {
            context[dikeOrientationKey] = dikeOrientation;
            context[outerToePositionKey] = table.Rows[0].GetString(outerToePositionKey);
            context[outerCrestPositionKey] = table.Rows[0].GetString(outerCrestPositionKey);

            context[xCoordinatesKey] = table.Rows.Select(row => row.GetString(xCoordinatesKey)).ToArray();
            context[zCoordinatesKey] = table.Rows.Select(row => row.GetString(zCoordinatesKey)).ToArray();
            context[roughnessCoefficientsKey] = table.Rows.Select(row => row.GetString(roughnessCoefficientsKey)).ToArray();
        }

        [When(@"I run the calculation")]
        public void WhenIRunTheCalculation()
        {
            var builder = new CalculationInputBuilder(GetDouble(dikeOrientationKey));
            AddTimeSteps(builder);
            AddDikeProfile(builder);
            AddProfilePoints(builder);
            AddForeshore(builder);
            AddLocation(builder);

            DataResult<ICalculationInput>? result = builder.Build();
            var calculator = new Calculator(result.Data);
            calculator.WaitForCompletion();

            IReadOnlyList<double> damages = calculator.Result.Data.LocationDependentOutputItems[0].GetDamages();
            context[damageKey] = damages[damages.Count - 1];
        }

        [Given(@"the following tijdstippen and hydraulischeBelastingen:")]
        [Given(@"the following series are adjusted:")]
        public void GivenTheFollowingCollectionsAreAdjusted(Table table)
        {
            SetCollectionValues(table);
        }

        [Given(@"the following karakteristiekePunten:")]
        [Given(@"the following locaties:")]
        [Given(@"the following rekenmethoden:")]
        [Given(@"the following constant inputs:")]
        [Given(@"the following values are adjusted:")]
        public void GivenTheFollowingValuesAreAdjusted(Table table)
        {
            SetPropertyValues(table);
        }

        [Then(@"the schadegetal is (.*)")]
        public void ThenTheSchadegetalIs(decimal expectedDamage)
        {
            Assert.That(context[damageKey], Is.EqualTo(expectedDamage).Within(1e-14));
        }

        [When(@"I change the property (\w*) to a value of (.*)")]
        public void WhenIChangeTheValueOf(string propertyName, string value)
        {
            context[propertyName] = value;
        }

        [Then(@"the output value for (.*) is")]
        public void ThenTheOutputValueForIs(float expectedValue)
        {
            Assert.That(context[damageKey], Is.EqualTo(expectedValue).Within(1e-14));
        }

        private void SetCollectionValues(Table table)
        {
            foreach (string property in table.Header)
            {
                context[property] = table.Rows.Select(r => r.GetString(property)).ToArray();
            }
        }

        private void SetPropertyValues(Table table)
        {
            foreach (string property in table.Header)
            {
                context[property] = table.Rows[0].GetString(property);
            }
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
            IReadOnlyList<double> times = GetDoubleCollection(timesKey);
            IReadOnlyList<double?> waterLevels = GetNullableDoubleCollection(waterLevelsKey);
            IReadOnlyList<double?> waveHeightsHm0 = GetNullableDoubleCollection(waveHeightsHm0Key);
            IReadOnlyList<double?> wavePeriodsTm10 = GetNullableDoubleCollection(wavePeriodsTm10Key);
            IReadOnlyList<double?> waveDirections = GetNullableDoubleCollection(waveDirectionsKey);

            for (var i = 0; i < times.Count - 1; i++)
            {
                builder.AddTimeStep(times[i], times[i + 1], waterLevels[i].Value, waveHeightsHm0[i].Value, wavePeriodsTm10[i].Value,
                                    waveDirections[i].Value);
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
                FailureNumber = GetNullableDouble(failureNumberKey),
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