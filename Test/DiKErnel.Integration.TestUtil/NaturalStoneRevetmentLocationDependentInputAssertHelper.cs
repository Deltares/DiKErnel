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

using DiKErnel.Integration.Data.NaturalStoneRevetment;
using NUnit.Framework;

namespace DiKErnel.Integration.TestUtil
{
    internal static class NaturalStoneRevetmentLocationDependentInputAssertHelper
    {
        public static void AssertGeneralProperties(double relativeDensity, double thicknessTopLayer,
                                                   NaturalStoneRevetmentLocationDependentInput locationDependentInput)
        {
            Assert.AreEqual(relativeDensity, locationDependentInput.RelativeDensity);
            Assert.AreEqual(thicknessTopLayer, locationDependentInput.ThicknessTopLayer);
        }

        public static void AssertHydraulicLoads(double hydraulicLoadAp, double hydraulicLoadBp, double hydraulicLoadCp,
                                                double hydraulicLoadNp, double hydraulicLoadAs, double hydraulicLoadBs,
                                                double hydraulicLoadCs, double hydraulicLoadNs, double hydraulicLoadXib,
                                                NaturalStoneRevetmentHydraulicLoads hydraulicLoads)
        {
            Assert.AreEqual(hydraulicLoadAp, hydraulicLoads.HydraulicLoadAp);
            Assert.AreEqual(hydraulicLoadBp, hydraulicLoads.HydraulicLoadBp);
            Assert.AreEqual(hydraulicLoadCp, hydraulicLoads.HydraulicLoadCp);
            Assert.AreEqual(hydraulicLoadNp, hydraulicLoads.HydraulicLoadNp);
            Assert.AreEqual(hydraulicLoadAs, hydraulicLoads.HydraulicLoadAs);
            Assert.AreEqual(hydraulicLoadBs, hydraulicLoads.HydraulicLoadBs);
            Assert.AreEqual(hydraulicLoadCs, hydraulicLoads.HydraulicLoadCs);
            Assert.AreEqual(hydraulicLoadNs, hydraulicLoads.HydraulicLoadNs);
            Assert.AreEqual(hydraulicLoadXib, hydraulicLoads.HydraulicLoadXib);
        }

        public static void AssertSlope(double slopeUpperLevelAus, double slopeLowerLevelAls,
                                       NaturalStoneRevetmentSlope slope)
        {
            Assert.AreEqual(slopeUpperLevelAus, slope.UpperLevelAus);
            Assert.AreEqual(slopeLowerLevelAls, slope.LowerLevelAls);
        }

        public static void AssertUpperLimitLoading(double upperLimitLoadingAul, double upperLimitLoadingBul,
                                                   double upperLimitLoadingCul,
                                                   NaturalStoneRevetmentUpperLimitLoading upperLimitLoading)
        {
            Assert.AreEqual(upperLimitLoadingAul, upperLimitLoading.UpperLimitAul);
            Assert.AreEqual(upperLimitLoadingBul, upperLimitLoading.UpperLimitBul);
            Assert.AreEqual(upperLimitLoadingCul, upperLimitLoading.UpperLimitCul);
        }

        public static void AssertLowerLimitLoading(double lowerLimitLoadingAll, double lowerLimitLoadingBll,
                                                   double lowerLimitLoadingCll,
                                                   NaturalStoneRevetmentLowerLimitLoading lowerLimitLoading)
        {
            Assert.AreEqual(lowerLimitLoadingAll, lowerLimitLoading.LowerLimitAll);
            Assert.AreEqual(lowerLimitLoadingBll, lowerLimitLoading.LowerLimitBll);
            Assert.AreEqual(lowerLimitLoadingCll, lowerLimitLoading.LowerLimitCll);
        }

        public static void AssertDistanceMaximumWaveElevation(
            double distanceMaximumWaveElevationAsmax, double distanceMaximumWaveElevationBsmax,
            NaturalStoneRevetmentDistanceMaximumWaveElevation distanceMaximumWaveElevation)
        {
            Assert.AreEqual(distanceMaximumWaveElevationAsmax,
                            distanceMaximumWaveElevation.DistanceMaximumWaveElevationAsmax);
            Assert.AreEqual(distanceMaximumWaveElevationBsmax,
                            distanceMaximumWaveElevation.DistanceMaximumWaveElevationBsmax);
        }

        public static void AssertNormativeWidthOfWaveImpact(double normativeWidthOfWaveImpactAwi,
                                                            double normativeWidthOfWaveImpactBwi,
                                                            NaturalStoneRevetmentNormativeWidthOfWaveImpact normativeWidthOfWaveImpact)
        {
            Assert.AreEqual(normativeWidthOfWaveImpactAwi, normativeWidthOfWaveImpact.NormativeWidthOfWaveImpactAwi);
            Assert.AreEqual(normativeWidthOfWaveImpactBwi, normativeWidthOfWaveImpact.NormativeWidthOfWaveImpactBwi);
        }

        public static void AssertWaveAngleImpact(double waveAngleImpactBetamax,
                                                 NaturalStoneRevetmentWaveAngleImpact waveAngleImpact)
        {
            Assert.AreEqual(waveAngleImpactBetamax, waveAngleImpact.Betamax);
        }
    }
}