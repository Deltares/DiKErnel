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

using System.Collections.Generic;

namespace DiKErnel.FunctionLibrary.Grass
{
    /// <summary>
    /// Input for grass representative 2P calculations.
    /// </summary>
    public class GrassRepresentative2PInput
    {
        /// <summary>
        /// Creates a new instance.
        /// </summary>
        /// <param name="waterLevel">The water level [m].</param>
        /// <param name="waveHeightHm0">The wave height [m].</param>
        /// <param name="wavePeriodTm10">The wave period Tm10 [s].</param>
        /// <param name="waveDirection">The wave direction with respect to the
        /// North [deg].</param>
        /// <param name="xValuesProfile">The x values of the profile points [m].</param>
        /// <param name="zValuesProfile">The z values of the profile points [m].</param>
        /// <param name="roughnessCoefficients">The roughness coefficients of the profile
        /// segments [-].</param>
        /// <param name="dikeHeight">The dike height [m].</param>
        /// <param name="dikeOrientation">The dike orientation with respect to the
        /// North [deg].</param>
        public GrassRepresentative2PInput(double waterLevel, double waveHeightHm0, double wavePeriodTm10,
                                          double waveDirection, IReadOnlyList<double> xValuesProfile,
                                          IReadOnlyList<double> zValuesProfile,
                                          IReadOnlyList<double> roughnessCoefficients, double dikeHeight,
                                          double dikeOrientation)
        {
            WaterLevel = waterLevel;
            WaveHeightHm0 = waveHeightHm0;
            WavePeriodTm10 = wavePeriodTm10;
            WaveDirection = waveDirection;
            XValuesProfile = xValuesProfile;
            ZValuesProfile = zValuesProfile;
            RoughnessCoefficients = roughnessCoefficients;
            DikeHeight = dikeHeight;
            DikeOrientation = dikeOrientation;
        }

        /// <summary>
        /// Gets the water level [m].
        /// </summary>
        public double WaterLevel { get; }

        /// <summary>
        /// Gets the wave height [m].
        /// </summary>
        public double WaveHeightHm0 { get; }

        /// <summary>
        /// Gets the wave period Tm10 [s].
        /// </summary>
        public double WavePeriodTm10 { get; }

        /// <summary>
        /// Gets the wave direction with respect to the North [deg].
        /// </summary>
        public double WaveDirection { get; }

        /// <summary>
        /// Gets the x values of the profile points [m].
        /// </summary>
        public IReadOnlyList<double> XValuesProfile { get; }

        /// <summary>
        /// Gets the z values of the profile points [m].
        /// </summary>
        public IReadOnlyList<double> ZValuesProfile { get; }

        /// <summary>
        /// Gets the roughness coefficients of the profile segments [-].
        /// </summary>
        public IReadOnlyList<double> RoughnessCoefficients { get; }

        /// <summary>
        /// Gets the dike height [m].
        /// </summary>
        public double DikeHeight { get; }

        /// <summary>
        /// Gets the dike orientation with respect to the North [deg].
        /// </summary>
        public double DikeOrientation { get; }
    }
}