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

#include "GrassRevetmentTopLayerType.h"
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
             * \brief Creates a new instance.
             * \param name
             *        The name.
             * \param positionZ
             *        The vertical position.
             * \param topLayerType
             *        The type of the top layer.
             */
            explicit GrassRevetmentWaveImpactLocationConstructionProperties(
                std::string name,
                double positionZ,
                GrassRevetmentTopLayerType topLayerType);

            #pragma region Set methods

            /*!
             * \brief Sets the Agwi coefficient.
             * \param timeLineAgwi
             *        The Agwi coefficient.
             */
            void SetTimeLineAgwi(
                std::unique_ptr<double> timeLineAgwi);

            /*!
             * \brief Sets the Bgwi coefficient.
             * \param timeLineBgwi
             *        The Bgwi coefficient.
             */
            void SetTimeLineBgwi(
                std::unique_ptr<double> timeLineBgwi);

            /*!
             * \brief Sets the Cgwi coefficient.
             * \param timeLineCgwi
             *        The Cgwi coefficient.
             */
            void SetTimeLineCgwi(
                std::unique_ptr<double> timeLineCgwi);

            /*!
             * \brief Sets the Temax coefficient.
             * \param minimumWaveHeightTemax
             *        The Temax coefficient.
             */
            void SetMinimumWaveHeightTemax(
                std::unique_ptr<double> minimumWaveHeightTemax);

            /*!
             * \brief Sets the Temin coefficient.
             * \param maximumWaveHeightTemin
             *        The Temin coefficient.
             */
            void SetMaximumWaveHeightTemin(
                std::unique_ptr<double> maximumWaveHeightTemin);

            /*!
             * \brief Sets the Nwa coefficient.
             * \param waveAngleImpactNwa
             *        The Nwa coefficient.
             */
            void SetWaveAngleImpactNwa(
                std::unique_ptr<double> waveAngleImpactNwa);

            /*!
             * \brief Sets the Qwa coefficient.
             * \param waveAngleImpactQwa
             *        The Qwa coefficient.
             */
            void SetWaveAngleImpactQwa(
                std::unique_ptr<double> waveAngleImpactQwa);

            /*!
             * \brief Sets the Rwa coefficient.
             * \param waveAngleImpactRwa
             *        The Rwa coefficient.
             */
            void SetWaveAngleImpactRwa(
                std::unique_ptr<double> waveAngleImpactRwa);

            /*!
             * \brief Sets the Aul coefficient.
             * \param upperLimitLoadingAul
             *        The Aul coefficient.
             */
            void SetUpperLimitLoadingAul(
                std::unique_ptr<double> upperLimitLoadingAul);

            /*!
             * \brief Sets the All coefficient.
             * \param lowerLimitLoadingAll
             *        The All coefficient.
             */
            void SetLowerLimitLoadingAll(
                std::unique_ptr<double> lowerLimitLoadingAll);

            #pragma endregion

            #pragma region Get methods

            /*!
             * \brief Gets the type of the top layer.
             * \return The type of the top layer.
             */
            GrassRevetmentTopLayerType GetTopLayerType() const;

            /*!
             * \brief Gets the Agwi coefficient.
             * \return The Agwi coefficient.
             */
            const double* GetTimeLineAgwi() const;

            /*!
             * \brief Gets the Bgwi coefficient.
             * \return The Bgwi coefficient.
             */
            const double* GetTimeLineBgwi() const;

            /*!
             * \brief Gets the Cgwi coefficient.
             * \return The Cgwi coefficient.
             */
            const double* GetTimeLineCgwi() const;

            /*!
             * \brief Gets the Temax coefficient.
             * \return The Temax coefficient.
             */
            const double* GetMinimumWaveHeightTemax() const;

            /*!
             * \brief Gets the Temin coefficient.
             * \return The Temin coefficient.
             */
            const double* GetMaximumWaveHeightTemin() const;

            /*!
             * \brief Gets the Nwa coefficient.
             * \return The Nwa coefficient.
             */
            const double* GetWaveAngleImpactNwa() const;

            /*!
             * \brief Gets the Qwa coefficient.
             * \return The Qwa coefficient.
             */
            const double* GetWaveAngleImpactQwa() const;

            /*!
             * \brief Gets the Rwa coefficient.
             * \return The Rwa coefficient.
             */
            const double* GetWaveAngleImpactRwa() const;

            /*!
             * \brief Gets the Aul coefficient.
             * \return The Aul coefficient.
             */
            const double* GetUpperLimitLoadingAul() const;

            /*!
             * \brief Gets the All coefficient.
             * \return The All coefficient.
             */
            const double* GetLowerLimitLoadingAll() const;

            #pragma endregion

        private:
            GrassRevetmentTopLayerType _topLayerType;
            std::unique_ptr<double> _timeLineAgwi = nullptr;
            std::unique_ptr<double> _timeLineBgwi = nullptr;
            std::unique_ptr<double> _timeLineCgwi = nullptr;
            std::unique_ptr<double> _minimumWaveHeightTemax = nullptr;
            std::unique_ptr<double> _maximumWaveHeightTemin = nullptr;
            std::unique_ptr<double> _waveAngleImpactNwa = nullptr;
            std::unique_ptr<double> _waveAngleImpactQwa = nullptr;
            std::unique_ptr<double> _waveAngleImpactRwa = nullptr;
            std::unique_ptr<double> _upperLimitLoadingAul = nullptr;
            std::unique_ptr<double> _lowerLimitLoadingAll = nullptr;
    };
}
