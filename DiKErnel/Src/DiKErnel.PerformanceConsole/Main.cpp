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

#include "CalculationInputBuilder.h"
#include "Calculator.h"

using namespace DiKErnel::Core;
using namespace DiKErnel::Integration;

using namespace std;
using namespace std::chrono;

#pragma region Forward declarations

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
        9, AsphaltRevetmentTopLayerType::HydraulicAsphaltConcrete, 1.75, 60, 0.3, 16000);

    builder->AddAsphaltWaveImpactLocation(std::move(locationConstructionProperties));

    builder->AddTimeStep(0, 1000, 1, 1, 1, 1);
    builder->AddTimeStep(1000, 2000, 1, 1, 1, 1);
    builder->AddTimeStep(2000, 3000, 1, 1, 1, 1);

    const auto input = builder->Build();

    Calculator calculator(*input->GetData());

    calculator.WaitForCompletion();


    return 0;
}
