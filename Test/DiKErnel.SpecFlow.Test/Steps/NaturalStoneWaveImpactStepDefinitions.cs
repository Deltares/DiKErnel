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
using DiKErnel.Integration.Data.NaturalStoneWaveImpact;
using DiKErnel.SpecFlow.Test.Steps.Definitions;
using TechTalk.SpecFlow;

namespace DiKErnel.SpecFlow.Test.Steps
{
    public class NaturalStoneWaveImpactStepDefinitions : StepDefinitionsBase
    {
        public NaturalStoneWaveImpactStepDefinitions(ScenarioContext context) : base(context) {}

        [When(@"I run the natural stone wave impact calculation")]
        public void WhenIRunTheNaturalStoneWaveImpactCalculation()
        {
            RunCalculation();
        }

        protected override void AddLocation(CalculationInputBuilder builder)
        {
            var thicknessTopLayer = 0.0;
            var relativeDensity = 0.0;

            var constructionProperties = new NaturalStoneWaveImpactLocationConstructionProperties(
                Context.GetDouble(GeneralDefinitions.CalculationPosition),
                NaturalStoneWaveImpactTopLayerType.NordicStone,
                thicknessTopLayer,
                relativeDensity)
            {
                FailureNumber = Context.GetNullableDouble(GeneralDefinitions.FailureNumber),
                InitialDamage = Context.GetNullableDouble(GeneralDefinitions.InitialDamage),
                HydraulicLoadAp = 0,
                HydraulicLoadBp = 0,
                HydraulicLoadCp = 0,
                HydraulicLoadNp = 0,
                HydraulicLoadAs = 0,
                HydraulicLoadBs = 0,
                HydraulicLoadCs = 0,
                HydraulicLoadNs = 0,
                HydraulicLoadXib = 0,
                SlopeUpperLevelAus = 0,
                SlopeLowerLevelAls = 0,
                UpperLimitLoadingAul = 0,
                UpperLimitLoadingBul = 0,
                UpperLimitLoadingCul = 0,
                LowerLimitLoadingAll = 0,
                LowerLimitLoadingBll = 0,
                LowerLimitLoadingCll = 0,
                DistanceMaximumWaveElevationAsmax = 0,
                DistanceMaximumWaveElevationBsmax = 0,
                NormativeWidthOfWaveImpactAwi = 0,
                NormativeWidthOfWaveImpactBwi = 0,
                WaveAngleImpactBetamax = 0
            };

            builder.AddNaturalStoneWaveImpactLocation(constructionProperties);
        }
    }
}