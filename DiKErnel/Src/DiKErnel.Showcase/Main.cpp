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
#include <thread>
#include <string>
#include "Calculator.h"

using namespace std;
using namespace DiKErnel::Core;

enum UserInput
{
	None,
	Cancel,
	Progress
};

void InputMethod(
	atomic<bool>& calculationFinished,
	atomic<UserInput>& userInput)
{
	string input;

	while (!calculationFinished)
	{
		std::getline(std::cin, input);

		if (input == "c")
		{
			userInput = Cancel;
		}

		if (input == "p")
		{
			userInput = Progress;
		}
	}
}

void SubCalculation()
{
	for (auto k = 0; k < 10000000; k++)
	{
		tanf(sqrt(k));
	}
}

int main()
{
	auto numberOfLocations = 0;
	auto numberOfTimeSteps = 0;
	std::atomic<bool> calculationFinished(false);
	std::atomic<UserInput> userInput;

	cout << "|===================|" << endl;
	cout << "| Calculation input |" << endl;
	cout << "|===================|" << endl;
	cout << "-> Enter the number of locations: ";
	cin >> numberOfLocations;
	cout << "-> Enter the number of time steps: ";
	cin >> numberOfTimeSteps;
	cout << endl;

	// Start stopwatch
	const auto start = std::chrono::high_resolution_clock::now();

	// Write start message
	cout << "|=====================|" << endl;
	cout << "| Calculation started |" << endl;
	cout << "|=====================|" << endl;
	cout << "-> Enter 'p' to show the current progress" << endl;
	cout << "-> Enter 'c' to cancel the calculation" << endl << endl;

    Calculator calculator(
		numberOfLocations,
		numberOfTimeSteps,
		SubCalculation);

	thread inputThread(
		InputMethod,
		ref(calculationFinished),
		ref(userInput));

	while (!calculator.IsFinished())
	{
		if (userInput == Cancel)
		{
			calculator.Cancel();
			userInput = None;
		}

		if (userInput == Progress)
		{
			cout << "Current progress = " << calculator.GetProgress() << "%" << endl;
			userInput = None;
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