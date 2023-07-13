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

namespace DiKErnel.FunctionLibrary.NaturalStoneRevetment
{
    /// <summary>
    /// Input for a natural stone revetment outer slope calculation.
    /// </summary>
    public class NaturalStoneRevetmentOuterSlopeInput
    {
        /// <summary>
        /// Creates a new instance of <see cref="NaturalStoneRevetmentOuterSlopeInput"/>.
        /// </summary>
        /// <param name="slopeLowerPosition">The slope lower position. [m]</param>
        /// <param name="slopeLowerLevel">The slope lower level. [m]</param>
        /// <param name="slopeUpperPosition">The slope upper position. [m]</param>
        /// <param name="slopeUpperLevel">The slope upper level. [m]</param>
        /// <param name="outerToeHeight">The outer toe height. [m]</param>
        /// <param name="outerCrestHeight">The outer crest height. [m]</param>
        public NaturalStoneRevetmentOuterSlopeInput(double slopeLowerPosition, double slopeLowerLevel, 
                                                    double slopeUpperPosition, double slopeUpperLevel,
                                                    double outerToeHeight, double outerCrestHeight)
        {
            SlopeLowerPosition = slopeLowerPosition;
            SlopeLowerLevel = slopeLowerLevel;
            SlopeUpperPosition = slopeUpperPosition;
            SlopeUpperLevel = slopeUpperLevel;
            OuterToeHeight = outerToeHeight;
            OuterCrestHeight = outerCrestHeight;

            NotchOuterBermPosition = double.PositiveInfinity;
            NotchOuterBermHeight = double.PositiveInfinity;
            CrestOuterBermPosition = double.PositiveInfinity;
            CrestOuterBermHeight = double.PositiveInfinity;
        }

        /// <summary>
        /// Gets the slope lower position. [m]
        /// </summary>
        public double SlopeLowerPosition { get; private set; }

        /// <summary>
        /// Gets the slope lower level. [m]
        /// </summary>
        public double SlopeLowerLevel { get; private set; }

        /// <summary>
        /// Gets the slope upper position. [m]
        /// </summary>
        public double SlopeUpperPosition { get; private set; }

        /// <summary>
        /// Gets the slope upper level. [m]
        /// </summary>
        public double SlopeUpperLevel { get; private set; }

        /// <summary>
        /// Gets the outer toe height. [m]
        /// </summary>
        public double OuterToeHeight { get; private set; }

        /// <summary>
        /// Gets the outer crest height. [m]
        /// </summary>
        public double OuterCrestHeight { get; private set; }

        /// <summary>
        /// Gets or sets the notch outer berm position. [m]
        /// </summary>
        public double NotchOuterBermPosition { get; set; }

        /// <summary>
        /// Gets or sets the notch outer berm height. [m]
        /// </summary>
        public double NotchOuterBermHeight { get; set; }

        /// <summary>
        /// Gets or sets the crest outer berm position. [m]
        /// </summary>
        public double CrestOuterBermPosition { get; set; }

        /// <summary>
        /// Gets or sets the crest outer berm height. [m]
        /// </summary>
        public double CrestOuterBermHeight { get; set; }

        /// <summary>
        /// Gets an indicator whether the input has a berm.
        /// </summary>
        /// <remarks><c>false</c> when one of the berm properties is <see cref="double.PositiveInfinity"/>;
        /// <c>true</c> otherwise.</remarks>
        public bool HasBerm => double.IsInfinity(NotchOuterBermPosition)
                               && double.IsInfinity(NotchOuterBermHeight)
                               && double.IsInfinity(CrestOuterBermPosition)
                               && double.IsInfinity(CrestOuterBermHeight);
    }
}