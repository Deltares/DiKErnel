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

#include "GrassRevetmentTopLayerType.h"
#include "RevetmentLocationConstructionPropertiesBase.h"

namespace DiKErnel::Integration
{
    /*!
     * \brief Construction properties to construct grass revetment overtopping location dependent
     *        input.
     */
    class GrassRevetmentOvertoppingLocationConstructionProperties : public RevetmentLocationConstructionPropertiesBase
    {
        public:
            /*!
             * \brief Creates a new instance.
             * \param x
             *        The x coordinate.
             * \param topLayerType
             *        The type of the top layer.
             */
            explicit GrassRevetmentOvertoppingLocationConstructionProperties(
                double x,
                GrassRevetmentTopLayerType topLayerType);

            #pragma region Set methods

            /*!
             * \brief Sets the critical cumulative overload.
             * \param criticalCumulativeOverload
             *        The critical cumulative overload.
             */
            void SetCriticalCumulativeOverload(
                std::unique_ptr<double> criticalCumulativeOverload);

            /*!
             * \brief Sets the critical front velocity.
             * \param criticalFrontVelocity
             *        The critical front velocity.
             */
            void SetCriticalFrontVelocity(
                std::unique_ptr<double> criticalFrontVelocity);

            /*!
             * \brief Sets the alpha M coefficient.
             * \param increasedLoadTransitionAlphaM
             *        The alpha M coefficient.
             */
            void SetIncreasedLoadTransitionAlphaM(
                std::unique_ptr<double> increasedLoadTransitionAlphaM);

            /*!
             * \brief Sets the alpha S coefficient.
             * \param reducedStrengthTransitionAlphaS
             *        The alpha S coefficient.
             */
            void SetReducedStrengthTransitionAlphaS(
                std::unique_ptr<double> reducedStrengthTransitionAlphaS);

            /*!
             * \brief Sets the Ctm coefficient.
             * \param averageNumberOfWavesCtm
             *        The Ctm coefficient.
             */
            void SetAverageNumberOfWavesCtm(
                std::unique_ptr<double> averageNumberOfWavesCtm);

            #pragma endregion

            #pragma region Get methods

            /*!
             * \brief Gets the type of the top layer.
             * \return The type of the top layer.
             */
            [[nodiscard]]
            GrassRevetmentTopLayerType GetTopLayerType() const;

            /*!
             * \brief Gets the critical cumulative overload.
             * \return The critical cumulative overload.
             */
            [[nodiscard]]
            const double* GetCriticalCumulativeOverload() const;

            /*!
             * \brief Gets the critical front velocity.
             * \return The critical front velocity.
             */
            [[nodiscard]]
            const double* GetCriticalFrontVelocity() const;

            /*!
             * \brief Gets the alpha M coefficient.
             * \return The alpha M coefficient.
             */
            [[nodiscard]]
            const double* GetIncreasedLoadTransitionAlphaM() const;

            /*!
             * \brief Gets the alpha S coefficient.
             * \return The alpha S coefficient.
             */
            [[nodiscard]]
            const double* GetReducedStrengthTransitionAlphaS() const;

            /*!
             * \brief Gets the Ctm coefficient.
             * \return The Ctm coefficient.
             */
            [[nodiscard]]
            const double* GetAverageNumberOfWavesCtm() const;

            #pragma endregion

        private:
            GrassRevetmentTopLayerType _topLayerType;
            std::unique_ptr<double> _criticalCumulativeOverload = nullptr;
            std::unique_ptr<double> _criticalFrontVelocity = nullptr;
            std::unique_ptr<double> _increasedLoadTransitionAlphaM = nullptr;
            std::unique_ptr<double> _reducedStrengthTransitionAlphaS = nullptr;
            std::unique_ptr<double> _averageNumberOfWavesCtm = nullptr;
    };
}
