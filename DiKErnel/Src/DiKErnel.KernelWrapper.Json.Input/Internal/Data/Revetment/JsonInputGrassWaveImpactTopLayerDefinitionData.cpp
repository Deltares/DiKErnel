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

#include "JsonInputGrassWaveImpactTopLayerDefinitionData.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    using namespace std;

    #pragma region Set methods

    void JsonInputGrassWaveImpactTopLayerDefinitionData::SetTimeLineA(
        unique_ptr<double> timeLineA)
    {
        _timeLineA = move(timeLineA);
    }

    void JsonInputGrassWaveImpactTopLayerDefinitionData::SetTimeLineB(
        unique_ptr<double> timeLineB)
    {
        _timeLineB = move(timeLineB);
    }

    void JsonInputGrassWaveImpactTopLayerDefinitionData::SetTimeLineC(
        unique_ptr<double> timeLineC)
    {
        _timeLineC = move(timeLineC);
    }

    #pragma endregion

    #pragma region Get methods

    const double* JsonInputGrassWaveImpactTopLayerDefinitionData::GetTimeLineA() const
    {
        return _timeLineA.get();
    }

    const double* JsonInputGrassWaveImpactTopLayerDefinitionData::GetTimeLineB() const
    {
        return _timeLineB.get();
    }

    const double* JsonInputGrassWaveImpactTopLayerDefinitionData::GetTimeLineC() const
    {
        return _timeLineC.get();
    }

    #pragma endregion
}
