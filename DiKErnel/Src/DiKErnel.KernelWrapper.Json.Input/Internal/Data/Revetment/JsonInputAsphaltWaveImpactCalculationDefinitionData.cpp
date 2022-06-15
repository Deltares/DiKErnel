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

#include "JsonInputAsphaltWaveImpactCalculationDefinitionData.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    using namespace std;

    JsonInputAsphaltWaveImpactCalculationDefinitionData::JsonInputAsphaltWaveImpactCalculationDefinitionData(
        unique_ptr<double> failureNumber,
        map<JsonInputAsphaltRevetmentTopLayerType, unique_ptr<JsonInputAsphaltWaveImpactTopLayerDefinitionData>> topLayerDefinitionData)
        : JsonInputCalculationDefinitionData(move(failureNumber)),
          _topLayerDefinitionData(move(topLayerDefinitionData))
    {
        for (const auto& [topLayerType, topLayerDefinition] : _topLayerDefinitionData)
        {
            _topLayerDefinitionDataReferences.insert(
                pair<JsonInputAsphaltRevetmentTopLayerType, reference_wrapper<JsonInputAsphaltWaveImpactTopLayerDefinitionData>>(
                    topLayerType, *topLayerDefinition));
        }
    }

    #pragma region Set methods

    void JsonInputAsphaltWaveImpactCalculationDefinitionData::SetDensityOfWater(
        unique_ptr<double> densityOfWater)
    {
        _densityOfWater = move(densityOfWater);
    }

    void JsonInputAsphaltWaveImpactCalculationDefinitionData::SetAverageNumberOfWavesCtm(
        unique_ptr<double> averageNumberOfWavesCtm)
    {
        _averageNumberOfWavesCtm = move(averageNumberOfWavesCtm);
    }

    void JsonInputAsphaltWaveImpactCalculationDefinitionData::SetImpactNumberC(
        unique_ptr<double> impactNumberC)
    {
        _impactNumberC = move(impactNumberC);
    }

    void JsonInputAsphaltWaveImpactCalculationDefinitionData::SetWidthFactors(
        unique_ptr<vector<pair<double, double>>> widthFactors)
    {
        _widthFactors = move(widthFactors);
    }

    void JsonInputAsphaltWaveImpactCalculationDefinitionData::SetDepthFactors(
        unique_ptr<vector<pair<double, double>>> depthFactors)
    {
        _depthFactors = move(depthFactors);
    }

    void JsonInputAsphaltWaveImpactCalculationDefinitionData::SetImpactFactors(
        unique_ptr<vector<pair<double, double>>> impactFactors)
    {
        _impactFactors = move(impactFactors);
    }

    #pragma endregion

    #pragma region Get methods

    const map<JsonInputAsphaltRevetmentTopLayerType, reference_wrapper<JsonInputAsphaltWaveImpactTopLayerDefinitionData>>&
    JsonInputAsphaltWaveImpactCalculationDefinitionData::GetTopLayerDefinitionData() const
    {
        return _topLayerDefinitionDataReferences;
    }

    const double* JsonInputAsphaltWaveImpactCalculationDefinitionData::GetDensityOfWater() const
    {
        return _densityOfWater.get();
    }

    const double* JsonInputAsphaltWaveImpactCalculationDefinitionData::GetAverageNumberOfWavesCtm() const
    {
        return _averageNumberOfWavesCtm.get();
    }

    const double* JsonInputAsphaltWaveImpactCalculationDefinitionData::GetImpactNumberC() const
    {
        return _impactNumberC.get();
    }

    const vector<pair<double, double>>* JsonInputAsphaltWaveImpactCalculationDefinitionData::GetWidthFactors() const
    {
        return _widthFactors.get();
    }

    const vector<pair<double, double>>* JsonInputAsphaltWaveImpactCalculationDefinitionData::GetDepthFactors() const
    {
        return _depthFactors.get();
    }

    const vector<pair<double, double>>* JsonInputAsphaltWaveImpactCalculationDefinitionData::GetImpactFactors() const
    {
        return _impactFactors.get();
    }

    #pragma endregion
}
