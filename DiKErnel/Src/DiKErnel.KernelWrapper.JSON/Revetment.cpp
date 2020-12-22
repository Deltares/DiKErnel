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

#include <utility>

#include "Revetment.h"

namespace DiKErnel::KernelWrapper::Json
{
    using namespace std;

    Revetment::Revetment(
        string typeTopLayer,
        const double relativeDensity,
        const double thicknessTopLayer,
        const double initialDamage,
        const double similarityParameterThreshold,
        const double coefficientPlungingAp,
        const double coefficientPlungingBp,
        const double coefficientPlungingCp,
        const double coefficientPlungingNp,
        const double coefficientSurgingAs,
        const double coefficientSurgingBs,
        const double coefficientSurgingCs,
        const double coefficientSurgingNs)
        : name(move(typeTopLayer)),
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

    const string& Revetment::GetTypeTopLayer() const
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
