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

#include "GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties.h"
#include "GrassRevetmentWaveImpactTimeLine.h"
#include "GrassRevetmentWaveImpactWaveAngleImpact.h"
#include "LocationDependentInput.h"

namespace DiKErnel::Integration
{
    class GrassRevetmentWaveImpactLocationDependentInput : public LocationDependentInput
    {
        public:
            explicit GrassRevetmentWaveImpactLocationDependentInput(
                double x,
                double initialDamage,
                double failureNumber,
                std::unique_ptr<GrassRevetmentWaveImpactWaveAngleImpact> waveAngleImpact,
                double minimumWaveHeightTemax,
                double maximumWaveHeightTemin,
                std::unique_ptr<GrassRevetmentWaveImpactTimeLine> timeLine,
                double upperLimitLoadingAul,
                double lowerLimitLoadingAll);

            [[nodiscard]]
            GrassRevetmentWaveImpactWaveAngleImpact& GetWaveAngleImpact() const;

            [[nodiscard]]
            double GetMinimumWaveHeightTemax() const;

            [[nodiscard]]
            double GetMaximumWaveHeightTemin() const;

            [[nodiscard]]
            GrassRevetmentWaveImpactTimeLine& GetTimeLine() const;

            [[nodiscard]]
            double GetUpperLimitLoadingAul() const;

            [[nodiscard]]
            double GetLowerLimitLoadingAll() const;

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
            std::unique_ptr<GrassRevetmentWaveImpactWaveAngleImpact> _waveAngleImpactInput;
            double _minimumWaveHeightTemax;
            double _maximumWaveHeightTemin;
            std::unique_ptr<GrassRevetmentWaveImpactTimeLine> _timeLine;
            double _upperLimitLoadingAul;
            double _lowerLimitLoadingAll;

            double _minimumWaveHeight = std::numeric_limits<double>::infinity();
            double _maximumWaveHeight = std::numeric_limits<double>::infinity();

            [[nodiscard]]
            std::unique_ptr<GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties> CreateConstructionProperties(
                double incrementDamage,
                double damage,
                double lowerLimitLoading,
                double upperLimitLoading,
                bool loadingRevetment,
                double waveAngleImpact,
                double waveHeightImpact,
                std::unique_ptr<int> timeOfFailure);
    };
}
