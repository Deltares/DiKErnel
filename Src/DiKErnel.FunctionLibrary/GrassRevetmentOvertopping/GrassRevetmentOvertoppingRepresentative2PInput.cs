// // Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
// //
// // This file is part of DiKErnel.
// //
// // DiKErnel is free software: you can redistribute it and/or modify it under the terms of the
// // GNU Lesser General Public License as published by the Free Software Foundation, either
// // version 3 of the License, or (at your option) any later version.
// //
// // This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// // without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// // See the GNU Lesser General Public License for more details.
// //
// // You should have received a copy of the GNU Lesser General Public License along with this
// // program. If not, see <http://www.gnu.org/licenses/>.
// //
// // All names, logos, and references to "Deltares" are registered trademarks of Stichting
// // Deltares and remain full property of Stichting Deltares at all times. All rights reserved.

using System.Collections.Generic;

namespace DiKErnel.FunctionLibrary.GrassRevetmentOvertopping
{
    /// <summary>
    /// Input for a grass revetment overtopping representative 2P calculation.
    /// </summary>
    public class GrassRevetmentOvertoppingRepresentative2PInput
    {
        /// <summary>
        /// Creates a new instance of
        /// <see cref="GrassRevetmentOvertoppingRepresentative2PInput"/>.
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
        public GrassRevetmentOvertoppingRepresentative2PInput(double waterLevel, double waveHeightHm0, double wavePeriodTm10, 
                                                              double waveDirection, IEnumerable<double> xValuesProfile, 
                                                              IEnumerable<double> zValuesProfile, 
                                                              IEnumerable<double> roughnessCoefficients, double dikeHeight)
        {
            WaterLevel = waterLevel;
            WaveHeightHm0 = waveHeightHm0;
            WavePeriodTm10 = wavePeriodTm10;
            WaveDirection = waveDirection;
            XValuesProfile = xValuesProfile;
            ZValuesProfile = zValuesProfile;
            RoughnessCoefficients = roughnessCoefficients;
            DikeHeight = dikeHeight;
        }

        /// <summary>
        /// Gets the water level [m].
        /// </summary>
        public double WaterLevel { get; private set; }

        /// <summary>
        /// Gets the wave height [m].
        /// </summary>
        public double WaveHeightHm0 { get; private set; }

        /// <summary>
        /// Gets the wave period Tm10 [s].
        /// </summary>
        public double WavePeriodTm10 { get; private set; }

        /// <summary>
        /// Gets the wave direction with respect to the North [deg].
        /// </summary>
        public double WaveDirection { get; private set; }

        /// <summary>
        /// Gets the x values of the profile points [m].
        /// </summary>
        public IEnumerable<double> XValuesProfile { get; private set; }

        /// <summary>
        /// Gets the z values of the profile points [m].
        /// </summary>
        public IEnumerable<double> ZValuesProfile { get; private set; }

        /// <summary>
        /// Gets the roughness coefficients of the profile segments [-].
        /// </summary>
        public IEnumerable<double> RoughnessCoefficients { get; private set; }

        /// <summary>
        /// Gets the dike height [m].
        /// </summary>
        public double DikeHeight { get; private set; }
    }
}