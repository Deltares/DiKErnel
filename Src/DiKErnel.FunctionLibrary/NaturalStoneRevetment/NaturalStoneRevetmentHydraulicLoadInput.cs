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

namespace DiKErnel.FunctionLibrary.NaturalStoneRevetment
{
    /// <summary>
    /// Input for a natural stone revetment hydraulic load calculation.
    /// </summary>
    public class NaturalStoneRevetmentHydraulicLoadInput
    {
        /// <summary>
        /// Creates a new instance of <see cref="NaturalStoneRevetmentHydraulicLoadInput"/>.
        /// </summary>
        /// <param name="surfSimilarityParameter">The surf similarity parameter [-].</param>
        /// <param name="waveHeightHm0">The wave height [m].</param>
        /// <param name="a">The a coefficient [-].</param>
        /// <param name="b">The b coefficient [-].</param>
        /// <param name="c">The c coefficient [-].</param>
        /// <param name="n">The n coefficient [-].</param>
        public NaturalStoneRevetmentHydraulicLoadInput(double surfSimilarityParameter, double waveHeightHm0, double a, double b,
                                                       double c, double n)
        {
            SurfSimilarityParameter = surfSimilarityParameter;
            WaveHeightHm0 = waveHeightHm0;
            A = a;
            B = b;
            C = c;
            N = n;
        }

        /// <summary>
        /// Gets the surf similarity parameter [-].
        /// </summary>
        public double SurfSimilarityParameter { get; private set; }

        /// <summary>
        /// Gets the wave height [m].
        /// </summary>
        public double WaveHeightHm0 { get; private set; }

        /// <summary>
        /// Gets the a coefficient [-].
        /// </summary>
        public double A { get; private set; }

        /// <summary>
        /// Gets the b coefficient [-].
        /// </summary>
        public double B { get; private set; }

        /// <summary>
        /// Gets the c coefficient [-].
        /// </summary>
        public double C { get; private set; }

        /// <summary>
        /// Gets the n coefficient [-].
        /// </summary>
        public double N { get; private set; }
    }
}