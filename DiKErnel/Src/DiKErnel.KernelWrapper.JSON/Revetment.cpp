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

#include "Revetment.h"

namespace DiKErnel::KernelWrapper::Json
{
    Revetment::Revetment(
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
        double coefficientSurgingNs)
        : name(typeTopLayer),
          relativeDensity(relativeDensity),
          thicknessTopLayer(thicknessTopLayer),
          initialDamage(initialDamage),
          similarityParameterThreshold(similarityParameterThreshold),
          coefficientPlungingAp(coefficientPlungingAp),
          coefficientPlungingBp(coefficientPlungingBp),
          coefficientPlungingCp(coefficientPlungingCp),
          coefficientPlungingNp(coefficientPlungingNp),
          coefficientSurgingAs(coefficientSurgingAs),
          coefficientSurgingBs(coefficientSurgingBs),
          coefficientSurgingCs(coefficientSurgingCs),
          coefficientSurgingNs(coefficientSurgingNs) { }

    std::string Revetment::GetTypeTopLayer() const
    {
        return name;
    }

    double Revetment::GetRelativeDensity() const
    {
        return relativeDensity;
    }

    double Revetment::GetThicknessTopLayer() const
    {
        return thicknessTopLayer;
    }

    double Revetment::GetInitialDamage() const
    {
        return initialDamage;
    }

    double Revetment::GetSimilarityParameterThreshold() const
    {
        return similarityParameterThreshold;
    }

    double Revetment::GetCoefficientPlungingAp() const
    {
        return coefficientPlungingAp;
    }

    double Revetment::GetCoefficientPlungingBp() const
    {
        return coefficientPlungingBp;
    }

    double Revetment::GetCoefficientPlungingCp() const
    {
        return coefficientPlungingCp;
    }

    double Revetment::GetCoefficientPlungingNp() const
    {
        return coefficientPlungingNp;
    }

    double Revetment::GetCoefficientSurgingAs() const
    {
        return coefficientSurgingAs;
    }

    double Revetment::GetCoefficientSurgingBs() const
    {
        return coefficientSurgingBs;
    }

    double Revetment::GetCoefficientSurgingCs() const
    {
        return coefficientSurgingCs;
    }

    double Revetment::GetCoefficientSurgingNs() const
    {
        return coefficientSurgingNs;
    }
}
