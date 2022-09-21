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

#include "JsonInputGrassOvertoppingCalculationDefinitionData.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    using namespace std;

    JsonInputGrassOvertoppingCalculationDefinitionData::JsonInputGrassOvertoppingCalculationDefinitionData(
        unique_ptr<double> failureNumber,
        map<JsonInputGrassRevetmentTopLayerType, unique_ptr<JsonInputGrassCumulativeOverloadTopLayerDefinitionData>>
        topLayerDefinitionData)
        : JsonInputCalculationDefinitionData(move(failureNumber)),
          _topLayerDefinitionData(move(topLayerDefinitionData))
    {
        for (const auto& [topLayerType, topLayerDefinition] : _topLayerDefinitionData)
        {
            _topLayerDefinitionDataReferences.insert(
                pair<JsonInputGrassRevetmentTopLayerType, reference_wrapper<JsonInputGrassCumulativeOverloadTopLayerDefinitionData>>(
                    topLayerType, *topLayerDefinition));
        }
    }

    #pragma region Set methods

    void JsonInputGrassOvertoppingCalculationDefinitionData::SetDikeHeight(
        unique_ptr<double> dikeHeight)
    {
        _dikeHeight = move(dikeHeight);
    }

    void JsonInputGrassOvertoppingCalculationDefinitionData::SetAccelerationAlphaAForCrest(
        unique_ptr<double> accelerationAlphaAForCrest)
    {
        _accelerationAlphaAForCrest = move(accelerationAlphaAForCrest);
    }

    void JsonInputGrassOvertoppingCalculationDefinitionData::SetAccelerationAlphaAForInnerSlope(
        unique_ptr<double> accelerationAlphaAForInnerSlope)
    {
        _accelerationAlphaAForInnerSlope = move(accelerationAlphaAForInnerSlope);
    }

    void JsonInputGrassOvertoppingCalculationDefinitionData::SetFixedNumberOfWaves(
        unique_ptr<int> fixedNumberOfWaves)
    {
        _fixedNumberOfWaves = move(fixedNumberOfWaves);
    }

    void JsonInputGrassOvertoppingCalculationDefinitionData::SetFrontVelocity(
        unique_ptr<double> frontVelocity)
    {
        _frontVelocity = move(frontVelocity);
    }

    void JsonInputGrassOvertoppingCalculationDefinitionData::SetFactorCtm(
        unique_ptr<double> factorCtm)
    {
        _factorCtm = move(factorCtm);
    }

    const map<JsonInputGrassRevetmentTopLayerType, reference_wrapper<JsonInputGrassCumulativeOverloadTopLayerDefinitionData>>&
    JsonInputGrassOvertoppingCalculationDefinitionData::GetTopLayerDefinitionData() const
    {
        return _topLayerDefinitionDataReferences;
    }

    #pragma endregion

    #pragma region Get methods

    const double* JsonInputGrassOvertoppingCalculationDefinitionData::GetDikeHeight() const
    {
        return _dikeHeight.get();
    }

    const double* JsonInputGrassOvertoppingCalculationDefinitionData::GetAccelerationAlphaAForCrest() const
    {
        return _accelerationAlphaAForCrest.get();
    }

    const double* JsonInputGrassOvertoppingCalculationDefinitionData::GetAccelerationAlphaAForInnerSlope() const
    {
        return _accelerationAlphaAForInnerSlope.get();
    }

    const int* JsonInputGrassOvertoppingCalculationDefinitionData::GetFixedNumberOfWaves() const
    {
        return _fixedNumberOfWaves.get();
    }

    const double* JsonInputGrassOvertoppingCalculationDefinitionData::GetFrontVelocity() const
    {
        return _frontVelocity.get();
    }

    const double* JsonInputGrassOvertoppingCalculationDefinitionData::GetFactorCtm() const
    {
        return _factorCtm.get();
    }

    #pragma endregion
}
