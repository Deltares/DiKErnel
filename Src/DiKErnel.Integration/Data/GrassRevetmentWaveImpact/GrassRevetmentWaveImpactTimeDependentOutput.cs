﻿// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
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

using DiKErnel.Core.Data;
using DiKErnel.Core.Exceptions;

namespace DiKErnel.Integration.Data.GrassRevetmentWaveImpact
{
    /// <summary>
    /// Time dependent output of a grass revetment wave impact location.
    /// </summary>
    public class GrassRevetmentWaveImpactTimeDependentOutput : TimeDependentOutput
    {
        /// <inheritdoc/>
        public GrassRevetmentWaveImpactTimeDependentOutput(
            GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties constructionProperties)
            : base(constructionProperties)
        {
            LoadingRevetment = constructionProperties.LoadingRevetment
                               ?? throw new InvalidTimeDependentOutputException(
                                   nameof(constructionProperties.LoadingRevetment));
            UpperLimitLoading = constructionProperties.UpperLimitLoading
                                ?? throw new InvalidTimeDependentOutputException(
                                    nameof(constructionProperties.UpperLimitLoading));
            LowerLimitLoading = constructionProperties.LowerLimitLoading
                                ?? throw new InvalidTimeDependentOutputException(
                                    nameof(constructionProperties.LowerLimitLoading));
            MinimumWaveHeight = constructionProperties.MinimumWaveHeight;
            MaximumWaveHeight = constructionProperties.MaximumWaveHeight;
            WaveAngleImpact = constructionProperties.WaveAngleImpact;
            WaveHeightImpact = constructionProperties.WaveHeightImpact;
        }

        /// <summary>
        /// Gets the loading revetment.
        /// </summary>
        public bool LoadingRevetment { get; }

        /// <summary>
        /// Gets the upper limit loading.
        /// </summary>
        public double UpperLimitLoading { get; }

        /// <summary>
        /// Gets the lower limit loading.
        /// </summary>
        public double LowerLimitLoading { get; }

        /// <summary>
        /// Gets the minimum wave height.
        /// </summary>
        public double? MinimumWaveHeight { get; }

        /// <summary>
        /// Gets the maximum wave height.
        /// </summary>
        public double? MaximumWaveHeight { get; }

        /// <summary>
        /// Gets the wave angle impact.
        /// </summary>
        public double? WaveAngleImpact { get; }

        /// <summary>
        /// Gets the wave height impact.
        /// </summary>
        public double? WaveHeightImpact { get; }
    }
}