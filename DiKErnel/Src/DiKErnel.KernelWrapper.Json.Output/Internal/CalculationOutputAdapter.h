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

#include "CalculationOutput.h"
#include "ICalculationInput.h"
#include "JsonOutputData.h"
#include "JsonProcessType.h"

namespace DiKErnel::KernelWrapper::Json::Output
{
    class CalculationOutputAdapter
    {
        public:
            static std::unique_ptr<JsonOutputData> AdaptCalculationOutput(
                const Core::CalculationOutput& calculationOutput,
                const Core::ICalculationInput& calculationInput,
                JsonProcessType processType);

        private:
            static std::vector<int> GetTimes(
                const std::vector<std::reference_wrapper<Core::ITimeDependentInput>>& timeDependentInputItems);

            static std::vector<std::unique_ptr<JsonOutputFailureLocationData>> GetJsonOutputLocations(
                const std::vector<std::reference_wrapper<Core::LocationDependentOutput>>& locationDependentOutputItems,
                const std::vector<std::reference_wrapper<Core::ILocationDependentInput>>& locationDependentInputItems,
                JsonProcessType processType);

            typedef std::unique_ptr<JsonOutputFailureLocationData> (*FuncPtr)(
                const Core::LocationDependentOutput&,
                const Core::ILocationDependentInput&);

            static FuncPtr GetCreateLocationDataMethod(
                JsonProcessType processType);

            static std::unique_ptr<JsonOutputFailureLocationData> CreateJsonOutputFailureLocationData(
                const Core::LocationDependentOutput& locationOutput,
                const Core::ILocationDependentInput& locationInput);

            static std::unique_ptr<JsonOutputFailureLocationData> CreateJsonOutputDamageLocationData(
                const Core::LocationDependentOutput& locationOutput,
                const Core::ILocationDependentInput& locationInput);
    };
}
