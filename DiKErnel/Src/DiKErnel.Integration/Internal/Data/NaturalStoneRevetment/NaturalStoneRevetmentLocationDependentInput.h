// Copyright (C) Stichting Deltares 2022. All rights reserved.
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
#include "NaturalStoneRevetmentTimeDependentOutputConstructionProperties.h"
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

            [[nodiscard]]
            double GetRelativeDensity() const;

            [[nodiscard]]
            double GetThicknessTopLayer() const;

            [[nodiscard]]
            NaturalStoneRevetmentHydraulicLoads& GetHydraulicLoads() const;

            [[nodiscard]]
            NaturalStoneRevetmentSlope& GetSlope() const;

            [[nodiscard]]
            NaturalStoneRevetmentUpperLimitLoading& GetUpperLimitLoading() const;

            [[nodiscard]]
            NaturalStoneRevetmentLowerLimitLoading& GetLowerLimitLoading() const;

            [[nodiscard]]
            NaturalStoneRevetmentDistanceMaximumWaveElevation& GetDistanceMaximumWaveElevation() const;

            [[nodiscard]]
            NaturalStoneRevetmentNormativeWidthOfWaveImpact& GetNormativeWidthOfWaveImpact() const;

            [[nodiscard]]
            NaturalStoneRevetmentWaveAngleImpact& GetWaveAngleImpact() const;

            [[nodiscard]]
            bool Validate(
                const std::vector<std::reference_wrapper<Core::ITimeDependentInput>>& timeDependentInputs,
                const Core::IProfileData& profileData) const override;

            [[nodiscard]]
            std::unique_ptr<Core::LocationDependentOutput> GetLocationDependentOutput(
                std::vector<std::unique_ptr<Core::TimeDependentOutput>> timeDependentOutputItems) override;

        protected:
            void InitializeDerivedLocationDependentInput(
                const Core::IProfileData& profileData) override;

            [[nodiscard]]
            std::unique_ptr<Core::TimeDependentOutput> CalculateTimeDependentOutput(
                double initialDamage,
                const Core::ITimeDependentInput& timeDependentInput,
                const Core::IProfileData& profileData) override;

        private:
            double _relativeDensity;
            double _thicknessTopLayer;
            std::unique_ptr<NaturalStoneRevetmentHydraulicLoads> _hydraulicLoadsInput;
            std::unique_ptr<NaturalStoneRevetmentSlope> _slopeInput;
            std::unique_ptr<NaturalStoneRevetmentUpperLimitLoading> _upperLimitLoadingInput;
            std::unique_ptr<NaturalStoneRevetmentLowerLimitLoading> _lowerLimitLoadingInput;
            std::unique_ptr<NaturalStoneRevetmentDistanceMaximumWaveElevation> _distanceMaximumWaveElevationInput;
            std::unique_ptr<NaturalStoneRevetmentNormativeWidthOfWaveImpact> _normativeWidthOfWaveImpactInput;
            std::unique_ptr<NaturalStoneRevetmentWaveAngleImpact> _waveAngleImpactInput;
            double _outerToeHeight = std::numeric_limits<double>::infinity();
            double _outerCrestHeight = std::numeric_limits<double>::infinity();
            std::unique_ptr<std::pair<double, double>> _notchOuterBerm = nullptr;
            std::unique_ptr<std::pair<double, double>> _crestOuterBerm = nullptr;

            double _resistance = std::numeric_limits<double>::infinity();

            [[nodiscard]]
            double CalculateHydraulicLoad(
                double surfSimilarityParameter,
                double waveHeightHm0) const;

            [[nodiscard]]
            int CalculateTimeOfFailure(
                double failureNumber,
                double wavePeriodTm10,
                double beginTime,
                double hydraulicLoad,
                double waveAngleImpact,
                double referenceTimeDegradation) const;

            [[nodiscard]]
            std::unique_ptr<NaturalStoneRevetmentTimeDependentOutputConstructionProperties> CreateConstructionProperties(
                double incrementDamage,
                double damage,
                double slopeLowerLevel,
                double slopeLowerPosition,
                double slopeUpperLevel,
                double slopeUpperPosition,
                double outerSlope,
                double waveSteepnessDeepWater,
                double distanceMaximumWaveElevation,
                double surfSimilarityParameter,
                double normativeWidthWaveImpact,
                double depthMaximumWaveLoad,
                double lowerLimitLoading,
                double upperLimitLoading,
                bool loadingRevetment,
                double hydraulicLoad,
                double waveAngleImpact,
                double referenceDegradation,
                double referenceTimeDegradation,
                std::unique_ptr<int> timeOfFailure);
    };
}
