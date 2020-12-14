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

#include <string>

namespace DiKErnel::KernelWrapper::Json
{
    /*!
     * \brief Class responsible for serving as data model for a revetment.
     */
    class Revetment
    {
        std::string typeTopLayer;
        double relativeDensity;
        double thicknessTopLayer;
        double initialDamage;
        double similarityParameterThreshold;
        double coefficientPlungingAp;
        double coefficientPlungingBp;
        double coefficientPlungingCp;
        double coefficientPlungingNp;
        double coefficientSurgingAs;
        double coefficientSurgingBs;
        double coefficientSurgingCs;
        double coefficientSurgingNs;

        public:
            explicit Revetment(
                std::string& typeTopLayer,
                double relativeDensity,
                double thicknessTopLayer,
                double initialDamage,
                double similarityParameterThreshold,
                double coefficientPlungingAp,
                double coefficientPlungingBp,
                double coefficientPlungingCp,
                double coefficientPlungingNp,
                double coefficientSurgingAs,
                double coefficientSurgingBs,
                double coefficientSurgingCs,
                double coefficientSurgingNs
            );

            std::string GetTypeTopLayer() const;

            double GetRelativeDensity() const;

            double GetThicknessTopLayer() const;

            double GetInitialDamage() const;

            double GetSimilarityParameterThreshold() const;

            double GetCoefficientPlungingAp() const;

            double GetCoefficientPlungingBp() const;

            double GetCoefficientPlungingCp() const;

            double GetCoefficientPlungingNp() const;

            double GetCoefficientSurgingAs() const;

            double GetCoefficientSurgingBs() const;

            double GetCoefficientSurgingCs() const;

            double GetCoefficientSurgingNs() const;
    };
}
