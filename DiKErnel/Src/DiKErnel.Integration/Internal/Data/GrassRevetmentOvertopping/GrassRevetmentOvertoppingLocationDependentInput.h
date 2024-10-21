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

#include "GrassRevetmentOvertoppingLocationDependentAccelerationAlphaA.h"
#include "GrassRevetmentOvertoppingTimeDependentOutputConstructionProperties.h"
#include "GrassRevetmentWaveRunupLocationDependentInput.h"

namespace DiKErnel::Integration
{
    class GrassRevetmentOvertoppingLocationDependentInput : public LocationDependentInput
    {
        public:
            explicit GrassRevetmentOvertoppingLocationDependentInput(
                double x,
                double initialDamage,
                double failureNumber,
                double criticalCumulativeOverload,
                double criticalFrontVelocity,
                double increasedLoadTransitionAlphaM,
                double reducedStrengthTransitionAlphaS,
                double averageNumberOfWavesCtm,
                int fixedNumberOfWaves,
                double frontVelocityCwo,
                std::unique_ptr<GrassRevetmentOvertoppingLocationDependentAccelerationAlphaA> locationDependentAccelerationAlphaA,
                std::unique_ptr<double> enforcedDikeHeight);

            [[nodiscard]]
            double GetCriticalCumulativeOverload() const;

            [[nodiscard]]
            double GetCriticalFrontVelocity() const;

            [[nodiscard]]
            double GetIncreasedLoadTransitionAlphaM() const;

            [[nodiscard]]
            double GetReducedStrengthTransitionAlphaS() const;

            [[nodiscard]]
            double GetAverageNumberOfWavesCtm() const;

            [[nodiscard]]
            int GetFixedNumberOfWaves() const;

            [[nodiscard]]
            double GetFrontVelocityCwo() const;

            [[nodiscard]]
            GrassRevetmentOvertoppingLocationDependentAccelerationAlphaA& GetLocationDependentAccelerationAlphaA() const;

            [[nodiscard]]
            const double* GetEnforcedDikeHeight() const;

            [[nodiscard]]
            bool Validate(
                const std::vector<std::reference_wrapper<Core::ITimeDependentInput>>& timeDependentInputs,
                const Core::IProfileData& profileData) const override;

            void InitializeDerivedLocationDependentInput(
                const Core::IProfileData& profileData) override;

            [[nodiscard]]
            std::unique_ptr<Core::LocationDependentOutput> GetLocationDependentOutput(
                std::vector<std::unique_ptr<Core::TimeDependentOutput>> timeDependentOutputItems) override;

        protected:
            [[nodiscard]]
            std::unique_ptr<Core::TimeDependentOutput> CalculateTimeDependentOutput(
                double initialDamage,
                const Core::ITimeDependentInput& timeDependentInput,
                const Core::IProfileData& profileData) override;

        private:
            const double _criticalCumulativeOverload;
            const double _criticalFrontVelocity;
            const double _increasedLoadTransitionAlphaM;
            const double _reducedStrengthTransitionAlphaS;
            const double _averageNumberOfWavesCtm;
            const int _fixedNumberOfWaves;
            const double _frontVelocityCwo;
            std::unique_ptr<GrassRevetmentOvertoppingLocationDependentAccelerationAlphaA> _locationDependentAccelerationAlphaA;
            std::unique_ptr<double> _enforcedDikeHeight;

            std::vector<double> _xValuesProfile;
            std::vector<double> _zValuesProfile;
            std::vector<double> _roughnessCoefficients;
            double _dikeHeight = std::numeric_limits<double>::infinity();
            double _accelerationAlphaA = std::numeric_limits<double>::infinity();

            void InitializeCalculationProfile(
                const std::pair<double, double>& outerToe,
                const std::pair<double, double>& outerCrest,
                const std::vector<std::reference_wrapper<Core::ProfileSegment>>& profileSegments);

            void InitializeDikeHeight(
                const std::pair<double, double>& outerCrest,
                const std::vector<std::reference_wrapper<Core::ProfileSegment>>& profileSegments);

            void InitializeAccelerationAlphaA(
                const std::pair<double, double>& outerCrest,
                const std::pair<double, double>& innerCrest);

            [[nodiscard]]
            double CalculateRepresentativeWaveRunup2P(
                double waterLevel,
                double waveHeightHm0,
                double wavePeriodTm10,
                double waveDirection) const;

            [[nodiscard]]
            double CalculateCumulativeOverload(
                double averageNumberOfWaves,
                double verticalDistanceWaterLevelElevation,
                double representativeWaveRunup2P) const;

            [[nodiscard]]
            double CalculateDikeHeight(
                const std::pair<double, double>& outerCrest,
                const std::vector<std::reference_wrapper<Core::ProfileSegment>>& profileSegments,
                double locationHeight) const;

            [[nodiscard]]
            static std::unique_ptr<GrassRevetmentOvertoppingTimeDependentOutputConstructionProperties> CreateConstructionProperties(
                double incrementDamage,
                double verticalDistanceWaterLevelElevation,
                double representativeWaveRunup2P,
                double cumulativeOverload);
    };
}
