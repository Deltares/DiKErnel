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

#include "JsonInputAsphaltWaveImpactLocationData.h"

#include <utility>

namespace DiKErnel::KernelWrapper::Json::Input
{
    using namespace std;

    JsonInputAsphaltWaveImpactLocationData::JsonInputAsphaltWaveImpactLocationData(
        const double x,
        unique_ptr<double> initialDamage,
        const JsonInputAsphaltRevetmentTopLayerType topLayerType,
        const double failureTension,
        const double soilElasticity,
        const double thicknessUpperLayer,
        const double elasticModulusUpperLayer,
        const double outerSlope)
        : JsonInputLocationData(x, move(initialDamage)),
          _topLayerType(topLayerType),
          _failureTension(failureTension),
          _soilElasticity(soilElasticity),
          _thicknessUpperLayer(thicknessUpperLayer),
          _elasticModulusUpperLayer(elasticModulusUpperLayer),
          _outerSlope(outerSlope) {}

    void JsonInputAsphaltWaveImpactLocationData::SetThicknessSubLayer(
        unique_ptr<double> thicknessSubLayer)
    {
        _thicknessSubLayer = move(thicknessSubLayer);
    }

    void JsonInputAsphaltWaveImpactLocationData::SetElasticModulusSubLayer(
        unique_ptr<double> elasticModulusSubLayer)
    {
        _elasticModulusSubLayer = move(elasticModulusSubLayer);
    }

    JsonInputAsphaltRevetmentTopLayerType JsonInputAsphaltWaveImpactLocationData::GetTopLayerType() const
    {
        return _topLayerType;
    }

    double JsonInputAsphaltWaveImpactLocationData::GetFailureTension() const
    {
        return _failureTension;
    }

    double JsonInputAsphaltWaveImpactLocationData::GetSoilElasticity() const
    {
        return _soilElasticity;
    }

    double JsonInputAsphaltWaveImpactLocationData::GetThicknessUpperLayer() const
    {
        return _thicknessUpperLayer;
    }

    double JsonInputAsphaltWaveImpactLocationData::GetElasticModulusUpperLayer() const
    {
        return _elasticModulusUpperLayer;
    }

    double JsonInputAsphaltWaveImpactLocationData::GetOuterSlope() const
    {
        return _outerSlope;
    }

    const double* JsonInputAsphaltWaveImpactLocationData::GetThicknessSubLayer() const
    {
        return _thicknessSubLayer.get();
    }

    const double* JsonInputAsphaltWaveImpactLocationData::GetElasticModulusSubLayer() const
    {
        return _elasticModulusSubLayer.get();
    }
}
