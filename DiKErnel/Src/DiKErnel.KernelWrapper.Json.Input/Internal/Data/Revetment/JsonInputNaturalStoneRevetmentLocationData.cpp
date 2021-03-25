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

    void JsonInputNaturalStoneRevetmentLocationData::SetHydraulicLoadAp(
        unique_ptr<double> hydraulicLoadAp)
    {
        _hydraulicLoadAp = move(hydraulicLoadAp);
    }

    void JsonInputNaturalStoneRevetmentLocationData::SetHydraulicLoadBp(
        unique_ptr<double> hydraulicLoadBp)
    {
        _hydraulicLoadBp = move(hydraulicLoadBp);
    }

    void JsonInputNaturalStoneRevetmentLocationData::SetHydraulicLoadCp(
        unique_ptr<double> hydraulicLoadCp)
    {
        _hydraulicLoadCp = move(hydraulicLoadCp);
    }

    void JsonInputNaturalStoneRevetmentLocationData::SetHydraulicLoadNp(
        unique_ptr<double> hydraulicLoadNp)
    {
        _hydraulicLoadNp = move(hydraulicLoadNp);
    }

    void JsonInputNaturalStoneRevetmentLocationData::SetHydraulicLoadAs(
        unique_ptr<double> hydraulicLoadAs)
    {
        _hydraulicLoadAs = move(hydraulicLoadAs);
    }

    void JsonInputNaturalStoneRevetmentLocationData::SetHydraulicLoadBs(
        unique_ptr<double> hydraulicLoadBs)
    {
        _hydraulicLoadBs = move(hydraulicLoadBs);
    }

    void JsonInputNaturalStoneRevetmentLocationData::SetHydraulicLoadCs(
        unique_ptr<double> hydraulicLoadCs)
    {
        _hydraulicLoadCs = move(hydraulicLoadCs);
    }

    void JsonInputNaturalStoneRevetmentLocationData::SetHydraulicLoadNs(
        unique_ptr<double> hydraulicLoadNs)
    {
        _hydraulicLoadNs = move(hydraulicLoadNs);
    }

    void JsonInputNaturalStoneRevetmentLocationData::SetHydraulicLoadXib(
        unique_ptr<double> hydraulicLoadXib)
    {
        _hydraulicLoadXib = move(hydraulicLoadXib);
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

    void JsonInputNaturalStoneRevetmentLocationData::SetWaveAngleImpactBetamax(
        std::unique_ptr<double> waveAngleImpactBetamax)
    {
        _waveAngleImpactBetamax = move(waveAngleImpactBetamax);
    }

    #pragma endregion

    #pragma region Get methods

    JsonInputNaturalStoneRevetmentLocationData::TopLayerType JsonInputNaturalStoneRevetmentLocationData::GetTopLayerType() const
    {
        return _topLayerType;
    }

    const double* JsonInputNaturalStoneRevetmentLocationData::GetHydraulicLoadXib() const
    {
        return _hydraulicLoadXib.get();
    }

    const double* JsonInputNaturalStoneRevetmentLocationData::GetHydraulicLoadAp() const
    {
        return _hydraulicLoadAp.get();
    }

    const double* JsonInputNaturalStoneRevetmentLocationData::GetHydraulicLoadBp() const
    {
        return _hydraulicLoadBp.get();
    }

    const double* JsonInputNaturalStoneRevetmentLocationData::GetHydraulicLoadCp() const
    {
        return _hydraulicLoadCp.get();
    }

    const double* JsonInputNaturalStoneRevetmentLocationData::GetHydraulicLoadNp() const
    {
        return _hydraulicLoadNp.get();
    }

    const double* JsonInputNaturalStoneRevetmentLocationData::GetHydraulicLoadAs() const
    {
        return _hydraulicLoadAs.get();
    }

    const double* JsonInputNaturalStoneRevetmentLocationData::GetHydraulicLoadBs() const
    {
        return _hydraulicLoadBs.get();
    }

    const double* JsonInputNaturalStoneRevetmentLocationData::GetHydraulicLoadCs() const
    {
        return _hydraulicLoadCs.get();
    }

    const double* JsonInputNaturalStoneRevetmentLocationData::GetHydraulicLoadNs() const
    {
        return _hydraulicLoadNs.get();
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

    const double* JsonInputNaturalStoneRevetmentLocationData::GetWaveAngleImpactBetamax() const
    {
        return _waveAngleImpactBetamax.get();
    }

    #pragma endregion
}
