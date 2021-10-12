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

#include <utility>

namespace DiKErnel::Integration
{
    using namespace std;

    NaturalStoneRevetmentLocationConstructionProperties::NaturalStoneRevetmentLocationConstructionProperties(
        string name,
        const double x,
        const double outerSlope,
        const NaturalStoneRevetmentTopLayerType topLayerType,
        const double thicknessTopLayer,
        const double relativeDensity)
        : RevetmentLocationConstructionPropertiesBase(move(name), x),
          _outerSlope(outerSlope),
          _topLayerType(topLayerType),
          _thicknessTopLayer(thicknessTopLayer),
          _relativeDensity(relativeDensity) { }

    #pragma region Set methods

    void NaturalStoneRevetmentLocationConstructionProperties::SetHydraulicLoadAp(
        unique_ptr<double> hydraulicLoadAp)
    {
        _hydraulicLoadAp = move(hydraulicLoadAp);
    }

    void NaturalStoneRevetmentLocationConstructionProperties::SetHydraulicLoadBp(
        unique_ptr<double> hydraulicLoadBp)
    {
        _hydraulicLoadBp = move(hydraulicLoadBp);
    }

    void NaturalStoneRevetmentLocationConstructionProperties::SetHydraulicLoadCp(
        unique_ptr<double> hydraulicLoadCp)
    {
        _hydraulicLoadCp = move(hydraulicLoadCp);
    }

    void NaturalStoneRevetmentLocationConstructionProperties::SetHydraulicLoadNp(
        unique_ptr<double> hydraulicLoadNp)
    {
        _hydraulicLoadNp = move(hydraulicLoadNp);
    }

    void NaturalStoneRevetmentLocationConstructionProperties::SetHydraulicLoadAs(
        unique_ptr<double> hydraulicLoadAs)
    {
        _hydraulicLoadAs = move(hydraulicLoadAs);
    }

    void NaturalStoneRevetmentLocationConstructionProperties::SetHydraulicLoadBs(
        unique_ptr<double> hydraulicLoadBs)
    {
        _hydraulicLoadBs = move(hydraulicLoadBs);
    }

    void NaturalStoneRevetmentLocationConstructionProperties::SetHydraulicLoadCs(
        unique_ptr<double> hydraulicLoadCs)
    {
        _hydraulicLoadCs = move(hydraulicLoadCs);
    }

    void NaturalStoneRevetmentLocationConstructionProperties::SetHydraulicLoadNs(
        unique_ptr<double> hydraulicLoadNs)
    {
        _hydraulicLoadNs = move(hydraulicLoadNs);
    }

    void NaturalStoneRevetmentLocationConstructionProperties::SetHydraulicLoadXib(
        unique_ptr<double> hydraulicLoadXib)
    {
        _hydraulicLoadXib = move(hydraulicLoadXib);
    }

    void NaturalStoneRevetmentLocationConstructionProperties::SetSlopeUpperLevelAus(
        std::unique_ptr<double> slopeUpperLevelAus)
    {
        _slopeUpperLevelAus = move(slopeUpperLevelAus);
    }

    void NaturalStoneRevetmentLocationConstructionProperties::SetSlopeLowerLevelAls(
        std::unique_ptr<double> slopeLowerLevelAls)
    {
        _slopeLowerLevelAls = move(slopeLowerLevelAls);
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

    void NaturalStoneRevetmentLocationConstructionProperties::SetWaveAngleImpactBetamax(
        unique_ptr<double> waveAngleImpactBetamax)
    {
        _waveAngleImpactBetamax = move(waveAngleImpactBetamax);
    }

    #pragma endregion

    #pragma region Get methods

    double NaturalStoneRevetmentLocationConstructionProperties::GetOuterSlope() const
    {
        return _outerSlope;
    }

    NaturalStoneRevetmentTopLayerType NaturalStoneRevetmentLocationConstructionProperties::GetTopLayerType() const
    {
        return _topLayerType;
    }

    double NaturalStoneRevetmentLocationConstructionProperties::GetThicknessTopLayer() const
    {
        return _thicknessTopLayer;
    }

    double NaturalStoneRevetmentLocationConstructionProperties::GetRelativeDensity() const
    {
        return _relativeDensity;
    }

    const double* NaturalStoneRevetmentLocationConstructionProperties::GetHydraulicLoadAp() const
    {
        return _hydraulicLoadAp.get();
    }

    const double* NaturalStoneRevetmentLocationConstructionProperties::GetHydraulicLoadBp() const
    {
        return _hydraulicLoadBp.get();
    }

    const double* NaturalStoneRevetmentLocationConstructionProperties::GetHydraulicLoadCp() const
    {
        return _hydraulicLoadCp.get();
    }

    const double* NaturalStoneRevetmentLocationConstructionProperties::GetHydraulicLoadNp() const
    {
        return _hydraulicLoadNp.get();
    }

    const double* NaturalStoneRevetmentLocationConstructionProperties::GetHydraulicLoadAs() const
    {
        return _hydraulicLoadAs.get();
    }

    const double* NaturalStoneRevetmentLocationConstructionProperties::GetHydraulicLoadBs() const
    {
        return _hydraulicLoadBs.get();
    }

    const double* NaturalStoneRevetmentLocationConstructionProperties::GetHydraulicLoadCs() const
    {
        return _hydraulicLoadCs.get();
    }

    const double* NaturalStoneRevetmentLocationConstructionProperties::GetHydraulicLoadNs() const
    {
        return _hydraulicLoadNs.get();
    }

    const double* NaturalStoneRevetmentLocationConstructionProperties::GetHydraulicLoadXib() const
    {
        return _hydraulicLoadXib.get();
    }

    const double* NaturalStoneRevetmentLocationConstructionProperties::GetSlopeUpperLevelAus() const
    {
        return _slopeUpperLevelAus.get();
    }

    const double* NaturalStoneRevetmentLocationConstructionProperties::GetSlopeLowerLevelAls() const
    {
        return _slopeLowerLevelAls.get();
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

    const double* NaturalStoneRevetmentLocationConstructionProperties::GetWaveAngleImpactBetamax() const
    {
        return _waveAngleImpactBetamax.get();
    }

    #pragma endregion
}
