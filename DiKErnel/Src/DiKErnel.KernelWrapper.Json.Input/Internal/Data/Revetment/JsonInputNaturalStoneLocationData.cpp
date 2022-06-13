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

#include "JsonInputNaturalStoneLocationData.h"

#include <utility>

namespace DiKErnel::KernelWrapper::Json::Input
{
    using namespace std;

    JsonInputNaturalStoneLocationData::JsonInputNaturalStoneLocationData(
        const double x,
        unique_ptr<double> initialDamage,
        const JsonInputNaturalStoneRevetmentTopLayerType topLayerType,
        const double relativeDensity,
        const double thicknessTopLayer,
        unique_ptr<JsonInputDamageData> damageData,
        unique_ptr<JsonInputNaturalStoneRevetmentLocationData> revetmentLocationData)
        : JsonInputLocationData(x, move(initialDamage), move(damageData)),
          _topLayerType(topLayerType),
          _relativeDensity(relativeDensity),
          _thicknessTopLayer(thicknessTopLayer),
          _revetmentLocationData(move(revetmentLocationData)) {}

    JsonInputNaturalStoneRevetmentTopLayerType JsonInputNaturalStoneLocationData::GetTopLayerType() const
    {
        return _topLayerType;
    }

    double JsonInputNaturalStoneLocationData::GetRelativeDensity() const
    {
        return _relativeDensity;
    }

    double JsonInputNaturalStoneLocationData::GetThicknessTopLayer() const
    {
        return _thicknessTopLayer;
    }

    const JsonInputNaturalStoneRevetmentLocationData& JsonInputNaturalStoneLocationData::GetRevetmentLocationData() const
    {
        return *_revetmentLocationData;
    }
}
