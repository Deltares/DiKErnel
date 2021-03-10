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
    using namespace std;

    JsonInputNaturalStoneRevetmentLocationData::JsonInputNaturalStoneRevetmentLocationData(
        const string& typeTopLayer,
        const double relativeDensity,
        const double thicknessTopLayer)
        : JsonInputRevetmentLocationData(
              typeTopLayer,
              relativeDensity,
              thicknessTopLayer) { }

    void JsonInputNaturalStoneRevetmentLocationData::SetPlungingCoefficientA(
        unique_ptr<double> plungingCoefficientA)
    {
        _plungingCoefficientA = move(plungingCoefficientA);
    }

    void JsonInputNaturalStoneRevetmentLocationData::SetPlungingCoefficientB(
        unique_ptr<double> plungingCoefficientB)
    {
        _plungingCoefficientB = move(plungingCoefficientB);
    }

    void JsonInputNaturalStoneRevetmentLocationData::SetPlungingCoefficientC(
        unique_ptr<double> plungingCoefficientC)
    {
        _plungingCoefficientC = move(plungingCoefficientC);
    }

    void JsonInputNaturalStoneRevetmentLocationData::SetPlungingCoefficientN(
        unique_ptr<double> plungingCoefficientN)
    {
        _plungingCoefficientN = move(plungingCoefficientN);
    }

    void JsonInputNaturalStoneRevetmentLocationData::SetSurgingCoefficientA(
        unique_ptr<double> surgingCoefficientA)
    {
        _surgingCoefficientA = move(surgingCoefficientA);
    }

    void JsonInputNaturalStoneRevetmentLocationData::SetSurgingCoefficientB(
        unique_ptr<double> surgingCoefficientB)
    {
        _surgingCoefficientB = move(surgingCoefficientB);
    }

    void JsonInputNaturalStoneRevetmentLocationData::SetSurgingCoefficientC(
        unique_ptr<double> surgingCoefficientC)
    {
        _surgingCoefficientC = move(surgingCoefficientC);
    }

    void JsonInputNaturalStoneRevetmentLocationData::SetSurgingCoefficientN(
        unique_ptr<double> surgingCoefficientN)
    {
        _surgingCoefficientN = move(surgingCoefficientN);
    }

    void JsonInputNaturalStoneRevetmentLocationData::SetSimilarityParameterThreshold(
        unique_ptr<double> similarityParameterThreshold)
    {
        _similarityParameterThreshold = move(similarityParameterThreshold);
    }

    const double* JsonInputNaturalStoneRevetmentLocationData::GetSimilarityParameterThreshold() const
    {
        return _similarityParameterThreshold.get();
    }

    const double* JsonInputNaturalStoneRevetmentLocationData::GetPlungingCoefficientA() const
    {
        return _plungingCoefficientA.get();
    }

    const double* JsonInputNaturalStoneRevetmentLocationData::GetPlungingCoefficientB() const
    {
        return _plungingCoefficientB.get();
    }

    const double* JsonInputNaturalStoneRevetmentLocationData::GetPlungingCoefficientC() const
    {
        return _plungingCoefficientC.get();
    }

    const double* JsonInputNaturalStoneRevetmentLocationData::GetPlungingCoefficientN() const
    {
        return _plungingCoefficientN.get();
    }

    const double* JsonInputNaturalStoneRevetmentLocationData::GetSurgingCoefficientA() const
    {
        return _surgingCoefficientA.get();
    }

    const double* JsonInputNaturalStoneRevetmentLocationData::GetSurgingCoefficientB() const
    {
        return _surgingCoefficientB.get();
    }

    const double* JsonInputNaturalStoneRevetmentLocationData::GetSurgingCoefficientC() const
    {
        return _surgingCoefficientC.get();
    }

    const double* JsonInputNaturalStoneRevetmentLocationData::GetSurgingCoefficientN() const
    {
        return _surgingCoefficientN.get();
    }
}
