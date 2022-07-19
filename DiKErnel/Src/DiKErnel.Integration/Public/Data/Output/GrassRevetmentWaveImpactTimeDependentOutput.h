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

#include "GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties.h"
#include "TimeDependentOutput.h"

namespace DiKErnel::Integration
{
    /*!
     * \brief Time dependent output of a grass revetment wave impact location.
     */
    class GrassRevetmentWaveImpactTimeDependentOutput : public Core::TimeDependentOutput
    {
        public:
            /*!
             * \brief Creates a new instance.
             * \param constructionProperties
             *        The construction properties.
             * \exception InvalidTimeDependentOutputException
             *            Thrown when mandatory properties are nullptr.
             */
            explicit GrassRevetmentWaveImpactTimeDependentOutput(
                GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties& constructionProperties);

            /*!
             * \brief Gets the loading revetment.
             * \return The loading revetment.
             */
            [[nodiscard]]
            bool GetLoadingRevetment() const;

            /*!
             * \brief Gets the upper limit loading.
             * \return The upper limit loading.
             */
            [[nodiscard]]
            double GetUpperLimitLoading() const;

            /*!
             * \brief Gets the lower limit loading.
             * \return The lower limit loading.
             */
            [[nodiscard]]
            double GetLowerLimitLoading() const;

            /*!
             * \brief Gets the minimum wave height.
             * \return The minimum wave height.
             */
            [[nodiscard]]
            const double* GetMinimumWaveHeight() const;

            /*!
             * \brief Gets the maximum wave height.
             * \return The maximum wave height.
             */
            [[nodiscard]]
            const double* GetMaximumWaveHeight() const;

            /*!
             * \brief Gets the wave angle impact.
             * \return The wave angle impact.
             */
            [[nodiscard]]
            const double* GetWaveAngleImpact() const;

            /*!
             * \brief Gets the wave height impact.
             * \return The wave height impact.
             */
            [[nodiscard]]
            const double* GetWaveHeightImpact() const;

        private:
            std::unique_ptr<bool> _loadingRevetment = nullptr;
            std::unique_ptr<double> _upperLimitLoading = nullptr;
            std::unique_ptr<double> _lowerLimitLoading = nullptr;
            std::unique_ptr<double> _minimumWaveHeight = nullptr;
            std::unique_ptr<double> _maximumWaveHeight = nullptr;
            std::unique_ptr<double> _waveAngleImpact = nullptr;
            std::unique_ptr<double> _waveHeightImpact = nullptr;
    };
}
