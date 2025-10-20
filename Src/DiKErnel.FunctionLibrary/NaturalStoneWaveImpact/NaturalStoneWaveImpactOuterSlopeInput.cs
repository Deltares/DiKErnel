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
    /// Input for natural stone wave impact outer slope calculations.
    /// </summary>
    public class NaturalStoneWaveImpactOuterSlopeInput
    {
        /// <summary>
        /// Creates a new instance.
        /// </summary>
        /// <param name="slopeLowerPosition">The slope lower position [m].</param>
        /// <param name="slopeLowerLevel">The slope lower level [m].</param>
        /// <param name="slopeUpperPosition">The slope upper position [m].</param>
        /// <param name="slopeUpperLevel">The slope upper level [m].</param>
        /// <param name="outerToeHeight">The outer toe height [m]</param>
        /// <param name="outerCrestHeight">The outer crest height [m]</param>
        public NaturalStoneWaveImpactOuterSlopeInput(double slopeLowerPosition, double slopeLowerLevel,
                                                     double slopeUpperPosition, double slopeUpperLevel,
                                                     double outerToeHeight, double outerCrestHeight)
        {
            SlopeLowerPosition = slopeLowerPosition;
            SlopeLowerLevel = slopeLowerLevel;
            SlopeUpperPosition = slopeUpperPosition;
            SlopeUpperLevel = slopeUpperLevel;
            OuterToeHeight = outerToeHeight;
            OuterCrestHeight = outerCrestHeight;

            NotchOuterBermPosition = double.NaN;
            NotchOuterBermHeight = double.NaN;
            CrestOuterBermPosition = double.NaN;
            CrestOuterBermHeight = double.NaN;
        }

        /// <summary>
        /// Gets the slope lower position [m].
        /// </summary>
        public double SlopeLowerPosition { get; }

        /// <summary>
        /// Gets the slope lower level [m].
        /// </summary>
        public double SlopeLowerLevel { get; }

        /// <summary>
        /// Gets the slope upper position [m].
        /// </summary>
        public double SlopeUpperPosition { get; }

        /// <summary>
        /// Gets the slope upper level [m].
        /// </summary>
        public double SlopeUpperLevel { get; }

        /// <summary>
        /// Gets the outer toe height [m].
        /// </summary>
        public double OuterToeHeight { get; }

        /// <summary>
        /// Gets the outer crest height [m].
        /// </summary>
        public double OuterCrestHeight { get; }

        /// <summary>
        /// Gets or sets the notch outer berm position [m].
        /// </summary>
        public double NotchOuterBermPosition { get; set; }

        /// <summary>
        /// Gets or sets the notch outer berm height [m].
        /// </summary>
        public double NotchOuterBermHeight { get; set; }

        /// <summary>
        /// Gets or sets the crest outer berm position [m].
        /// </summary>
        public double CrestOuterBermPosition { get; set; }

        /// <summary>
        /// Gets or sets the crest outer berm height [m].
        /// </summary>
        public double CrestOuterBermHeight { get; set; }
    }
}