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

    void JsonInputGrassWaveImpactCalculationDefinitionData::SetMinimumWaveHeightTemax(
        unique_ptr<double> minimumWaveHeightTemax)
    {
        _minimumWaveHeightTemax = move(minimumWaveHeightTemax);
    }

    void JsonInputGrassWaveImpactCalculationDefinitionData::SetMaximumWaveHeightTemin(
        unique_ptr<double> maximumWaveHeightTemin)
    {
        _maximumWaveHeightTemin = move(maximumWaveHeightTemin);
    }

    void JsonInputGrassWaveImpactCalculationDefinitionData::SetWaveAngleImpactNwa(
        unique_ptr<double> waveAngleImpactNwa)
    {
        _waveAngleImpactNwa = move(waveAngleImpactNwa);
    }

    void JsonInputGrassWaveImpactCalculationDefinitionData::SetWaveAngleImpactQwa(
        unique_ptr<double> waveAngleImpactQwa)
    {
        _waveAngleImpactQwa = move(waveAngleImpactQwa);
    }

    void JsonInputGrassWaveImpactCalculationDefinitionData::SetWaveAngleImpactRwa(
        unique_ptr<double> waveAngleImpactRwa)
    {
        _waveAngleImpactRwa = move(waveAngleImpactRwa);
    }

    void JsonInputGrassWaveImpactCalculationDefinitionData::SetUpperLimitLoadingAul(
        unique_ptr<double> upperLimitLoadingAul)
    {
        _upperLimitLoadingAul = move(upperLimitLoadingAul);
    }

    void JsonInputGrassWaveImpactCalculationDefinitionData::SetLowerLimitLoadingAll(
        unique_ptr<double> lowerLimitLoadingAll)
    {
        _lowerLimitLoadingAll = move(lowerLimitLoadingAll);
    }

    const map<JsonInputGrassRevetmentTopLayerType, reference_wrapper<JsonInputGrassWaveImpactTopLayerDefinitionData>>&
    JsonInputGrassWaveImpactCalculationDefinitionData::GetTopLayerDefinitionData() const
    {
        return _topLayerDefinitionDataReferences;
    }

    #pragma endregion

    #pragma region Get methods

    const double* JsonInputGrassWaveImpactCalculationDefinitionData::GetMinimumWaveHeightTemax() const
    {
        return _minimumWaveHeightTemax.get();
    }

    const double* JsonInputGrassWaveImpactCalculationDefinitionData::GetMaximumWaveHeightTemin() const
    {
        return _maximumWaveHeightTemin.get();
    }

    const double* JsonInputGrassWaveImpactCalculationDefinitionData::GetWaveAngleImpactNwa() const
    {
        return _waveAngleImpactNwa.get();
    }

    const double* JsonInputGrassWaveImpactCalculationDefinitionData::GetWaveAngleImpactQwa() const
    {
        return _waveAngleImpactQwa.get();
    }

    const double* JsonInputGrassWaveImpactCalculationDefinitionData::GetWaveAngleImpactRwa() const
    {
        return _waveAngleImpactRwa.get();
    }

    const double* JsonInputGrassWaveImpactCalculationDefinitionData::GetUpperLimitLoadingAul() const
    {
        return _upperLimitLoadingAul.get();
    }

    const double* JsonInputGrassWaveImpactCalculationDefinitionData::GetLowerLimitLoadingAll() const
    {
        return _lowerLimitLoadingAll.get();
    }

    #pragma endregion
}
