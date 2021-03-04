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

#include "Internal/Data/Generic/JsonInputRevetmentLocationData.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    class JsonInputNaturalStoneRevetmentLocationData : JsonInputRevetmentLocationData
    {
        public:
            JsonInputNaturalStoneRevetmentLocationData(
                const std::string& typeTopLayer,
                double relativeDensity,
                double thicknessTopLayer,
                std::unique_ptr<double> similarityParameterThreshold,
                std::unique_ptr<double> plungingCoefficientA,
                std::unique_ptr<double> plungingCoefficientB,
                std::unique_ptr<double> plungingCoefficientC,
                std::unique_ptr<double> plungingCoefficientN,
                std::unique_ptr<double> surgingCoefficientA,
                std::unique_ptr<double> surgingCoefficientB,
                std::unique_ptr<double> surgingCoefficientC,
                std::unique_ptr<double> surgingCoefficientN);

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
            std::unique_ptr<double> _similarityParameterThreshold;
            std::unique_ptr<double> _plungingCoefficientA;
            std::unique_ptr<double> _plungingCoefficientB;
            std::unique_ptr<double> _plungingCoefficientC;
            std::unique_ptr<double> _plungingCoefficientN;
            std::unique_ptr<double> _surgingCoefficientA;
            std::unique_ptr<double> _surgingCoefficientB;
            std::unique_ptr<double> _surgingCoefficientC;
            std::unique_ptr<double> _surgingCoefficientN;
    };
}
