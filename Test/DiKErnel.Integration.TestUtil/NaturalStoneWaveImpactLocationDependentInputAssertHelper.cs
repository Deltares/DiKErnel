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

using DiKErnel.Integration.Data.NaturalStoneWaveImpact;
using NUnit.Framework;

namespace DiKErnel.Integration.TestUtil
{
    internal static class NaturalStoneWaveImpactLocationDependentInputAssertHelper
    {
        public static void AssertGeneralProperties(double relativeDensity, double thicknessTopLayer,
                                                   NaturalStoneWaveImpactLocationDependentInput locationDependentInput)
        {
            Assert.That(locationDependentInput.RelativeDensity, Is.EqualTo(relativeDensity));
            Assert.That(locationDependentInput.ThicknessTopLayer, Is.EqualTo(thicknessTopLayer));
        }

        public static void AssertHydraulicLoads(double hydraulicLoadAp, double hydraulicLoadBp, double hydraulicLoadCp,
                                                double hydraulicLoadNp, double hydraulicLoadAs, double hydraulicLoadBs,
                                                double hydraulicLoadCs, double hydraulicLoadNs, double hydraulicLoadXib,
                                                NaturalStoneWaveImpactHydraulicLoads hydraulicLoads)
        {
            Assert.That(hydraulicLoads.HydraulicLoadAp, Is.EqualTo(hydraulicLoadAp));
            Assert.That(hydraulicLoads.HydraulicLoadBp, Is.EqualTo(hydraulicLoadBp));
            Assert.That(hydraulicLoads.HydraulicLoadCp, Is.EqualTo(hydraulicLoadCp));
            Assert.That(hydraulicLoads.HydraulicLoadNp, Is.EqualTo(hydraulicLoadNp));
            Assert.That(hydraulicLoads.HydraulicLoadAs, Is.EqualTo(hydraulicLoadAs));
            Assert.That(hydraulicLoads.HydraulicLoadBs, Is.EqualTo(hydraulicLoadBs));
            Assert.That(hydraulicLoads.HydraulicLoadCs, Is.EqualTo(hydraulicLoadCs));
            Assert.That(hydraulicLoads.HydraulicLoadNs, Is.EqualTo(hydraulicLoadNs));
            Assert.That(hydraulicLoads.HydraulicLoadXib, Is.EqualTo(hydraulicLoadXib));
        }

        public static void AssertSlope(double slopeUpperLevelAus, double slopeLowerLevelAls,
                                       NaturalStoneWaveImpactSlope slope)
        {
            Assert.That(slope.UpperLevelAus, Is.EqualTo(slopeUpperLevelAus));
            Assert.That(slope.LowerLevelAls, Is.EqualTo(slopeLowerLevelAls));
        }

        public static void AssertUpperLimitLoading(double upperLimitLoadingAul, double upperLimitLoadingBul,
                                                   double upperLimitLoadingCul,
                                                   NaturalStoneWaveImpactUpperLimitLoading upperLimitLoading)
        {
            Assert.That(upperLimitLoading.UpperLimitAul, Is.EqualTo(upperLimitLoadingAul));
            Assert.That(upperLimitLoading.UpperLimitBul, Is.EqualTo(upperLimitLoadingBul));
            Assert.That(upperLimitLoading.UpperLimitCul, Is.EqualTo(upperLimitLoadingCul));
        }

        public static void AssertLowerLimitLoading(double lowerLimitLoadingAll, double lowerLimitLoadingBll,
                                                   double lowerLimitLoadingCll,
                                                   NaturalStoneWaveImpactLowerLimitLoading lowerLimitLoading)
        {
            Assert.That(lowerLimitLoading.LowerLimitAll, Is.EqualTo(lowerLimitLoadingAll));
            Assert.That(lowerLimitLoading.LowerLimitBll, Is.EqualTo(lowerLimitLoadingBll));
            Assert.That(lowerLimitLoading.LowerLimitCll, Is.EqualTo(lowerLimitLoadingCll));
        }

        public static void AssertDistanceMaximumWaveElevation(
            double distanceMaximumWaveElevationAsmax, double distanceMaximumWaveElevationBsmax,
            NaturalStoneWaveImpactDistanceMaximumWaveElevation distanceMaximumWaveElevation)
        {
            Assert.That(distanceMaximumWaveElevation.DistanceMaximumWaveElevationAsmax, Is.EqualTo(distanceMaximumWaveElevationAsmax));
            Assert.That(distanceMaximumWaveElevation.DistanceMaximumWaveElevationBsmax, Is.EqualTo(distanceMaximumWaveElevationBsmax));
        }

        public static void AssertNormativeWidthOfWaveImpact(double normativeWidthOfWaveImpactAwi,
                                                            double normativeWidthOfWaveImpactBwi,
                                                            NaturalStoneWaveImpactNormativeWidthOfWaveImpact normativeWidthOfWaveImpact)
        {
            Assert.That(normativeWidthOfWaveImpact.NormativeWidthOfWaveImpactAwi, Is.EqualTo(normativeWidthOfWaveImpactAwi));
            Assert.That(normativeWidthOfWaveImpact.NormativeWidthOfWaveImpactBwi, Is.EqualTo(normativeWidthOfWaveImpactBwi));
        }

        public static void AssertWaveAngleImpact(double waveAngleImpactBetamax,
                                                 NaturalStoneWaveImpactWaveAngleImpact waveAngleImpact)
        {
            Assert.That(waveAngleImpact.Betamax, Is.EqualTo(waveAngleImpactBetamax));
        }
    }
}