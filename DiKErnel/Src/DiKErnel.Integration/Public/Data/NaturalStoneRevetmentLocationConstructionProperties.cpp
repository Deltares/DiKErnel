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

#include "NaturalStoneRevetmentLocationConstructionProperties.h"

namespace DiKErnel::Integration
{
    using namespace std;

    NaturalStoneRevetmentLocationConstructionProperties::NaturalStoneRevetmentLocationConstructionProperties(
        const TopLayerType topLayerType,
        const double initialDamage,
        const double slopeAngle,
        const double thicknessTopLayer,
        const double relativeDensity)
        : _topLayerType(topLayerType),
          _initialDamage(initialDamage),
          _slopeAngle(slopeAngle),
          _thicknessTopLayer(thicknessTopLayer),
          _relativeDensity(relativeDensity) { }

    #pragma region Set methods

    void NaturalStoneRevetmentLocationConstructionProperties::SetPlungingCoefficientA(
        unique_ptr<double> plungingCoefficientA)
    {
        _plungingCoefficientA = move(plungingCoefficientA);
    }

    void NaturalStoneRevetmentLocationConstructionProperties::SetPlungingCoefficientB(
        unique_ptr<double> plungingCoefficientB)
    {
        _plungingCoefficientB = move(plungingCoefficientB);
    }

    void NaturalStoneRevetmentLocationConstructionProperties::SetPlungingCoefficientC(
        unique_ptr<double> plungingCoefficientC)
    {
        _plungingCoefficientC = move(plungingCoefficientC);
    }

    void NaturalStoneRevetmentLocationConstructionProperties::SetPlungingCoefficientN(
        unique_ptr<double> plungingCoefficientN)
    {
        _plungingCoefficientN = move(plungingCoefficientN);
    }

    void NaturalStoneRevetmentLocationConstructionProperties::SetSurgingCoefficientA(
        unique_ptr<double> surgingCoefficientA)
    {
        _surgingCoefficientA = move(surgingCoefficientA);
    }

    void NaturalStoneRevetmentLocationConstructionProperties::SetSurgingCoefficientB(
        unique_ptr<double> surgingCoefficientB)
    {
        _surgingCoefficientB = move(surgingCoefficientB);
    }

    void NaturalStoneRevetmentLocationConstructionProperties::SetSurgingCoefficientC(
        unique_ptr<double> surgingCoefficientC)
    {
        _surgingCoefficientC = move(surgingCoefficientC);
    }

    void NaturalStoneRevetmentLocationConstructionProperties::SetSurgingCoefficientN(
        unique_ptr<double> surgingCoefficientN)
    {
        _surgingCoefficientN = move(surgingCoefficientN);
    }

    void NaturalStoneRevetmentLocationConstructionProperties::SetSimilarityParameterThreshold(
        unique_ptr<double> similarityParameterThreshold)
    {
        _similarityParameterThreshold = move(similarityParameterThreshold);
    }

    void NaturalStoneRevetmentLocationConstructionProperties::SetUpperLimitLoadingAul(
        unique_ptr<double> upperLimitLoadingAul)
    {
        _upperLimitLoadingAul = move(upperLimitLoadingAul);
    }

    void NaturalStoneRevetmentLocationConstructionProperties::SetUpperLimitLoadingBul(
        unique_ptr<double> upperLimitLoadingBul)
    {
        _upperLimitLoadingBul = move(upperLimitLoadingBul);
    }

    void NaturalStoneRevetmentLocationConstructionProperties::SetUpperLimitLoadingCul(
        unique_ptr<double> upperLimitLoadingCul)
    {
        _upperLimitLoadingCul = move(upperLimitLoadingCul);
    }

    void NaturalStoneRevetmentLocationConstructionProperties::SetLowerLimitLoadingAll(
        unique_ptr<double> lowerLimitLoadingAll)
    {
        _lowerLimitLoadingAll = move(lowerLimitLoadingAll);
    }

    void NaturalStoneRevetmentLocationConstructionProperties::SetLowerLimitLoadingBll(
        unique_ptr<double> lowerLimitLoadingBll)
    {
        _lowerLimitLoadingBll = move(lowerLimitLoadingBll);
    }

    void NaturalStoneRevetmentLocationConstructionProperties::SetLowerLimitLoadingCll(
        unique_ptr<double> lowerLimitLoadingCll)
    {
        _lowerLimitLoadingCll = move(lowerLimitLoadingCll);
    }

    void NaturalStoneRevetmentLocationConstructionProperties::SetDistanceMaximumWaveElevationAsmax(
        unique_ptr<double> distanceMaximumWaveElevationAsmax)
    {
        _distanceMaximumWaveElevationAsmax = move(distanceMaximumWaveElevationAsmax);
    }

    void NaturalStoneRevetmentLocationConstructionProperties::SetDistanceMaximumWaveElevationBsmax(
        unique_ptr<double> distanceMaximumWaveElevationBsmax)
    {
        _distanceMaximumWaveElevationBsmax = move(distanceMaximumWaveElevationBsmax);
    }

    void NaturalStoneRevetmentLocationConstructionProperties::SetNormativeWidthOfWaveImpactAwi(
        unique_ptr<double> normativeWidthOfWaveImpactAwi)
    {
        _normativeWidthOfWaveImpactAwi = move(normativeWidthOfWaveImpactAwi);
    }

    void NaturalStoneRevetmentLocationConstructionProperties::SetNormativeWidthOfWaveImpactBwi(
        unique_ptr<double> normativeWidthOfWaveImpactBwi)
    {
        _normativeWidthOfWaveImpactBwi = move(normativeWidthOfWaveImpactBwi);
    }

    #pragma endregion

    #pragma region Get methods

    NaturalStoneRevetmentLocationConstructionProperties::TopLayerType NaturalStoneRevetmentLocationConstructionProperties::GetTopLayerType() const
    {
        return _topLayerType;
    }

    double NaturalStoneRevetmentLocationConstructionProperties::GetInitialDamage() const
    {
        return _initialDamage;
    }

    double NaturalStoneRevetmentLocationConstructionProperties::GetSlopeAngle() const
    {
        return _slopeAngle;
    }

    double NaturalStoneRevetmentLocationConstructionProperties::GetThicknessTopLayer() const
    {
        return _thicknessTopLayer;
    }

    double NaturalStoneRevetmentLocationConstructionProperties::GetRelativeDensity() const
    {
        return _relativeDensity;
    }

    const double* NaturalStoneRevetmentLocationConstructionProperties::GetPlungingCoefficientA() const
    {
        return _plungingCoefficientA.get();
    }

    const double* NaturalStoneRevetmentLocationConstructionProperties::GetPlungingCoefficientB() const
    {
        return _plungingCoefficientB.get();
    }

    const double* NaturalStoneRevetmentLocationConstructionProperties::GetPlungingCoefficientC() const
    {
        return _plungingCoefficientC.get();
    }

    const double* NaturalStoneRevetmentLocationConstructionProperties::GetPlungingCoefficientN() const
    {
        return _plungingCoefficientN.get();
    }

    const double* NaturalStoneRevetmentLocationConstructionProperties::GetSurgingCoefficientA() const
    {
        return _surgingCoefficientA.get();
    }

    const double* NaturalStoneRevetmentLocationConstructionProperties::GetSurgingCoefficientB() const
    {
        return _surgingCoefficientB.get();
    }

    const double* NaturalStoneRevetmentLocationConstructionProperties::GetSurgingCoefficientC() const
    {
        return _surgingCoefficientC.get();
    }

    const double* NaturalStoneRevetmentLocationConstructionProperties::GetSurgingCoefficientN() const
    {
        return _surgingCoefficientN.get();
    }

    const double* NaturalStoneRevetmentLocationConstructionProperties::GetSimilarityParameterThreshold() const
    {
        return _similarityParameterThreshold.get();
    }

    const double* NaturalStoneRevetmentLocationConstructionProperties::GetUpperLimitLoadingAul() const
    {
        return _upperLimitLoadingAul.get();
    }

    const double* NaturalStoneRevetmentLocationConstructionProperties::GetUpperLimitLoadingBul() const
    {
        return _upperLimitLoadingBul.get();
    }

    const double* NaturalStoneRevetmentLocationConstructionProperties::GetUpperLimitLoadingCul() const
    {
        return _upperLimitLoadingCul.get();
    }

    const double* NaturalStoneRevetmentLocationConstructionProperties::GetLowerLimitLoadingAll() const
    {
        return _lowerLimitLoadingAll.get();
    }

    const double* NaturalStoneRevetmentLocationConstructionProperties::GetLowerLimitLoadingBll() const
    {
        return _lowerLimitLoadingBll.get();
    }

    const double* NaturalStoneRevetmentLocationConstructionProperties::GetLowerLimitLoadingCll() const
    {
        return _lowerLimitLoadingCll.get();
    }

    const double* NaturalStoneRevetmentLocationConstructionProperties::GetDistanceMaximumWaveElevationAsmax() const
    {
        return _distanceMaximumWaveElevationAsmax.get();
    }

    const double* NaturalStoneRevetmentLocationConstructionProperties::GetDistanceMaximumWaveElevationBsmax() const
    {
        return _distanceMaximumWaveElevationBsmax.get();
    }

    const double* NaturalStoneRevetmentLocationConstructionProperties::GetNormativeWidthOfWaveImpactAwi() const
    {
        return _normativeWidthOfWaveImpactAwi.get();
    }

    const double* NaturalStoneRevetmentLocationConstructionProperties::GetNormativeWidthOfWaveImpactBwi() const
    {
        return _normativeWidthOfWaveImpactBwi.get();
    }

    #pragma endregion
}
