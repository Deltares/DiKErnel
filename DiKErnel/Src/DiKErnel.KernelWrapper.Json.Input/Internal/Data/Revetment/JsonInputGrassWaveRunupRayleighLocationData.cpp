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

#include "JsonInputGrassWaveRunupRayleighLocationData.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    using namespace std;

    JsonInputGrassWaveRunupRayleighLocationData::JsonInputGrassWaveRunupRayleighLocationData(
        const double x,
        unique_ptr<double> initialDamage,
        const JsonInputGrassRevetmentTopLayerType topLayerType,
        const double outerSlope,
        unique_ptr<JsonInputDamageData> damageData,
        unique_ptr<JsonInputGrassWaveRunupRayleighCalculationDefinitionData> revetmentLocationData)
        : JsonInputLocationData(x, move(initialDamage), move(damageData)),
          _topLayerType(topLayerType),
          _outerSlope(outerSlope),
          _revetmentLocationData(move(revetmentLocationData)) {}

    void JsonInputGrassWaveRunupRayleighLocationData::SetIncreasedLoadTransitionAlphaM(
        unique_ptr<double> increasedLoadTransitionAlphaM)
    {
        _increasedLoadTransitionAlphaM = move(increasedLoadTransitionAlphaM);
    }

    void JsonInputGrassWaveRunupRayleighLocationData::SetReducedStrengthTransitionAlphaS(
        unique_ptr<double> reducedStrengthTransitionAlphaS)
    {
        _reducedStrengthTransitionAlphaS = move(reducedStrengthTransitionAlphaS);
    }

    void JsonInputGrassWaveRunupRayleighLocationData::SetRepresentativeWaveRunup2PGammab(
        unique_ptr<double> representativeWaveRunup2PGammab)
    {
        _representativeWaveRunup2PGammab = move(representativeWaveRunup2PGammab);
    }

    void JsonInputGrassWaveRunupRayleighLocationData::SetRepresentativeWaveRunup2PGammaf(
        unique_ptr<double> representativeWaveRunup2PGammaf)
    {
        _representativeWaveRunup2PGammaf = move(representativeWaveRunup2PGammaf);
    }

    JsonInputGrassRevetmentTopLayerType JsonInputGrassWaveRunupRayleighLocationData::GetTopLayerType() const
    {
        return _topLayerType;
    }

    double JsonInputGrassWaveRunupRayleighLocationData::GetOuterSlope() const
    {
        return _outerSlope;
    }

    const double* JsonInputGrassWaveRunupRayleighLocationData::GetIncreasedLoadTransitionAlphaM() const
    {
        return _increasedLoadTransitionAlphaM.get();
    }

    const double* JsonInputGrassWaveRunupRayleighLocationData::GetReducedStrengthTransitionAlphaS() const
    {
        return _reducedStrengthTransitionAlphaS.get();
    }

    const double* JsonInputGrassWaveRunupRayleighLocationData::GetRepresentativeWaveRunup2PGammab() const
    {
        return _representativeWaveRunup2PGammab.get();
    }

    const double* JsonInputGrassWaveRunupRayleighLocationData::GetRepresentativeWaveRunup2PGammaf() const
    {
        return _representativeWaveRunup2PGammaf.get();
    }

    const JsonInputGrassWaveRunupRayleighCalculationDefinitionData& JsonInputGrassWaveRunupRayleighLocationData::GetRevetmentLocationData() const
    {
        return *_revetmentLocationData;
    }
}
