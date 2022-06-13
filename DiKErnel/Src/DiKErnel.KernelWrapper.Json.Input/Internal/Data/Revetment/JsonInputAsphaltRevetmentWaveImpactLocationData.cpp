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

#include "JsonInputAsphaltRevetmentWaveImpactLocationData.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    using namespace std;

    JsonInputAsphaltRevetmentWaveImpactLocationData::JsonInputAsphaltRevetmentWaveImpactLocationData(
        const double densityOfWater)
        : _densityOfWater(densityOfWater) { }

    #pragma region Set methods

    void JsonInputAsphaltRevetmentWaveImpactLocationData::SetAverageNumberOfWavesCtm(
        unique_ptr<double> averageNumberOfWavesCtm)
    {
        _averageNumberOfWavesCtm = move(averageNumberOfWavesCtm);
    }

    void JsonInputAsphaltRevetmentWaveImpactLocationData::SetFatigueAlpha(
        unique_ptr<double> fatigueAlpha)
    {
        _fatigueAlpha = move(fatigueAlpha);
    }

    void JsonInputAsphaltRevetmentWaveImpactLocationData::SetFatigueBeta(
        unique_ptr<double> fatigueBeta)
    {
        _fatigueBeta = move(fatigueBeta);
    }

    void JsonInputAsphaltRevetmentWaveImpactLocationData::SetImpactNumberC(
        unique_ptr<double> impactNumberC)
    {
        _impactNumberC = move(impactNumberC);
    }

    void JsonInputAsphaltRevetmentWaveImpactLocationData::SetStiffnessRelationNu(
        unique_ptr<double> stiffnessRelationNu)
    {
        _stiffnessRelationNu = move(stiffnessRelationNu);
    }

    void JsonInputAsphaltRevetmentWaveImpactLocationData::SetWidthFactors(
        unique_ptr<vector<pair<double, double>>> widthFactors)
    {
        _widthFactors = move(widthFactors);
    }

    void JsonInputAsphaltRevetmentWaveImpactLocationData::SetDepthFactors(
        unique_ptr<vector<pair<double, double>>> depthFactors)
    {
        _depthFactors = move(depthFactors);
    }

    void JsonInputAsphaltRevetmentWaveImpactLocationData::SetImpactFactors(
        unique_ptr<vector<pair<double, double>>> impactFactors)
    {
        _impactFactors = move(impactFactors);
    }

    #pragma endregion

    #pragma region Get methods

    double JsonInputAsphaltRevetmentWaveImpactLocationData::GetDensityOfWater() const
    {
        return _densityOfWater;
    }

    const double* JsonInputAsphaltRevetmentWaveImpactLocationData::GetAverageNumberOfWavesCtm() const
    {
        return _averageNumberOfWavesCtm.get();
    }

    const double* JsonInputAsphaltRevetmentWaveImpactLocationData::GetFatigueAlpha() const
    {
        return _fatigueAlpha.get();
    }

    const double* JsonInputAsphaltRevetmentWaveImpactLocationData::GetFatigueBeta() const
    {
        return _fatigueBeta.get();
    }

    const double* JsonInputAsphaltRevetmentWaveImpactLocationData::GetImpactNumberC() const
    {
        return _impactNumberC.get();
    }

    const double* JsonInputAsphaltRevetmentWaveImpactLocationData::GetStiffnessRelationNu() const
    {
        return _stiffnessRelationNu.get();
    }

    const vector<pair<double, double>>* JsonInputAsphaltRevetmentWaveImpactLocationData::GetWidthFactors() const
    {
        return _widthFactors.get();
    }

    const vector<pair<double, double>>* JsonInputAsphaltRevetmentWaveImpactLocationData::GetDepthFactors() const
    {
        return _depthFactors.get();
    }

    const vector<pair<double, double>>* JsonInputAsphaltRevetmentWaveImpactLocationData::GetImpactFactors() const
    {
        return _impactFactors.get();
    }

    #pragma endregion
}
