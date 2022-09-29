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

#include <filesystem>
#include <fstream>

#include "EventRegistry.h"
#include "JsonInputAdapter.h"
#include "JsonInputParser.h"
#include "JsonSchemaDefinition.h"
#include "ValidationHelper.h"
#include "ValidationIssue.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    using namespace Core;
    using namespace Integration;
    using namespace nlohmann;
    using namespace json_schema;
    using namespace std;
    using namespace std::filesystem;
    using namespace Util;

    json_validator JsonInputComposer::_validator
    {
        json::parse(JSON_SCHEMA_DEFINITION)
    };

    bool JsonInputComposer::ValidateJson(
        const string& filePath)
    {
        vector<unique_ptr<ValidationIssue>> validationIssues;

        if (!exists(filePath))
        {
            validationIssues.emplace_back(make_unique<ValidationIssue>(ValidationIssueType::Error, "The provided input file does not exist"));
        }
        else
        {
            try
            {
                _validator.validate(json::parse(ifstream(filePath)), *_customErrorHandler);
            }
            catch (const json::parse_error& e)
            {
                validationIssues.emplace_back(make_unique<ValidationIssue>(ValidationIssueType::Error, e.what()));
            }
            catch (const invalid_argument& e)
            {
                validationIssues.emplace_back(make_unique<ValidationIssue>(ValidationIssueType::Error, e.what()));
            }
        }

        return ValidationHelper::RegisterValidationIssues(validationIssues);
    }

    unique_ptr<DataResult<ICalculationInput>> JsonInputComposer::GetInputDataFromJson(
        const string& filePath)
    {
        if (!exists(filePath))
        {
            EventRegistry::Register(make_unique<Event>("The provided input file does not exist", EventType::Error));
        }
        else
        {
            try
            {
                const auto jsonInputData = JsonInputParser::GetJsonInputData(filePath);
                return JsonInputAdapter::AdaptJsonInputData(*jsonInputData);
            }
            catch (const exception& e)
            {
                EventRegistry::Register(make_unique<Event>("An unhandled error occurred while composing calculation data from the Json input. See "
                                                           "stack trace for more information:\n" + static_cast<string>(e.what()),
                                                           EventType::Error));
            }
        }

        return make_unique<DataResult<ICalculationInput>>(EventRegistry::Flush());
    }
}
