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

#include <variant>

#include "CalculationOutput.h"
#include "JsonOutputData.h"
#include "JsonOutputType.h"

namespace DiKErnel::KernelWrapper::Json::Output
{
    class CalculationOutputAdapter
    {
        public:
            static std::unique_ptr<JsonOutputData> AdaptCalculationOutput(
                const Core::CalculationOutput& calculationOutput,
                JsonOutputType outputType,
                const std::vector<std::pair<std::string, std::variant<double, std::string>>>& metaData =
                        std::vector<std::pair<std::string, std::variant<double, std::string>>>());

        private:
            static std::vector<std::unique_ptr<JsonOutputFailureLocationData>> GetJsonOutputLocations(
                const std::vector<std::reference_wrapper<Core::LocationDependentOutput>>& locationDependentOutputItems,
                JsonOutputType outputType);

            typedef std::unique_ptr<JsonOutputFailureLocationData> (*FuncPtr)(
                const Core::LocationDependentOutput&);

            static FuncPtr GetCreateLocationDataMethod(
                JsonOutputType outputType);

            static std::unique_ptr<JsonOutputFailureLocationData> CreateJsonOutputFailureLocationData(
                const Core::LocationDependentOutput& locationOutput);

            static std::unique_ptr<JsonOutputFailureLocationData> CreateJsonOutputDamageLocationData(
                const Core::LocationDependentOutput& locationOutput);

            static std::unique_ptr<JsonOutputFailureLocationData> CreateJsonOutputPhysicsLocationData(
                const Core::LocationDependentOutput& locationOutput);
    };
}
