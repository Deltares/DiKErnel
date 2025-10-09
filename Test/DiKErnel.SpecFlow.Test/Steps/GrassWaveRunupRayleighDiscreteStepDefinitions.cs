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

using DiKErnel.Integration;
using DiKErnel.Integration.Data.GrassWaveRunup;
using DiKErnel.SpecFlow.Test.Steps.Definitions;
using TechTalk.SpecFlow;

namespace DiKErnel.SpecFlow.Test.Steps
{
    internal sealed class GrassWaveRunupRayleighDiscreteStepDefinitions : StepDefinitionsBase
    {
        public GrassWaveRunupRayleighDiscreteStepDefinitions(ScenarioContext context) : base(context) {}

        [When(@"I run the grass wave run-up Rayleigh discrete calculation")]
        public void WhenIRunTheGrassWaveRunupRayleighDiscreteCalculation()
        {
            RunCalculation();
        }

        protected override void AddLocation(CalculationInputBuilder builder)
        {
            var constructionProperties = new GrassWaveRunupRayleighDiscreteLocationConstructionProperties(
                Context.GetDouble(GeneralDefinitions.CalculationPosition), Context.GetGrassTopLayerType())
            {
                FailureNumber = Context.GetNullableDouble(GeneralDefinitions.FailureNumber),
                InitialDamage = Context.GetNullableDouble(GeneralDefinitions.InitialDamage),
                CriticalCumulativeOverload = Context.GetNullableDouble(GrassCumulativeOverloadDefinitions.CriticalCumulativeOverload),
                CriticalFrontVelocity = Context.GetNullableDouble(GrassCumulativeOverloadDefinitions.CriticalFrontVelocity),
                IncreasedLoadTransitionAlphaM = Context.GetNullableDouble(GrassCumulativeOverloadDefinitions.IncreasedLoadTransition),
                ReducedStrengthTransitionAlphaS = Context.GetNullableDouble(GrassCumulativeOverloadDefinitions.ReducedStrengthTransition),
                AverageNumberOfWavesCtm = Context.GetNullableDouble(GeneralDefinitions.AverageNumberOfWavesCtm),
                FrontVelocityCu = Context.GetNullableDouble(GrassCumulativeOverloadDefinitions.FrontVelocity),
                FixedNumberOfWaves = Context.GetNullableInt(GrassRayleighDiscreteDefinitions.FixedNumberOfWaves)
            };

            builder.AddGrassWaveRunupRayleighDiscreteLocation(constructionProperties);
        }
    }
}