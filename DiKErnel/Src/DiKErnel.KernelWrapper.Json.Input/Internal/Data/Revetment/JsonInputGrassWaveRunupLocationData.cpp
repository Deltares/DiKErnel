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

#include "JsonInputGrassWaveRunupLocationData.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    using namespace std;

    JsonInputGrassWaveRunupLocationData::JsonInputGrassWaveRunupLocationData(
        const double x,
        unique_ptr<double> initialDamage,
        const JsonInputGrassRevetmentTopLayerType topLayerType,
        const double outerSlope)
        : JsonInputLocationData(x, move(initialDamage)),
          _topLayerType(topLayerType),
          _outerSlope(outerSlope) {}

    void JsonInputGrassWaveRunupLocationData::SetIncreasedLoadTransitionAlphaM(
        unique_ptr<double> increasedLoadTransitionAlphaM)
    {
        _increasedLoadTransitionAlphaM = move(increasedLoadTransitionAlphaM);
    }

    void JsonInputGrassWaveRunupLocationData::SetReducedStrengthTransitionAlphaS(
        unique_ptr<double> reducedStrengthTransitionAlphaS)
    {
        _reducedStrengthTransitionAlphaS = move(reducedStrengthTransitionAlphaS);
    }

    void JsonInputGrassWaveRunupLocationData::SetRepresentativeWaveRunup2PGammaB(
        unique_ptr<double> representativeWaveRunup2PGammaB)
    {
        _representativeWaveRunup2PGammaB = move(representativeWaveRunup2PGammaB);
    }

    void JsonInputGrassWaveRunupLocationData::SetRepresentativeWaveRunup2PGammaF(
        unique_ptr<double> representativeWaveRunup2PGammaF)
    {
        _representativeWaveRunup2PGammaF = move(representativeWaveRunup2PGammaF);
    }

    JsonInputGrassRevetmentTopLayerType JsonInputGrassWaveRunupLocationData::GetTopLayerType() const
    {
        return _topLayerType;
    }

    double JsonInputGrassWaveRunupLocationData::GetOuterSlope() const
    {
        return _outerSlope;
    }

    const double* JsonInputGrassWaveRunupLocationData::GetIncreasedLoadTransitionAlphaM() const
    {
        return _increasedLoadTransitionAlphaM.get();
    }

    const double* JsonInputGrassWaveRunupLocationData::GetReducedStrengthTransitionAlphaS() const
    {
        return _reducedStrengthTransitionAlphaS.get();
    }

    const double* JsonInputGrassWaveRunupLocationData::GetRepresentativeWaveRunup2PGammaG() const
    {
        return _representativeWaveRunup2PGammaB.get();
    }

    const double* JsonInputGrassWaveRunupLocationData::GetRepresentativeWaveRunup2PGammaF() const
    {
        return _representativeWaveRunup2PGammaF.get();
    }
}
