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

using DiKErnel.FunctionLibrary.GrassRevetmentWaveRunup;
using DiKErnel.FunctionLibrary.TestUtil;
using NUnit.Framework;

namespace DiKErnel.FunctionLibrary.Test.GrassRevetmentWaveRunup
{
    [TestFixture]
    public class GrassRevetmentWaveRunupFunctionsTest
    {
        [Test]
        public void WaveAngleImpact_ValidInput_ExpectedValue()
        {
            // Setup
            const double waveAngle = 45;
            const double waveAngleImpactAbeta = 0.0022;
            const double waveAngleImpactBetamax = 80;

            // Call
            double waveAngleImpact = GrassRevetmentWaveRunupFunctions.WaveAngleImpact(waveAngle, waveAngleImpactAbeta,
                                                                                      waveAngleImpactBetamax);

            // Assert
            AssertHelper.AreEqual(0.901, waveAngleImpact);
        }
    }
}