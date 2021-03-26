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

namespace DiKErnel::Integration
{
    /*!
     * \brief Construction properties to construct natural stone revetment location dependent
     *        input.
     */
    class NaturalStoneRevetmentLocationConstructionProperties
    {
        public:

            /*!
             * \brief The types of the top layer.
             */
            enum class TopLayerType
            {
                NordicStone
            };

            /*!
             * \brief Creates a new instance.
             * \param topLayerType
             *        The type of the top layer.
             * \param name
             *        The name.
             * \param tanA
             *        The tanA value.
             * \param thicknessTopLayer
             *        The thickness of the top layer.
             * \param relativeDensity
             *        The relative density.
             */
            explicit NaturalStoneRevetmentLocationConstructionProperties(
                TopLayerType topLayerType,
                std::string name,
                double tanA,
                double thicknessTopLayer,
                double relativeDensity);

            #pragma region Set methods

            /*!
             * \brief Sets the initial damage.
             * \param initialDamage
             *        The initial damage.
             */
            void SetInitialDamage(
                std::unique_ptr<double> initialDamage);

            /*!
             * \brief Sets the failure number.
             * \param failureNumber
             *        The failure number.
             */
            void SetFailureNumber(
                std::unique_ptr<double> failureNumber);

            /*!
             * \brief Sets the hydraulic load Ap.
             * \param hydraulicLoadAp
             *        The hydraulic load Ap.
             */
            void SetHydraulicLoadAp(
                std::unique_ptr<double> hydraulicLoadAp);

            /*!
             * \brief Sets the hydraulic load Bp.
             * \param hydraulicLoadBp
             *        The hydraulic load Bp.
             */
            void SetHydraulicLoadBp(
                std::unique_ptr<double> hydraulicLoadBp);

            /*!
             * \brief Sets the hydraulic load Cp.
             * \param hydraulicLoadCp
             *        The hydraulic load Cp.
             */
            void SetHydraulicLoadCp(
                std::unique_ptr<double> hydraulicLoadCp);

            /*!
             * \brief Sets the hydraulic load Np.
             * \param hydraulicLoadNp
             *        The hydraulic load Np.
             */
            void SetHydraulicLoadNp(
                std::unique_ptr<double> hydraulicLoadNp);

            /*!
             * \brief Sets the hydraulic load As.
             * \param hydraulicLoadAs
             *        The hydraulic load As.
             */
            void SetHydraulicLoadAs(
                std::unique_ptr<double> hydraulicLoadAs);

            /*!
             * \brief Sets the hydraulic load Bs.
             * \param hydraulicLoadBs
             *        The hydraulic load Bs.
             */
            void SetHydraulicLoadBs(
                std::unique_ptr<double> hydraulicLoadBs);

            /*!
             * \brief Sets the hydraulic load Cs.
             * \param hydraulicLoadCs
             *        The hydraulic load Cs.
             */
            void SetHydraulicLoadCs(
                std::unique_ptr<double> hydraulicLoadCs);

            /*!
             * \brief Sets the hydraulic load Ns.
             * \param hydraulicLoadNs
             *        The hydraulic load Ns.
             */
            void SetHydraulicLoadNs(
                std::unique_ptr<double> hydraulicLoadNs);

            /*!
             * \brief Sets the hydraulic load Xib.
             * \param hydraulicLoadXib
             *        The hydraulic load Xib.
             */
            void SetHydraulicLoadXib(
                std::unique_ptr<double> hydraulicLoadXib);

            /*!
             * \brief Sets the upper limit loading Aul.
             */
            void SetUpperLimitLoadingAul(
                std::unique_ptr<double> upperLimitLoadingAul);

            /*!
             * \brief Sets the upper limit loading Bul.
             */
            void SetUpperLimitLoadingBul(
                std::unique_ptr<double> upperLimitLoadingBul);

            /*!
             * \brief Sets the upper limit loading Cul.
             */
            void SetUpperLimitLoadingCul(
                std::unique_ptr<double> upperLimitLoadingCul);

            /*!
             * \brief Sets the lower limit loading All.
             */
            void SetLowerLimitLoadingAll(
                std::unique_ptr<double> lowerLimitLoadingAll);

            /*!
             * \brief Sets the lower limit loading Bll.
             */
            void SetLowerLimitLoadingBll(
                std::unique_ptr<double> lowerLimitLoadingBll);

            /*!
             * \brief Sets the lower limit loading Cll.
             */
            void SetLowerLimitLoadingCll(
                std::unique_ptr<double> lowerLimitLoadingCll);

            /*!
             * \brief Sets the distance maximum wave elevation Asmax.
             */
            void SetDistanceMaximumWaveElevationAsmax(
                std::unique_ptr<double> distanceMaximumWaveElevationAsmax);

            /*!
             * \brief Sets the distance maximum wave elevation Bsmax.
             */
            void SetDistanceMaximumWaveElevationBsmax(
                std::unique_ptr<double> distanceMaximumWaveElevationBsmax);

            /*!
             * \brief Sets the normative width of wave impact Awi.
             */
            void SetNormativeWidthOfWaveImpactAwi(
                std::unique_ptr<double> normativeWidthOfWaveImpactAwi);

            /*!
             * \brief Sets the normative width of wave impact Bwi.
             */
            void SetNormativeWidthOfWaveImpactBwi(
                std::unique_ptr<double> normativeWidthOfWaveImpactBwi);

            /*!
             * \brief Sets the wave angle impact beta max
             * \param waveAngleImpactBetamax
             *        The wave angle impact beta max.
             */
            void SetWaveAngleImpactBetamax(
                std::unique_ptr<double> waveAngleImpactBetamax);

            #pragma endregion

            #pragma region Get methods

            /*!
             * \brief Gets the type of the top layer.
             * \return The type of the top layer.
             */
            TopLayerType GetTopLayerType() const;

            /*!
             * \brief Gets the name.
             * \return The name.
             */
            std::string GetName() const;

            /*!
             * \brief Gets the tanA value.
             * \return The tanA value.
             */
            double GetTanA() const;

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
             * \brief Gets the initial damage.
             * \return The initial damage.
             */
            const double* GetInitialDamage() const;

            /*!
             * \brief Gets the failure number.
             * \return The failure number.
             */
            const double* GetFailureNumber() const;

            /*!
             * \brief Gets the hydraulic load Ap.
             * \return The hydraulic load Ap.
             */
            const double* GetHydraulicLoadAp() const;

            /*!
             * \brief Gets the hydraulic load Bp.
             * \return The hydraulic load Bp.
             */
            const double* GetHydraulicLoadBp() const;

            /*!
             * \brief Gets the hydraulic load Cp.
             * \return The hydraulic load Cp.
             */
            const double* GetHydraulicLoadCp() const;

            /*!
             * \brief Gets the hydraulic load Np.
             * \return The hydraulic load Np.
             */
            const double* GetHydraulicLoadNp() const;

            /*!
             * \brief Gets the hydraulic load As.
             * \return The hydraulic load As.
             */
            const double* GetHydraulicLoadAs() const;

            /*!
             * \brief Gets the hydraulic load Bs.
             * \return The hydraulic load Bs.
             */
            const double* GetHydraulicLoadBs() const;

            /*!
             * \brief Gets the hydraulic load Cs.
             * \return The hydraulic load Cs.
             */
            const double* GetHydraulicLoadCs() const;

            /*!
             * \brief Gets the hydraulic load Ns.
             * \return The hydraulic load Ns.
             */
            const double* GetHydraulicLoadNs() const;

            /*!
             * \brief Gets the hydraulic load Xib.
             * \return The hydraulic load Xib.
             */
            const double* GetHydraulicLoadXib() const;

            /*!
             * \brief Gets the upper limit loading Aul.
             * \return The upper limit loading Aul.
             */
            const double* GetUpperLimitLoadingAul() const;

            /*!
             * \brief Gets the upper limit loading Bul.
             * \return The upper limit loading Bul.
             */
            const double* GetUpperLimitLoadingBul() const;

            /*!
             * \brief Gets the upper limit loading Cul.
             * \return The upper limit loading Cul.
             */
            const double* GetUpperLimitLoadingCul() const;

            /*!
             * \brief Gets the lower limit loading All.
             * \return The lower limit loading All.
             */
            const double* GetLowerLimitLoadingAll() const;

            /*!
             * \brief Gets the lower limit loading Bll.
             * \return The lower limit loading Bll.
             */
            const double* GetLowerLimitLoadingBll() const;

            /*!
             * \brief Gets the lower limit loading Cll.
             * \return The lower limit loading Cll.
             */
            const double* GetLowerLimitLoadingCll() const;

            /*!
             * \brief Gets the distance maximum wave elevation Asmax.
             * \return The distance maximum wave elevation Asmax.
             */
            const double* GetDistanceMaximumWaveElevationAsmax() const;

            /*!
             * \brief Gets the distance maximum wave elevation Bsmax.
             * \return The distance maximum wave elevation Bsmax.
             */
            const double* GetDistanceMaximumWaveElevationBsmax() const;

            /*!
             * \brief Gets the normative width of wave impact Awi.
             * \return The normative width of wave impact Awi.
             */
            const double* GetNormativeWidthOfWaveImpactAwi() const;

            /*!
             * \brief Gets the normative width of wave impact Bwi.
             * \return The normative width of wave impact Bwi.
             */
            const double* GetNormativeWidthOfWaveImpactBwi() const;

            /*!
             * \brief Gets the wave angle impact beta max
             * \return The wave angle impact beta max.
             */
            const double* GetWaveAngleImpactBetamax() const;

            #pragma endregion

        private:
            TopLayerType _topLayerType;
            std::string _name;
            double _tanA;
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
