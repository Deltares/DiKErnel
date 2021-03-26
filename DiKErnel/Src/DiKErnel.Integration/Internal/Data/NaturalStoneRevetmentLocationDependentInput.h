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

#include <memory>

#include "LocationDependentInput.h"
#include "NaturalStoneRevetmentDistanceMaximumWaveElevation.h"
#include "NaturalStoneRevetmentHydraulicLoads.h"
#include "NaturalStoneRevetmentLowerLimitLoading.h"
#include "NaturalStoneRevetmentNormativeWidthOfWaveImpact.h"
#include "NaturalStoneRevetmentUpperLimitLoading.h"
#include "NaturalStoneRevetmentWaveAngleImpact.h"

namespace DiKErnel::Integration
{
    class NaturalStoneRevetmentLocationDependentInput : public LocationDependentInput
    {
        public:
            explicit NaturalStoneRevetmentLocationDependentInput(
                std::string name,
                double initialDamage,
                double failureNumber,
                double tanA,
                double relativeDensity,
                double thicknessTopLayer,
                std::unique_ptr<NaturalStoneRevetmentHydraulicLoads> hydraulicLoads,
                std::unique_ptr<NaturalStoneRevetmentUpperLimitLoading> upperLimitLoading,
                std::unique_ptr<NaturalStoneRevetmentLowerLimitLoading> lowerLimitLoading,
                std::unique_ptr<NaturalStoneRevetmentDistanceMaximumWaveElevation> distanceMaximumWaveElevation,
                std::unique_ptr<NaturalStoneRevetmentNormativeWidthOfWaveImpact> normativeWidthOfWaveImpact,
                std::unique_ptr<NaturalStoneRevetmentWaveAngleImpact> waveAngleImpact);

            double Calculate(
                double initialDamage,
                const Core::ITimeDependentInput& timeDependentInput) override;

            double GetTanA() const;

            double GetRelativeDensity() const;

            double GetThicknessTopLayer() const;

            NaturalStoneRevetmentHydraulicLoads& GetHydraulicLoads() const;

            NaturalStoneRevetmentUpperLimitLoading& GetUpperLimitLoading() const;

            NaturalStoneRevetmentLowerLimitLoading& GetLowerLimitLoading() const;

            NaturalStoneRevetmentDistanceMaximumWaveElevation& GetDistanceMaximumWaveElevation() const;

            NaturalStoneRevetmentNormativeWidthOfWaveImpact& GetNormativeWidthOfWaveImpact() const;

            NaturalStoneRevetmentWaveAngleImpact& GetWaveAngleImpact() const;

        private:
            double _tanA;
            double _relativeDensity;
            double _thicknessTopLayer;
            std::unique_ptr<NaturalStoneRevetmentHydraulicLoads> _hydraulicLoads;
            std::unique_ptr<NaturalStoneRevetmentUpperLimitLoading> _upperLimitLoading;
            std::unique_ptr<NaturalStoneRevetmentLowerLimitLoading> _lowerLimitLoading;
            std::unique_ptr<NaturalStoneRevetmentDistanceMaximumWaveElevation> _distanceMaximumWaveElevation;
            std::unique_ptr<NaturalStoneRevetmentNormativeWidthOfWaveImpact> _normativeWidthOfWaveImpact;
            std::unique_ptr<NaturalStoneRevetmentWaveAngleImpact> _waveAngleImpact;
    };
}
