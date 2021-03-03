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

#include "JsonInputNaturalStoneRevetmentLocationData.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    JsonInputNaturalStoneRevetmentLocationData::JsonInputNaturalStoneRevetmentLocationData(
        const std::string& typeTopLayer,
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
        : JsonInputRevetmentLocationData(
              typeTopLayer,
              relativeDensity,
              thicknessTopLayer),
          _similarityParameterThreshold(similarityParameterThreshold),
          _plungingCoefficientA(plungingCoefficientA),
          _plungingCoefficientB(plungingCoefficientB),
          _plungingCoefficientC(plungingCoefficientC),
          _plungingCoefficientN(plungingCoefficientN),
          _surgingCoefficientA(surgingCoefficientA),
          _surgingCoefficientB(surgingCoefficientB),
          _surgingCoefficientC(surgingCoefficientC),
          _surgingCoefficientN(surgingCoefficientN) { }

    double JsonInputNaturalStoneRevetmentLocationData::GetSimilarityParameterThreshold() const
    {
        return _similarityParameterThreshold;
    }

    double JsonInputNaturalStoneRevetmentLocationData::GetPlungingCoefficientA() const
    {
        return _plungingCoefficientA;
    }

    double JsonInputNaturalStoneRevetmentLocationData::GetPlungingCoefficientB() const
    {
        return _plungingCoefficientB;
    }

    double JsonInputNaturalStoneRevetmentLocationData::GetPlungingCoefficientC() const
    {
        return _plungingCoefficientC;
    }

    double JsonInputNaturalStoneRevetmentLocationData::GetPlungingCoefficientN() const
    {
        return _plungingCoefficientN;
    }

    double JsonInputNaturalStoneRevetmentLocationData::GetSurgingCoefficientA() const
    {
        return _surgingCoefficientA;
    }

    double JsonInputNaturalStoneRevetmentLocationData::GetSurgingCoefficientB() const
    {
        return _surgingCoefficientB;
    }

    double JsonInputNaturalStoneRevetmentLocationData::GetSurgingCoefficientC() const
    {
        return _surgingCoefficientC;
    }

    double JsonInputNaturalStoneRevetmentLocationData::GetSurgingCoefficientN() const
    {
        return _surgingCoefficientN;
    }
}
