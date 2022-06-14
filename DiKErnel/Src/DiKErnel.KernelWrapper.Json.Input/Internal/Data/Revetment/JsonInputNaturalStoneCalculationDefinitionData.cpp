// Copyright (C) Stichting Deltares 2022. All rights reserved.
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

#include "JsonInputNaturalStoneCalculationDefinitionData.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    using namespace std;

    JsonInputNaturalStoneCalculationDefinitionData::JsonInputNaturalStoneCalculationDefinitionData(
        unique_ptr<double> failureNumber)
        : JsonInputCalculationDefinitionData(move(failureNumber)) {}

    #pragma region Set methods

    void JsonInputNaturalStoneCalculationDefinitionData::SetHydraulicLoadAp(
        unique_ptr<double> hydraulicLoadAp)
    {
        _hydraulicLoadAp = move(hydraulicLoadAp);
    }

    void JsonInputNaturalStoneCalculationDefinitionData::SetHydraulicLoadBp(
        unique_ptr<double> hydraulicLoadBp)
    {
        _hydraulicLoadBp = move(hydraulicLoadBp);
    }

    void JsonInputNaturalStoneCalculationDefinitionData::SetHydraulicLoadCp(
        unique_ptr<double> hydraulicLoadCp)
    {
        _hydraulicLoadCp = move(hydraulicLoadCp);
    }

    void JsonInputNaturalStoneCalculationDefinitionData::SetHydraulicLoadNp(
        unique_ptr<double> hydraulicLoadNp)
    {
        _hydraulicLoadNp = move(hydraulicLoadNp);
    }

    void JsonInputNaturalStoneCalculationDefinitionData::SetHydraulicLoadAs(
        unique_ptr<double> hydraulicLoadAs)
    {
        _hydraulicLoadAs = move(hydraulicLoadAs);
    }

    void JsonInputNaturalStoneCalculationDefinitionData::SetHydraulicLoadBs(
        unique_ptr<double> hydraulicLoadBs)
    {
        _hydraulicLoadBs = move(hydraulicLoadBs);
    }

    void JsonInputNaturalStoneCalculationDefinitionData::SetHydraulicLoadCs(
        unique_ptr<double> hydraulicLoadCs)
    {
        _hydraulicLoadCs = move(hydraulicLoadCs);
    }

    void JsonInputNaturalStoneCalculationDefinitionData::SetHydraulicLoadNs(
        unique_ptr<double> hydraulicLoadNs)
    {
        _hydraulicLoadNs = move(hydraulicLoadNs);
    }

    void JsonInputNaturalStoneCalculationDefinitionData::SetHydraulicLoadXib(
        unique_ptr<double> hydraulicLoadXib)
    {
        _hydraulicLoadXib = move(hydraulicLoadXib);
    }

    void JsonInputNaturalStoneCalculationDefinitionData::SetSlopeUpperLevelAus(
        unique_ptr<double> slopeUpperLevelAus)
    {
        _slopeUpperLevelAus = move(slopeUpperLevelAus);
    }

    void JsonInputNaturalStoneCalculationDefinitionData::SetSlopeLowerLevelAls(
        unique_ptr<double> slopeLowerLevelAls)
    {
        _slopeLowerLevelAls = move(slopeLowerLevelAls);
    }

    void JsonInputNaturalStoneCalculationDefinitionData::SetUpperLimitLoadingAul(
        unique_ptr<double> upperLimitLoadingAul)
    {
        _upperLimitLoadingAul = move(upperLimitLoadingAul);
    }

    void JsonInputNaturalStoneCalculationDefinitionData::SetUpperLimitLoadingBul(
        unique_ptr<double> upperLimitLoadingBul)
    {
        _upperLimitLoadingBul = move(upperLimitLoadingBul);
    }

    void JsonInputNaturalStoneCalculationDefinitionData::SetUpperLimitLoadingCul(
        unique_ptr<double> upperLimitLoadingCul)
    {
        _upperLimitLoadingCul = move(upperLimitLoadingCul);
    }

    void JsonInputNaturalStoneCalculationDefinitionData::SetLowerLimitLoadingAll(
        unique_ptr<double> lowerLimitLoadingAll)
    {
        _lowerLimitLoadingAll = move(lowerLimitLoadingAll);
    }

    void JsonInputNaturalStoneCalculationDefinitionData::SetLowerLimitLoadingBll(
        unique_ptr<double> lowerLimitLoadingBll)
    {
        _lowerLimitLoadingBll = move(lowerLimitLoadingBll);
    }

    void JsonInputNaturalStoneCalculationDefinitionData::SetLowerLimitLoadingCll(
        unique_ptr<double> lowerLimitLoadingCll)
    {
        _lowerLimitLoadingCll = move(lowerLimitLoadingCll);
    }

    void JsonInputNaturalStoneCalculationDefinitionData::SetDistanceMaximumWaveElevationAsmax(
        unique_ptr<double> distanceMaximumWaveElevationAsmax)
    {
        _distanceMaximumWaveElevationAsmax = move(distanceMaximumWaveElevationAsmax);
    }

    void JsonInputNaturalStoneCalculationDefinitionData::SetDistanceMaximumWaveElevationBsmax(
        unique_ptr<double> distanceMaximumWaveElevationBsmax)
    {
        _distanceMaximumWaveElevationBsmax = move(distanceMaximumWaveElevationBsmax);
    }

    void JsonInputNaturalStoneCalculationDefinitionData::SetNormativeWidthOfWaveImpactAwi(
        unique_ptr<double> normativeWidthOfWaveImpactAwi)
    {
        _normativeWidthOfWaveImpactAwi = move(normativeWidthOfWaveImpactAwi);
    }

    void JsonInputNaturalStoneCalculationDefinitionData::SetNormativeWidthOfWaveImpactBwi(
        unique_ptr<double> normativeWidthOfWaveImpactBwi)
    {
        _normativeWidthOfWaveImpactBwi = move(normativeWidthOfWaveImpactBwi);
    }

    void JsonInputNaturalStoneCalculationDefinitionData::SetWaveAngleImpactBetamax(
        unique_ptr<double> waveAngleImpactBetamax)
    {
        _waveAngleImpactBetamax = move(waveAngleImpactBetamax);
    }

    #pragma endregion

    #pragma region Get methods

    const double* JsonInputNaturalStoneCalculationDefinitionData::GetHydraulicLoadXib() const
    {
        return _hydraulicLoadXib.get();
    }

    const double* JsonInputNaturalStoneCalculationDefinitionData::GetHydraulicLoadAp() const
    {
        return _hydraulicLoadAp.get();
    }

    const double* JsonInputNaturalStoneCalculationDefinitionData::GetHydraulicLoadBp() const
    {
        return _hydraulicLoadBp.get();
    }

    const double* JsonInputNaturalStoneCalculationDefinitionData::GetHydraulicLoadCp() const
    {
        return _hydraulicLoadCp.get();
    }

    const double* JsonInputNaturalStoneCalculationDefinitionData::GetHydraulicLoadNp() const
    {
        return _hydraulicLoadNp.get();
    }

    const double* JsonInputNaturalStoneCalculationDefinitionData::GetHydraulicLoadAs() const
    {
        return _hydraulicLoadAs.get();
    }

    const double* JsonInputNaturalStoneCalculationDefinitionData::GetHydraulicLoadBs() const
    {
        return _hydraulicLoadBs.get();
    }

    const double* JsonInputNaturalStoneCalculationDefinitionData::GetHydraulicLoadCs() const
    {
        return _hydraulicLoadCs.get();
    }

    const double* JsonInputNaturalStoneCalculationDefinitionData::GetHydraulicLoadNs() const
    {
        return _hydraulicLoadNs.get();
    }

    const double* JsonInputNaturalStoneCalculationDefinitionData::GetSlopeUpperLevelAus() const
    {
        return _slopeUpperLevelAus.get();
    }

    const double* JsonInputNaturalStoneCalculationDefinitionData::GetSlopeLowerLevelAls() const
    {
        return _slopeLowerLevelAls.get();
    }

    const double* JsonInputNaturalStoneCalculationDefinitionData::GetUpperLimitLoadingAul() const
    {
        return _upperLimitLoadingAul.get();
    }

    const double* JsonInputNaturalStoneCalculationDefinitionData::GetUpperLimitLoadingBul() const
    {
        return _upperLimitLoadingBul.get();
    }

    const double* JsonInputNaturalStoneCalculationDefinitionData::GetUpperLimitLoadingCul() const
    {
        return _upperLimitLoadingCul.get();
    }

    const double* JsonInputNaturalStoneCalculationDefinitionData::GetLowerLimitLoadingAll() const
    {
        return _lowerLimitLoadingAll.get();
    }

    const double* JsonInputNaturalStoneCalculationDefinitionData::GetLowerLimitLoadingBll() const
    {
        return _lowerLimitLoadingBll.get();
    }

    const double* JsonInputNaturalStoneCalculationDefinitionData::GetLowerLimitLoadingCll() const
    {
        return _lowerLimitLoadingCll.get();
    }

    const double* JsonInputNaturalStoneCalculationDefinitionData::GetDistanceMaximumWaveElevationAsmax() const
    {
        return _distanceMaximumWaveElevationAsmax.get();
    }

    const double* JsonInputNaturalStoneCalculationDefinitionData::GetDistanceMaximumWaveElevationBsmax() const
    {
        return _distanceMaximumWaveElevationBsmax.get();
    }

    const double* JsonInputNaturalStoneCalculationDefinitionData::GetNormativeWidthOfWaveImpactAwi() const
    {
        return _normativeWidthOfWaveImpactAwi.get();
    }

    const double* JsonInputNaturalStoneCalculationDefinitionData::GetNormativeWidthOfWaveImpactBwi() const
    {
        return _normativeWidthOfWaveImpactBwi.get();
    }

    const double* JsonInputNaturalStoneCalculationDefinitionData::GetWaveAngleImpactBetamax() const
    {
        return _waveAngleImpactBetamax.get();
    }

    #pragma endregion
}
