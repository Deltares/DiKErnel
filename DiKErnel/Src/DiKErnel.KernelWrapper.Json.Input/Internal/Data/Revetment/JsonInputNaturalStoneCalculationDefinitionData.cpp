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

#include "JsonInputNaturalStoneCalculationDefinitionData.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    using namespace std;

    JsonInputNaturalStoneCalculationDefinitionData::JsonInputNaturalStoneCalculationDefinitionData(
        unique_ptr<double> failureNumber,
        map<JsonInputNaturalStoneRevetmentTopLayerType, unique_ptr<JsonInputNaturalStoneTopLayerDefinitionData>> topLayerDefinitionData)
        : JsonInputCalculationDefinitionData(move(failureNumber)),
          _topLayerDefinitionData(move(topLayerDefinitionData))
    {
        for (const auto& [topLayerType, topLayerDefinition] : _topLayerDefinitionData)
        {
            _topLayerDefinitionDataReferences.insert(
                pair<JsonInputNaturalStoneRevetmentTopLayerType, reference_wrapper<JsonInputNaturalStoneTopLayerDefinitionData>>(
                    topLayerType, *topLayerDefinition));
        }
    }

    #pragma region Set methods

    void JsonInputNaturalStoneCalculationDefinitionData::SetSlopeUpperLevel(
        unique_ptr<double> slopeUpperLevel)
    {
        _slopeUpperLevel = move(slopeUpperLevel);
    }

    void JsonInputNaturalStoneCalculationDefinitionData::SetSlopeLowerLevel(
        unique_ptr<double> slopeLowerLevel)
    {
        _slopeLowerLevel = move(slopeLowerLevel);
    }

    void JsonInputNaturalStoneCalculationDefinitionData::SetUpperLimitLoadingA(
        unique_ptr<double> upperLimitLoadingA)
    {
        _upperLimitLoadingA = move(upperLimitLoadingA);
    }

    void JsonInputNaturalStoneCalculationDefinitionData::SetUpperLimitLoadingB(
        unique_ptr<double> upperLimitLoadingB)
    {
        _upperLimitLoadingB = move(upperLimitLoadingB);
    }

    void JsonInputNaturalStoneCalculationDefinitionData::SetUpperLimitLoadingC(
        unique_ptr<double> upperLimitLoadingC)
    {
        _upperLimitLoadingC = move(upperLimitLoadingC);
    }

    void JsonInputNaturalStoneCalculationDefinitionData::SetLowerLimitLoadingA(
        unique_ptr<double> lowerLimitLoadingA)
    {
        _lowerLimitLoadingA = move(lowerLimitLoadingA);
    }

    void JsonInputNaturalStoneCalculationDefinitionData::SetLowerLimitLoadingB(
        unique_ptr<double> lowerLimitLoadingB)
    {
        _lowerLimitLoadingB = move(lowerLimitLoadingB);
    }

    void JsonInputNaturalStoneCalculationDefinitionData::SetLowerLimitLoadingC(
        unique_ptr<double> lowerLimitLoadingC)
    {
        _lowerLimitLoadingC = move(lowerLimitLoadingC);
    }

    void JsonInputNaturalStoneCalculationDefinitionData::SetDistanceMaximumWaveElevationA(
        unique_ptr<double> distanceMaximumWaveElevationA)
    {
        _distanceMaximumWaveElevationA = move(distanceMaximumWaveElevationA);
    }

    void JsonInputNaturalStoneCalculationDefinitionData::SetDistanceMaximumWaveElevationB(
        unique_ptr<double> distanceMaximumWaveElevationB)
    {
        _distanceMaximumWaveElevationB = move(distanceMaximumWaveElevationB);
    }

    void JsonInputNaturalStoneCalculationDefinitionData::SetNormativeWidthOfWaveImpactA(
        unique_ptr<double> normativeWidthOfWaveImpactA)
    {
        _normativeWidthOfWaveImpactA = move(normativeWidthOfWaveImpactA);
    }

    void JsonInputNaturalStoneCalculationDefinitionData::SetNormativeWidthOfWaveImpactB(
        unique_ptr<double> normativeWidthOfWaveImpactB)
    {
        _normativeWidthOfWaveImpactB = move(normativeWidthOfWaveImpactB);
    }

    void JsonInputNaturalStoneCalculationDefinitionData::SetWaveAngleImpactBetaMax(
        unique_ptr<double> waveAngleImpactBetaMax)
    {
        _waveAngleImpactBetaMax = move(waveAngleImpactBetaMax);
    }

    #pragma endregion

    #pragma region Get methods

    const map<JsonInputNaturalStoneRevetmentTopLayerType, reference_wrapper<JsonInputNaturalStoneTopLayerDefinitionData>>&
    JsonInputNaturalStoneCalculationDefinitionData::GetTopLayerDefinitionData() const
    {
        return _topLayerDefinitionDataReferences;
    }

    const double* JsonInputNaturalStoneCalculationDefinitionData::GetSlopeUpperLevelA() const
    {
        return _slopeUpperLevel.get();
    }

    const double* JsonInputNaturalStoneCalculationDefinitionData::GetSlopeLowerLevelA() const
    {
        return _slopeLowerLevel.get();
    }

    const double* JsonInputNaturalStoneCalculationDefinitionData::GetUpperLimitLoadingA() const
    {
        return _upperLimitLoadingA.get();
    }

    const double* JsonInputNaturalStoneCalculationDefinitionData::GetUpperLimitLoadingB() const
    {
        return _upperLimitLoadingB.get();
    }

    const double* JsonInputNaturalStoneCalculationDefinitionData::GetUpperLimitLoadingC() const
    {
        return _upperLimitLoadingC.get();
    }

    const double* JsonInputNaturalStoneCalculationDefinitionData::GetLowerLimitLoadingA() const
    {
        return _lowerLimitLoadingA.get();
    }

    const double* JsonInputNaturalStoneCalculationDefinitionData::GetLowerLimitLoadingB() const
    {
        return _lowerLimitLoadingB.get();
    }

    const double* JsonInputNaturalStoneCalculationDefinitionData::GetLowerLimitLoadingC() const
    {
        return _lowerLimitLoadingC.get();
    }

    const double* JsonInputNaturalStoneCalculationDefinitionData::GetDistanceMaximumWaveElevationA() const
    {
        return _distanceMaximumWaveElevationA.get();
    }

    const double* JsonInputNaturalStoneCalculationDefinitionData::GetDistanceMaximumWaveElevationB() const
    {
        return _distanceMaximumWaveElevationB.get();
    }

    const double* JsonInputNaturalStoneCalculationDefinitionData::GetNormativeWidthOfWaveImpactA() const
    {
        return _normativeWidthOfWaveImpactA.get();
    }

    const double* JsonInputNaturalStoneCalculationDefinitionData::GetNormativeWidthOfWaveImpactB() const
    {
        return _normativeWidthOfWaveImpactB.get();
    }

    const double* JsonInputNaturalStoneCalculationDefinitionData::GetWaveAngleImpactBetaMax() const
    {
        return _waveAngleImpactBetaMax.get();
    }

    #pragma endregion
}
