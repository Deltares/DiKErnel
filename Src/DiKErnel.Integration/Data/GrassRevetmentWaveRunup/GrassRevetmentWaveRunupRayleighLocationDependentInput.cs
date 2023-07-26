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

#include "GrassRevetmentWaveRunupLocationDependentInput.h"
#include "GrassRevetmentWaveRunupRayleighTimeDependentOutput.h"

namespace DiKErnel.Integration.Data.GrassRevetmentWaveRunup
{
    class GrassRevetmentWaveRunupRayleighLocationDependentInput : public GrassRevetmentWaveRunupLocationDependentInput
    {
        public:
            explicit GrassRevetmentWaveRunupRayleighLocationDependentInput(
                double x,
                double initialDamage,
                double failureNumber,
                double outerSlope,
                double criticalCumulativeOverload,
                double criticalFrontVelocity,
                double increasedLoadTransitionAlphaM,
                double reducedStrengthTransitionAlphaS,
                double averageNumberOfWavesCtm,
                std::unique_ptr<GrassRevetmentWaveRunupRepresentative2P> representative2P,
                std::unique_ptr<GrassRevetmentWaveRunupWaveAngleImpact> waveAngleImpact,
                int fixedNumberOfWaves,
                double frontVelocityCu);

            [[nodiscard]]
            int GetFixedNumberOfWaves() const;

            [[nodiscard]]
            double GetFrontVelocityCu() const;

            [[nodiscard]]
            bool Validate(
                const std::vector<std::reference_wrapper<Core::ITimeDependentInput>>& timeDependentInputs,
                const Core::IProfileData& profileData) const override;

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
            const int _fixedNumberOfWaves;
            const double _frontVelocityCu;

            double _verticalDistanceWaterLevelElevation = std::numeric_limits<double>::infinity();
            double _waveAngleImpact = std::numeric_limits<double>::infinity();
            double _representativeWaveRunup2P = std::numeric_limits<double>::infinity();
            double _cumulativeOverload = std::numeric_limits<double>::infinity();

            [[nodiscard]]
            double CalculateRepresentativeWaveRunup2P(
                double surfSimilarityParameter,
                double waveHeightHm0) const;

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
