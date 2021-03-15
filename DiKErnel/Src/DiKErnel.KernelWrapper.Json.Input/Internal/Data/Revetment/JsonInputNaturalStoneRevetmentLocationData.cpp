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
        const double relativeDensity,
        const double thicknessTopLayer,
        const TopLayerType topLayerType)
        : JsonInputRevetmentLocationData(
              relativeDensity,
              thicknessTopLayer),
          _topLayerType(topLayerType) { }

    #pragma region Set methods

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

    void JsonInputNaturalStoneRevetmentLocationData::SetUpperLimitLoadingAul(
        unique_ptr<double> upperLimitLoadingAul)
    {
        _upperLimitLoadingAul = move(upperLimitLoadingAul);
    }

    void JsonInputNaturalStoneRevetmentLocationData::SetUpperLimitLoadingBul(
        unique_ptr<double> upperLimitLoadingBul)
    {
        _upperLimitLoadingBul = move(upperLimitLoadingBul);
    }

    void JsonInputNaturalStoneRevetmentLocationData::SetUpperLimitLoadingCul(
        unique_ptr<double> upperLimitLoadingCul)
    {
        _upperLimitLoadingCul = move(upperLimitLoadingCul);
    }

    void JsonInputNaturalStoneRevetmentLocationData::SetLowerLimitLoadingAll(
        unique_ptr<double> lowerLimitLoadingAll)
    {
        _lowerLimitLoadingAll = move(lowerLimitLoadingAll);
    }

    void JsonInputNaturalStoneRevetmentLocationData::SetLowerLimitLoadingBll(
        unique_ptr<double> lowerLimitLoadingBll)
    {
        _lowerLimitLoadingBll = move(lowerLimitLoadingBll);
    }

    void JsonInputNaturalStoneRevetmentLocationData::SetLowerLimitLoadingCll(
        unique_ptr<double> lowerLimitLoadingCll)
    {
        _lowerLimitLoadingCll = move(lowerLimitLoadingCll);
    }

    void JsonInputNaturalStoneRevetmentLocationData::SetDistanceMaximumWaveElevationAsmax(
        unique_ptr<double> distanceMaximumWaveElevationAsmax)
    {
        _distanceMaximumWaveElevationAsmax = move(distanceMaximumWaveElevationAsmax);
    }

    void JsonInputNaturalStoneRevetmentLocationData::SetDistanceMaximumWaveElevationBsmax(
        unique_ptr<double> distanceMaximumWaveElevationBsmax)
    {
        _distanceMaximumWaveElevationBsmax = move(distanceMaximumWaveElevationBsmax);
    }

    void JsonInputNaturalStoneRevetmentLocationData::SetNormativeWidthOfWaveImpactAwi(
        unique_ptr<double> normativeWidthOfWaveImpactAwi)
    {
        _normativeWidthOfWaveImpactAwi = move(normativeWidthOfWaveImpactAwi);
    }

    void JsonInputNaturalStoneRevetmentLocationData::SetNormativeWidthOfWaveImpactBwi(
        unique_ptr<double> normativeWidthOfWaveImpactBwi)
    {
        _normativeWidthOfWaveImpactBwi = move(normativeWidthOfWaveImpactBwi);
    }

    #pragma endregion

    #pragma region Get methods

    JsonInputNaturalStoneRevetmentLocationData::TopLayerType JsonInputNaturalStoneRevetmentLocationData::GetTopLayerType() const
    {
        return _topLayerType;
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

    const double* JsonInputNaturalStoneRevetmentLocationData::GetUpperLimitLoadingAul() const
    {
        return _upperLimitLoadingAul.get();
    }

    const double* JsonInputNaturalStoneRevetmentLocationData::GetUpperLimitLoadingBul() const
    {
        return _upperLimitLoadingBul.get();
    }

    const double* JsonInputNaturalStoneRevetmentLocationData::GetUpperLimitLoadingCul() const
    {
        return _upperLimitLoadingCul.get();
    }

    const double* JsonInputNaturalStoneRevetmentLocationData::GetLowerLimitLoadingAll() const
    {
        return _lowerLimitLoadingAll.get();
    }

    const double* JsonInputNaturalStoneRevetmentLocationData::GetLowerLimitLoadingBll() const
    {
        return _lowerLimitLoadingBll.get();
    }

    const double* JsonInputNaturalStoneRevetmentLocationData::GetLowerLimitLoadingCll() const
    {
        return _lowerLimitLoadingCll.get();
    }

    const double* JsonInputNaturalStoneRevetmentLocationData::GetDistanceMaximumWaveElevationAsmax() const
    {
        return _distanceMaximumWaveElevationAsmax.get();
    }

    const double* JsonInputNaturalStoneRevetmentLocationData::GetDistanceMaximumWaveElevationBsmax() const
    {
        return _distanceMaximumWaveElevationBsmax.get();
    }

    const double* JsonInputNaturalStoneRevetmentLocationData::GetNormativeWidthOfWaveImpactAwi() const
    {
        return _normativeWidthOfWaveImpactAwi.get();
    }

    const double* JsonInputNaturalStoneRevetmentLocationData::GetNormativeWidthOfWaveImpactBwi() const
    {
        return _normativeWidthOfWaveImpactBwi.get();
    }

    #pragma endregion
}
