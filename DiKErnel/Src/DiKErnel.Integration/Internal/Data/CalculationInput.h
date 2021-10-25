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
#include <vector>

#include "ICalculationInput.h"
#include "LocationDependentInput.h"
#include "TimeDependentInput.h"

namespace DiKErnel::Integration
{
    class CalculationInput : public Core::ICalculationInput
    {
        public:
            explicit CalculationInput(
                std::unique_ptr<Core::IProfileData> profileData,
                std::vector<std::unique_ptr<LocationDependentInput>> locationDependentInputItems,
                std::vector<std::unique_ptr<TimeDependentInput>> timeDependentInputItems);

            bool Validate() override;

            const Core::IProfileData& GetProfileData() const override;

            const std::vector<std::reference_wrapper<Core::ILocationDependentInput>>& GetLocationDependentInputItems() const override;

            const std::vector<std::reference_wrapper<Core::ITimeDependentInput>>& GetTimeDependentInputItems() const override;

        private:
            std::unique_ptr<Core::IProfileData> _profileData;
            std::vector<std::unique_ptr<LocationDependentInput>> _locationDependentInputItems;
            std::vector<std::reference_wrapper<Core::ILocationDependentInput>> _locationDependentInputItemReferences;
            std::vector<std::unique_ptr<TimeDependentInput>> _timeDependentInputItems;
            std::vector<std::reference_wrapper<Core::ITimeDependentInput>> _timeDependentInputItemReferences;
    };
}
