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

#include "AsphaltRevetmentWaveImpactLocationConstructionProperties.h"

namespace DiKErnel::Integration
{
    using namespace std;

    AsphaltRevetmentWaveImpactLocationConstructionProperties::AsphaltRevetmentWaveImpactLocationConstructionProperties(
        const double x,
        const AsphaltRevetmentTopLayerType topLayerType,
        const double failureTension,
        const double soilElasticity,
        const double thicknessUpperLayer,
        const double elasticModulusUpperLayer)
        : RevetmentLocationConstructionPropertiesBase(x),
          _topLayerType(topLayerType),
          _failureTension(failureTension),
          _soilElasticity(soilElasticity),
          _thicknessUpperLayer(thicknessUpperLayer),
          _elasticModulusUpperLayer(elasticModulusUpperLayer) {}

    #pragma region Set methods

    void AsphaltRevetmentWaveImpactLocationConstructionProperties::SetDensityOfWater(
        unique_ptr<double> densityOfWater)
    {
        _densityOfWater = move(densityOfWater);
    }

    void AsphaltRevetmentWaveImpactLocationConstructionProperties::SetThicknessSubLayer(
        unique_ptr<double> thicknessSubLayer)
    {
        _thicknessSubLayer = move(thicknessSubLayer);
    }

    void AsphaltRevetmentWaveImpactLocationConstructionProperties::SetElasticModulusSubLayer(
        unique_ptr<double> elasticModulusSubLayer)
    {
        _elasticModulusSubLayer = move(elasticModulusSubLayer);
    }

    void AsphaltRevetmentWaveImpactLocationConstructionProperties::SetAverageNumberOfWavesCtm(
        unique_ptr<double> averageNumberOfWavesCtm)
    {
        _averageNumberOfWavesCtm = move(averageNumberOfWavesCtm);
    }

    void AsphaltRevetmentWaveImpactLocationConstructionProperties::SetFatigueAlpha(
        unique_ptr<double> fatigueAlpha)
    {
        _fatigueAlpha = move(fatigueAlpha);
    }

    void AsphaltRevetmentWaveImpactLocationConstructionProperties::SetFatigueBeta(
        unique_ptr<double> fatigueBeta)
    {
        _fatigueBeta = move(fatigueBeta);
    }

    void AsphaltRevetmentWaveImpactLocationConstructionProperties::SetImpactNumberC(
        unique_ptr<double> impactNumberC)
    {
        _impactNumberC = move(impactNumberC);
    }

    void AsphaltRevetmentWaveImpactLocationConstructionProperties::SetStiffnessRelationNu(
        unique_ptr<double> stiffnessRelationNu)
    {
        _stiffnessRelationNu = move(stiffnessRelationNu);
    }

    void AsphaltRevetmentWaveImpactLocationConstructionProperties::SetWidthFactors(
        unique_ptr<vector<pair<double, double>>> widthFactors)
    {
        _widthFactors = move(widthFactors);
    }

    void AsphaltRevetmentWaveImpactLocationConstructionProperties::SetDepthFactors(
        unique_ptr<vector<pair<double, double>>> depthFactors)
    {
        _depthFactors = move(depthFactors);
    }

    void AsphaltRevetmentWaveImpactLocationConstructionProperties::SetImpactFactors(
        unique_ptr<vector<pair<double, double>>> impactFactors)
    {
        _impactFactors = move(impactFactors);
    }

    #pragma endregion

    #pragma region Get methods

    AsphaltRevetmentTopLayerType AsphaltRevetmentWaveImpactLocationConstructionProperties::GetTopLayerType() const
    {
        return _topLayerType;
    }

    double AsphaltRevetmentWaveImpactLocationConstructionProperties::GetFailureTension() const
    {
        return _failureTension;
    }

    double AsphaltRevetmentWaveImpactLocationConstructionProperties::GetSoilElasticity() const
    {
        return _soilElasticity;
    }

    double AsphaltRevetmentWaveImpactLocationConstructionProperties::GetThicknessUpperLayer() const
    {
        return _thicknessUpperLayer;
    }

    double AsphaltRevetmentWaveImpactLocationConstructionProperties::GetElasticModulusUpperLayer() const
    {
        return _elasticModulusUpperLayer;
    }

    const double* AsphaltRevetmentWaveImpactLocationConstructionProperties::GetDensityOfWater() const
    {
        return _densityOfWater.get();
    }

    const double* AsphaltRevetmentWaveImpactLocationConstructionProperties::GetThicknessSubLayer() const
    {
        return _thicknessSubLayer.get();
    }

    const double* AsphaltRevetmentWaveImpactLocationConstructionProperties::GetElasticModulusSubLayer() const
    {
        return _elasticModulusSubLayer.get();
    }

    const double* AsphaltRevetmentWaveImpactLocationConstructionProperties::GetAverageNumberOfWavesCtm() const
    {
        return _averageNumberOfWavesCtm.get();
    }

    const double* AsphaltRevetmentWaveImpactLocationConstructionProperties::GetFatigueAlpha() const
    {
        return _fatigueAlpha.get();
    }

    const double* AsphaltRevetmentWaveImpactLocationConstructionProperties::GetFatigueBeta() const
    {
        return _fatigueBeta.get();
    }

    const double* AsphaltRevetmentWaveImpactLocationConstructionProperties::GetImpactNumberC() const
    {
        return _impactNumberC.get();
    }

    const double* AsphaltRevetmentWaveImpactLocationConstructionProperties::GetStiffnessRelationNu() const
    {
        return _stiffnessRelationNu.get();
    }

    const vector<pair<double, double>>* AsphaltRevetmentWaveImpactLocationConstructionProperties::GetWidthFactors() const
    {
        return _widthFactors.get();
    }

    const vector<pair<double, double>>* AsphaltRevetmentWaveImpactLocationConstructionProperties::GetDepthFactors() const
    {
        return _depthFactors.get();
    }

    const vector<pair<double, double>>* AsphaltRevetmentWaveImpactLocationConstructionProperties::GetImpactFactors() const
    {
        return _impactFactors.get();
    }

    #pragma endregion
}
