// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
//
// This file is part of DiKErnel.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <https://www.gnu.org/licenses/>.
//
// All names, logos, and references to "Deltares" are registered trademarks of
// Stichting Deltares and remain full property of Stichting Deltares at all times.
// All rights reserved.

using DiKErnel.Integration.Data.GrassRevetmentWaveRunup;
using NUnit.Framework;

namespace DiKErnel.Integration.TestUtil
{
    internal static class GrassRevetmentWaveRunupLocationDependentInputAssertHelper
    {
        public static void AssertGeneralProperties(double outerSlope,
                                                   GrassRevetmentWaveRunupLocationDependentInput locationDependentInput)
        {
            Assert.AreEqual(outerSlope, locationDependentInput.OuterSlope);
        }

        public static void AssertRepresentative2P(double representative2PAru, double representative2PBru,
                                                  double representative2PCru, double gammab, double gammaf,
                                                  GrassRevetmentWaveRunupRepresentative2P representative2P)
        {
            Assert.AreEqual(representative2PAru, representative2P.Representative2PAru);
            Assert.AreEqual(representative2PBru, representative2P.Representative2PBru);
            Assert.AreEqual(representative2PCru, representative2P.Representative2PCru);
            Assert.AreEqual(gammab, representative2P.Gammab);
            Assert.AreEqual(gammaf, representative2P.Gammaf);
        }

        public static void AssertWaveAngleImpact(double abeta, double betamax,
                                                 GrassRevetmentWaveRunupWaveAngleImpact waveAngleImpact)
        {
            Assert.AreEqual(abeta, waveAngleImpact.Abeta);
            Assert.AreEqual(betamax, waveAngleImpact.Betamax);
        }

        public static void AssertCumulativeOverload(double criticalCumulativeOverload,
                                                    GrassRevetmentWaveRunupLocationDependentInput locationDependentInput)
        {
            Assert.AreEqual(criticalCumulativeOverload, locationDependentInput.CriticalCumulativeOverload);
        }

        public static void AssertFrontVelocity(double criticalFrontVelocity,
                                               GrassRevetmentWaveRunupLocationDependentInput locationDependentInput)
        {
            Assert.AreEqual(criticalFrontVelocity, locationDependentInput.CriticalFrontVelocity);
        }

        public static void AssertTransitionAlpha(double increasedLoadTransitionAlphaM,
                                                 double reducedStrengthTransitionAlphaS,
                                                 GrassRevetmentWaveRunupLocationDependentInput locationDependentInput)
        {
            Assert.AreEqual(increasedLoadTransitionAlphaM, locationDependentInput.IncreasedLoadTransitionAlphaM);
            Assert.AreEqual(reducedStrengthTransitionAlphaS, locationDependentInput.ReducedStrengthTransitionAlphaS);
        }

        public static void AssertAverageNumberOfWaves(double averageNumberOfWavesCtm,
                                                      GrassRevetmentWaveRunupLocationDependentInput locationDependentInput)
        {
            Assert.AreEqual(averageNumberOfWavesCtm, locationDependentInput.AverageNumberOfWavesCtm);
        }
    }
}