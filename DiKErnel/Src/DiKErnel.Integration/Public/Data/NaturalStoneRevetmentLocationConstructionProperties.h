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
#include <string>

#include "NaturalStoneRevetmentTopLayerType.h"
#include "RevetmentLocationConstructionPropertiesBase.h"

namespace DiKErnel::Integration
{
    /*!
     * \brief Construction properties to construct natural stone revetment location dependent
     *        input.
     */
    class NaturalStoneRevetmentLocationConstructionProperties : public RevetmentLocationConstructionPropertiesBase
    {
        public:
            /*!
             * \brief Creates a new instance.
             * \param name
             *        The name.
             * \param x
             *        The x coordinate.
             * \param tanA
             *        The tanA.
             * \param positionZ
             *        The vertical position.
             * \param topLayerType
             *        The type of the top layer.
             * \param thicknessTopLayer
             *        The thickness of the top layer.
             * \param relativeDensity
             *        The relative density.
             */
            explicit NaturalStoneRevetmentLocationConstructionProperties(
                std::string name,
                double x,
                double tanA,
                double positionZ,
                NaturalStoneRevetmentTopLayerType topLayerType,
                double thicknessTopLayer,
                double relativeDensity);

            #pragma region Set methods

            /*!
             * \brief Sets the Ap coefficient.
             * \param hydraulicLoadAp
             *        The Ap coefficient.
             */
            void SetHydraulicLoadAp(
                std::unique_ptr<double> hydraulicLoadAp);

            /*!
             * \brief Sets the Bp coefficient.
             * \param hydraulicLoadBp
             *        The Bp coefficient.
             */
            void SetHydraulicLoadBp(
                std::unique_ptr<double> hydraulicLoadBp);

            /*!
             * \brief Sets the Cp coefficient.
             * \param hydraulicLoadCp
             *        The Cp coefficient.
             */
            void SetHydraulicLoadCp(
                std::unique_ptr<double> hydraulicLoadCp);

            /*!
             * \brief Sets the Np coefficient.
             * \param hydraulicLoadNp
             *        The Np coefficient.
             */
            void SetHydraulicLoadNp(
                std::unique_ptr<double> hydraulicLoadNp);

            /*!
             * \brief Sets the As coefficient.
             * \param hydraulicLoadAs
             *        The As coefficient.
             */
            void SetHydraulicLoadAs(
                std::unique_ptr<double> hydraulicLoadAs);

            /*!
             * \brief Sets the Bs coefficient.
             * \param hydraulicLoadBs
             *        The Bs coefficient.
             */
            void SetHydraulicLoadBs(
                std::unique_ptr<double> hydraulicLoadBs);

            /*!
             * \brief Sets the Cs coefficient.
             * \param hydraulicLoadCs
             *        The Cs coefficient.
             */
            void SetHydraulicLoadCs(
                std::unique_ptr<double> hydraulicLoadCs);

            /*!
             * \brief Sets the Ns coefficient.
             * \param hydraulicLoadNs
             *        The Ns coefficient.
             */
            void SetHydraulicLoadNs(
                std::unique_ptr<double> hydraulicLoadNs);

            /*!
             * \brief Sets the Xib coefficient.
             * \param hydraulicLoadXib
             *        The Xib coefficient.
             */
            void SetHydraulicLoadXib(
                std::unique_ptr<double> hydraulicLoadXib);

            /*!
             * \brief Sets the Aus coefficient.
             * \param slopeUpperLevelAus
             *        The Aus coefficient.
             */
            void SetSlopeUpperLevelAus(
                std::unique_ptr<double> slopeUpperLevelAus);

            /*!
             * \brief Sets the Als coefficient.
             * \param slopeLowerLevelAls
             *        The Als coefficient.
             */
            void SetSlopeLowerLevelAus(
                std::unique_ptr<double> slopeLowerLevelAls);

            /*!
             * \brief Sets the Aul coefficient.
             * \param upperLimitLoadingAul
             *        The Aul coefficient.
             */
            void SetUpperLimitLoadingAul(
                std::unique_ptr<double> upperLimitLoadingAul);

            /*!
             * \brief Sets the Bul coefficient.
             * \param upperLimitLoadingBul
             *        The Bul coefficient.
             */
            void SetUpperLimitLoadingBul(
                std::unique_ptr<double> upperLimitLoadingBul);

            /*!
             * \brief Sets the Cul coefficient.
             * \param upperLimitLoadingCul
             *        The Cul coefficient.
             */
            void SetUpperLimitLoadingCul(
                std::unique_ptr<double> upperLimitLoadingCul);

            /*!
             * \brief Sets the All coefficient.
             * \param lowerLimitLoadingAll
             *        The All coefficient.
             */
            void SetLowerLimitLoadingAll(
                std::unique_ptr<double> lowerLimitLoadingAll);

            /*!
             * \brief Sets the Bll coefficient.
             * \param lowerLimitLoadingBll
             *        The Bll coefficient.
             */
            void SetLowerLimitLoadingBll(
                std::unique_ptr<double> lowerLimitLoadingBll);

            /*!
             * \brief Sets the Cll coefficient.
             * \param lowerLimitLoadingCll
             *        The Cll coefficient.
             */
            void SetLowerLimitLoadingCll(
                std::unique_ptr<double> lowerLimitLoadingCll);

            /*!
             * \brief Sets the Asmax coefficient.
             * \param distanceMaximumWaveElevationAsmax
             *        The Asmax coefficient.
             */
            void SetDistanceMaximumWaveElevationAsmax(
                std::unique_ptr<double> distanceMaximumWaveElevationAsmax);

            /*!
             * \brief Sets the Bsmax coefficient.
             * \param distanceMaximumWaveElevationBsmax
             *        The Bsmax coefficient.
             */
            void SetDistanceMaximumWaveElevationBsmax(
                std::unique_ptr<double> distanceMaximumWaveElevationBsmax);

            /*!
             * \brief Sets the Awi coefficient.
             * \param normativeWidthOfWaveImpactAwi
             *        The Awi coefficient.
             */
            void SetNormativeWidthOfWaveImpactAwi(
                std::unique_ptr<double> normativeWidthOfWaveImpactAwi);

            /*!
             * \brief Sets the Bwi coefficient.
             * \param normativeWidthOfWaveImpactBwi
             *        The Bwi coefficient.
             */
            void SetNormativeWidthOfWaveImpactBwi(
                std::unique_ptr<double> normativeWidthOfWaveImpactBwi);

            /*!
             * \brief Sets the Betamax coefficient.
             * \param waveAngleImpactBetamax
             *        The Betamax coefficient.
             */
            void SetWaveAngleImpactBetamax(
                std::unique_ptr<double> waveAngleImpactBetamax);

            #pragma endregion

            #pragma region Get methods

            /*!
             * \brief Gets the tanA.
             * \return The tanA.
             */
            double GetTanA() const;

            /*!
             * \brief Gets the type of the top layer.
             * \return The type of the top layer.
             */
            NaturalStoneRevetmentTopLayerType GetTopLayerType() const;

            /*!
             * \brief Gets the thickness of the top layer.
             * \return The thickness of the top layer.
             */
            double GetThicknessTopLayer() const;

            /*!
             * \brief Gets the relative density.
             * \return The relative density.
             */
            double GetRelativeDensity() const;

            /*!
             * \brief Gets the Ap coefficient.
             * \return The Ap coefficient.
             */
            const double* GetHydraulicLoadAp() const;

            /*!
             * \brief Gets the Bp coefficient.
             * \return The Bp coefficient.
             */
            const double* GetHydraulicLoadBp() const;

            /*!
             * \brief Gets the Cp coefficient.
             * \return The Cp coefficient.
             */
            const double* GetHydraulicLoadCp() const;

            /*!
             * \brief Gets the Np coefficient.
             * \return The Np coefficient.
             */
            const double* GetHydraulicLoadNp() const;

            /*!
             * \brief Gets the As coefficient.
             * \return The As coefficient.
             */
            const double* GetHydraulicLoadAs() const;

            /*!
             * \brief Gets the Bs coefficient.
             * \return The Bs coefficient.
             */
            const double* GetHydraulicLoadBs() const;

            /*!
             * \brief Gets the Cs coefficient.
             * \return The Cs coefficient.
             */
            const double* GetHydraulicLoadCs() const;

            /*!
             * \brief Gets the Ns coefficient.
             * \return The Ns coefficient.
             */
            const double* GetHydraulicLoadNs() const;

            /*!
             * \brief Gets the Xib coefficient.
             * \return The Xib coefficient.
             */
            const double* GetHydraulicLoadXib() const;

            /*!
             * \brief Gets the Aus coefficient.
             * \return The Aus coefficient.
             */
            const double* GetSlopeUpperLevelAus() const;

            /*!
             * \brief Gets the Als coefficient.
             * \return The Als coefficient.
             */
            const double* GetSlopeLowerLevelAls() const;

            /*!
             * \brief Gets the Aul coefficient.
             * \return The Aul coefficient.
             */
            const double* GetUpperLimitLoadingAul() const;

            /*!
             * \brief Gets the Bul coefficient.
             * \return The Bul coefficient.
             */
            const double* GetUpperLimitLoadingBul() const;

            /*!
             * \brief Gets the Cul coefficient.
             * \return The Cul coefficient.
             */
            const double* GetUpperLimitLoadingCul() const;

            /*!
             * \brief Gets the All coefficient.
             * \return The All coefficient.
             */
            const double* GetLowerLimitLoadingAll() const;

            /*!
             * \brief Gets the Bll coefficient.
             * \return The Bll coefficient.
             */
            const double* GetLowerLimitLoadingBll() const;

            /*!
             * \brief Gets the Cll coefficient.
             * \return The Cll coefficient.
             */
            const double* GetLowerLimitLoadingCll() const;

            /*!
             * \brief Gets the Asmax coefficient.
             * \return The Asmax coefficient.
             */
            const double* GetDistanceMaximumWaveElevationAsmax() const;

            /*!
             * \brief Gets the Bsmax coefficient.
             * \return The Bsmax coefficient.
             */
            const double* GetDistanceMaximumWaveElevationBsmax() const;

            /*!
             * \brief Gets the Awi coefficient.
             * \return The Awi coefficient.
             */
            const double* GetNormativeWidthOfWaveImpactAwi() const;

            /*!
             * \brief Gets the Bwi coefficient.
             * \return The Bwi coefficient.
             */
            const double* GetNormativeWidthOfWaveImpactBwi() const;

            /*!
             * \brief Gets the Betamax coefficient.
             * \return The Betmax coefficient.
             */
            const double* GetWaveAngleImpactBetamax() const;

            #pragma endregion

        private:
            double _tanA;
            NaturalStoneRevetmentTopLayerType _topLayerType;
            double _thicknessTopLayer;
            double _relativeDensity;
            std::unique_ptr<double> _initialDamage = nullptr;
            std::unique_ptr<double> _failureNumber = nullptr;
            std::unique_ptr<double> _hydraulicLoadAp = nullptr;
            std::unique_ptr<double> _hydraulicLoadBp = nullptr;
            std::unique_ptr<double> _hydraulicLoadCp = nullptr;
            std::unique_ptr<double> _hydraulicLoadNp = nullptr;
            std::unique_ptr<double> _hydraulicLoadAs = nullptr;
            std::unique_ptr<double> _hydraulicLoadBs = nullptr;
            std::unique_ptr<double> _hydraulicLoadCs = nullptr;
            std::unique_ptr<double> _hydraulicLoadNs = nullptr;
            std::unique_ptr<double> _hydraulicLoadXib = nullptr;
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
