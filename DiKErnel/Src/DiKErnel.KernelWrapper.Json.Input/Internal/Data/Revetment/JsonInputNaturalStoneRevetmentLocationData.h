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

#pragma once

#include <memory>

#include "IJsonInputRevetmentLocationData.h"
#include "JsonInputNaturalStoneRevetmentTopLayerType.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    class JsonInputNaturalStoneRevetmentLocationData : public IJsonInputRevetmentLocationData
    {
        public:
            explicit JsonInputNaturalStoneRevetmentLocationData(
                double relativeDensity,
                double thicknessTopLayer,
                JsonInputNaturalStoneRevetmentTopLayerType topLayerType);

            #pragma region Set methods

            void SetHydraulicLoadAp(
                std::unique_ptr<double> hydraulicLoadAp);

            void SetHydraulicLoadBp(
                std::unique_ptr<double> hydraulicLoadBp);

            void SetHydraulicLoadCp(
                std::unique_ptr<double> hydraulicLoadCp);

            void SetHydraulicLoadNp(
                std::unique_ptr<double> hydraulicLoadNp);

            void SetHydraulicLoadAs(
                std::unique_ptr<double> hydraulicLoadAs);

            void SetHydraulicLoadBs(
                std::unique_ptr<double> hydraulicLoadBs);

            void SetHydraulicLoadCs(
                std::unique_ptr<double> hydraulicLoadCs);

            void SetHydraulicLoadNs(
                std::unique_ptr<double> hydraulicLoadNs);

            void SetHydraulicLoadXib(
                std::unique_ptr<double> hydraulicLoadXib);

            void SetUpperLimitLoadingAul(
                std::unique_ptr<double> upperLimitLoadingAul);

            void SetUpperLimitLoadingBul(
                std::unique_ptr<double> upperLimitLoadingBul);

            void SetUpperLimitLoadingCul(
                std::unique_ptr<double> upperLimitLoadingCul);

            void SetLowerLimitLoadingAll(
                std::unique_ptr<double> lowerLimitLoadingAll);

            void SetLowerLimitLoadingBll(
                std::unique_ptr<double> lowerLimitLoadingBll);

            void SetLowerLimitLoadingCll(
                std::unique_ptr<double> lowerLimitLoadingCll);

            void SetDistanceMaximumWaveElevationAsmax(
                std::unique_ptr<double> distanceMaximumWaveElevationAsmax);

            void SetDistanceMaximumWaveElevationBsmax(
                std::unique_ptr<double> distanceMaximumWaveElevationBsmax);

            void SetNormativeWidthOfWaveImpactAwi(
                std::unique_ptr<double> normativeWidthOfWaveImpactAwi);

            void SetNormativeWidthOfWaveImpactBwi(
                std::unique_ptr<double> normativeWidthOfWaveImpactBwi);

            void SetWaveAngleImpactBetamax(
                std::unique_ptr<double> waveAngleImpactBetamax);

            #pragma endregion

            #pragma region Get methods

            double GetRelativeDensity() const;

            double GetThicknessTopLayer() const;

            JsonInputNaturalStoneRevetmentTopLayerType GetTopLayerType() const;

            const double* GetHydraulicLoadXib() const;

            const double* GetHydraulicLoadAp() const;

            const double* GetHydraulicLoadBp() const;

            const double* GetHydraulicLoadCp() const;

            const double* GetHydraulicLoadNp() const;

            const double* GetHydraulicLoadAs() const;

            const double* GetHydraulicLoadBs() const;

            const double* GetHydraulicLoadCs() const;

            const double* GetHydraulicLoadNs() const;

            const double* GetUpperLimitLoadingAul() const;

            const double* GetUpperLimitLoadingBul() const;

            const double* GetUpperLimitLoadingCul() const;

            const double* GetLowerLimitLoadingAll() const;

            const double* GetLowerLimitLoadingBll() const;

            const double* GetLowerLimitLoadingCll() const;

            const double* GetDistanceMaximumWaveElevationAsmax() const;

            const double* GetDistanceMaximumWaveElevationBsmax() const;

            const double* GetNormativeWidthOfWaveImpactAwi() const;

            const double* GetNormativeWidthOfWaveImpactBwi() const;

            const double* GetWaveAngleImpactBetamax() const;

            #pragma endregion

        private:
            double _relativeDensity;
            double _thicknessTopLayer;
            JsonInputNaturalStoneRevetmentTopLayerType _topLayerType;
            std::unique_ptr<double> _hydraulicLoadXib = nullptr;
            std::unique_ptr<double> _hydraulicLoadAp = nullptr;
            std::unique_ptr<double> _hydraulicLoadBp = nullptr;
            std::unique_ptr<double> _hydraulicLoadCp = nullptr;
            std::unique_ptr<double> _hydraulicLoadNp = nullptr;
            std::unique_ptr<double> _hydraulicLoadAs = nullptr;
            std::unique_ptr<double> _hydraulicLoadBs = nullptr;
            std::unique_ptr<double> _hydraulicLoadCs = nullptr;
            std::unique_ptr<double> _hydraulicLoadNs = nullptr;
            std::unique_ptr<double> _upperLimitLoadingAul = nullptr;
            std::unique_ptr<double> _upperLimitLoadingBul = nullptr;
            std::unique_ptr<double> _upperLimitLoadingCul = nullptr;
            std::unique_ptr<double> _lowerLimitLoadingAll = nullptr;
            std::unique_ptr<double> _lowerLimitLoadingBll = nullptr;
            std::unique_ptr<double> _lowerLimitLoadingCll = nullptr;
            std::unique_ptr<double> _distanceMaximumWaveElevationAsmax = nullptr;
            std::unique_ptr<double> _distanceMaximumWaveElevationBsmax = nullptr;
            std::unique_ptr<double> _normativeWidthOfWaveImpactAwi = nullptr;
            std::unique_ptr<double> _normativeWidthOfWaveImpactBwi = nullptr;
            std::unique_ptr<double> _waveAngleImpactBetamax = nullptr;
    };
}
