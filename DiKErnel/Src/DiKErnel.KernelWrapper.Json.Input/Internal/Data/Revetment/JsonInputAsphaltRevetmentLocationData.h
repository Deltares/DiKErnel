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

#pragma once

#include "IJsonInputRevetmentLocationData.h"
#include "JsonInputAsphaltRevetmentTopLayerType.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    class JsonInputAsphaltRevetmentLocationData : public IJsonInputRevetmentLocationData
    {
        public:
            explicit JsonInputAsphaltRevetmentLocationData(
                JsonInputAsphaltRevetmentTopLayerType topLayerType,
                double failureTension,
                double densityOfWater,
                double soilElasticity,
                double thicknessUpperLayer,
                double elasticModulusUpperLayer);

            #pragma region Set methods

            #pragma endregion

            #pragma region Get methods

            JsonInputAsphaltRevetmentTopLayerType GetTopLayerType() const;

            double GetFailureTension() const;

            double GetDensityOfWater() const;

            double GetSoilElasticity() const;

            double GetThicknessUpperLayer() const;

            double GetElasticModulusUpperLayer() const;

            #pragma endregion

        private:
            JsonInputAsphaltRevetmentTopLayerType _topLayerType;
            double _failureTension;
            double _densityOfWater;
            double _soilElasticity;
            double _thicknessUpperLayer;
            double _elasticModulusUpperLayer;
    };
}
