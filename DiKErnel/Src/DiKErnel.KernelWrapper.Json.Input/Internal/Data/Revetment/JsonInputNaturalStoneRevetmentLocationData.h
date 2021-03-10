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

#include "JsonInputRevetmentLocationData.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    class JsonInputNaturalStoneRevetmentLocationData : public JsonInputRevetmentLocationData
    {
        public:
            explicit JsonInputNaturalStoneRevetmentLocationData(
                const std::string& typeTopLayer,
                double relativeDensity,
                double thicknessTopLayer);

            void SetPlungingCoefficientA(
                std::unique_ptr<double> plungingCoefficientA);

            void SetPlungingCoefficientB(
                std::unique_ptr<double> plungingCoefficientB);

            void SetPlungingCoefficientC(
                std::unique_ptr<double> plungingCoefficientC);

            void SetPlungingCoefficientN(
                std::unique_ptr<double> plungingCoefficientN);

            void SetSurgingCoefficientA(
                std::unique_ptr<double> surgingCoefficientA);

            void SetSurgingCoefficientB(
                std::unique_ptr<double> surgingCoefficientB);

            void SetSurgingCoefficientC(
                std::unique_ptr<double> surgingCoefficientC);

            void SetSurgingCoefficientN(
                std::unique_ptr<double> surgingCoefficientN);

            void SetSimilarityParameterThreshold(
                std::unique_ptr<double> similarityParameterThreshold);

            const double* GetSimilarityParameterThreshold() const;

            const double* GetPlungingCoefficientA() const;

            const double* GetPlungingCoefficientB() const;

            const double* GetPlungingCoefficientC() const;

            const double* GetPlungingCoefficientN() const;

            const double* GetSurgingCoefficientA() const;

            const double* GetSurgingCoefficientB() const;

            const double* GetSurgingCoefficientC() const;

            const double* GetSurgingCoefficientN() const;

        private:
            std::unique_ptr<double> _similarityParameterThreshold = nullptr;
            std::unique_ptr<double> _plungingCoefficientA = nullptr;
            std::unique_ptr<double> _plungingCoefficientB = nullptr;
            std::unique_ptr<double> _plungingCoefficientC = nullptr;
            std::unique_ptr<double> _plungingCoefficientN = nullptr;
            std::unique_ptr<double> _surgingCoefficientA = nullptr;
            std::unique_ptr<double> _surgingCoefficientB = nullptr;
            std::unique_ptr<double> _surgingCoefficientC = nullptr;
            std::unique_ptr<double> _surgingCoefficientN = nullptr;
    };
}
