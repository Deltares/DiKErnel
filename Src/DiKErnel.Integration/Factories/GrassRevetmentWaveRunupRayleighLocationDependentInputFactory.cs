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
using DiKErnel.DomainLibrary.Defaults.GrassRevetment;
using DiKErnel.DomainLibrary.Defaults.GrassRevetmentWaveRunup;
using DiKErnel.Integration.Data.GrassRevetmentWaveRunup;

namespace DiKErnel.Integration.Factories
{
    internal static class GrassRevetmentWaveRunupRayleighLocationDependentInputFactory
    {
        public static GrassRevetmentWaveRunupRayleighLocationDependentInput CreateLocationDependentInput(
            GrassRevetmentWaveRunupRayleighLocationConstructionProperties constructionProperties)
        {
            IGrassRevetmentCumulativeOverloadTopLayerDefaults topLayerDefaults =
                GrassRevetmentCumulativeOverloadDefaultsFactory.CreateTopLayerDefaults(
                    constructionProperties.TopLayerType);

            var representative2P = new GrassRevetmentWaveRunupRepresentative2P(
                constructionProperties.RepresentativeWaveRunup2PAru
                ?? GrassRevetmentWaveRunupDefaults.RepresentativeWaveRunup2PAru,
                constructionProperties.RepresentativeWaveRunup2PBru
                ?? GrassRevetmentWaveRunupDefaults.RepresentativeWaveRunup2PBru,
                constructionProperties.RepresentativeWaveRunup2PCru
                ?? GrassRevetmentWaveRunupDefaults.RepresentativeWaveRunup2PCru,
                constructionProperties.RepresentativeWaveRunup2PGammab
                ?? GrassRevetmentWaveRunupDefaults.RepresentativeWaveRunup2PGammab,
                constructionProperties.RepresentativeWaveRunup2PGammaf
                ?? GrassRevetmentWaveRunupDefaults.RepresentativeWaveRunup2PGammaf);

            var waveAngleImpact = new GrassRevetmentWaveRunupWaveAngleImpact(
                constructionProperties.WaveAngleImpactAbeta
                ?? GrassRevetmentWaveRunupDefaults.WaveAngleImpactAbeta,
                constructionProperties.WaveAngleImpactBetamax
                ?? GrassRevetmentWaveRunupDefaults.WaveAngleImpactBetamax);

            return new GrassRevetmentWaveRunupRayleighLocationDependentInput(
                constructionProperties.X,
                constructionProperties.InitialDamage ?? RevetmentDefaults.InitialDamage,
                constructionProperties.FailureNumber ?? RevetmentDefaults.FailureNumber,
                constructionProperties.OuterSlope,
                constructionProperties.CriticalCumulativeOverload ?? topLayerDefaults.CriticalCumulativeOverload,
                constructionProperties.CriticalFrontVelocity ?? topLayerDefaults.CriticalFrontVelocity,
                constructionProperties.IncreasedLoadTransitionAlphaM ??
                GrassRevetmentCumulativeOverloadDefaults.IncreasedLoadTransitionAlphaM,
                constructionProperties.ReducedStrengthTransitionAlphaS ??
                GrassRevetmentCumulativeOverloadDefaults.ReducedStrengthTransitionAlphaS,
                constructionProperties.AverageNumberOfWavesCtm
                ?? GrassRevetmentCumulativeOverloadDefaults.AverageNumberOfWavesCtm,
                representative2P,
                waveAngleImpact,
                constructionProperties.FixedNumberOfWaves ?? GrassRevetmentCumulativeOverloadDefaults.FixedNumberOfWaves,
                constructionProperties.FrontVelocityCu ?? GrassRevetmentWaveRunupRayleighDefaults.FrontVelocityCu);
        }
    }
}