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

namespace DiKErnel.FunctionLibrary.GrassRevetmentOvertopping
{
    /// <summary>
    /// Input for a grass revetment overtopping cumulative overload calculation.
    /// </summary>
    public class GrassRevetmentOvertoppingCumulativeOverloadInput : GrassRevetment.GrassRevetmentCumulativeOverloadInput
    {
        /// <summary>
        /// Creates a new instance of <see cref="GrassRevetmentOvertoppingCumulativeOverloadInput"/>
        /// </summary>
        /// <param name="accelerationAlphaA">The AlphaA coefficient [-].</param>
        /// <param name="frontVelocityCwo">The Cwo coefficient [-].</param>
        /// <inheritdoc/>
        public GrassRevetmentOvertoppingCumulativeOverloadInput(double averageNumberOfWaves, double representativeWaveRunup2P,
                                                                int fixedNumberOfWaves, double verticalDistanceWaterLevelElevation,
                                                                double criticalFrontVelocity, double increasedLoadTransitionAlphaM,
                                                                double reducedStrengthTransitionAlphaS, 
                                                                double gravitationalAcceleration, double accelerationAlphaA,
                                                                double frontVelocityCwo)
            : base(averageNumberOfWaves, representativeWaveRunup2P, fixedNumberOfWaves, verticalDistanceWaterLevelElevation,
                   criticalFrontVelocity, increasedLoadTransitionAlphaM, reducedStrengthTransitionAlphaS,
                   gravitationalAcceleration)
        {
            AccelerationAlphaA = accelerationAlphaA;
            FrontVelocityCwo = frontVelocityCwo;
        }

        /// <summary>
        /// Gets the AlphaA coefficient [-].
        /// </summary>
        public double AccelerationAlphaA { get; private set; }

        /// <summary>
        /// Gets the Cwo coefficient [-].
        /// </summary>
        public double FrontVelocityCwo { get; private set; }
    }
}