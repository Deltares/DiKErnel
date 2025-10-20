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

namespace DiKErnel.FunctionLibrary.NaturalStoneWaveImpact
{
    /// <summary>
    /// Input for natural stone wave impact limit loading calculations.
    /// </summary>
    public class NaturalStoneWaveImpactLimitLoadingInput
    {
        /// <summary>
        /// Creates a new instance.
        /// </summary>
        /// <param name="depthMaximumWaveLoad">The depth of the maximum wave
        /// load [m].</param>
        /// <param name="surfSimilarityParameter">The surf similarity parameter [-].</param>
        /// <param name="waterLevel">The water level [m].</param>
        /// <param name="waveHeightHm0">The wave height [m].</param>
        /// <param name="a">The a coefficient [-].</param>
        /// <param name="b">The b coefficient [-].</param>
        /// <param name="c">The c coefficient [-].</param>
        public NaturalStoneWaveImpactLimitLoadingInput(double depthMaximumWaveLoad, double surfSimilarityParameter,
                                                       double waterLevel, double waveHeightHm0, double a, double b,
                                                       double c)
        {
            DepthMaximumWaveLoad = depthMaximumWaveLoad;
            SurfSimilarityParameter = surfSimilarityParameter;
            WaterLevel = waterLevel;
            WaveHeightHm0 = waveHeightHm0;
            A = a;
            B = b;
            C = c;
        }

        /// <summary>
        /// Gets the depth of the maximum wave load [m].
        /// </summary>
        public double DepthMaximumWaveLoad { get; }

        /// <summary>
        /// Gets the surf similarity parameter [-].
        /// </summary>
        public double SurfSimilarityParameter { get; }

        /// <summary>
        /// Gets the water level [m].
        /// </summary>
        public double WaterLevel { get; }

        /// <summary>
        /// Gets the wave height [m].
        /// </summary>
        public double WaveHeightHm0 { get; }

        /// <summary>
        /// Gets the a coefficient [-].
        /// </summary>
        public double A { get; }

        /// <summary>
        /// Gets the b coefficient [-].
        /// </summary>
        public double B { get; }

        /// <summary>
        /// Gets the c coefficient [-].
        /// </summary>
        public double C { get; }
    }
}