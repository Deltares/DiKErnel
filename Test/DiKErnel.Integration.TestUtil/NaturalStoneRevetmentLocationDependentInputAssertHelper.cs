// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
//
// This file is part of DiKErnel.
//
// DiKErnel is free software: you can redistribute it and/or modify it under the terms of the
// GNU Lesser General Public License as published by the Free Software Foundation, either
// version 3 of the License, or (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with this
// program. If not, see <http://www.gnu.org/licenses/>.
//
// All names, logos, and references to "Deltares" are registered trademarks of Stichting
// Deltares and remain full property of Stichting Deltares at all times. All rights reserved.

using DiKErnel.Integration.Data.NaturalStoneRevetment;

namespace DiKErnel.Integration.TestUtil
{
    internal static class NaturalStoneRevetmentLocationDependentInputAssertHelper
    {
        public static void AssertGeneralProperties(
            double x,
            double relativeDensity,
            double thicknessTopLayer,
            NaturalStoneRevetmentLocationDependentInput locationDependentInput) {}

        public static void AssertHydraulicLoads(
            double hydraulicLoadAp,
            double hydraulicLoadBp,
            double hydraulicLoadCp,
            double hydraulicLoadNp,
            double hydraulicLoadAs,
            double hydraulicLoadBs,
            double hydraulicLoadCs,
            double hydraulicLoadNs,
            double hydraulicLoadXib,
            NaturalStoneRevetmentHydraulicLoads hydraulicLoads) {}

        public static void AssertSlope(
            double slopeUpperLevelAus,
            double slopeLowerLevelAls,
            NaturalStoneRevetmentSlope slope) {}

        public static void AssertUpperLimitLoading(
            double upperLimitLoadingAul,
            double upperLimitLoadingBul,
            double upperLimitLoadingCul,
            NaturalStoneRevetmentUpperLimitLoading upperLimitLoading) {}

        public static void AssertLowerLimitLoading(
            double lowerLimitLoadingAll,
            double lowerLimitLoadingBll,
            double lowerLimitLoadingCll,
            NaturalStoneRevetmentLowerLimitLoading lowerLimitLoading) {}

        public static void AssertDistanceMaximumWaveElevation(
            double distanceMaximumWaveElevationAsmax,
            double distanceMaximumWaveElevationBsmax,
            NaturalStoneRevetmentDistanceMaximumWaveElevation distanceMaximumWaveElevation) {}

        public static void AssertNormativeWidthOfWaveImpact(
            double normativeWidthOfWaveImpactAwi,
            double normativeWidthOfWaveImpactBwi,
            NaturalStoneRevetmentNormativeWidthOfWaveImpact normativeWidthOfWaveImpact) {}

        public static void AssertWaveAngleImpact(
            double waveAngleImpactBetamax,
            NaturalStoneRevetmentWaveAngleImpact waveAngleImpact) {}
    }
}