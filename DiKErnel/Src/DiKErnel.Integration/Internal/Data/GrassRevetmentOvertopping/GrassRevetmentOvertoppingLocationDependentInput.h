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

#include <functional>
#include <memory>

#include "GrassRevetmentWaveRunupLocationDependentInput.h"
#include "GrassRevetmentWaveRunupRayleighTimeDependentOutput.h"

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
                std::function<double(
                    const Core::IProfileData&)>& getAccelerationAlphaA,
                std::function<double(
                    const Core::IProfileData&)>& getDikeHeight);

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
            bool Validate(
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
            double _criticalCumulativeOverload;
            double _criticalFrontVelocity;
            double _increasedLoadTransitionAlphaM;
            double _reducedStrengthTransitionAlphaS;
            double _averageNumberOfWavesCtm;
            const int _fixedNumberOfWaves;
            const double _frontVelocityCwo;

            std::function<double(
                const Core::IProfileData&)> _getAccelerationAlphaA;
            std::function<double(
                const Core::IProfileData&)> _getDikeHeight;

            std::vector<double> _xValuesProfile;
            std::vector<double> _zValuesProfile;
            std::vector<double> _roughnessCoefficients;
            double _accelerationAlphaA = std::numeric_limits<double>::infinity();
            double _dikeHeight = std::numeric_limits<double>::infinity();
            double _verticalDistanceWaterLevelElevation = std::numeric_limits<double>::infinity();
            double _representativeWaveRunup2P = std::numeric_limits<double>::infinity();
            double _cumulativeOverload = std::numeric_limits<double>::infinity();

            [[nodiscard]]
            double CalculateRepresentativeWaveRunup2P(
                double waterLevel,
                double waveHeightHm0,
                double wavePeriodTm10,
                double waveDirection) const;

            [[nodiscard]]
            double CalculateCumulativeOverload(
                double averageNumberOfWaves) const;

            [[nodiscard]]
            std::unique_ptr<GrassRevetmentWaveRunupRayleighTimeDependentOutputConstructionProperties> CreateConstructionProperties(
                double incrementDamage,
                double damage,
                std::unique_ptr<int> timeOfFailure);
    };
}
