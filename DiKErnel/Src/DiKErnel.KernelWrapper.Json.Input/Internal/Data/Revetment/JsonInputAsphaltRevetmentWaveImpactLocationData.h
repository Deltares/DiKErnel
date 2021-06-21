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

#include <memory>

#include "IJsonInputRevetmentLocationData.h"
#include "JsonInputAsphaltRevetmentTopLayerType.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    class JsonInputAsphaltRevetmentWaveImpactLocationData : public IJsonInputRevetmentLocationData
    {
        public:
            explicit JsonInputAsphaltRevetmentWaveImpactLocationData(
                JsonInputAsphaltRevetmentTopLayerType topLayerType,
                double failureTension,
                double densityOfWater,
                double soilElasticity,
                double thicknessUpperLayer,
                double elasticModulusUpperLayer);

            #pragma region Set methods

            void SetThicknessSubLayer(
                std::unique_ptr<double> thicknessSubLayer);

            void SetElasticModulusSubLayer(
                std::unique_ptr<double> elasticModulusSubLayer);

            void SetAverageNumberOfWavesCtm(
                std::unique_ptr<double> averageNumberOfWavesCtm);

            void SetFatigueAlpha(
                std::unique_ptr<double> fatigueAlpha);

            void SetFatigueBeta(
                std::unique_ptr<double> fatigueBeta);

            void SetImpactNumberC(
                std::unique_ptr<double> impactNumberC);

            void SetStiffnessRelationNu(
                std::unique_ptr<double> stiffnessRelationNu);

            #pragma endregion

            #pragma region Get methods

            JsonInputAsphaltRevetmentTopLayerType GetTopLayerType() const;

            double GetFailureTension() const;

            double GetDensityOfWater() const;

            double GetSoilElasticity() const;

            double GetThicknessUpperLayer() const;

            double GetElasticModulusUpperLayer() const;

            const double* GetThicknessSubLayer() const;

            const double* GetElasticModulusSubLayer() const;

            const double* GetAverageNumberOfWavesCtm() const;

            const double* GetFatigueAlpha() const;

            const double* GetFatigueBeta() const;

            const double* GetImpactNumberC() const;

            const double* GetStiffnessRelationNu() const;

            #pragma endregion

        private:
            JsonInputAsphaltRevetmentTopLayerType _topLayerType;
            double _failureTension;
            double _densityOfWater;
            double _soilElasticity;
            double _thicknessUpperLayer;
            double _elasticModulusUpperLayer;
            std::unique_ptr<double> _thicknessSubLayer = nullptr;
            std::unique_ptr<double> _elasticModulusSubLayer = nullptr;
            std::unique_ptr<double> _averageNumberOfWavesCtm = nullptr;
            std::unique_ptr<double> _fatigueAlpha = nullptr;
            std::unique_ptr<double> _fatigueBeta = nullptr;
            std::unique_ptr<double> _impactNumberC = nullptr;
            std::unique_ptr<double> _stiffnessRelationNu = nullptr;
    };
}
