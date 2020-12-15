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

#include <iostream>
#include <string>
#include <thread>
#include "Calculator.h"
#include "InputComposer.h"
#include "InputData.h"
#include "NaturalStoneRevetment.h"

using namespace std;
using namespace DiKErnel::Core;
using namespace DiKErnel::FunctionLibrary;
using namespace DiKErnel::KernelWrapper::Json;

enum class UserInput
{
    None,
    Cancel,
    Progress
};

#pragma region Forward declarations

void InputMethod(
    const atomic<bool>& calculationFinished,
    atomic<UserInput>& userInput);

#pragma endregion

int main()
{
    string jsonFilePath;
    std::atomic<bool> calculationFinished(false);
    std::atomic<UserInput> userInput;

    cout << "|===================|" << endl;
    cout << "| Calculation input |" << endl;
    cout << "|===================|" << endl;
    cout << "-> Enter the path to the JSON file: ";
    getline(cin, jsonFilePath);
    cout << endl;

    const auto inputData = InputComposer::GetDomainParametersFromJson(jsonFilePath);

    const auto times = inputData->GetCalculationData()->GetTimes();
    const auto locations = inputData->GetLocations();
    const auto* hydraulicLoads = inputData->GetHydraulicLoads();
    const auto boundariesPerTimeStep = hydraulicLoads->GetBoundaryConditionsPerTimeStep();

    auto timeSteps = std::vector<std::tuple<int, int, BoundaryConditionsPerTimeStep*>>();

    for (auto i = 0; i < times.size() - 1; i++)
    {
        timeSteps.emplace_back(times[i], times[i + 1], boundariesPerTimeStep[i]);
    }

    cout << "|===========|" << endl;
    cout << "| Read data |" << endl;
    cout << "|===========|" << endl;
    cout << "-> Number of time steps: " << timeSteps.size() << endl;
    cout << "-> Number of locations: " << locations.size() << endl << endl;

    // Start stopwatch
    const auto start = std::chrono::high_resolution_clock::now();

    // Write start message
    cout << "|=====================|" << endl;
    cout << "| Calculation started |" << endl;
    cout << "|=====================|" << endl;
    cout << "-> Enter 'p' to show the current progress" << endl;
    cout << "-> Enter 'c' to cancel the calculation" << endl << endl;

    Calculator calculator(
        locations,
        timeSteps,
        hydraulicLoads,
        &NaturalStoneRevetment::CalculateDamage);

    thread inputThread(
        InputMethod,
        ref(calculationFinished),
        ref(userInput));

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

    calculator.WaitForCompletion();

    // Write end message
    if (calculator.IsCancelled())
    {
        cout << endl;
        cout << "|=======================|" << endl;
        cout << "| Calculation cancelled |" << endl;
        cout << "|=======================|" << endl;
    }
    else
    {
        cout << endl;
        cout << "|========================|" << endl;
        cout << "| Calculation successful |" << endl;
        cout << "|========================|" << endl;
    }

    // End stopwatch
    const auto end = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double> elapsed = end - start;
    cout << "=> Time elapsed: " << elapsed.count() << endl << endl;

    // Notify thread being finished
    calculationFinished = true;

    cout << endl << "Press 'Enter' to exit the application.";

    inputThread.join();

    return 0;
}

void InputMethod(
    const atomic<bool>& calculationFinished,
    atomic<UserInput>& userInput)
{
    string input;

    while (!calculationFinished)
    {
        std::getline(std::cin, input);

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
