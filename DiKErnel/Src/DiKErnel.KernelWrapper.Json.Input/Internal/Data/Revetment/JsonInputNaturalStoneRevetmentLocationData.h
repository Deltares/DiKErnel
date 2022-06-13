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

#pragma once

#include <memory>

namespace DiKErnel::KernelWrapper::Json::Input
{
    class JsonInputNaturalStoneRevetmentLocationData
    {
        public:
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

            void SetSlopeUpperLevelAus(
                std::unique_ptr<double> slopeUpperLevelAus);

            void SetSlopeLowerLevelAls(
                std::unique_ptr<double> slopeLowerLevelAls);

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

            [[nodiscard]]
            const double* GetHydraulicLoadXib() const;

            [[nodiscard]]
            const double* GetHydraulicLoadAp() const;

            [[nodiscard]]
            const double* GetHydraulicLoadBp() const;

            [[nodiscard]]
            const double* GetHydraulicLoadCp() const;

            [[nodiscard]]
            const double* GetHydraulicLoadNp() const;

            [[nodiscard]]
            const double* GetHydraulicLoadAs() const;

            [[nodiscard]]
            const double* GetHydraulicLoadBs() const;

            [[nodiscard]]
            const double* GetHydraulicLoadCs() const;

            [[nodiscard]]
            const double* GetHydraulicLoadNs() const;

            [[nodiscard]]
            const double* GetSlopeUpperLevelAus() const;

            [[nodiscard]]
            const double* GetSlopeLowerLevelAls() const;

            [[nodiscard]]
            const double* GetUpperLimitLoadingAul() const;

            [[nodiscard]]
            const double* GetUpperLimitLoadingBul() const;

            [[nodiscard]]
            const double* GetUpperLimitLoadingCul() const;

            [[nodiscard]]
            const double* GetLowerLimitLoadingAll() const;

            [[nodiscard]]
            const double* GetLowerLimitLoadingBll() const;

            [[nodiscard]]
            const double* GetLowerLimitLoadingCll() const;

            [[nodiscard]]
            const double* GetDistanceMaximumWaveElevationAsmax() const;

            [[nodiscard]]
            const double* GetDistanceMaximumWaveElevationBsmax() const;

            [[nodiscard]]
            const double* GetNormativeWidthOfWaveImpactAwi() const;

            [[nodiscard]]
            const double* GetNormativeWidthOfWaveImpactBwi() const;

            [[nodiscard]]
            const double* GetWaveAngleImpactBetamax() const;

            #pragma endregion

        private:
            std::unique_ptr<double> _hydraulicLoadXib = nullptr;
            std::unique_ptr<double> _hydraulicLoadAp = nullptr;
            std::unique_ptr<double> _hydraulicLoadBp = nullptr;
            std::unique_ptr<double> _hydraulicLoadCp = nullptr;
            std::unique_ptr<double> _hydraulicLoadNp = nullptr;
            std::unique_ptr<double> _hydraulicLoadAs = nullptr;
            std::unique_ptr<double> _hydraulicLoadBs = nullptr;
            std::unique_ptr<double> _hydraulicLoadCs = nullptr;
            std::unique_ptr<double> _hydraulicLoadNs = nullptr;
            std::unique_ptr<double> _slopeUpperLevelAus = nullptr;
            std::unique_ptr<double> _slopeLowerLevelAls = nullptr;
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
