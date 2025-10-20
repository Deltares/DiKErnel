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

using DiKErnel.Core.Data;
using DiKErnel.Core.Exceptions;

namespace DiKErnel.Integration.Data.NaturalStoneWaveImpact
{
    /// <summary>
    /// Time dependent output of a natural stone wave impact calculation.
    /// </summary>
    public class NaturalStoneWaveImpactTimeDependentOutput : TimeDependentOutput
    {
        /// <inheritdoc/>
        public NaturalStoneWaveImpactTimeDependentOutput(
            NaturalStoneWaveImpactTimeDependentOutputConstructionProperties constructionProperties)
            : base(constructionProperties)
        {
            OuterSlope = constructionProperties.OuterSlope
                         ?? throw new InvalidTimeDependentOutputException(
                             nameof(constructionProperties.OuterSlope));
            SlopeUpperLevel = constructionProperties.SlopeUpperLevel
                              ?? throw new InvalidTimeDependentOutputException(
                                  nameof(constructionProperties.SlopeUpperLevel));
            SlopeUpperPosition = constructionProperties.SlopeUpperPosition
                                 ?? throw new InvalidTimeDependentOutputException(
                                     nameof(constructionProperties.SlopeUpperPosition));
            SlopeLowerLevel = constructionProperties.SlopeLowerLevel
                              ?? throw new InvalidTimeDependentOutputException(
                                  nameof(constructionProperties.SlopeLowerLevel));
            SlopeLowerPosition = constructionProperties.SlopeLowerPosition
                                 ?? throw new InvalidTimeDependentOutputException(
                                     nameof(constructionProperties.SlopeLowerPosition));
            LoadingRevetment = constructionProperties.LoadingRevetment
                               ?? throw new InvalidTimeDependentOutputException(
                                   nameof(constructionProperties.LoadingRevetment));
            SurfSimilarityParameter = constructionProperties.SurfSimilarityParameter
                                      ?? throw new InvalidTimeDependentOutputException(
                                          nameof(constructionProperties.SurfSimilarityParameter));
            WaveSteepnessDeepWater = constructionProperties.WaveSteepnessDeepWater
                                     ?? throw new InvalidTimeDependentOutputException(
                                         nameof(constructionProperties.WaveSteepnessDeepWater));
            UpperLimitLoading = constructionProperties.UpperLimitLoading
                                ?? throw new InvalidTimeDependentOutputException(
                                    nameof(constructionProperties.UpperLimitLoading));
            LowerLimitLoading = constructionProperties.LowerLimitLoading
                                ?? throw new InvalidTimeDependentOutputException(
                                    nameof(constructionProperties.LowerLimitLoading));
            DepthMaximumWaveLoad = constructionProperties.DepthMaximumWaveLoad
                                   ?? throw new InvalidTimeDependentOutputException(
                                       nameof(constructionProperties.DepthMaximumWaveLoad));
            DistanceMaximumWaveElevation = constructionProperties.DistanceMaximumWaveElevation
                                           ?? throw new InvalidTimeDependentOutputException(
                                               nameof(constructionProperties.DistanceMaximumWaveElevation));
            NormativeWidthOfWaveImpact = constructionProperties.NormativeWidthOfWaveImpact
                                         ?? throw new InvalidTimeDependentOutputException(
                                             nameof(constructionProperties.NormativeWidthOfWaveImpact));
            HydraulicLoad = constructionProperties.HydraulicLoad;
            WaveAngle = constructionProperties.WaveAngle;
            WaveAngleImpact = constructionProperties.WaveAngleImpact;
            ReferenceTimeDegradation = constructionProperties.ReferenceTimeDegradation;
            ReferenceDegradation = constructionProperties.ReferenceDegradation;
        }

        /// <summary>
        /// Gets the outer slope.
        /// </summary>
        public double OuterSlope { get; }

        /// <summary>
        /// Gets the slope upper level.
        /// </summary>
        public double SlopeUpperLevel { get; }

        /// <summary>
        /// Gets the slope upper position.
        /// </summary>
        public double SlopeUpperPosition { get; }

        /// <summary>
        /// Gets the slope lower level.
        /// </summary>
        public double SlopeLowerLevel { get; }

        /// <summary>
        /// Gets the slope lower position.
        /// </summary>
        public double SlopeLowerPosition { get; }

        /// <summary>
        /// Gets the loading revetment.
        /// </summary>
        public bool LoadingRevetment { get; }

        /// <summary>
        /// Gets the surf similarity parameter.
        /// </summary>
        public double SurfSimilarityParameter { get; }

        /// <summary>
        /// Gets the wave steepness deep water.
        /// </summary>
        public double WaveSteepnessDeepWater { get; }

        /// <summary>
        /// Gets the upper limit loading.
        /// </summary>
        public double UpperLimitLoading { get; }

        /// <summary>
        /// Gets the lower limit loading.
        /// </summary>
        public double LowerLimitLoading { get; }

        /// <summary>
        /// Gets the depth maximum wave load.
        /// </summary>
        public double DepthMaximumWaveLoad { get; }

        /// <summary>
        /// Gets the distance maximum wave elevation.
        /// </summary>
        public double DistanceMaximumWaveElevation { get; }

        /// <summary>
        /// Gets the normative width of wave impact.
        /// </summary>
        public double NormativeWidthOfWaveImpact { get; }

        /// <summary>
        /// Gets the hydraulic load.
        /// </summary>
        public double? HydraulicLoad { get; }

        /// <summary>
        /// Gets the wave angle.
        /// </summary>
        public double? WaveAngle { get; }

        /// <summary>
        /// Gets the wave angle impact.
        /// </summary>
        public double? WaveAngleImpact { get; }

        /// <summary>
        /// Gets the reference time degradation.
        /// </summary>
        public double? ReferenceTimeDegradation { get; }

        /// <summary>
        /// Gets the reference degradation.
        /// </summary>
        public double? ReferenceDegradation { get; }
    }
}