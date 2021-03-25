// Copyright (C) Stichting Deltares 2020. All rights reserved.
//
// This file is part of DiKErnel.
//
// DiKErnel is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, version 3.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/lgpl-3.0.html>.
//
// All names, logos, and references to "Deltares" are registered trademarks of
// Stichting Deltares and remain full property of Stichting Deltares at all times.
// All rights reserved.

#pragma once

#include "NaturalStoneRevetmentLocationDependentInput.h"

namespace DiKErnel::Integration::TestUtil
{
    class NaturalStoneRevetmentLocationDependentInputAssertHelper
    {
        public:
            static void AssertMandatoryProperties(
                const std::string& name,
                double slopeAngle,
                double relativeDensity,
                double thicknessTopLayer,
                const NaturalStoneRevetmentLocationDependentInput& locationDependentInput);

            static void AssertHydraulicLoads(
                double hydraulicLoadAp,
                double hydraulicLoadBp,
                double hydraulicLoadCp,
                double hydraulicLoadNp,
                double hydraulicLoadAs,
                double hydraulicLoadBs,
                double hydraulicLoadCs,
                double hydraulicLoadNs,
                double hydraulicLoadXib,
                const NaturalStoneRevetmentHydraulicLoads& hydraulicLoads);

            static void AssertUpperLimitLoading(
                double upperLimitLoadingAul,
                double upperLimitLoadingBul,
                double upperLimitLoadingCul,
                const NaturalStoneRevetmentUpperLimitLoading& upperLimitLoading);

            static void AssertLowerLimitLoading(
                double lowerLimitLoadingAll,
                double lowerLimitLoadingBll,
                double lowerLimitLoadingCll,
                const NaturalStoneRevetmentLowerLimitLoading& lowerLimitLoading);

            static void AssertDistanceMaximumWaveElevation(
                double distanceMaximumWaveElevationAsmax,
                double distanceMaximumWaveElevationBsmax,
                const NaturalStoneRevetmentDistanceMaximumWaveElevation& distanceMaximumWaveElevation);

            static void AssertNormativeWidthOfWaveImpact(
                double normativeWidthOfWaveImpactAwi,
                double normativeWidthOfWaveImpactBwi,
                const NaturalStoneRevetmentNormativeWidthOfWaveImpact& normativeWidthOfWaveImpact);

            static void AssertWaveAngleImpact(
                double waveAngleImpactBetamax,
                const NaturalStoneRevetmentWaveAngleImpact& waveAngleImpact);
    };
}
