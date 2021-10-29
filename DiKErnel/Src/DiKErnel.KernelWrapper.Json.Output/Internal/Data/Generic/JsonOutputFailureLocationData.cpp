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

#include "JsonOutputFailureLocationData.h"

#include "JsonOutputDefinitions.h"

namespace DiKErnel::KernelWrapper::Json::Output
{
    using namespace Core;
    using namespace nlohmann;

    JsonOutputFailureLocationData::JsonOutputFailureLocationData(
        const LocationDependentOutput& locationOutput)
        : _locationOutput(locationOutput) {}

    ordered_json JsonOutputFailureLocationData::CreateJson() const
    {
        const auto* timeOfFailure = _locationOutput.GetTimeOfFailure();

        auto output = ordered_json::object(
            {
                {
                    JsonOutputDefinitions::FAILURE_REVETMENT,
                    {
                        {
                            JsonOutputDefinitions::FAILED,
                            timeOfFailure != nullptr
                        },
                        {
                            JsonOutputDefinitions::TIME_OF_FAILURE,
                            nullptr
                        }
                    }
                }
            });

        if (timeOfFailure != nullptr)
        {
            output.at(JsonOutputDefinitions::FAILURE_REVETMENT).at(JsonOutputDefinitions::TIME_OF_FAILURE) = *timeOfFailure;
        }

        return output;
    }

    const LocationDependentOutput& JsonOutputFailureLocationData::GetLocationOutput() const
    {
        return _locationOutput;
    }
}
