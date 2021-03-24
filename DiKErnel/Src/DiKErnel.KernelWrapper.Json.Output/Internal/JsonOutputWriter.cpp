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

#include "JsonOutputWriter.h"

#include <fstream>
#include <iomanip>

#include "JsonOutputDefinitions.h"

namespace DiKErnel::KernelWrapper::Json::Output
{
    using namespace nlohmann;
    using namespace std;

    void JsonOutputWriter::Write(
        const string& filePath,
        const JsonOutputData& jsonOutputData)
    {
        const auto jsonOutput = ordered_json::object(
            {
                {
                    JsonOutputDefinitions::OUTPUT_DATA,
                    {
                        {
                            JsonOutputDefinitions::TIME,
                            jsonOutputData.GetTimes()
                        },
                        {
                            JsonOutputDefinitions::LOCATIONS,
                            GetLocations(jsonOutputData.GetLocationDataItems())
                        }
                    }
                }
            });

        ofstream outfile(filePath, ios::trunc);
        outfile << setw(4) << jsonOutput << endl;
    }

    vector<basic_json<ordered_map>> JsonOutputWriter::GetLocations(
        const vector<reference_wrapper<JsonOutputLocationData>>& locationDataItems)
    {
        vector<basic_json<ordered_map>> locationOutputJsonItems;

        for (const auto& locationDataReference : locationDataItems)
        {
            const auto& locationData = locationDataReference.get();

            auto locationFailed = locationData.GetLocationFailed();
            auto locationOutputJson = ordered_json::object(
                {
                    {
                        JsonOutputDefinitions::NAME,
                        locationData.GetName()
                    },
                    {
                        JsonOutputDefinitions::DAMAGE,
                        {
                            {
                                JsonOutputDefinitions::FAILED,
                                locationFailed
                            },
                            {
                                JsonOutputDefinitions::TIME_OF_FAILURE,
                                nullptr
                            },
                            {
                                JsonOutputDefinitions::DAMAGE_OVER_TIME,
                                locationData.GetDamages()
                            }
                        }
                    }
                }
            );

            if (locationFailed)
            {
                locationOutputJson[JsonOutputDefinitions::DAMAGE][JsonOutputDefinitions::TIME_OF_FAILURE] = *locationData.GetTimeOfFailure();
            }

            locationOutputJsonItems.push_back(locationOutputJson);
        }

        return locationOutputJsonItems;
    }
}
