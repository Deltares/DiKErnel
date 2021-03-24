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
#include <iostream>
#include <string>
#include <thread>

#include "DeprecatedCalculator.h"
#include "InputComposer.h"
#include "InputData.h"
#include "NaturalStoneRevetmentDeprecated.h"
#include "OutputComposer.h"

using namespace DiKErnel::Core;
using namespace DiKErnel::FunctionLibrary;
using namespace DiKErnel::KernelWrapper::Json;
using namespace std;

enum class UserInput
{
    None,
    Cancel,
    Progress
};

#pragma region Forward declarations

double CalculateDamageWithDelay(
    double,
    double,
    double,
    double,
    double,
    double,
    double,
    double,
    double,
    double,
    double,
    double,
    double,
    double,
    double,
    double,
    double,
    double,
    double);

void InputMethod(
    const atomic<bool>&,
    atomic<UserInput>&);

#pragma endregion

int subCalculationDelay = 0;

int main()
{
    try
    {
        string jsonFilePath;
        atomic<UserInput> userInput;
        atomic<bool> calculationFinished(false);

        // Obtain user input
        cout << "|===================|" << endl;
        cout << "| Calculation input |" << endl;
        cout << "|===================|" << endl;
        cout << "-> Enter the path to the Json file: ";
        getline(cin, jsonFilePath);
        cout << "-> Enter any additional sub-calculation delay (in seconds): ";
        cin >> subCalculationDelay;
        cout << endl;

        // Read input Json file
        const auto inputData = InputComposer::GetDomainParametersFromJson(jsonFilePath);

        // Write user feedback
        cout << "|===========|" << endl;
        cout << "| Read data |" << endl;
        cout << "|===========|" << endl;
        cout << "-> Number of read time steps: " << inputData->GetCalculationData().GetTimes().size() - 1 << endl;
        cout << "-> Number of read locations: " << inputData->GetLocations().size() << endl << endl;

        // Start stopwatch
        const auto start = chrono::high_resolution_clock::now();

        // Write start message for the calculation
        cout << "|=====================|" << endl;
        cout << "| Calculation started |" << endl;
        cout << "|=====================|" << endl;
        cout << "-> Enter 'p' to show the current progress" << endl;
        cout << "-> Enter 'c' to cancel the calculation" << endl << endl;

        // Start calculation on separate thread
        DeprecatedCalculator calculator(
            *inputData,
            CalculateDamageWithDelay);

        // Start obtaining user input on separate thread
        thread inputThread(
            InputMethod,
            ref(calculationFinished),
            ref(userInput));

        // Handle user input until the calculation is finished
        while (!calculator.IsFinished())
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

        // Write end message for the calculation
        if (calculator.IsCancelled())
        {
            cout << endl;
            cout << "|=======================|" << endl;
            cout << "| Calculation cancelled |" << endl;
            cout << "|=======================|" << endl;
        }
        else
        {
            // Determine output file path
            const auto timeStamp = chrono::system_clock::now();
            const auto milliseconds = chrono::duration_cast<chrono::milliseconds>(timeStamp.time_since_epoch());
            const auto outputDirectory = filesystem::path(jsonFilePath).parent_path();
            const auto outputPath = outputDirectory / ("output-" + to_string(milliseconds.count() % 1000) + ".json");

            // Write Json output to file
            const auto outputData = calculator.GetOutputData();
            OutputComposer::WriteParametersToJson(outputPath.u8string(), *outputData, inputData->GetCalculationData().GetTimes());

            cout << endl;
            cout << "|========================|" << endl;
            cout << "| Calculation successful |" << endl;
            cout << "|========================|" << endl;
            cout << "=> Calculation output is written to: " << outputPath << endl;
        }

        // End stopwatch and write the elapsed time since the start of the calculation
        const auto end = chrono::high_resolution_clock::now();
        const chrono::duration<double> elapsed = end - start;
        cout << "=> Time elapsed: " << elapsed.count() << endl << endl;

        // Notify calculation thread being finished
        calculationFinished = true;

        // Write closing message
        cout << endl << "Press 'Enter' to exit the application.";

        // Wait for actual completion of the user input thread
        inputThread.join();

        return 0;
    }
    catch (...)
    {
        return -1;
    }
}

double CalculateDamageWithDelay(
    const double initialDamage,
    const double slopeAngle,
    const double relativeDensity,
    const double thicknessTopLayer,
    const double spectralWaveHeight,
    const double spectralWavePeriod,
    const double waveAngle,
    const double startTime,
    const double endTime,
    const double coefficientPlungingA,
    const double coefficientPlungingB,
    const double coefficientPlungingC,
    const double coefficientPlungingN,
    const double coefficientSurgingA,
    const double coefficientSurgingB,
    const double coefficientSurgingC,
    const double coefficientSurgingN,
    const double waveAngleMaximum,
    const double similarityParameterThreshold)
{
    this_thread::sleep_for(chrono::seconds(subCalculationDelay));

    return NaturalStoneRevetmentDeprecated::CalculateDamage(
        initialDamage,
        slopeAngle,
        relativeDensity,
        thicknessTopLayer,
        spectralWaveHeight,
        spectralWavePeriod,
        waveAngle,
        startTime,
        endTime,
        coefficientPlungingA,
        coefficientPlungingB,
        coefficientPlungingC,
        coefficientPlungingN,
        coefficientSurgingA,
        coefficientSurgingB,
        coefficientSurgingC,
        coefficientSurgingN,
        waveAngleMaximum,
        similarityParameterThreshold);
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
