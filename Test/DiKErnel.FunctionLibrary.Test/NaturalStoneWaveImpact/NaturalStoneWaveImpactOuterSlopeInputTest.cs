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

using DiKErnel.FunctionLibrary.NaturalStoneWaveImpact;
using DiKErnel.TestUtil;
using NUnit.Framework;

namespace DiKErnel.FunctionLibrary.Test.NaturalStoneWaveImpact
{
    [TestFixture]
    internal sealed class NaturalStoneWaveImpactOuterSlopeInputTest
    {
        [Test]
        public void Constructor_ExpectedValues()
        {
            // Setup
            double slopeLowerPosition = Random.NextDouble();
            double slopeLowerLevel = Random.NextDouble();
            double slopeUpperPosition = Random.NextDouble();
            double slopeUpperLevel = Random.NextDouble();
            double outerToeHeight = Random.NextDouble();
            double outerCrestHeight = Random.NextDouble();

            // Call
            var input = new NaturalStoneWaveImpactOuterSlopeInput(slopeLowerPosition, slopeLowerLevel,
                                                                  slopeUpperPosition, slopeUpperLevel, outerToeHeight,
                                                                  outerCrestHeight);

            // Assert
            Assert.That(input.SlopeLowerPosition, Is.EqualTo(slopeLowerPosition));
            Assert.That(input.SlopeLowerLevel, Is.EqualTo(slopeLowerLevel));
            Assert.That(input.SlopeUpperPosition, Is.EqualTo(slopeUpperPosition));
            Assert.That(input.SlopeUpperLevel, Is.EqualTo(slopeUpperLevel));
            Assert.That(input.OuterToeHeight, Is.EqualTo(outerToeHeight));
            Assert.That(input.OuterCrestHeight, Is.EqualTo(outerCrestHeight));
            Assert.That(input.NotchOuterBermPosition, Is.NaN);
            Assert.That(input.NotchOuterBermHeight, Is.NaN);
            Assert.That(input.CrestOuterBermPosition, Is.NaN);
            Assert.That(input.CrestOuterBermHeight, Is.NaN);
        }
    }
}