﻿// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
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

namespace DiKErnel.FunctionLibrary.GrassRevetmentWaveRunup
{
    /// <summary>
    /// Input for a grass revetment wave run-up representative 2P calculation.
    /// </summary>
    public class GrassRevetmentWaveRunupRepresentative2PInput
    {
        /// <summary>
        /// Creates a new instance.
        /// </summary>
        /// <param name="waveAngle">The wave angle [deg].</param>
        /// <param name="waveAngleImpact">The wave impact with respect to the wave
        /// angle [-].</param>
        /// <param name="waveHeightHm0">The wave height [m].</param>
        /// <param name="wavePeriodTm10">The wave period [s].</param>
        /// <param name="representativeWaveRunup2PGammab">The Gammab value [-].</param>
        /// <param name="representativeWaveRunup2PGammaf">The Gammaf value [-].</param>
        /// <param name="representativeWaveRunup2PAru">The Aru coefficient [-].</param>
        /// <param name="representativeWaveRunup2PBru">The Bru coefficient [-].</param>
        /// <param name="representativeWaveRunup2PCru">The Cru coefficient [-].</param>
        /// <param name="outerSlope">The outer slope [-].</param>
        /// <param name="gravitationalAcceleration">The gravitational
        /// acceleration [m/s^2].</param>
        public GrassRevetmentWaveRunupRepresentative2PInput(double waveAngle, double waveAngleImpact,
                                                            double waveHeightHm0, double wavePeriodTm10,
                                                            double representativeWaveRunup2PGammab,
                                                            double representativeWaveRunup2PGammaf,
                                                            double representativeWaveRunup2PAru,
                                                            double representativeWaveRunup2PBru,
                                                            double representativeWaveRunup2PCru, 
                                                            double outerSlope, double gravitationalAcceleration)
        {
            WaveAngle = waveAngle;
            WaveAngleImpact = waveAngleImpact;
            WaveHeightHm0 = waveHeightHm0;
            WavePeriodTm10 = wavePeriodTm10;
            RepresentativeWaveRunup2PGammab = representativeWaveRunup2PGammab;
            RepresentativeWaveRunup2PGammaf = representativeWaveRunup2PGammaf;
            RepresentativeWaveRunup2PAru = representativeWaveRunup2PAru;
            RepresentativeWaveRunup2PBru = representativeWaveRunup2PBru;
            RepresentativeWaveRunup2PCru = representativeWaveRunup2PCru;
            OuterSlope = outerSlope;
            GravitationalAcceleration = gravitationalAcceleration;
        }

        /// <summary>
        /// Gets the wave angle [deg].
        /// </summary>
        public double WaveAngle { get; }

        /// <summary>
        /// Gets the wave impact with respect to the wave angle [-].
        /// </summary>
        public double WaveAngleImpact { get; }

        /// <summary>
        /// Gets the wave height [m].
        /// </summary>
        public double WaveHeightHm0 { get; }

        /// <summary>
        /// Gets the wave period [s].
        /// </summary>
        public double WavePeriodTm10 { get; private set; }

        /// <summary>
        /// Gets the Gammab value [-].
        /// </summary>
        public double RepresentativeWaveRunup2PGammab { get; }

        /// <summary>
        /// Gets the Gammaf value [-].
        /// </summary>
        public double RepresentativeWaveRunup2PGammaf { get; }

        /// <summary>
        /// Gets the Aru coefficient [-].
        /// </summary>
        public double RepresentativeWaveRunup2PAru { get; }

        /// <summary>
        /// Gets the Bru coefficient [-].
        /// </summary>
        public double RepresentativeWaveRunup2PBru { get; }

        /// <summary>
        /// Gets the Cru coefficient [-].
        /// </summary>
        public double RepresentativeWaveRunup2PCru { get; }

        /// <summary>
        /// Gets the outer slope [-].
        /// </summary>
        public double OuterSlope { get; }

        /// <summary>
        /// Gets the gravitational acceleration [m/s^2].
        /// </summary>
        public double GravitationalAcceleration { get; }
    }
}