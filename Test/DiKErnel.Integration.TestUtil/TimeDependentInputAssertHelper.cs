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

using DiKErnel.Core.Data;
using NUnit.Framework;

namespace DiKErnel.Integration.TestUtil
{
    internal static class TimeDependentInputAssertHelper
    {
        public static void AssertTimeDependentInputItem(double beginTime, double endTime, double waterLevel,
                                                        double waveHeightHm0, double wavePeriodTm10,
                                                        double waveDirection, ITimeDependentInput timeDependentInput)
        {
            Assert.That(timeDependentInput.BeginTime, Is.EqualTo(beginTime));
            Assert.That(timeDependentInput.EndTime, Is.EqualTo(endTime));
            Assert.That(timeDependentInput.WaterLevel, Is.EqualTo(waterLevel));
            Assert.That(timeDependentInput.WaveHeightHm0, Is.EqualTo(waveHeightHm0));
            Assert.That(timeDependentInput.WavePeriodTm10, Is.EqualTo(wavePeriodTm10));
            Assert.That(timeDependentInput.WaveDirection, Is.EqualTo(waveDirection));
        }
    }
}