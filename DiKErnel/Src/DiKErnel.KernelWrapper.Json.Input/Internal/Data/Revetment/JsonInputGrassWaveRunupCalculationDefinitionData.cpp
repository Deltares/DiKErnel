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

#include "JsonInputGrassWaveRunupCalculationDefinitionData.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    using namespace std;

    JsonInputGrassWaveRunupCalculationDefinitionData::JsonInputGrassWaveRunupCalculationDefinitionData(
        unique_ptr<double> failureNumber,
        unique_ptr<JsonInputGrassWaveRunupCalculationProtocolData> calculationProtocolData,
        map<JsonInputGrassRevetmentTopLayerType, unique_ptr<JsonInputGrassWaveRunupTopLayerDefinitionData>> topLayerDefinitionData)
        : JsonInputCalculationDefinitionData(move(failureNumber)),
          _calculationProtocolData(move(calculationProtocolData)),
          _topLayerDefinitionData(move(topLayerDefinitionData))
    {
        for (const auto& [topLayerType, topLayerDefinition] : _topLayerDefinitionData)
        {
            _topLayerDefinitionDataReferences.insert(
                pair<JsonInputGrassRevetmentTopLayerType, reference_wrapper<JsonInputGrassWaveRunupTopLayerDefinitionData>>(
                    topLayerType, *topLayerDefinition));
        }
    }

    #pragma region Set methods

    void JsonInputGrassWaveRunupCalculationDefinitionData::SetFactorCtm(
        unique_ptr<double> factorCtm)
    {
        _factorCtm = move(factorCtm);
    }

    void JsonInputGrassWaveRunupCalculationDefinitionData::SetRepresentativeWaveRunup2PA(
        unique_ptr<double> representativeWaveRunup2PA)
    {
        _representativeWaveRunup2PA = move(representativeWaveRunup2PA);
    }

    void JsonInputGrassWaveRunupCalculationDefinitionData::SetRepresentativeWaveRunup2PB(
        unique_ptr<double> representativeWaveRunup2PB)
    {
        _representativeWaveRunup2PB = move(representativeWaveRunup2PB);
    }

    void JsonInputGrassWaveRunupCalculationDefinitionData::SetRepresentativeWaveRunup2PC(
        unique_ptr<double> representativeWaveRunup2PC)
    {
        _representativeWaveRunup2PC = move(representativeWaveRunup2PC);
    }

    void JsonInputGrassWaveRunupCalculationDefinitionData::SetWaveAngleImpactABeta(
        unique_ptr<double> waveAngleImpactABeta)
    {
        _waveAngleImpactABeta = move(waveAngleImpactABeta);
    }

    void JsonInputGrassWaveRunupCalculationDefinitionData::SetWaveAngleImpactBetaMax(
        unique_ptr<double> waveAngleImpactBetaMax)
    {
        _waveAngleImpactBetaMax = move(waveAngleImpactBetaMax);
    }

    const JsonInputGrassWaveRunupCalculationProtocolData* JsonInputGrassWaveRunupCalculationDefinitionData::GetCalculationProtocolData() const
    {
        return _calculationProtocolData.get();
    }

    const map<JsonInputGrassRevetmentTopLayerType, reference_wrapper<JsonInputGrassWaveRunupTopLayerDefinitionData>>&
    JsonInputGrassWaveRunupCalculationDefinitionData::GetTopLayerDefinitionData() const
    {
        return _topLayerDefinitionDataReferences;
    }

    #pragma endregion

    #pragma region Get methods

    const double* JsonInputGrassWaveRunupCalculationDefinitionData::GetFactorCtm() const
    {
        return _factorCtm.get();
    }

    const double* JsonInputGrassWaveRunupCalculationDefinitionData::GetRepresentativeWaveRunup2PA() const
    {
        return _representativeWaveRunup2PA.get();
    }

    const double* JsonInputGrassWaveRunupCalculationDefinitionData::GetRepresentativeWaveRunup2PB() const
    {
        return _representativeWaveRunup2PB.get();
    }

    const double* JsonInputGrassWaveRunupCalculationDefinitionData::GetRepresentativeWaveRunup2PC() const
    {
        return _representativeWaveRunup2PC.get();
    }

    const double* JsonInputGrassWaveRunupCalculationDefinitionData::GetWaveAngleImpactABeta() const
    {
        return _waveAngleImpactABeta.get();
    }

    const double* JsonInputGrassWaveRunupCalculationDefinitionData::GetWaveAngleImpactBetaMax() const
    {
        return _waveAngleImpactBetaMax.get();
    }

    #pragma endregion
}
