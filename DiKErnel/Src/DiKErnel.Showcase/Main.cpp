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

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>

#include "Calculator.h"
#include "EventRegistry.h"
#include "JsonInputComposer.h"
#include "JsonOutputComposer.h"
#include "Validator.h"

using namespace DiKErnel::Core;
using namespace DiKErnel::KernelWrapper::Json::Input;
using namespace DiKErnel::KernelWrapper::Json::Output;
using namespace DiKErnel::Util;
using namespace std;

enum class UserInput
{
    None,
    Cancel,
    Progress
};

#pragma region Forward declarations

void InputMethod(
    const atomic<bool>&,
    atomic<UserInput>&);

JsonOutputType ConvertProcessType(
    JsonInputProcessType);

void WriteToLogFile(
    const string& filePath,
    const vector<reference_wrapper<Event>>& events);

string GetEventTypeString(
    EventType eventType);

void CloseApplication(
    const string& logOutputPath);

void UnhandledErrorHandler();

#pragma endregion

string logOutputPath;

int main()
{
    set_terminate(UnhandledErrorHandler);

    try
    {
        string jsonFilePath;
        atomic<UserInput> userInput;
        atomic calculationFinished(false);

        #pragma region Reading calculation input

        // Obtain input file path
        cout << "|===================|" << endl;
        cout << "| Calculation input |" << endl;
        cout << "|===================|" << endl;
        cout << "-> Enter the path to the Json file: ";
        getline(cin, jsonFilePath);
        cout << endl;

        // Determine output file path
        const auto timeStamp = chrono::system_clock::now();
        const auto milliseconds = chrono::duration_cast<chrono::milliseconds>(timeStamp.time_since_epoch());
        const auto outputDirectory = filesystem::path(jsonFilePath).parent_path();
        const auto outputFileNameBase = "output-" + to_string(milliseconds.count() % 1000);

        // Read input Json file
        const auto inputComposerResult = JsonInputComposer::GetInputDataFromJson(jsonFilePath);

        // Write to log file
        logOutputPath = (outputDirectory / (outputFileNameBase + ".txt")).u8string();
        WriteToLogFile(logOutputPath, inputComposerResult->GetEvents());

        // Handle error during read operation
        if (!inputComposerResult->GetSuccessful())
        {
            cout << "|=====================|" << endl;
            cout << "| Reading data failed |" << endl;
            cout << "|=====================|" << endl;
            cout << "-> An error occurred. See the log file for details" << endl;

            CloseApplication(logOutputPath);
            return -1;
        }

        const auto* inputData = inputComposerResult->GetData();
        const auto& calculationInput = inputData->GetCalculationInput();

        // Write user feedback
        cout << "|===========|" << endl;
        cout << "| Read data |" << endl;
        cout << "|===========|" << endl;
        cout << "-> Number of read time steps: " << calculationInput.GetTimeDependentInputItems().size() - 1 << endl;
        cout << "-> Number of read locations: " << calculationInput.GetLocationDependentInputItems().size() << endl << endl;

        #pragma endregion

        #pragma region Performing validation

        const auto validationResult = Validator::Validate(calculationInput);

        // Write to log file
        WriteToLogFile(logOutputPath, validationResult->GetEvents());

        // Handle error during validation
        if (!validationResult->GetSuccessful())
        {
            cout << "|===================|" << endl;
            cout << "| Validation failed |" << endl;
            cout << "|===================|" << endl;
            cout << "-> An error occurred. See the log file for details" << endl;

            CloseApplication(logOutputPath);
            return -1;
        }

        cout << "|=======================|" << endl;
        cout << "| Validation successful |" << endl;
        cout << "|=======================|" << endl;

        if (*validationResult->GetData() == ValidationResultType::Successful)
        {
            cout << "-> Data is valid" << endl << endl;
        }
        else
        {
            cout << "-> Data is invalid" << endl;
            cout << "-> See the log file for details" << endl;
        }

        #pragma endregion

        #pragma region Performing calculation

        // Start stopwatch
        const auto start = chrono::high_resolution_clock::now();

        // Write start message for the calculation
        cout << "|=====================|" << endl;
        cout << "| Calculation started |" << endl;
        cout << "|=====================|" << endl;
        cout << "-> Enter 'p' to show the current progress" << endl;
        cout << "-> Enter 'c' to cancel the calculation" << endl << endl;

        // Start calculation on separate thread
        Calculator calculator(calculationInput);

        // Start obtaining user input on separate thread
        thread inputThread(
            InputMethod,
            ref(calculationFinished),
            ref(userInput));

        // Handle user input while the calculation is running
        while (calculator.GetCalculationState() == CalculationState::Running)
        {
            if (userInput == UserInput::Cancel)
            {
                calculator.Cancel();
                userInput = UserInput::None;
            }

            if (userInput == UserInput::Progress)
            {
                cout << "Current progress = " << calculator.GetProgress() << "%" << endl;
                userInput = UserInput::None;
            }
        }

        // Wait for actual completion of the calculation thread
        calculator.WaitForCompletion();

        // Write to log file
        const auto calculatorResult = calculator.GetResult();
        WriteToLogFile(logOutputPath, calculatorResult->GetEvents());

        #pragma endregion

        #pragma region Handling cancelled calculation

        if (calculator.GetCalculationState() == CalculationState::Cancelled)
        {
            cout << "|=======================|" << endl;
            cout << "| Calculation cancelled |" << endl;
            cout << "|=======================|" << endl;

            CloseApplication(logOutputPath);
            return -1;
        }

        #pragma endregion

        #pragma region Handling calculation that finished in error

        if (calculator.GetCalculationState() == CalculationState::FinishedInError)
        {
            cout << "|====================|" << endl;
            cout << "| Calculation failed |" << endl;
            cout << "|====================|" << endl;
            cout << "-> An error occurred. See the log file for details" << endl;

            CloseApplication(logOutputPath);
            return -1;
        }

        #pragma endregion

        #pragma region Writing calculation output

        // Determine output file path
        const auto jsonOutputPath = outputDirectory / (outputFileNameBase + ".json");

        // Write output Json file
        const auto outputComposerResult = JsonOutputComposer::WriteCalculationOutputToJson(jsonOutputPath.u8string(),
                                                                                           *calculatorResult->GetData(),
                                                                                           ConvertProcessType(inputData->GetProcessType()));

        // Write to log file
        WriteToLogFile(logOutputPath, outputComposerResult->GetEvents());

        // Handle error during write operation
        if (!outputComposerResult->GetSuccessful())
        {
            cout << "|================|" << endl;
            cout << "| Writing failed |" << endl;
            cout << "|================|" << endl;
            cout << "-> An error occurred. See the log file for details" << endl;

            CloseApplication(logOutputPath);
            return -1;
        }

        #pragma endregion

        #pragma region Writing final user feedback

        cout << "|========================|" << endl;
        cout << "| Calculation successful |" << endl;
        cout << "|========================|" << endl;
        cout << "-> Calculation output is written to: " << jsonOutputPath << endl;

        // End stopwatch and write the elapsed time since the start of the calculation
        const auto end = chrono::high_resolution_clock::now();
        const chrono::duration<double> elapsed = end - start;
        cout << "-> Time elapsed: " << elapsed.count() << endl << endl;

        // Notify calculation thread being finished
        calculationFinished = true;

        // Write closing message
        CloseApplication(logOutputPath);

        // Wait for actual completion of the user input thread
        inputThread.join();

        #pragma endregion

        return 0;
    }
    catch (const exception& e)
    {
        EventRegistry::Register(make_unique<Event>("An unhandled error occurred in the showcase. See stack trace for more information:\n"
                                                   + static_cast<string>(e.what()), EventType::Error));
        const auto result = make_unique<SimpleResult>(false, EventRegistry::Flush());
        WriteToLogFile(logOutputPath, result->GetEvents());

        cout << "-> An error occurred. See the log file for details" << endl;

        CloseApplication(logOutputPath);

        return -1;
    }
}

void InputMethod(
    const atomic<bool>& calculationFinished,
    atomic<UserInput>& userInput)
{
    string input;

    while (!calculationFinished)
    {
        getline(cin, input);

        if (input == "c")
        {
            userInput = UserInput::Cancel;
        }

        if (input == "p")
        {
            userInput = UserInput::Progress;
        }
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
    const string& filePath,
    const vector<reference_wrapper<Event>>& events)
{
    if (events.empty())
    {
        return;
    }

    ofstream logFile;

    // Open file and append if already exists.
    logFile.open(filePath, ios::app);

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
    }
    return "";
}

void CloseApplication(
    const string& logOutputPath)
{
    cout << "-> The log file is written to: " << logOutputPath << endl;
    cout << endl << "Press 'Enter' to exit the application.";
    cin.get();
}

void UnhandledErrorHandler()
{
    EventRegistry::Register(make_unique<Event>("An unhandled error occurred in the Showcase. No stacktrace available.", EventType::Error));
    const auto result = make_unique<SimpleResult>(false, EventRegistry::Flush());
    WriteToLogFile(logOutputPath, result->GetEvents());

    cout << "-> An error occurred. See the log file for details" << endl;

    CloseApplication(logOutputPath);

    exit(-1);
}
