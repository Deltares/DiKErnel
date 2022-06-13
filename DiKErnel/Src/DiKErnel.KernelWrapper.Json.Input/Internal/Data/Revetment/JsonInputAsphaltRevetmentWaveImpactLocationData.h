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

#include <memory>
#include <vector>

namespace DiKErnel::KernelWrapper::Json::Input
{
    class JsonInputAsphaltRevetmentWaveImpactLocationData
    {
        public:
            explicit JsonInputAsphaltRevetmentWaveImpactLocationData(
                double densityOfWater);

            #pragma region Set methods

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

            void SetWidthFactors(
                std::unique_ptr<std::vector<std::pair<double, double>>> widthFactors);

            void SetDepthFactors(
                std::unique_ptr<std::vector<std::pair<double, double>>> depthFactors);

            void SetImpactFactors(
                std::unique_ptr<std::vector<std::pair<double, double>>> impactFactors);

            #pragma endregion

            #pragma region Get methods

            [[nodiscard]]
            double GetDensityOfWater() const;

            [[nodiscard]]
            const double* GetAverageNumberOfWavesCtm() const;

            [[nodiscard]]
            const double* GetFatigueAlpha() const;

            [[nodiscard]]
            const double* GetFatigueBeta() const;

            [[nodiscard]]
            const double* GetImpactNumberC() const;

            [[nodiscard]]
            const double* GetStiffnessRelationNu() const;

            [[nodiscard]]
            const std::vector<std::pair<double, double>>* GetWidthFactors() const;

            [[nodiscard]]
            const std::vector<std::pair<double, double>>* GetDepthFactors() const;

            [[nodiscard]]
            const std::vector<std::pair<double, double>>* GetImpactFactors() const;

            #pragma endregion

        private:
            double _densityOfWater;
            std::unique_ptr<double> _averageNumberOfWavesCtm = nullptr;
            std::unique_ptr<double> _fatigueAlpha = nullptr;
            std::unique_ptr<double> _fatigueBeta = nullptr;
            std::unique_ptr<double> _impactNumberC = nullptr;
            std::unique_ptr<double> _stiffnessRelationNu = nullptr;
            std::unique_ptr<std::vector<std::pair<double, double>>> _widthFactors = nullptr;
            std::unique_ptr<std::vector<std::pair<double, double>>> _depthFactors = nullptr;
            std::unique_ptr<std::vector<std::pair<double, double>>> _impactFactors = nullptr;
    };
}
