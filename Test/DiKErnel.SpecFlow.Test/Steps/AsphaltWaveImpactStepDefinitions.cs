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
using DiKErnel.Integration.Data.AsphaltWaveImpact;
using DiKErnel.SpecFlow.Test.Steps.Definitions;
using TechTalk.SpecFlow;

namespace DiKErnel.SpecFlow.Test.Steps
{
    public class AsphaltWaveImpactStepDefinitions : StepDefinitionsBase
    {
        public AsphaltWaveImpactStepDefinitions(ScenarioContext context) : base(context) {}

        [When(@"I run the asphalt wave impact calculation")]
        public void WhenIRunTheAsphaltWaveImpactCalculation()
        {
            RunCalculation();
        }

        protected override void AddLocation(CalculationInputBuilder builder)
        {
            var constructionProperties = new AsphaltWaveImpactLocationConstructionProperties(
                Context.GetDouble(GeneralDefinitions.CalculationPosition),
                AsphaltWaveImpactTopLayerType.HydraulicAsphaltConcrete,
                Context.GetDouble(AsphaltWaveImpactDefinitions.FlexuralStrength),
                Context.GetDouble(AsphaltWaveImpactDefinitions.SoilElasticity),
                Context.GetDouble(AsphaltWaveImpactDefinitions.ThicknessUpperLayer),
                Context.GetDouble(AsphaltWaveImpactDefinitions.ElasticModulusUpperLayer))
            {
                FailureNumber = Context.GetNullableDouble(GeneralDefinitions.FailureNumber),
                InitialDamage = Context.GetNullableDouble(GeneralDefinitions.InitialDamage),
                DensityOfWater = Context.GetNullableDouble(AsphaltWaveImpactDefinitions.DensityOfWater),
                ThicknessSubLayer = Context.GetNullableDouble(AsphaltWaveImpactDefinitions.ThicknessSubLayer),
                ElasticModulusSubLayer = Context.GetNullableDouble(AsphaltWaveImpactDefinitions.ElasticModulusSubLayer),
                AverageNumberOfWavesCtm = Context.GetNullableDouble(GeneralDefinitions.AverageNumberOfWaves),
                FatigueAlpha = Context.GetNullableDouble(AsphaltWaveImpactDefinitions.FatigueAlpha),
                FatigueBeta = Context.GetNullableDouble(AsphaltWaveImpactDefinitions.FatigueBeta),
                ImpactNumberC = Context.GetNullableDouble(AsphaltWaveImpactDefinitions.ImpactNumberC),
                StiffnessRelationNu = Context.GetNullableDouble(AsphaltWaveImpactDefinitions.StiffnessRelation)
            };

            builder.AddAsphaltWaveImpactLocation(constructionProperties);
        }
    }
}