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

#include <fstream>
#include <iostream>

#include "CalculationInputBuilder.h"
#include "Calculator.h"

using namespace DiKErnel::Core;
using namespace DiKErnel::Integration;

using namespace std;
using namespace std::chrono;

#pragma region Forward declarations

vector<double> GetValuesFromFile(
    const string& fileName);

#pragma endregion

int main(
    const int argc,
    char** argv)
{
    const auto builder = make_unique<CalculationInputBuilder>();

    builder->AddDikeProfileSegment(0, 7.09, 18.39, 13.22, 1);
    builder->AddDikeProfileSegment(18.39, 13.22, 23.39, 13.22, 1);
    builder->AddDikeProfileSegment(23.39, 13.22, 33.05, 0, 1);

    builder->AddDikeProfilePointData(0, CharacteristicPointType::OuterToe);
    builder->AddDikeProfilePointData(18.39, CharacteristicPointType::OuterCrest);
    builder->AddDikeProfilePointData(23.39, CharacteristicPointType::InnerCrest);
    builder->AddDikeProfilePointData(33.05, CharacteristicPointType::InnerToe);

    auto locationConstructionProperties = make_unique<AsphaltRevetmentWaveImpactLocationConstructionProperties>(
        10, AsphaltRevetmentTopLayerType::HydraulicAsphaltConcrete, 1.75, 60, 0.3, 16000);

    builder->AddAsphaltWaveImpactLocation(std::move(locationConstructionProperties));

    const vector<double> waterLevels = GetValuesFromFile("htime_12h.csv");
    const vector<double> waveHeights = GetValuesFromFile("Hm0_12h.csv");
    const vector<double> wavePeriods = GetValuesFromFile("Tmm10_12h.csv");
    const vector<double> waveDirections = GetValuesFromFile("WDir_12h.csv");

    double currentStartTime = 0;

    for (int i = 0; i < waterLevels.size(); i++)
    {
        const double currentEndTime = currentStartTime + 3600 * 12;

        builder->AddTimeStep(currentStartTime, currentEndTime, waterLevels[i], waveHeights[i], wavePeriods[i], waveDirections[i]);

        currentStartTime = currentEndTime;
    }

    const auto input = builder->Build();

    const auto startTime = high_resolution_clock::now();

    Calculator calculator(*input->GetData());

    calculator.WaitForCompletion();

    const auto endTime = high_resolution_clock::now();

    const duration<double, std::milli> ms_double = endTime - startTime;

    const auto result = calculator.GetResult();

    const auto output = result->GetData();

    const auto& locationDependentOutputItems = output->GetLocationDependentOutputItems();

    const auto& damages = locationDependentOutputItems.at(0).get().GetDamages();

    auto finalDamage = damages[damages.size() - 1];

    ofstream out("damages.txt");

    for (double damage : damages)
    {
        out << damage << '\n';
    }

    out.close();

    cout << ms_double.count() / 1000;

    return 0;
}

vector<double> GetValuesFromFile(
    const string& fileName)
{
    vector<double> values;

    ifstream in(fileName);

    string valueString;
    getline(in, valueString, '\n');

    int i = 0;
    int j = valueString.find(',');

    while (j >= 0)
    {
        values.push_back(stod(valueString.substr(i, j - i)));

        i = ++j;

        j = valueString.find(',', j);

        if (j < 0)
        {
            values.push_back(stod(valueString.substr(i, valueString.length())));
        }
    }

    in.close();

    return values;
}
