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

#include "JsonInputNaturalStoneTopLayerDefinitionData.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    using namespace std;

    #pragma region Set methods

    void JsonInputNaturalStoneTopLayerDefinitionData::SetStabilityPlungingA(
        unique_ptr<double> stabilityPlungingA)
    {
        _stabilityPlungingA = move(stabilityPlungingA);
    }

    void JsonInputNaturalStoneTopLayerDefinitionData::SetStabilityPlungingB(
        unique_ptr<double> stabilityPlungingB)
    {
        _stabilityPlungingB = move(stabilityPlungingB);
    }

    void JsonInputNaturalStoneTopLayerDefinitionData::SetStabilityPlungingC(
        unique_ptr<double> stabilityPlungingC)
    {
        _stabilityPlungingC = move(stabilityPlungingC);
    }

    void JsonInputNaturalStoneTopLayerDefinitionData::SetStabilityPlungingN(
        unique_ptr<double> stabilityPlungingN)
    {
        _stabilityPlungingN = move(stabilityPlungingN);
    }

    void JsonInputNaturalStoneTopLayerDefinitionData::SetStabilitySurgingA(
        unique_ptr<double> stabilitySurgingA)
    {
        _stabilitySurgingA = move(stabilitySurgingA);
    }

    void JsonInputNaturalStoneTopLayerDefinitionData::SetStabilitySurgingB(
        unique_ptr<double> stabilitySurgingB)
    {
        _stabilitySurgingB = move(stabilitySurgingB);
    }

    void JsonInputNaturalStoneTopLayerDefinitionData::SetStabilitySurgingC(
        unique_ptr<double> stabilitySurgingC)
    {
        _stabilitySurgingC = move(stabilitySurgingC);
    }

    void JsonInputNaturalStoneTopLayerDefinitionData::SetStabilitySurgingN(
        unique_ptr<double> stabilitySurgingN)
    {
        _stabilitySurgingN = move(stabilitySurgingN);
    }

    void JsonInputNaturalStoneTopLayerDefinitionData::SetStabilityXib(
        unique_ptr<double> stabilityXib)
    {
        _stabilityXib = move(stabilityXib);
    }

    #pragma endregion

    #pragma region Get methods

    const double* JsonInputNaturalStoneTopLayerDefinitionData::GetStabilityXib() const
    {
        return _stabilityXib.get();
    }

    const double* JsonInputNaturalStoneTopLayerDefinitionData::GetStabilityPlungingA() const
    {
        return _stabilityPlungingA.get();
    }

    const double* JsonInputNaturalStoneTopLayerDefinitionData::GetStabilityPlungingB() const
    {
        return _stabilityPlungingB.get();
    }

    const double* JsonInputNaturalStoneTopLayerDefinitionData::GetStabilityPlungingC() const
    {
        return _stabilityPlungingC.get();
    }

    const double* JsonInputNaturalStoneTopLayerDefinitionData::GetStabilityPlungingN() const
    {
        return _stabilityPlungingN.get();
    }

    const double* JsonInputNaturalStoneTopLayerDefinitionData::GetStabilitySurgingA() const
    {
        return _stabilitySurgingA.get();
    }

    const double* JsonInputNaturalStoneTopLayerDefinitionData::GetStabilitySurgingB() const
    {
        return _stabilitySurgingB.get();
    }

    const double* JsonInputNaturalStoneTopLayerDefinitionData::GetStabilitySurgingC() const
    {
        return _stabilitySurgingC.get();
    }

    const double* JsonInputNaturalStoneTopLayerDefinitionData::GetStabilitySurgingN() const
    {
        return _stabilitySurgingN.get();
    }

    #pragma endregion
}
