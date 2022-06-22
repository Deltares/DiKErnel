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

#include "JsonInputGrassWaveImpactCalculationDefinitionData.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    using namespace std;

    JsonInputGrassWaveImpactCalculationDefinitionData::JsonInputGrassWaveImpactCalculationDefinitionData(
        unique_ptr<double> failureNumber,
        map<JsonInputGrassRevetmentTopLayerType, unique_ptr<JsonInputGrassWaveImpactTopLayerDefinitionData>> topLayerDefinitionData)
        : JsonInputCalculationDefinitionData(move(failureNumber)),
          _topLayerDefinitionData(move(topLayerDefinitionData))
    {
        for (const auto& [topLayerType, topLayerDefinition] : _topLayerDefinitionData)
        {
            _topLayerDefinitionDataReferences.insert(
                pair<JsonInputGrassRevetmentTopLayerType, reference_wrapper<JsonInputGrassWaveImpactTopLayerDefinitionData>>(
                    topLayerType, *topLayerDefinition));
        }
    }

    #pragma region Set methods

    void JsonInputGrassWaveImpactCalculationDefinitionData::SetTemax(
        unique_ptr<double> temax)
    {
        _temax = move(temax);
    }

    void JsonInputGrassWaveImpactCalculationDefinitionData::SetTemin(
        unique_ptr<double> temin)
    {
        _temin = move(temin);
    }

    void JsonInputGrassWaveImpactCalculationDefinitionData::SetWaveAngleImpactN(
        unique_ptr<double> waveAngleImpactN)
    {
        _waveAngleImpactN = move(waveAngleImpactN);
    }

    void JsonInputGrassWaveImpactCalculationDefinitionData::SetWaveAngleImpactQ(
        unique_ptr<double> waveAngleImpactQ)
    {
        _waveAngleImpactQ = move(waveAngleImpactQ);
    }

    void JsonInputGrassWaveImpactCalculationDefinitionData::SetWaveAngleImpactR(
        unique_ptr<double> waveAngleImpactR)
    {
        _waveAngleImpactR = move(waveAngleImpactR);
    }

    void JsonInputGrassWaveImpactCalculationDefinitionData::SetUpperLimitLoading(
        unique_ptr<double> upperLimitLoading)
    {
        _upperLimitLoading = move(upperLimitLoading);
    }

    void JsonInputGrassWaveImpactCalculationDefinitionData::SetLowerLimitLoading(
        unique_ptr<double> lowerLimitLoading)
    {
        _lowerLimitLoading = move(lowerLimitLoading);
    }

    const map<JsonInputGrassRevetmentTopLayerType, reference_wrapper<JsonInputGrassWaveImpactTopLayerDefinitionData>>&
    JsonInputGrassWaveImpactCalculationDefinitionData::GetTopLayerDefinitionData() const
    {
        return _topLayerDefinitionDataReferences;
    }

    #pragma endregion

    #pragma region Get methods

    const double* JsonInputGrassWaveImpactCalculationDefinitionData::GetTemax() const
    {
        return _temax.get();
    }

    const double* JsonInputGrassWaveImpactCalculationDefinitionData::GetTemin() const
    {
        return _temin.get();
    }

    const double* JsonInputGrassWaveImpactCalculationDefinitionData::GetWaveAngleImpactN() const
    {
        return _waveAngleImpactN.get();
    }

    const double* JsonInputGrassWaveImpactCalculationDefinitionData::GetWaveAngleImpactQ() const
    {
        return _waveAngleImpactQ.get();
    }

    const double* JsonInputGrassWaveImpactCalculationDefinitionData::GetWaveAngleImpactR() const
    {
        return _waveAngleImpactR.get();
    }

    const double* JsonInputGrassWaveImpactCalculationDefinitionData::GetUpperLimitLoading() const
    {
        return _upperLimitLoading.get();
    }

    const double* JsonInputGrassWaveImpactCalculationDefinitionData::GetLowerLimitLoading() const
    {
        return _lowerLimitLoading.get();
    }

    #pragma endregion
}
