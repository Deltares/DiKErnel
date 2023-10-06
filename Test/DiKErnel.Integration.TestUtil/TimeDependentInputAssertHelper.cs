// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
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

using DiKErnel.Core.Data;
using NUnit.Framework;

namespace DiKErnel.Integration.TestUtil
{
    internal static class TimeDependentInputAssertHelper
    {
        public static void AssertTimeDependentInputItem(int expectedBeginTime, int expectedEndTime,
                                                        double expectedWaterLevel, double expectedWaveHeightHm0,
                                                        double expectedWavePeriodTm10, double expectedWaveDirection,
                                                        ITimeDependentInput actualTimeDependentInput)
        {
            Assert.AreEqual(expectedBeginTime, actualTimeDependentInput.BeginTime);
            Assert.AreEqual(expectedEndTime, actualTimeDependentInput.EndTime);
            Assert.AreEqual(expectedWaterLevel, actualTimeDependentInput.WaterLevel);
            Assert.AreEqual(expectedWaveHeightHm0, actualTimeDependentInput.WaveHeightHm0);
            Assert.AreEqual(expectedWavePeriodTm10, actualTimeDependentInput.WavePeriodTm10);
            Assert.AreEqual(expectedWaveDirection, actualTimeDependentInput.WaveDirection);
        }
    }
}