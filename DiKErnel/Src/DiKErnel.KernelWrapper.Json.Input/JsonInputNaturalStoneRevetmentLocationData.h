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

#include "JsonInputRevetmentLocationData.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    /*!
     * \brief Container for natural stone revetment specific location data read from Json.
     */
    class JsonInputNaturalStoneRevetmentLocationData : JsonInputRevetmentLocationData
    {
        public:
            JsonInputNaturalStoneRevetmentLocationData(
                const std::string& typeTopLayer,
                double relativeDensity,
                double thicknessTopLayer,
                double similarityParameterThreshold,
                double plungingCoefficientA,
                double plungingCoefficientB,
                double plungingCoefficientC,
                double plungingCoefficientN,
                double surgingCoefficientA,
                double surgingCoefficientB,
                double surgingCoefficientC,
                double surgingCoefficientN);

            double GetSimilarityParameterThreshold() const;

            double GetPlungingCoefficientA() const;

            double GetPlungingCoefficientB() const;

            double GetPlungingCoefficientC() const;

            double GetPlungingCoefficientN() const;

            double GetSurgingCoefficientA() const;

            double GetSurgingCoefficientB() const;

            double GetSurgingCoefficientC() const;

            double GetSurgingCoefficientN() const;

        private:
            double _similarityParameterThreshold;
            double _plungingCoefficientA;
            double _plungingCoefficientB;
            double _plungingCoefficientC;
            double _plungingCoefficientN;
            double _surgingCoefficientA;
            double _surgingCoefficientB;
            double _surgingCoefficientC;
            double _surgingCoefficientN;
    };
}
