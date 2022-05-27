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

#include <filesystem>
#include <fstream>
#include <string>
#include <thread>

#include "Calculator.h"
#include "CommandLineArgumentParser.h"
#include "EventRegistry.h"
#include "JsonInputComposer.h"
#include "JsonOutputComposer.h"
#include "Validator.h"

using namespace DiKErnel::Cli;
using namespace DiKErnel::Core;
using namespace DiKErnel::KernelWrapper::Json::Input;
using namespace DiKErnel::KernelWrapper::Json::Output;
using namespace DiKErnel::Util;
using namespace std;

#pragma region Forward declarations

JsonOutputType ConvertProcessType(
    JsonInputProcessType);

void WriteToLogFile(
    const vector<reference_wrapper<Event>>& events);

string GetEventTypeString(
    EventType eventType);

void CloseApplicationAfterUnhandledError();

[[noreturn]]
void UnhandledErrorHandler();

vector<reference_wrapper<Event>> GetEventReferences(
    const vector<unique_ptr<Event>>& events
);

#pragma endregion

string logOutputFilePath;

int main(
    const int argc,
    char** argv)
{
    set_terminate(UnhandledErrorHandler);

    try
    {
        const CommandLineArgumentParser parser(argc, argv);
        if (!parser.ArgumentsAreValid())
        {
            return -1;
        }

        logOutputFilePath = parser.GetLogOutputFilePath();

        const auto inputComposerResult = JsonInputComposer::GetInputDataFromJson(parser.GetJsonInputFilePath());
        WriteToLogFile(inputComposerResult->GetEvents());

        if (!inputComposerResult->GetSuccessful())
        {
            return -1;
        }

        const auto* inputData = inputComposerResult->GetData();
        const auto& calculationInput = inputData->GetCalculationInput();

        const auto validationResult = Validator::Validate(calculationInput);
        WriteToLogFile(validationResult->GetEvents());

        if (!validationResult->GetSuccessful())
        {
            return -1;
        }

        if (*validationResult->GetData() != ValidationResultType::Successful)
        {
            return -1;
        }

        Calculator calculator(calculationInput);
        calculator.WaitForCompletion();

        const auto calculatorResult = calculator.GetResult();
        WriteToLogFile(calculatorResult->GetEvents());

        if (calculator.GetCalculationState() == CalculationState::FinishedInError)
        {
            return -1;
        }

        const auto outputComposerResult = JsonOutputComposer::WriteCalculationOutputToJson(
            parser.GetJsonOutputFilePath(), *calculatorResult->GetData(),
            ConvertProcessType(inputData->GetProcessType()));

        WriteToLogFile(outputComposerResult->GetEvents());

        if (!outputComposerResult->GetSuccessful())
        {
            return -1;
        }

        return 0;
    }
    catch (const exception& e)
    {
        EventRegistry::Register(make_unique<Event>("An unhandled error occurred in the Showcase. See stack trace for more information:\n"
                                                   + static_cast<string>(e.what()), EventType::Error));

        CloseApplicationAfterUnhandledError();
        return -1;
    }
}

JsonOutputType ConvertProcessType(
    const JsonInputProcessType processType)
{
    switch (processType)
    {
        case JsonInputProcessType::Failure:
            return JsonOutputType::Failure;
        case JsonInputProcessType::Damage:
            return JsonOutputType::Damage;
        case JsonInputProcessType::Physics:
            return JsonOutputType::Physics;
        default:
            throw runtime_error("Unsupported processType");
    }
}

void WriteToLogFile(
    const vector<reference_wrapper<Event>>& events)
{
    if (events.empty())
    {
        return;
    }

    ofstream logFile;

    // Open file and append if already exists.
    logFile.open(logOutputFilePath, ios::app);

    for (const auto& eventReference : events)
    {
        const auto& event = eventReference.get();

        logFile << GetEventTypeString(event.GetEventType()) << ": " << event.GetMessage() << endl;
    }
}

string GetEventTypeString(
    const EventType eventType)
{
    switch (eventType)
    {
        case EventType::Warning:
            return "Warning";
        case EventType::Error:
            return "Error";
        default:
            throw runtime_error("Unsupported EventType");
    }
}

void CloseApplicationAfterUnhandledError()
{
    const auto events = EventRegistry::Flush();
    WriteToLogFile(GetEventReferences(events));
}

void UnhandledErrorHandler()
{
    EventRegistry::Register(make_unique<Event>("An unhandled error occurred in the Showcase. No stacktrace available.", EventType::Error));

    CloseApplicationAfterUnhandledError();

    _exit(-1);
}

vector<reference_wrapper<Event>> GetEventReferences(
    const vector<unique_ptr<Event>>& events
)
{
    vector<reference_wrapper<Event>> eventReferences;

    eventReferences.reserve(events.size());

    for (const auto& event : events)
    {
        eventReferences.emplace_back(*event);
    }

    return eventReferences;
}
