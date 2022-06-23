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

#include "JsonInputComposer.h"

#include <fstream>

#include "EventRegistry.h"
#include "JsonInputAdapter.h"
#include "JsonInputParser.h"
#include "ValidationHelper.h"
#include "ValidationIssue.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    using namespace Integration;
    using namespace nlohmann;
    using namespace json_schema;
    using namespace std;
    using namespace Util;

    bool JsonInputComposer::ValidateJson(
        const string& filePath)
    {
        vector<unique_ptr<ValidationIssue>> validationIssues;

        try
        {
            _validator.validate(json::parse(ifstream(filePath)));
        }
        catch (const invalid_argument& e)
        {
            validationIssues.emplace_back(make_unique<ValidationIssue>(ValidationIssueType::Error, e.what()));
        }

        return ValidationHelper::RegisterValidationIssues(validationIssues);
    }

    unique_ptr<DataResult<JsonInputComposerResult>> JsonInputComposer::GetInputDataFromJson(
        const string& filePath)
    {
        try
        {
            auto processType = JsonInputProcessType::Damage;

            const auto& jsonInputData = JsonInputParser::GetJsonInputData(filePath);

            if (const auto* readProcessType = jsonInputData->GetProcessData().GetProcessType(); readProcessType != nullptr)
            {
                processType = *readProcessType;
            }

            auto inputComposerResult = make_unique<JsonInputComposerResult>(JsonInputAdapter::AdaptJsonInputData(*jsonInputData), processType);

            return make_unique<DataResult<JsonInputComposerResult>>(move(inputComposerResult), EventRegistry::Flush());
        }
        catch (const exception& e)
        {
            EventRegistry::Register(make_unique<Event>("An unhandled error occurred while composing calculation data from the Json input. See "
                                                       "stack trace for more information:\n" + static_cast<string>(e.what()), EventType::Error));

            return make_unique<DataResult<JsonInputComposerResult>>(EventRegistry::Flush());
        }
    }
}
