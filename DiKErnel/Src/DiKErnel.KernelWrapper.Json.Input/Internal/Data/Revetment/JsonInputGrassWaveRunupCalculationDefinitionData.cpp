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

    void JsonInputGrassWaveRunupCalculationDefinitionData::SetAverageNumberOfWavesCtm(
        unique_ptr<double> averageNumberOfWavesCtm)
    {
        _averageNumberOfWavesCtm = move(averageNumberOfWavesCtm);
    }

    void JsonInputGrassWaveRunupCalculationDefinitionData::SetRepresentativeWaveRunup2PAru(
        unique_ptr<double> representativeWaveRunup2PAru)
    {
        _representativeWaveRunup2PAru = move(representativeWaveRunup2PAru);
    }

    void JsonInputGrassWaveRunupCalculationDefinitionData::SetRepresentativeWaveRunup2PBru(
        unique_ptr<double> representativeWaveRunup2PBru)
    {
        _representativeWaveRunup2PBru = move(representativeWaveRunup2PBru);
    }

    void JsonInputGrassWaveRunupCalculationDefinitionData::SetRepresentativeWaveRunup2PCru(
        unique_ptr<double> representativeWaveRunup2PCru)
    {
        _representativeWaveRunup2PCru = move(representativeWaveRunup2PCru);
    }

    void JsonInputGrassWaveRunupCalculationDefinitionData::SetWaveAngleImpactAbeta(
        unique_ptr<double> waveAngleImpactAbeta)
    {
        _waveAngleImpactAbeta = move(waveAngleImpactAbeta);
    }

    void JsonInputGrassWaveRunupCalculationDefinitionData::SetWaveAngleImpactBetamax(
        unique_ptr<double> waveAngleImpactBetamax)
    {
        _waveAngleImpactBetamax = move(waveAngleImpactBetamax);
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

    const double* JsonInputGrassWaveRunupCalculationDefinitionData::GetAverageNumberOfWavesCtm() const
    {
        return _averageNumberOfWavesCtm.get();
    }

    const double* JsonInputGrassWaveRunupCalculationDefinitionData::GetRepresentativeWaveRunup2PAru() const
    {
        return _representativeWaveRunup2PAru.get();
    }

    const double* JsonInputGrassWaveRunupCalculationDefinitionData::GetRepresentativeWaveRunup2PBru() const
    {
        return _representativeWaveRunup2PBru.get();
    }

    const double* JsonInputGrassWaveRunupCalculationDefinitionData::GetRepresentativeWaveRunup2PCru() const
    {
        return _representativeWaveRunup2PCru.get();
    }

    const double* JsonInputGrassWaveRunupCalculationDefinitionData::GetWaveAngleImpactAbeta() const
    {
        return _waveAngleImpactAbeta.get();
    }

    const double* JsonInputGrassWaveRunupCalculationDefinitionData::GetWaveAngleImpactBetamax() const
    {
        return _waveAngleImpactBetamax.get();
    }

    #pragma endregion
}
