// Copyright (C) Stichting Deltares 2020. All rights reserved.
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

#include "JsonInputAsphaltRevetmentLocationData.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    using namespace std;

    JsonInputAsphaltRevetmentLocationData::JsonInputAsphaltRevetmentLocationData(
        const JsonInputAsphaltRevetmentTopLayerType topLayerType,
        const double failureTension,
        const double densityOfWater,
        const double soilElasticity,
        const double thicknessUpperLayer,
        const double elasticModulusUpperLayer)
        : _topLayerType(topLayerType),
          _failureTension(failureTension),
          _densityOfWater(densityOfWater),
          _soilElasticity(soilElasticity),
          _thicknessUpperLayer(thicknessUpperLayer),
          _elasticModulusUpperLayer(elasticModulusUpperLayer) { }

    #pragma region Set methods

    void JsonInputAsphaltRevetmentLocationData::SetThicknessSubLayer(
        unique_ptr<double> thicknessSubLayer)
    {
        _thicknessSubLayer = move(thicknessSubLayer);
    }

    void JsonInputAsphaltRevetmentLocationData::SetElasticModulusSubLayer(
        unique_ptr<double> elasticModulusSubLayer)
    {
        _elasticModulusSubLayer = move(elasticModulusSubLayer);
    }

    void JsonInputAsphaltRevetmentLocationData::SetAverageNumberOfWavesCtm(
        unique_ptr<double> averageNumberOfWavesCtm)
    {
        _averageNumberOfWavesCtm = move(averageNumberOfWavesCtm);
    }

    void JsonInputAsphaltRevetmentLocationData::SetFatigueAlpha(
        unique_ptr<double> fatigueAlpha)
    {
        _fatigueAlpha = move(fatigueAlpha);
    }

    void JsonInputAsphaltRevetmentLocationData::SetFatigueBeta(
        unique_ptr<double> fatigueBeta)
    {
        _fatigueBeta = move(fatigueBeta);
    }

    void JsonInputAsphaltRevetmentLocationData::SetImpactNumberC(
        unique_ptr<double> impactNumberC)
    {
        _impactNumberC = move(impactNumberC);
    }

    void JsonInputAsphaltRevetmentLocationData::SetStiffnessRelationNu(
        unique_ptr<double> stiffnessRelationNu)
    {
        _stiffnessRelationNu = move(stiffnessRelationNu);
    }

    #pragma endregion

    #pragma region Get methods

    JsonInputAsphaltRevetmentTopLayerType JsonInputAsphaltRevetmentLocationData::GetTopLayerType() const
    {
        return _topLayerType;
    }

    double JsonInputAsphaltRevetmentLocationData::GetFailureTension() const
    {
        return _failureTension;
    }

    double JsonInputAsphaltRevetmentLocationData::GetDensityOfWater() const
    {
        return _densityOfWater;
    }

    double JsonInputAsphaltRevetmentLocationData::GetSoilElasticity() const
    {
        return _soilElasticity;
    }

    double JsonInputAsphaltRevetmentLocationData::GetThicknessUpperLayer() const
    {
        return _thicknessUpperLayer;
    }

    double JsonInputAsphaltRevetmentLocationData::GetElasticModulusUpperLayer() const
    {
        return _elasticModulusUpperLayer;
    }

    const double* JsonInputAsphaltRevetmentLocationData::GetThicknessSubLayer() const
    {
        return _thicknessSubLayer.get();
    }

    const double* JsonInputAsphaltRevetmentLocationData::GetElasticModulusSubLayer() const
    {
        return _elasticModulusSubLayer.get();
    }

    const double* JsonInputAsphaltRevetmentLocationData::GetAverageNumberOfWavesCtm() const
    {
        return _averageNumberOfWavesCtm.get();
    }

    const double* JsonInputAsphaltRevetmentLocationData::GetFatigueAlpha() const
    {
        return _fatigueAlpha.get();
    }

    const double* JsonInputAsphaltRevetmentLocationData::GetFatigueBeta() const
    {
        return _fatigueBeta.get();
    }

    const double* JsonInputAsphaltRevetmentLocationData::GetImpactNumberC() const
    {
        return _impactNumberC.get();
    }

    const double* JsonInputAsphaltRevetmentLocationData::GetStiffnessRelationNu() const
    {
        return _stiffnessRelationNu.get();
    }

    #pragma endregion
}
