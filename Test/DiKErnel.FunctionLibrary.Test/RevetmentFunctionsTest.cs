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

using DiKErnel.FunctionLibrary.TestUtil;
using NUnit.Framework;

namespace DiKErnel.FunctionLibrary.Test
{
    [TestFixture]
    internal sealed class RevetmentFunctionsTest
    {
        [Test]
        public void IncrementTime_ValidInput_ExpectedValue()
        {
            // Setup
            const double beginTime = 12.3;
            const double endTime = 45.6;

            // Call
            double incrementTime = RevetmentFunctions.IncrementTime(beginTime, endTime);

            // Assert
            AssertHelper.AreEqual(33.3, incrementTime);
        }

        [Test]
        public void AverageNumberOfWaves_ValidInput_ExpectedValue()
        {
            // Setup
            const double incrementTime = 900;
            const double wavePeriodTm10 = 1.2;
            const double averageNumberOfWavesCtm = 6.5;

            // Call
            double averageNumberOfWaves = RevetmentFunctions.AverageNumberOfWaves(incrementTime, wavePeriodTm10,
                                                                                  averageNumberOfWavesCtm);

            // Assert
            AssertHelper.AreEqual(115.38461538461539, averageNumberOfWaves);
        }
    }
}