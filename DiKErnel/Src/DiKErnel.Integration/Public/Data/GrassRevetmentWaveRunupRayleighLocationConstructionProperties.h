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

#include "GrassRevetmentWaveRunupLocationConstructionProperties.h"

namespace DiKErnel::Integration
{
    /*!
     * \brief Construction properties to construct grass revetment wave run-up location dependent
     *        input for the Rayleigh protocol.
     */
    class GrassRevetmentWaveRunupRayleighLocationConstructionProperties : public GrassRevetmentWaveRunupLocationConstructionProperties
    {
        public:
            /*!
             * \brief Creates a new instance.
             * \param x
             *        The x coordinate.
             * \param outerSlope
             *        The outer slope.
             * \param topLayerType
             *        The type of the top layer.
             */
            explicit GrassRevetmentWaveRunupRayleighLocationConstructionProperties(
                double x,
                double outerSlope,
                GrassRevetmentTopLayerType topLayerType);

            #pragma region Set methods

            /*!
             * \brief Sets the fixed number of waves.
             * \param fixedNumberOfWaves
             *        The fixed number of waves.
             */
            void SetFixedNumberOfWaves(
                std::unique_ptr<int> fixedNumberOfWaves);

            /*!
             * \brief Sets the Cu coefficient.
             * \param frontVelocityCu
             *        The Cu coefficient.
             */
            void SetFrontVelocityCu(
                std::unique_ptr<double> frontVelocityCu);

            #pragma endregion

            #pragma region Get methods

            /*!
             * \brief Gets the fixed number of waves.
             * \return The fixed number of waves.
             */
            const int* GetFixedNumberOfWaves() const;

            /*!
             * \brief Gets the Cu coefficient.
             * \return The Cu coefficient.
             */
            const double* GetFrontVelocityCu() const;

            #pragma endregion

        private:
            std::unique_ptr<int> _fixedNumberOfWaves = nullptr;
            std::unique_ptr<double> _frontVelocityCu = nullptr;
    };
}
