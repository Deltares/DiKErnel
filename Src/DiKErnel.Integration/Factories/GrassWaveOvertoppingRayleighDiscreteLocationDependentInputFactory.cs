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

using DiKErnel.DomainLibrary.Defaults;
using DiKErnel.DomainLibrary.Defaults.Grass;
using DiKErnel.DomainLibrary.Defaults.GrassWaveOvertopping;
using DiKErnel.Integration.Data.GrassWaveOvertopping;

namespace DiKErnel.Integration.Factories
{
    internal static class GrassWaveOvertoppingRayleighDiscreteLocationDependentInputFactory
    {
        public static GrassWaveOvertoppingRayleighDiscreteLocationDependentInput CreateLocationDependentInput(
            GrassWaveOvertoppingRayleighDiscreteLocationConstructionProperties constructionProperties)
        {
            IGrassCumulativeOverloadTopLayerDefaults topLayerDefaults =
                GrassCumulativeOverloadDefaultsFactory.CreateTopLayerDefaults(constructionProperties.TopLayerType);

            var accelerationAlphaA = new GrassWaveOvertoppingRayleighAccelerationAlphaA(
                constructionProperties.AccelerationAlphaAForCrest
                ?? GrassWaveOvertoppingRayleighDefaults.AccelerationAlphaAForCrest,
                constructionProperties.AccelerationAlphaAForInnerSlope
                ?? GrassWaveOvertoppingRayleighDefaults.AccelerationAlphaAForInnerSlope);

            return new GrassWaveOvertoppingRayleighDiscreteLocationDependentInput(
                constructionProperties.X,
                constructionProperties.InitialDamage ?? RevetmentDefaults.InitialDamage,
                constructionProperties.FailureNumber ?? RevetmentDefaults.FailureNumber,
                constructionProperties.CriticalCumulativeOverload ?? topLayerDefaults.CriticalCumulativeOverload,
                constructionProperties.CriticalFrontVelocity ?? topLayerDefaults.CriticalFrontVelocity,
                constructionProperties.IncreasedLoadTransitionAlphaM
                ?? GrassCumulativeOverloadDefaults.IncreasedLoadTransitionAlphaM,
                constructionProperties.ReducedStrengthTransitionAlphaS
                ?? GrassCumulativeOverloadDefaults.ReducedStrengthTransitionAlphaS,
                constructionProperties.AverageNumberOfWavesCtm
                ?? GrassCumulativeOverloadDefaults.AverageNumberOfWavesCtm,
                constructionProperties.FrontVelocityCwo
                ?? GrassWaveOvertoppingRayleighDefaults.FrontVelocityCwo,
                accelerationAlphaA,
                constructionProperties.DikeHeight,
                constructionProperties.FixedNumberOfWaves
                ?? GrassRayleighDiscreteDefaults.FixedNumberOfWaves);
        }
    }
}