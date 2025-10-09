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
using DiKErnel.Integration.Data.GrassWaveImpact;
using DiKErnel.SpecFlow.Test.Steps.Definitions;
using TechTalk.SpecFlow;

namespace DiKErnel.SpecFlow.Test.Steps
{
    internal sealed class GrassWaveImpactStepDefinitions : StepDefinitionsBase
    {
        public GrassWaveImpactStepDefinitions(ScenarioContext context) : base(context) {}

        [When(@"I run the grass wave impact calculation")]
        public void WhenIRunTheGrassWaveImpactCalculation()
        {
            RunCalculation();
        }

        protected override void AddLocation(CalculationInputBuilder builder)
        {
            var constructionProperties = new GrassWaveImpactLocationConstructionProperties(
                Context.GetDouble(GeneralDefinitions.CalculationPosition), Context.GetGrassTopLayerType())
            {
                FailureNumber = Context.GetNullableDouble(GeneralDefinitions.FailureNumber),
                InitialDamage = Context.GetNullableDouble(GeneralDefinitions.InitialDamage),
                TimeLineAgwi = Context.GetNullableDouble(GrassWaveImpactDefinitions.TimeLineA),
                TimeLineBgwi = Context.GetNullableDouble(GrassWaveImpactDefinitions.TimeLineB),
                TimeLineCgwi = Context.GetNullableDouble(GrassWaveImpactDefinitions.TimeLineC),
                MinimumWaveHeightTemax = Context.GetNullableDouble(GrassWaveImpactDefinitions.MinimumWaveHeight),
                MaximumWaveHeightTemin = Context.GetNullableDouble(GrassWaveImpactDefinitions.MaximumWaveHeight),
                WaveAngleImpactNwa = Context.GetNullableDouble(GrassWaveImpactDefinitions.WaveAngleImpactN),
                WaveAngleImpactQwa = Context.GetNullableDouble(GrassWaveImpactDefinitions.WaveAngleImpactQ),
                WaveAngleImpactRwa = Context.GetNullableDouble(GrassWaveImpactDefinitions.WaveAngleImpactR),
                UpperLimitLoadingAul = Context.GetNullableDouble(GrassWaveImpactDefinitions.UpperLimitLoading),
                LowerLimitLoadingAll = Context.GetNullableDouble(GrassWaveImpactDefinitions.LowerLimitLoading)
            };

            builder.AddGrassWaveImpactLocation(constructionProperties);
        }
    }
}