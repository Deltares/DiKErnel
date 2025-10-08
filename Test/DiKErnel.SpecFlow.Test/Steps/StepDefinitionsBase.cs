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

using System.Collections.Generic;
using DiKErnel.Core;
using DiKErnel.Core.Data;
using DiKErnel.Integration;
using DiKErnel.SpecFlow.Test.Steps.Definitions;
using DiKErnel.Util;
using TechTalk.SpecFlow;

namespace DiKErnel.SpecFlow.Test.Steps
{
    [Binding]
    public abstract class StepDefinitionsBase
    {
        protected StepDefinitionsBase(ScenarioContext context)
        {
            Context = context;
        }

        protected ScenarioContext Context { get; }

        protected void RunCalculation()
        {
            var builder = new CalculationInputBuilder(Context.GetDouble(DikeProfileDefinitions.DikeOrientation));

            ConfigureBuilder(builder);

            DataResult<ICalculationInput> inputResult = builder.Build();

            var result = (SuccessResult) Calculator.Calculate(inputResult.Data);

            Context[GeneralDefinitions.Output] = result.CalculationOutput.LocationDependentOutputItems[0];
        }

        protected virtual void ConfigureBuilder(CalculationInputBuilder builder)
        {
            AddTimeSteps(builder);
            AddDikeProfile(builder);
            AddProfilePoints(builder);
            AddLocation(builder);
        }

        protected abstract void AddLocation(CalculationInputBuilder builder);

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
            double? position = Context.GetNullableDouble(key);
            if (position.HasValue)
            {
                builder.AddDikeProfilePoint(position.Value, characteristicPoint);
            }
        }

        private void AddTimeSteps(CalculationInputBuilder builder)
        {
            IReadOnlyList<double> times = Context.GetDoubleCollection(HydraulicLoadDefinitions.TimeSteps);
            IReadOnlyList<double> waterLevels = Context.GetDoubleCollection(HydraulicLoadDefinitions.WaterLevels);
            IReadOnlyList<double> waveHeightsHm0 = Context.GetDoubleCollection(HydraulicLoadDefinitions.WaveHeights);
            IReadOnlyList<double> wavePeriodsTm10 = Context.GetDoubleCollection(HydraulicLoadDefinitions.WavePeriods);
            IReadOnlyList<double> waveDirections = Context.GetDoubleCollection(HydraulicLoadDefinitions.WaveDirections);

            for (var i = 0; i < times.Count - 1; i++)
            {
                builder.AddTimeStep(times[i], times[i + 1], waterLevels[i], waveHeightsHm0[i], wavePeriodsTm10[i],
                                    waveDirections[i]);
            }
        }

        private void AddDikeProfile(CalculationInputBuilder builder)
        {
            IReadOnlyList<double> xLocations = Context.GetDoubleCollection(DikeProfileDefinitions.XCoordinates);
            IReadOnlyList<double> zLocations = Context.GetDoubleCollection(DikeProfileDefinitions.ZCoordinates);
            IReadOnlyList<double> roughnessCoefficients = Context.GetNullableDoubleCollection(DikeProfileDefinitions.RoughnessCoefficients);

            for (var i = 0; i < xLocations.Count - 1; i++)
            {
                builder.AddDikeProfileSegment(xLocations[i], zLocations[i], xLocations[i + 1], zLocations[i + 1],
                                              roughnessCoefficients?[i]);
            }
        }
    }
}