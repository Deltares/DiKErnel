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

#include "JsonInputComposer.h"

#include "EventRegistry.h"
#include "JsonInputAdapter.h"
#include "JsonInputParser.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    using namespace Core;
    using namespace std;
    using namespace Util;

    tuple<unique_ptr<ICalculationInput>, JsonInputProcessType, vector<unique_ptr<Event>>> JsonInputComposer::GetInputDataFromJson(
        const string& filePath)
    {
        unique_ptr<ICalculationInput> calculationInput = nullptr;
        auto processType = JsonInputProcessType::Damage;

        try
        {
            const auto jsonInputData = JsonInputParser::GetJsonInputData(filePath);

            if (const auto* readProcessType = jsonInputData->GetProcessData().GetProcessType(); readProcessType != nullptr)
            {
                processType = *readProcessType;
            }

            calculationInput = JsonInputAdapter::AdaptJsonInputData(*jsonInputData);
        }
        catch (const exception& e)
        {
            EventRegistry::Register(make_unique<Event>(e.what(), EventType::Error));
        }

        return make_tuple(move(calculationInput), processType, EventRegistry::Flush());
    }
}
