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
          _topLayerDefinitionData(move(topLayerDefinitionData)) {}

    #pragma region Set methods

    void JsonInputGrassOvertoppingCalculationDefinitionData::SetDikeHeight(
        unique_ptr<double> dikeHeight)
    {
        _dikeHeight = move(dikeHeight);
    }

    void JsonInputGrassOvertoppingCalculationDefinitionData::SetAccelerationAlphaACrest(
        unique_ptr<double> accelerationAlphaACrest)
    {
        _accelerationAlphaACrest = move(accelerationAlphaACrest);
    }

    void JsonInputGrassOvertoppingCalculationDefinitionData::SetAccelerationAlphaAInnerSlope(
        unique_ptr<double> accelerationAlphaAInnerSlope)
    {
        _accelerationAlphaAInnerSlope = move(accelerationAlphaAInnerSlope);
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

    #pragma endregion

    #pragma region Get methods

    const double* JsonInputGrassOvertoppingCalculationDefinitionData::GetDikeHeight() const
    {
        return _dikeHeight.get();
    }

    const double* JsonInputGrassOvertoppingCalculationDefinitionData::GetAccelerationAlphaACrest() const
    {
        return _accelerationAlphaACrest.get();
    }

    const double* JsonInputGrassOvertoppingCalculationDefinitionData::GetAccelerationAlphaAInnerSlope() const
    {
        return _accelerationAlphaAInnerSlope.get();
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
