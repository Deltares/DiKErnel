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
#include "NaturalStoneRevetmentSlope.h"
#include "NaturalStoneRevetmentUpperLimitLoading.h"
#include "NaturalStoneRevetmentWaveAngleImpact.h"

namespace DiKErnel::Integration
{
    class NaturalStoneRevetmentLocationDependentInput : public LocationDependentInput
    {
        public:
            explicit NaturalStoneRevetmentLocationDependentInput(
                double x,
                double initialDamage,
                double failureNumber,
                double relativeDensity,
                double thicknessTopLayer,
                std::unique_ptr<NaturalStoneRevetmentHydraulicLoads> hydraulicLoads,
                std::unique_ptr<NaturalStoneRevetmentSlope> slope,
                std::unique_ptr<NaturalStoneRevetmentUpperLimitLoading> upperLimitLoading,
                std::unique_ptr<NaturalStoneRevetmentLowerLimitLoading> lowerLimitLoading,
                std::unique_ptr<NaturalStoneRevetmentDistanceMaximumWaveElevation> distanceMaximumWaveElevation,
                std::unique_ptr<NaturalStoneRevetmentNormativeWidthOfWaveImpact> normativeWidthOfWaveImpact,
                std::unique_ptr<NaturalStoneRevetmentWaveAngleImpact> waveAngleImpact);

            double GetRelativeDensity() const;

            double GetThicknessTopLayer() const;

            NaturalStoneRevetmentHydraulicLoads& GetHydraulicLoads() const;

            NaturalStoneRevetmentSlope& GetSlope() const;

            NaturalStoneRevetmentUpperLimitLoading& GetUpperLimitLoading() const;

            NaturalStoneRevetmentLowerLimitLoading& GetLowerLimitLoading() const;

            NaturalStoneRevetmentDistanceMaximumWaveElevation& GetDistanceMaximumWaveElevation() const;

            NaturalStoneRevetmentNormativeWidthOfWaveImpact& GetNormativeWidthOfWaveImpact() const;

            NaturalStoneRevetmentWaveAngleImpact& GetWaveAngleImpact() const;

        protected:
            void InitializeDerivedLocationDependentInput(
                const Core::IProfileData& profileData) override;

            std::unique_ptr<Core::TimeDependentOutput> CalculateTimeDependentOutput(
                double initialDamage,
                const Core::ITimeDependentInput& timeDependentInput,
                const Core::IProfileData& profileData) override;

        private:
            double _relativeDensity;
            double _thicknessTopLayer;
            std::unique_ptr<NaturalStoneRevetmentHydraulicLoads> _hydraulicLoads;
            std::unique_ptr<NaturalStoneRevetmentSlope> _slope;
            std::unique_ptr<NaturalStoneRevetmentUpperLimitLoading> _upperLimitLoading;
            std::unique_ptr<NaturalStoneRevetmentLowerLimitLoading> _lowerLimitLoading;
            std::unique_ptr<NaturalStoneRevetmentDistanceMaximumWaveElevation> _distanceMaximumWaveElevation;
            std::unique_ptr<NaturalStoneRevetmentNormativeWidthOfWaveImpact> _normativeWidthOfWaveImpact;
            std::unique_ptr<NaturalStoneRevetmentWaveAngleImpact> _waveAngleImpact;
            double _outerToeHeight = std::numeric_limits<double>::infinity();
            double _outerCrestHeight = std::numeric_limits<double>::infinity();
            std::unique_ptr<std::pair<double, double>> _notchOuterBerm = nullptr;
            std::unique_ptr<std::pair<double, double>> _crestOuterBerm = nullptr;
            double _resistance = std::numeric_limits<double>::infinity();

            static std::pair<double, double> GetCharacteristicPointCoordinates(
                const std::vector<std::reference_wrapper<Core::CharacteristicPoint>>& characteristicPoints,
                Core::CharacteristicPointType characteristicPointType);
    };
}
