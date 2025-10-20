// Copyright (C) Stichting Deltares and State of the Netherlands 2025. All rights reserved.
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

using DiKErnel.Integration;
using DiKErnel.Integration.Data.NaturalStoneWaveImpact;
using DiKErnel.SpecFlow.Test.Steps.Definitions;
using TechTalk.SpecFlow;

namespace DiKErnel.SpecFlow.Test.Steps
{
    internal sealed class NaturalStoneWaveImpactStepDefinitions : StepDefinitionsBase
    {
        public NaturalStoneWaveImpactStepDefinitions(ScenarioContext context) : base(context) {}

        [When(@"I run the natural stone wave impact calculation")]
        public void WhenIRunTheNaturalStoneWaveImpactCalculation()
        {
            RunCalculation();
        }

        protected override void AddLocation(CalculationInputBuilder builder)
        {
            var constructionProperties = new NaturalStoneWaveImpactLocationConstructionProperties(
                Context.GetDouble(GeneralDefinitions.CalculationPosition),
                NaturalStoneWaveImpactTopLayerType.NordicStone,
                Context.GetDouble(NaturalStoneWaveImpactDefinitions.ThicknessTopLayer),
                Context.GetDouble(NaturalStoneWaveImpactDefinitions.RelativeDensity))
            {
                FailureNumber = Context.GetNullableDouble(GeneralDefinitions.FailureNumber),
                InitialDamage = Context.GetNullableDouble(GeneralDefinitions.InitialDamage),
                HydraulicLoadAp = Context.GetNullableDouble(NaturalStoneWaveImpactDefinitions.HydraulicLoadAp),
                HydraulicLoadBp = Context.GetNullableDouble(NaturalStoneWaveImpactDefinitions.HydraulicLoadBp),
                HydraulicLoadCp = Context.GetNullableDouble(NaturalStoneWaveImpactDefinitions.HydraulicLoadCp),
                HydraulicLoadNp = Context.GetNullableDouble(NaturalStoneWaveImpactDefinitions.HydraulicLoadNp),
                HydraulicLoadAs = Context.GetNullableDouble(NaturalStoneWaveImpactDefinitions.HydraulicLoadAs),
                HydraulicLoadBs = Context.GetNullableDouble(NaturalStoneWaveImpactDefinitions.HydraulicLoadBs),
                HydraulicLoadCs = Context.GetNullableDouble(NaturalStoneWaveImpactDefinitions.HydraulicLoadCs),
                HydraulicLoadNs = Context.GetNullableDouble(NaturalStoneWaveImpactDefinitions.HydraulicLoadNs),
                HydraulicLoadXib = Context.GetNullableDouble(NaturalStoneWaveImpactDefinitions.HydraulicLoadXib),
                SlopeUpperLevelAus = Context.GetNullableDouble(NaturalStoneWaveImpactDefinitions.SlopeUpperLevelAus),
                SlopeLowerLevelAls = Context.GetNullableDouble(NaturalStoneWaveImpactDefinitions.SlopeLowerLevelAls),
                UpperLimitLoadingAul = Context.GetNullableDouble(NaturalStoneWaveImpactDefinitions.UpperLimitLoadingAul),
                UpperLimitLoadingBul = Context.GetNullableDouble(NaturalStoneWaveImpactDefinitions.UpperLimitLoadingBul),
                UpperLimitLoadingCul = Context.GetNullableDouble(NaturalStoneWaveImpactDefinitions.UpperLimitLoadingCul),
                LowerLimitLoadingAll = Context.GetNullableDouble(NaturalStoneWaveImpactDefinitions.LowerLimitLoadingAll),
                LowerLimitLoadingBll = Context.GetNullableDouble(NaturalStoneWaveImpactDefinitions.LowerLimitLoadingBll),
                LowerLimitLoadingCll = Context.GetNullableDouble(NaturalStoneWaveImpactDefinitions.LowerLimitLoadingCll),
                DistanceMaximumWaveElevationAsmax =
                    Context.GetNullableDouble(NaturalStoneWaveImpactDefinitions.DistanceMaximumWaveElevationAsmax),
                DistanceMaximumWaveElevationBsmax =
                    Context.GetNullableDouble(NaturalStoneWaveImpactDefinitions.DistanceMaximumWaveElevationBsmax),
                NormativeWidthOfWaveImpactAwi = Context.GetNullableDouble(NaturalStoneWaveImpactDefinitions.NormativeWidthOfWaveImpactAwi),
                NormativeWidthOfWaveImpactBwi = Context.GetNullableDouble(NaturalStoneWaveImpactDefinitions.NormativeWidthOfWaveImpactBwi),
                WaveAngleImpactBetamax = Context.GetNullableDouble(NaturalStoneWaveImpactDefinitions.WaveAngleImpactBetamax)
            };

            builder.AddNaturalStoneWaveImpactLocation(constructionProperties);
        }
    }
}