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

using DiKErnel.DomainLibrary.Defaults;
using DiKErnel.DomainLibrary.Defaults.GrassRevetmentWaveImpact;
using DiKErnel.Integration.Data.GrassRevetmentWaveImpact;

namespace DiKErnel.Integration.Factories
{
    internal static class GrassRevetmentWaveImpactLocationDependentInputFactory
    {
        public static GrassRevetmentWaveImpactLocationDependentInput CreateLocationDependentInput(
            GrassRevetmentWaveImpactLocationConstructionProperties constructionProperties)
        {
            IGrassRevetmentWaveImpactTopLayerDefaults topLayerDefaults =
                GrassRevetmentWaveImpactDefaultsFactory.CreateTopLayerDefaults(constructionProperties.TopLayerType);

            var waveAngleImpact = new GrassRevetmentWaveImpactWaveAngleImpact(
                constructionProperties.WaveAngleImpactNwa ?? GrassRevetmentWaveImpactDefaults.WaveAngleImpactNwa,
                constructionProperties.WaveAngleImpactQwa ?? GrassRevetmentWaveImpactDefaults.WaveAngleImpactQwa,
                constructionProperties.WaveAngleImpactRwa ?? GrassRevetmentWaveImpactDefaults.WaveAngleImpactRwa);

            var timeLine = new GrassRevetmentWaveImpactTimeLine(
                constructionProperties.TimeLineAgwi ?? topLayerDefaults.TimeLineAgwi,
                constructionProperties.TimeLineBgwi ?? topLayerDefaults.TimeLineBgwi,
                constructionProperties.TimeLineCgwi ?? topLayerDefaults.TimeLineCgwi);

            return new GrassRevetmentWaveImpactLocationDependentInput(
                constructionProperties.X,
                constructionProperties.InitialDamage ?? RevetmentDefaults.InitialDamage,
                constructionProperties.FailureNumber ?? RevetmentDefaults.FailureNumber,
                waveAngleImpact,
                constructionProperties.MinimumWaveHeightTemax ?? GrassRevetmentWaveImpactDefaults.MinimumWaveHeightTemax,
                constructionProperties.MaximumWaveHeightTemin ?? GrassRevetmentWaveImpactDefaults.MaximumWaveHeightTemin,
                timeLine,
                constructionProperties.UpperLimitLoadingAul ?? GrassRevetmentWaveImpactDefaults.UpperLimitLoadingAul,
                constructionProperties.LowerLimitLoadingAll ?? GrassRevetmentWaveImpactDefaults.LowerLimitLoadingAll);
        }
    }
}