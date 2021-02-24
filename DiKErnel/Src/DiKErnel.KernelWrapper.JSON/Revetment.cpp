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
        const double similarityParameterThreshold,
        const double plungingCoefficientA,
        const double plungingCoefficientB,
        const double plungingCoefficientC,
        const double plungingCoefficientN,
        const double surgingCoefficientA,
        const double surgingCoefficientB,
        const double surgingCoefficientC,
        const double surgingCoefficientN)
        : typeTopLayer(move(typeTopLayer)),
          relativeDensity(relativeDensity),
          thicknessTopLayer(thicknessTopLayer),
          similarityParameterThreshold(similarityParameterThreshold),
          plungingCoefficientA(plungingCoefficientA),
          plungingCoefficientB(plungingCoefficientB),
          plungingCoefficientC(plungingCoefficientC),
          plungingCoefficientN(plungingCoefficientN),
          surgingCoefficientA(surgingCoefficientA),
          surgingCoefficientB(surgingCoefficientB),
          surgingCoefficientC(surgingCoefficientC),
          surgingCoefficientN(surgingCoefficientN) { }

    const string& Revetment::GetTypeTopLayer() const
    {
        return typeTopLayer;
    }

    double Revetment::GetRelativeDensity() const
    {
        return relativeDensity;
    }

    double Revetment::GetThicknessTopLayer() const
    {
        return thicknessTopLayer;
    }

    double Revetment::GetSimilarityParameterThreshold() const
    {
        return similarityParameterThreshold;
    }

    double Revetment::GetPlungingCoefficientA() const
    {
        return plungingCoefficientA;
    }

    double Revetment::GetPlungingCoefficientB() const
    {
        return plungingCoefficientB;
    }

    double Revetment::GetPlungingCoefficientC() const
    {
        return plungingCoefficientC;
    }

    double Revetment::GetPlungingCoefficientN() const
    {
        return plungingCoefficientN;
    }

    double Revetment::GetSurgingCoefficientA() const
    {
        return surgingCoefficientA;
    }

    double Revetment::GetSurgingCoefficientB() const
    {
        return surgingCoefficientB;
    }

    double Revetment::GetSurgingCoefficientC() const
    {
        return surgingCoefficientC;
    }

    double Revetment::GetSurgingCoefficientN() const
    {
        return surgingCoefficientN;
    }
}
