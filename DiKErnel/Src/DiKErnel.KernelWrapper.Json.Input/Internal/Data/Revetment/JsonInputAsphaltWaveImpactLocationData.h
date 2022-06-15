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

#pragma once

#include "JsonInputAsphaltRevetmentTopLayerType.h"
#include "JsonInputAsphaltWaveImpactCalculationDefinitionData.h"
#include "JsonInputLocationData.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    class JsonInputAsphaltWaveImpactLocationData : public JsonInputLocationData
    {
        public:
            explicit JsonInputAsphaltWaveImpactLocationData(
                double x,
                std::unique_ptr<double> initialDamage,
                JsonInputAsphaltRevetmentTopLayerType topLayerType,
                double failureTension,
                double soilElasticity,
                double thicknessUpperLayer,
                double elasticModulusUpperLayer,
                double outerSlope,
                std::unique_ptr<JsonInputDamageData> damageData,
                std::unique_ptr<JsonInputAsphaltWaveImpactCalculationDefinitionData> revetmentLocationData);

            void SetThicknessSubLayer(
                std::unique_ptr<double> thicknessSubLayer);

            void SetElasticModulusSubLayer(
                std::unique_ptr<double> elasticModulusSubLayer);

            [[nodiscard]]
            JsonInputAsphaltRevetmentTopLayerType GetTopLayerType() const;

            [[nodiscard]]
            double GetFailureTension() const;

            [[nodiscard]]
            double GetSoilElasticity() const;

            [[nodiscard]]
            double GetThicknessUpperLayer() const;

            [[nodiscard]]
            double GetElasticModulusUpperLayer() const;

            [[nodiscard]]
            double GetOuterSlope() const;

            [[nodiscard]]
            const double* GetThicknessSubLayer() const;

            [[nodiscard]]
            const double* GetElasticModulusSubLayer() const;

            [[nodiscard]]
            const JsonInputAsphaltWaveImpactCalculationDefinitionData& GetRevetmentLocationData() const;

        private:
            JsonInputAsphaltRevetmentTopLayerType _topLayerType;
            double _failureTension;
            double _soilElasticity;
            double _thicknessUpperLayer;
            double _elasticModulusUpperLayer;
            double _outerSlope;
            std::unique_ptr<double> _thicknessSubLayer = nullptr;
            std::unique_ptr<double> _elasticModulusSubLayer = nullptr;
            std::unique_ptr<JsonInputAsphaltWaveImpactCalculationDefinitionData> _revetmentLocationData;
    };
}
