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

#include "JsonInputAsphaltWaveImpactTopLayerDefinitionData.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    using namespace std;

    #pragma region Set methods

    void JsonInputAsphaltWaveImpactTopLayerDefinitionData::SetFatigueAlpha(
        unique_ptr<double> fatigueAlpha)
    {
        _fatigueAlpha = move(fatigueAlpha);
    }

    void JsonInputAsphaltWaveImpactTopLayerDefinitionData::SetFatigueBeta(
        unique_ptr<double> fatigueBeta)
    {
        _fatigueBeta = move(fatigueBeta);
    }

    void JsonInputAsphaltWaveImpactTopLayerDefinitionData::SetStiffnessRelationNu(
        unique_ptr<double> stiffnessRelationNu)
    {
        _stiffnessRelationNu = move(stiffnessRelationNu);
    }

    #pragma endregion

    #pragma region Get methods

    const double* JsonInputAsphaltWaveImpactTopLayerDefinitionData::GetFatigueAlpha() const
    {
        return _fatigueAlpha.get();
    }

    const double* JsonInputAsphaltWaveImpactTopLayerDefinitionData::GetFatigueBeta() const
    {
        return _fatigueBeta.get();
    }

    const double* JsonInputAsphaltWaveImpactTopLayerDefinitionData::GetStiffnessRelationNu() const
    {
        return _stiffnessRelationNu.get();
    }

    #pragma endregion
}
