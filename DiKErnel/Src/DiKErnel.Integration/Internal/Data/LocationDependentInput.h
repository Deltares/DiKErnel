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

#include <limits>

#include "ILocationDependentInput.h"

namespace DiKErnel::Integration
{
    class LocationDependentInput : public Core::ILocationDependentInput
    {
        public:
            [[nodiscard]]
            bool Validate(
                const std::vector<std::reference_wrapper<Core::ITimeDependentInput>>& timeDependentInputs,
                const Core::IProfileData& profileData) const override;

            std::unique_ptr<Core::TimeDependentOutput> Calculate(
                double initialDamage,
                const Core::ITimeDependentInput& timeDependentInput,
                const Core::IProfileData& profileData) override;

            [[nodiscard]]
            double GetX() const override;

            [[nodiscard]]
            double GetInitialDamage() const override;

            [[nodiscard]]
            double GetFailureNumber() const override;

            [[nodiscard]]
            double GetZ() const override;

        protected:
            explicit LocationDependentInput(
                double x,
                double initialDamage,
                double failureNumber);

            virtual void InitializeDerivedLocationDependentInput(
                const Core::IProfileData& profileData);

            [[nodiscard]]
            virtual std::unique_ptr<Core::TimeDependentOutput> CalculateTimeDependentOutput(
                double initialDamage,
                const Core::ITimeDependentInput& timeDependentInput,
                const Core::IProfileData& profileData) = 0;

        private:
            const double _x;
            const double _initialDamage;
            const double _failureNumber;
            bool _derivedLocationDependentInputInitialized = false;
            double _z = std::numeric_limits<double>::infinity();
    };
}
