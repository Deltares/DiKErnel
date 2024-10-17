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
#include <functional>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "CalculationInputBuilder.h"
#include "Calculator.h"

using namespace DiKErnel::Core;
using namespace DiKErnel::Integration;
using namespace DiKErnel::Util;

using namespace std;
using namespace std::chrono;

double xStartCalculationZoneOuterSlope = 7;
double xEndCalculationZoneOuterSlope = 11;
double xStartCalculationZoneInnerSlope = 24;
double xEndCalculationZoneInnerSlope = 32;

string asphaltWaveImpactIdentifier = "AsphaltWaveImpact";
string grassWaveImpactIdentifier = "GrassWaveImpact";
string grassWaveOvertoppingRayleighAnalyticalIdentifier = "GrassWaveOvertoppingRayleighAnalytical";
string grassWaveOvertoppingRayleighDiscreteIdentifier = "GrassWaveOvertoppingRayleighDiscrete";
string grassWaveRunupBattjesGroenendijkAnalyticalIdentifier = "GrassWaveRunupBattjesGroenendijkAnalytical";
string grassWaveRunupRayleighDiscreteIdentifier = "GrassWaveRunupRayleighDiscrete";
string naturalStoneWaveImpactIdentifier = "NaturalStoneWaveImpact";

string oneHourTimeStepIdentifier = "1h";
string twelveHoursTimeStepIdentifier = "12h";

#pragma region Forward declarations

void AddDikeProfile(
    const unique_ptr<CalculationInputBuilder>&);

void AddLocations(
    const unique_ptr<CalculationInputBuilder>&,
    const string&,
    int);

vector<double> GetXValues(
    const string&,
    int);

void AddTimeSteps(
    const unique_ptr<CalculationInputBuilder>&,
    const string&);

void AddTimeSteps(
    const unique_ptr<CalculationInputBuilder>&,
    int,
    const string&,
    const string&,
    const string&);

vector<double> GetValuesFromFile(
    const string&);

void CalculateAndWriteOutput(
    const ICalculationInput*,
    const string&);

#pragma endregion

int main(
    const int argc,
    char** argv)
{
    const auto builder = make_unique<CalculationInputBuilder>();

    AddDikeProfile(builder);

    AddLocations(builder, argv[1], stoi(argv[2]));

    AddTimeSteps(builder, argv[3]);

    const auto input = builder->Build();

    CalculateAndWriteOutput(input->GetData(), argv[1]);

    return 0;
}

void AddDikeProfile(
    const unique_ptr<CalculationInputBuilder>& builder)
{
    builder->AddDikeProfileSegment(0, 7.09, 18.39, 13.22, 1);
    builder->AddDikeProfileSegment(18.39, 13.22, 23.39, 13.22, 1);
    builder->AddDikeProfileSegment(23.39, 13.22, 33.05, 0, 1);

    builder->AddDikeProfilePointData(0, CharacteristicPointType::OuterToe);
    builder->AddDikeProfilePointData(18.39, CharacteristicPointType::OuterCrest);
    builder->AddDikeProfilePointData(23.39, CharacteristicPointType::InnerCrest);
    builder->AddDikeProfilePointData(33.05, CharacteristicPointType::InnerToe);
}

void AddLocations(
    const unique_ptr<CalculationInputBuilder>& builder,
    const string& failureMechanismArgument,
    const int numberOfLocations)
{
    function<void(
        double,
        const unique_ptr<CalculationInputBuilder>&)> addLocationAction;

    if (failureMechanismArgument == asphaltWaveImpactIdentifier)
    {
        addLocationAction = [](
            double x,
            const unique_ptr<CalculationInputBuilder>& builderToUse) ->
            void
                {
                    builderToUse->AddAsphaltWaveImpactLocation(make_unique<AsphaltRevetmentWaveImpactLocationConstructionProperties>(
                        x, AsphaltRevetmentTopLayerType::HydraulicAsphaltConcrete, 1.75, 60, 0.3, 16000));
                };
    }
    else if (failureMechanismArgument == grassWaveImpactIdentifier)
    {
        addLocationAction = [](
            double x,
            const unique_ptr<CalculationInputBuilder>& builderToUse) ->
            void
                {
                    builderToUse->AddGrassWaveImpactLocation(make_unique<GrassRevetmentWaveImpactLocationConstructionProperties>(
                        x, GrassRevetmentTopLayerType::OpenSod));
                };
    }
    else if (failureMechanismArgument == grassWaveOvertoppingRayleighAnalyticalIdentifier)
    {
        cout << grassWaveOvertoppingRayleighAnalyticalIdentifier << " not supported in C++";
        exit(0);
    }
    else if (failureMechanismArgument == grassWaveOvertoppingRayleighDiscreteIdentifier)
    {
        addLocationAction = [](
            double x,
            const unique_ptr<CalculationInputBuilder>& builderToUse) ->
            void
            {
                auto grassRevetmentOvertoppingLocationConstructionProperties = make_unique<GrassRevetmentOvertoppingLocationConstructionProperties>(
                    x, GrassRevetmentTopLayerType::OpenSod);

                grassRevetmentOvertoppingLocationConstructionProperties->SetDikeHeight(make_unique<double>(11));

                builderToUse->AddGrassOvertoppingLocation(move(grassRevetmentOvertoppingLocationConstructionProperties));
            };
    }
    else if (failureMechanismArgument == grassWaveRunupBattjesGroenendijkAnalyticalIdentifier)
    {
        cout << grassWaveRunupBattjesGroenendijkAnalyticalIdentifier << " not supported in C++";
        exit(0);
    }
    else if (failureMechanismArgument == grassWaveRunupRayleighDiscreteIdentifier)
    {
        cout << grassWaveRunupRayleighDiscreteIdentifier << " not supported in C++";
        exit(0);
    }
    else if (failureMechanismArgument == naturalStoneWaveImpactIdentifier)
    {
        addLocationAction = [](
            double x,
            const unique_ptr<CalculationInputBuilder>& builderToUse) ->
            void
                {
                    builderToUse->AddNaturalStoneLocation(make_unique<NaturalStoneRevetmentLocationConstructionProperties>(
                        x, NaturalStoneRevetmentTopLayerType::NordicStone, 0.4, 1.65));
                };
    }

    const auto xValues = GetXValues(failureMechanismArgument, numberOfLocations);

    for (int i = 0; i < numberOfLocations; i++)
    {
        addLocationAction(xValues[i], builder);
    }
}

vector<double> GetXValues(
    const string& failureMechanismArgument,
    const int numberOfLocations)
{
    vector<double> xValues;

    double xStartCalculationZone;
    double xEndCalculationZone;

    if (failureMechanismArgument == grassWaveOvertoppingRayleighAnalyticalIdentifier ||
        failureMechanismArgument == grassWaveOvertoppingRayleighDiscreteIdentifier)
    {
        xStartCalculationZone = xStartCalculationZoneInnerSlope;
        xEndCalculationZone = xEndCalculationZoneInnerSlope;
    }
    else
    {
        xStartCalculationZone = xStartCalculationZoneOuterSlope;
        xEndCalculationZone = xEndCalculationZoneOuterSlope;
    }

    switch (numberOfLocations)
    {
        case 1:
            xValues.push_back(xStartCalculationZone + (xEndCalculationZone - xStartCalculationZone) * 1 / 2);
            break;
        case 2:
            xValues.push_back(xStartCalculationZone + (xEndCalculationZone - xStartCalculationZone) * 1 / 3);
            xValues.push_back(xStartCalculationZone + (xEndCalculationZone - xStartCalculationZone) * 2 / 3);
            break;
        default:
        {
            const double increment = (xEndCalculationZone - xStartCalculationZone) / (numberOfLocations - 1);

            for (int i = 0; i < numberOfLocations; i++)
            {
                xValues.push_back(xStartCalculationZone + i * increment);
            }
        }
    }

    return xValues;
}

void AddTimeSteps(
    const unique_ptr<CalculationInputBuilder>& builder,
    const string& timeStepArgument)
{
    if (timeStepArgument == oneHourTimeStepIdentifier)
    {
        AddTimeSteps(builder, 1, "htime_1h.csv", "Hm0_1h.csv", "Tmm10_1h.csv");
    }
    else if (timeStepArgument == twelveHoursTimeStepIdentifier)
    {
        AddTimeSteps(builder, 12, "htime_12h.csv", "Hm0_12h.csv", "Tmm10_12h.csv");
    }
}

void AddTimeSteps(
    const unique_ptr<CalculationInputBuilder>& builder,
    int hours,
    const string& waterLevelsFile,
    const string& waveHeightsFile,
    const string& wavePeriodsFile)
{
    const vector<double> waterLevels = GetValuesFromFile(waterLevelsFile);
    const vector<double> waveHeights = GetValuesFromFile(waveHeightsFile);
    const vector<double> wavePeriods = GetValuesFromFile(wavePeriodsFile);

    double currentStartTime = 0;

    for (int i = 0; i < waterLevels.size(); i++)
    {
        const double currentEndTime = currentStartTime + 3600 * 12;

        builder->AddTimeStep(currentStartTime, currentEndTime, waterLevels[i], waveHeights[i], wavePeriods[i], 0);

        currentStartTime = currentEndTime;
    }
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

void CalculateAndWriteOutput(
    const ICalculationInput* calculationInput,
    const string& failureMechanismArgument)
{
    const auto startTime = high_resolution_clock::now();

    const Calculator calculator(*calculationInput);

    const auto endTime = high_resolution_clock::now();

    const auto locationDependentInputItems = calculationInput->GetLocationDependentInputItems();

    stringstream outputMessage;

    outputMessage << fixed << showpoint << setprecision(2);
    outputMessage << setw(43) << failureMechanismArgument << ";";
    outputMessage << setw(4) << locationDependentInputItems.size() << ";";
    outputMessage << setw(8) << calculationInput->GetTimeDependentInputItems().size() << ";";
    outputMessage << setw(7) << duration<double, milli>(endTime - startTime).count() / 1000.0 << ";";

    const auto& locationDependentOutputItems = calculator.GetResult()->GetData()->GetLocationDependentOutputItems();

    for (int i = 0; i < locationDependentOutputItems.size(); i++)
    {
        auto damages = locationDependentOutputItems[i].get().GetDamages();

        outputMessage << setw(5) << locationDependentInputItems[i].get().GetX() << ";";
        outputMessage << setw(8) << damages[damages.size() - 1] << ";";
    }

    auto outputMessageString = outputMessage.str();

    outputMessageString.pop_back();

    cout << outputMessageString;
}
