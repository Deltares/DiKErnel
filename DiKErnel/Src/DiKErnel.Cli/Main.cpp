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
#include <iostream>
#include <string>
#include <thread>

#include "ApplicationHelper.h"
#include "Calculator.h"
#include "CommandLineArgumentParser.h"
#include "EventRegistry.h"
#include "JsonInputComposer.h"
#include "JsonOutputComposer.h"
#include "Validator.h"

using namespace DiKErnel::Application;
using namespace DiKErnel::Cli;
using namespace DiKErnel::Core;
using namespace DiKErnel::KernelWrapper::Json::Input;
using namespace DiKErnel::KernelWrapper::Json::Output;
using namespace DiKErnel::Util;
using namespace std;
using namespace std::chrono;

#pragma region Forward declarations

void RemoveFileWhenExists(
    const string& filePath);

unique_ptr<DataResult<ICalculationInput>> ValidateAndReadInput(
    const string& jsonInputFilePath,
    const CommandLineArgumentParser& parser);

bool ValidateCalculationInput(
    const ICalculationInput& calculationInput);

shared_ptr<DataResult<CalculationOutput>> Calculate(
    const ICalculationInput& calculationInput);

bool WriteOutput(
    const CalculationOutput& calculationOutput,
    const CommandLineArgumentParser& parser,
    duration<double> elapsed);

JsonOutputType ConvertOutputType(
    const string& outputTypeString);

void WriteToLogFile(
    const vector<reference_wrapper<Event>>& events);

string GetEventTypeString(
    EventType eventType);

void CloseApplicationAfterUnhandledError();

[[noreturn]]
void UnhandledErrorHandler();

vector<reference_wrapper<Event>> GetEventReferences(
    const vector<unique_ptr<Event>>& events);

#pragma endregion

string logOutputFilePath;
string unexpectedErrorMessage = "Er is een onverwachte fout opgetreden. Indien gewenst kunt u contact met ons opnemen via dikernel@deltares.nl.";

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
            cout << CommandLineArgumentParser::GetHelpMessage();
            return -1;
        }

        const auto jsonInputFilePath = parser.GetJsonInputFilePath();
        const auto jsonOutputFilePath = parser.GetJsonOutputFilePath();
        logOutputFilePath = parser.GetLogOutputFilePath();

        RemoveFileWhenExists(jsonOutputFilePath);
        RemoveFileWhenExists(logOutputFilePath);

        const auto calculationInputDataResult = ValidateAndReadInput(jsonInputFilePath, parser);

        if(calculationInputDataResult == nullptr)
        {
            return -1;
        }

        const auto& calculationInput = *calculationInputDataResult->GetData();

        if(!ValidateCalculationInput(calculationInput))
        {
            return -1;
        }

        const auto startTime = high_resolution_clock::now();

        const auto calculatorResult = Calculate(calculationInput);

        if (calculatorResult == nullptr)
        {
            return -1;
        }

        const duration<double> elapsed = high_resolution_clock::now() - startTime;

        const auto writeOutputResult = WriteOutput(*calculatorResult->GetData(), parser, elapsed);

        return !writeOutputResult ? -1 : 0;
    }
    catch (const exception&)
    {
        EventRegistry::Register(make_unique<Event>(unexpectedErrorMessage, EventType::Error));

        CloseApplicationAfterUnhandledError();
        return -1;
    }
}

void RemoveFileWhenExists(
    const string& filePath)
{
    if (filesystem::exists(filePath))
    {
        filesystem::remove(filePath);
    }
}

unique_ptr<DataResult<ICalculationInput>> ValidateAndReadInput(
    const string& jsonInputFilePath,
    const CommandLineArgumentParser& parser)
{
    if (parser.GetValidateJsonFormat())
    {
        const auto validationResult = JsonInputComposer::ValidateJson(jsonInputFilePath);

        const auto validationEvents = EventRegistry::Flush();

        WriteToLogFile(GetEventReferences(validationEvents));

        if(!validationResult)
        {
            return nullptr;
        }
    }

    auto inputComposerResult = JsonInputComposer::GetInputDataFromJson(jsonInputFilePath);
    WriteToLogFile(inputComposerResult->GetEvents());

    if (!inputComposerResult->GetSuccessful())
    {
        return nullptr;
    }

    return inputComposerResult;
}

bool ValidateCalculationInput(
    const ICalculationInput& calculationInput)
{
    const auto validationResult = Validator::Validate(calculationInput);
    WriteToLogFile(validationResult->GetEvents());

    return validationResult->GetSuccessful() && *validationResult->GetData() == ValidationResultType::Successful;
}

shared_ptr<DataResult<CalculationOutput>> Calculate(
    const ICalculationInput& calculationInput)
{
    Calculator calculator(calculationInput);
    calculator.WaitForCompletion();

    auto calculatorResult = calculator.GetResult();
    WriteToLogFile(calculatorResult->GetEvents());

    if (calculator.GetCalculationState() == CalculationState::FinishedInError)
    {
        return nullptr;
    }

    return calculatorResult;
}

bool WriteOutput(
    const CalculationOutput& calculationOutput,
    const CommandLineArgumentParser& parser,
    const duration<double> elapsed)
{
    vector<pair<string, variant<double, string>>> metaDataItems;

    if (parser.GetWriteMetaData())
    {
        metaDataItems.emplace_back(pair<string, variant<double, string>>("versie", ApplicationHelper::GetApplicationVersionString()));
        metaDataItems.emplace_back(pair<string, variant<double, string>>("besturingssysteem", ApplicationHelper::GetOperatingSystemName()));
        metaDataItems.emplace_back(pair<string, variant<double, string>>("tijdstipBerekening", ApplicationHelper::GetFormattedDateTimeString()));
        metaDataItems.emplace_back(pair<string, variant<double, string>>("tijdsduurBerekening", elapsed.count()));
    }

    const auto outputComposerResult = JsonOutputComposer::WriteCalculationOutputToJson(
        parser.GetJsonOutputFilePath(),
        calculationOutput,
        ConvertOutputType(parser.GetOutputLevel()),
        metaDataItems);

    WriteToLogFile(outputComposerResult->GetEvents());

    return outputComposerResult->GetSuccessful();
}

JsonOutputType ConvertOutputType(
    const string& outputTypeString)
{
    if (outputTypeString == "falen")
    {
        return JsonOutputType::Failure;
    }

    if (outputTypeString == "schade")
    {
        return JsonOutputType::Damage;
    }

    return JsonOutputType::Physics;
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
    EventRegistry::Register(make_unique<Event>(unexpectedErrorMessage, EventType::Error));

    CloseApplicationAfterUnhandledError();

    _exit(-1);
}

vector<reference_wrapper<Event>> GetEventReferences(
    const vector<unique_ptr<Event>>& events)
{
    vector<reference_wrapper<Event>> eventReferences;

    eventReferences.reserve(events.size());

    for (const auto& event : events)
    {
        eventReferences.emplace_back(*event);
    }

    return eventReferences;
}
