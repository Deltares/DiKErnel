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

#include <string>

#include "RevetmentLocationConstructionPropertiesBase.h"

namespace DiKErnel::Integration
{
    /*!
     * \brief Construction properties to construct grass revetment wave impact location dependent
     *        input.
     */
    class GrassRevetmentWaveImpactLocationConstructionProperties : public RevetmentLocationConstructionPropertiesBase
    {
        public:

            /*!
             * \brief The types of the top layer.
             */
            enum class TopLayerType
            {
                ClosedSod,
                OpenSod
            };

            /*!
             * \brief Creates a new instance.
             * \param name
             *        The name.
             * \param tanA
             *        The tanA.
             * \param positionZ
             *        The vertical position.
             * \param topLayerType
             *        The type of the top layer.
             */
            explicit GrassRevetmentWaveImpactLocationConstructionProperties(
                std::string name,
                double tanA,
                double positionZ,
                TopLayerType topLayerType);

            #pragma region Set methods

            /*!
             * \brief Sets the failure time Agwi.
             * \param failureTimeAgwi
             *        The failure time Agwi.
             */
            void SetFailureTimeAgwi(
                std::unique_ptr<double> failureTimeAgwi);

            /*!
             * \brief Sets the failure time Bgwi.
             * \param failureTimeBgwi
             *        The failure time Bgwi.
             */
            void SetFailureTimeBgwi(
                std::unique_ptr<double> failureTimeBgwi);

            /*!
             * \brief Sets the failure time Cgwi.
             * \param failureTimeCgwi
             *        The failure time Cgwi.
             */
            void SetFailureTimeCgwi(
                std::unique_ptr<double> failureTimeCgwi);

            /*!
             * \brief Sets the minimum wave height Temax.
             * \param minimumWaveHeightTemax
             *        The minimum wave height Temax.
             */
            void SetMinimumWaveHeightTemax(
                std::unique_ptr<double> minimumWaveHeightTemax);

            /*!
             * \brief Sets the maximum wave height Temin.
             * \param maximumWaveHeightTemin
             *        The maximum wave height Temin.
             */
            void SetMaximumWaveHeightTemin(
                std::unique_ptr<double> maximumWaveHeightTemin);

            /*!
             * \brief Sets the wave angle impact Nwa.
             * \param waveAngleImpactNwa
             *        The wave angle impact Nwa.
             */
            void SetWaveAngleImpactNwa(
                std::unique_ptr<double> waveAngleImpactNwa);

            /*!
             * \brief Sets the wave angle impact Qwa.
             * \param waveAngleImpactQwa
             *        The wave angle impact Qwa.
             */
            void SetWaveAngleImpactQwa(
                std::unique_ptr<double> waveAngleImpactQwa);

            /*!
             * \brief Sets the wave angle impact Rwa.
             * \param waveAngleImpactRwa
             *        The wave angle impact Rwa.
             */
            void SetWaveAngleImpactRwa(
                std::unique_ptr<double> waveAngleImpactRwa);

            /*!
             * \brief Sets the upper limit loading Aul.
             * \param upperLimitLoadingAul
             *        The upper limit loading Aul.
             */
            void SetUpperLimitLoadingAul(
                std::unique_ptr<double> upperLimitLoadingAul);

            /*!
             * \brief Sets the lower limit loading All.
             * \param lowerLimitLoadingAll
             *        The lower limit loading All.
             */
            void SetLowerLimitLoadingAll(
                std::unique_ptr<double> lowerLimitLoadingAll);

            #pragma endregion

            #pragma region Get methods

            /*!
             * \brief Gets the type of the top layer.
             * \return The type of the top layer.
             */
            TopLayerType GetTopLayerType() const;

            /*!
             * \brief Gets the failure time Agwi.
             * \return The failure time Agwi.
             */
            const double* GetFailureTimeAgwi() const;

            /*!
             * \brief Gets the failure time Bgwi.
             * \return The failure time Bgwi.
             */
            const double* GetFailureTimeBgwi() const;

            /*!
             * \brief Gets the failure time Cgwi.
             * \return The failure time Cgwi.
             */
            const double* GetFailureTimeCgwi() const;

            /*!
             * \brief Gets the minimum wave height Temax.
             * \return The minimum wave height Temax.
             */
            const double* GetMinimumWaveHeightTemax() const;

            /*!
             * \brief Gets the maximum wave height Temin.
             * \return The maximum wave height Temin.
             */
            const double* GetMaximumWaveHeightTemin() const;

            /*!
             * \brief Gets the maximum wave angle impact Nwa.
             * \return The maximum wave angle impact Nwa.
             */
            const double* GetWaveAngleImpactNwa() const;

            /*!
             * \brief Gets the maximum wave angle impact Qwa.
             * \return The maximum wave angle impact Qwa.
             */
            const double* GetWaveAngleImpactQwa() const;

            /*!
             * \brief Gets the maximum wave angle impact Rwa.
             * \return The maximum wave angle impact Rwa.
             */
            const double* GetWaveAngleImpactRwa() const;

            /*!
             * \brief Gets the upper limit loading Aul.
             * \return The upper limit loading Aul.
             */
            const double* GetUpperLimitLoadingAul() const;

            /*!
             * \brief Gets the lower limit loading All.
             * \return The lower limit loading All.
             */
            const double* GetLowerLimitLoadingAll() const;

            #pragma endregion

        private:
            TopLayerType _topLayerType;
            std::unique_ptr<double> _failureTimeAgwi = nullptr;
            std::unique_ptr<double> _failureTimeBgwi = nullptr;
            std::unique_ptr<double> _failureTimeCgwi = nullptr;
            std::unique_ptr<double> _minimumWaveHeightTemax = nullptr;
            std::unique_ptr<double> _maximumWaveHeightTemin = nullptr;
            std::unique_ptr<double> _waveAngleImpactNwa = nullptr;
            std::unique_ptr<double> _waveAngleImpactQwa = nullptr;
            std::unique_ptr<double> _waveAngleImpactRwa = nullptr;
            std::unique_ptr<double> _upperLimitLoadingAul = nullptr;
            std::unique_ptr<double> _lowerLimitLoadingAll = nullptr;
    };
}
