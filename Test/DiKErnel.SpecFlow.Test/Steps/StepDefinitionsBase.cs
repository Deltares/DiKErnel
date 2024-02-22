// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
// 
// This file is part of DiKErnel.
// 
// DiKErnel is free software: you can redistribute it and/or modify it under the terms of the
// GNU Lesser General Public License as published by the Free Software Foundation, either
// version 3 of the License, or (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License along with this
// program. If not, see <http://www.gnu.org/licenses/>.
// 
// All names, logos, and references to "Deltares" are registered trademarks of Stichting
// Deltares and remain full property of Stichting Deltares at all times. All rights reserved.

using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using DiKErnel.Core;
using DiKErnel.Core.Data;
using DiKErnel.Integration;
using DiKErnel.Integration.Data.Grass;
using DiKErnel.SpecFlow.Test.Steps.Definitions;
using DiKErnel.Util;
using TechTalk.SpecFlow;

namespace DiKErnel.SpecFlow.Test.Steps
{
    public abstract class StepDefinitionsBase
    {
        protected StepDefinitionsBase(ScenarioContext context)
        {
            Context = context;
        }

        protected ScenarioContext Context { get; }

        protected void RunCalculation()
        {
            var builder = new CalculationInputBuilder(GetDouble(DikeProfileDefinitions.DikeOrientationKey));
            ConfigureBuilder(builder);

            DataResult<ICalculationInput> result = builder.Build();
            var calculator = new Calculator(result.Data);
            calculator.WaitForCompletion();

            Context[GeneralDefinitions.OutputKey] = calculator.Result.Data.LocationDependentOutputItems[0];
        }

        protected virtual void ConfigureBuilder(CalculationInputBuilder builder)
        {
            AddTimeSteps(builder);
            AddDikeProfile(builder);
            AddProfilePoints(builder);
            AddLocation(builder);
        }

        protected abstract void AddLocation(CalculationInputBuilder builder);

        protected double GetDouble(string id)
        {
            return double.Parse(GetString(id), CultureInfo.InvariantCulture);
        }

        protected GrassTopLayerType GetGrassTopLayerType(string id)
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

        protected double? GetNullableDouble(string id)
        {
            if (Context.TryGetValue(id, out object retrievedValue))
            {
                var value = (string) retrievedValue;
                return string.IsNullOrWhiteSpace(value) ? (double?) null : double.Parse(value, CultureInfo.InvariantCulture);
            }

            return null;
        }

        private void AddProfilePoints(CalculationInputBuilder builder)
        {
            AddProfilePoint(builder, DikeProfileDefinitions.CharacteristicPointTypeOuterToe, CharacteristicPointType.OuterToe);
            AddProfilePoint(builder, DikeProfileDefinitions.CharacteristicPointTypeCrestOuterBerm, CharacteristicPointType.CrestOuterBerm);
            AddProfilePoint(builder, DikeProfileDefinitions.CharacteristicPointTypeNotchOuterBerm, CharacteristicPointType.NotchOuterBerm);
            AddProfilePoint(builder, DikeProfileDefinitions.CharacteristicPointTypeOuterCrest, CharacteristicPointType.OuterCrest);
            AddProfilePoint(builder, DikeProfileDefinitions.CharacteristicPointTypeInnerCrest, CharacteristicPointType.InnerCrest);
            AddProfilePoint(builder, DikeProfileDefinitions.CharacteristicPointTypeInnerToe, CharacteristicPointType.InnerToe);
        }

        private void AddProfilePoint(CalculationInputBuilder builder, string key, CharacteristicPointType characteristicPoint)
        {
            double? position = GetNullableDouble(key);
            if (position.HasValue)
            {
                builder.AddDikeProfilePoint(position.Value, characteristicPoint);
            }
        }

        private string GetString(string id)
        {
            return (string) Context[id];
        }

        private double[] GetDoubleCollection(string id)
        {
            var values = (IReadOnlyList<string>) Context[id];
            return values.Where(s => !Equals(s, GeneralDefinitions.NotApplicable)).Select(double.Parse).ToArray();
        }

        private void AddTimeSteps(CalculationInputBuilder builder)
        {
            IReadOnlyList<double> times = GetDoubleCollection(HydraulicLoadDefinitions.TimeStepsKey);
            IReadOnlyList<double> waterLevels = GetDoubleCollection(HydraulicLoadDefinitions.WaterLevelsKey);
            IReadOnlyList<double> waveHeightsHm0 = GetDoubleCollection(HydraulicLoadDefinitions.WaveHeightsKey);
            IReadOnlyList<double> wavePeriodsTm10 = GetDoubleCollection(HydraulicLoadDefinitions.WavePeriodsKey);
            IReadOnlyList<double> waveDirections = GetDoubleCollection(HydraulicLoadDefinitions.WaveDirectionsKey);

            for (var i = 0; i < times.Count - 1; i++)
            {
                builder.AddTimeStep(times[i], times[i + 1], waterLevels[i], waveHeightsHm0[i], wavePeriodsTm10[i],
                                    waveDirections[i]);
            }
        }

        private void AddDikeProfile(CalculationInputBuilder builder)
        {
            IReadOnlyList<double> xLocations = GetDoubleCollection(DikeProfileDefinitions.XCoordinatesKey);
            IReadOnlyList<double> zLocations = GetDoubleCollection(DikeProfileDefinitions.ZCoordinatesKey);
            IReadOnlyList<double> roughnessCoefficients = GetDoubleCollection(DikeProfileDefinitions.RoughnessCoefficientsKey);

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
    }
}