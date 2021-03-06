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

#include "OutputComposer.h"

#include <fstream>
#include <iomanip>

#include <nlohmann/json.hpp>

#include "OutputData.h"
#include "OutputJsonDefinitions.h"
#include "RevetmentOutput.h"

namespace DiKErnel::KernelWrapper::Json
{
    using namespace std;

    void OutputComposer::WriteParametersToJson(
        const string& filePath,
        const OutputData& outputData,
        const vector<int>& times)
    {
        nlohmann::ordered_json json;

        json[OutputJsonDefinitions::OUTPUT_DATA][OutputJsonDefinitions::TIME] = times;

        for (const auto& calculationLocationOutputReference : outputData.GetCalculationLocationsOutput())
        {
            const auto& calculationLocationOutput = calculationLocationOutputReference.get();
            const auto& revetmentOutput = calculationLocationOutput.GetRevetmentOutput();

            const auto* timeOfFailure = revetmentOutput.GetTimeOfFailure();

            auto locationJson = nlohmann::ordered_json::object(
                {
                    {
                        OutputJsonDefinitions::NAME,
                        calculationLocationOutput.GetName()
                    },
                    {
                        OutputJsonDefinitions::DAMAGE,
                        {
                            {
                                OutputJsonDefinitions::FAILED,
                                timeOfFailure != nullptr
                            },
                            {
                                OutputJsonDefinitions::TIME_OF_FAILURE,
                                nullptr
                            },
                            {
                                OutputJsonDefinitions::DAMAGE_OVER_TIME,
                                revetmentOutput.GetDamages()
                            }
                        }
                    }
                });

            if (timeOfFailure != nullptr)
            {
                locationJson[OutputJsonDefinitions::DAMAGE][OutputJsonDefinitions::TIME_OF_FAILURE] = *timeOfFailure;
            }

            json[OutputJsonDefinitions::OUTPUT_DATA][OutputJsonDefinitions::LOCATIONS].push_back(
                locationJson);
        }

        ofstream outfile(filePath, ios::trunc);
        outfile << setw(4) << json << endl;
    }
}
