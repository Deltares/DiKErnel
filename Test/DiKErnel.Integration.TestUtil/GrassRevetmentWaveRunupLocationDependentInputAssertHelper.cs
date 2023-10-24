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

using DiKErnel.Integration.Data.GrassRevetmentWaveRunup;
using NUnit.Framework;

namespace DiKErnel.Integration.TestUtil
{
    internal static class GrassRevetmentWaveRunupLocationDependentInputAssertHelper
    {
        public static void AssertGeneralProperties(double outerSlope,
                                                   GrassRevetmentWaveRunupLocationDependentInput locationDependentInput)
        {
            Assert.That(locationDependentInput.OuterSlope, Is.EqualTo(outerSlope));
        }

        public static void AssertRepresentative2P(double representative2PAru, double representative2PBru,
                                                  double representative2PCru, double gammab, double gammaf,
                                                  GrassRevetmentWaveRunupRepresentative2P representative2P)
        {
            Assert.That(representative2P.Representative2PAru, Is.EqualTo(representative2PAru));
            Assert.That(representative2P.Representative2PBru, Is.EqualTo(representative2PBru));
            Assert.That(representative2P.Representative2PCru, Is.EqualTo(representative2PCru));
            Assert.That(representative2P.Gammab, Is.EqualTo(gammab));
            Assert.That(representative2P.Gammaf, Is.EqualTo(gammaf));
        }

        public static void AssertWaveAngleImpact(double abeta, double betamax,
                                                 GrassRevetmentWaveRunupWaveAngleImpact waveAngleImpact)
        {
            Assert.That(waveAngleImpact.Abeta, Is.EqualTo(abeta));
            Assert.That(waveAngleImpact.Betamax, Is.EqualTo(betamax));
        }

        public static void AssertCumulativeOverload(double criticalCumulativeOverload,
                                                    GrassRevetmentWaveRunupLocationDependentInput locationDependentInput)
        {
            Assert.That(locationDependentInput.CriticalCumulativeOverload, Is.EqualTo(criticalCumulativeOverload));
        }

        public static void AssertFrontVelocity(double criticalFrontVelocity,
                                               GrassRevetmentWaveRunupLocationDependentInput locationDependentInput)
        {
            Assert.That(locationDependentInput.CriticalFrontVelocity, Is.EqualTo(criticalFrontVelocity));
        }

        public static void AssertTransitionAlpha(double increasedLoadTransitionAlphaM,
                                                 double reducedStrengthTransitionAlphaS,
                                                 GrassRevetmentWaveRunupLocationDependentInput locationDependentInput)
        {
            Assert.That(locationDependentInput.IncreasedLoadTransitionAlphaM, Is.EqualTo(increasedLoadTransitionAlphaM));
            Assert.That(locationDependentInput.ReducedStrengthTransitionAlphaS, Is.EqualTo(reducedStrengthTransitionAlphaS));
        }

        public static void AssertAverageNumberOfWaves(double averageNumberOfWavesCtm,
                                                      GrassRevetmentWaveRunupLocationDependentInput locationDependentInput)
        {
            Assert.That(locationDependentInput.AverageNumberOfWavesCtm, Is.EqualTo(averageNumberOfWavesCtm));
        }
    }
}