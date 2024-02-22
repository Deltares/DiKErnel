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
        private const double tolerance = 1e-14;

        private const string timeStepsKey = "Time step";
        private const string waterLevelsKey = "Water level";
        private const string waveHeightsKey = "Wave height";
        private const string wavePeriodsKey = "Wave period";
        private const string waveDirectionsKey = "Wave direction";

        private const string dikeOrientationKey = "Orientation";
        private const string outerToePositionKey = "Outer toe";
        private const string outerCrestPositionKey = "Outer crest";

        private const string calculationPositionKey = "Position";
        private const string topLayerTypeKey = "Top layer type";

        private const string xCoordinatesKey = "X";
        private const string zCoordinatesKey = "Z";
        private const string roughnessCoefficientsKey = "Roughness coefficient";

        private const string slopeForeshoreKey = "Slope foreshore";
        private const string bottomZForeshoreKey = "Bottom level foreshore";

        private const string damageKey = "Failure number";
        private const string initialDamageKey = "Initial damage";
        private const string averageNumberOfWavesKey = "Average number of waves";
        private const string criticalFrontVelocityKey = "Critical front velocity";
        private const string frontVelocityKey = "Front velocity";
        private const string criticalCumulativeOverloadKey = "Critical cumulative overload";
        private const string increasedLoadTransitionKey = "Increased load transition";
        private const string reducedStrengthTransitionKey = "Reduced strength transition";

        private readonly ScenarioContext context;

        private LocationDependentOutput output;

        public GrassWaveRunupBattjesGroenendijkAnalyticalStepDefinitions(ScenarioContext context)
        {
            this.context = context;
        }

        [Given(@"the following(?: adjusted)? hydraulic loads:")]
        [Given(@"the following(?: adjusted)? dike geometry:")]
        public void GivenTheFollowingCollectionsAreAdjusted(Table table)
        {
            foreach (string property in table.Header)
            {
                context[property] = table.Rows.Select(r => r.GetString(property)).ToArray();
            }
        }

        [Given(@"the following(?: adjusted)? calculation settings:")]
        [Given(@"the following(?: adjusted)? dike properties:")]
        [Given(@"the following(?: adjusted)? characteristic points:")]
        public void GivenTheFollowingPropertiesAreAdjusted(Table table)
        {
            foreach (TableRow row in table.Rows)
            {
                context[row.Id()] = row.Value();
            }
        }

        [Given(@"the (.*) is adjusted to (.*)")]
        public void GivenPropertyIsAdjustedTo(string propertyName, string value)
        {
            char[] characters = propertyName.ToCharArray();
            characters[0] = char.ToUpper(characters[0], CultureInfo.InvariantCulture);
            var adjustedPropertyName = new string(characters);
            
            context[adjustedPropertyName] = value;
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

            output = calculator.Result.Data.LocationDependentOutputItems[0];
        }

        [Then(@"the damage is (.*)")]
        public void ThenTheDamageIs(double expectedDamage)
        {
            IReadOnlyList<double> damages = output.GetDamages();
            double actualDamage = damages[damages.Count - 1];
            Assert.That(actualDamage, Is.EqualTo(expectedDamage).Within(tolerance));
        }

        [Then(@"the cumulative overload is (.*)")]
        public void ThenTheCumulativeOverloadIs(double? expectedCumulativeOverload)
        {
            GrassCumulativeOverloadTimeDependentOutput[] cumulativeOverLoadOutputs =
                output.TimeDependentOutputItems.Cast<GrassCumulativeOverloadTimeDependentOutput>().ToArray();
            
            Assert.That(cumulativeOverLoadOutputs[cumulativeOverLoadOutputs.Length - 1].CumulativeOverload,
                        Is.EqualTo(expectedCumulativeOverload).Within(tolerance));
        }

        private GrassTopLayerType GetGrassTopLayerType(string id)
        {
            switch (GetString(id))
            {
                case "Open sod":
                    return GrassTopLayerType.OpenSod;
                case "Closed sod":
                    return GrassTopLayerType.ClosedSod;
                default:
                    throw new NotSupportedException();
            }
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
            return values.Where(s => !Equals(s, "N.A.")).Select(double.Parse).ToArray();
        }

        private void AddTimeSteps(CalculationInputBuilder builder)
        {
            IReadOnlyList<double> times = GetDoubleCollection(timeStepsKey);
            IReadOnlyList<double> waterLevels = GetDoubleCollection(waterLevelsKey);
            IReadOnlyList<double> waveHeightsHm0 = GetDoubleCollection(waveHeightsKey);
            IReadOnlyList<double> wavePeriodsTm10 = GetDoubleCollection(wavePeriodsKey);
            IReadOnlyList<double> waveDirections = GetDoubleCollection(waveDirectionsKey);

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
            IReadOnlyList<double> roughnessCoefficients = GetDoubleCollection(roughnessCoefficientsKey);

            for (var i = 0; i < xLocations.Count - 1; i++)
            {
                double startPointX = xLocations[i];
                double startPointZ = zLocations[i];
                double endPointX = xLocations[i + 1];
                double endPointZ = zLocations[i + 1];

                if (i < roughnessCoefficients.Count)
                {
                    builder.AddDikeProfileSegment(startPointX, startPointZ, endPointX, endPointZ, roughnessCoefficients[i]);
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
            builder.AddForeshore(GetDouble(slopeForeshoreKey), GetDouble(bottomZForeshoreKey));
        }

        private void AddLocation(CalculationInputBuilder builder)
        {
            var constructionProperties = new GrassWaveRunupBattjesGroenendijkAnalyticalLocationConstructionProperties(
                GetDouble(calculationPositionKey), GetGrassTopLayerType(topLayerTypeKey))
            {
                FailureNumber = GetNullableDouble(damageKey),
                InitialDamage = GetNullableDouble(initialDamageKey),
                AverageNumberOfWavesCtm = GetNullableDouble(averageNumberOfWavesKey),
                CriticalFrontVelocity = GetNullableDouble(criticalFrontVelocityKey),
                FrontVelocityCu = GetNullableDouble(frontVelocityKey),
                CriticalCumulativeOverload = GetNullableDouble(criticalCumulativeOverloadKey),
                IncreasedLoadTransitionAlphaM = GetNullableDouble(increasedLoadTransitionKey),
                ReducedStrengthTransitionAlphaS = GetNullableDouble(reducedStrengthTransitionKey)
            };

            builder.AddGrassWaveRunupBattjesGroenendijkAnalyticalLocation(constructionProperties);
        }
    }
}