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

#include <limits>
#include <vector>

namespace DiKErnel::FunctionLibrary
{
    /*!
     * \brief Class that holds all asphalt revetment wave impact specific input.
     */
    class AsphaltRevetmentWaveImpactFunctionsInput
    {
        public:
            /*!
             * \brief Creates a new instance.
             * \param z
             *        The z coordinate.
             *        Unit = [m]
             * \param widthFactors
             *        The width factors.
             *        Unit = [-]
             * \param depthFactors
             *        The depth factors.
             *        Unit = [-]
             * \param impactFactors
             *        The impact factors.
             *        Unit = [-]
             * \param fatigueAlpha
             *        The fatigue alpha coefficient.
             *        Unit = [-]
             * \param fatigueBeta
             *        The fatigue beta coefficient.
             *        Unit = [-]
             * \param impactNumberC
             *        The impact number c coefficient.
             *        Unit = [-]
             */
            explicit AsphaltRevetmentWaveImpactFunctionsInput(
                double z,
                const std::vector<std::pair<double, double>>& widthFactors,
                const std::vector<std::pair<double, double>>& depthFactors,
                const std::vector<std::pair<double, double>>& impactFactors,
                double fatigueAlpha,
                double fatigueBeta,
                double impactNumberC);

            /*!
             * \brief Sets the water level.
             * \param waterLevel
             *        The water level.
             *        Unit = [m]
             */
            void SetWaterLevel(
                double waterLevel);

            /*!
             * \brief Sets the wave height.
             * \param waveHeightHm0
             *        The wave height.
             *        Unit = [m]
             */
            void SetWaveHeightHm0(
                double waveHeightHm0);

            /*!
             * \brief Gets the z coordinate.
             * \return The z coordinate.
             *         Unit = [m]
             */
            [[nodiscard]]
            double GetZ() const;

            /*!
             * \brief Gets the width factors.
             * \return The width factors.
             *         Unit = [-]
             */
            [[nodiscard]]
            const std::vector<std::pair<double, double>>& GetWidthFactors() const;

            /*!
             * \brief Gets the depth factors.
             * \return The depth factors.
             *         Unit = [-]
             */
            [[nodiscard]]
            const std::vector<std::pair<double, double>>& GetDepthFactors() const;

            /*!
             * \brief Gets the impact factors.
             * \return The impact factors.
             *         Unit = [-]
             */
            [[nodiscard]]
            const std::vector<std::pair<double, double>>& GetImpactFactors() const;

            /*!
             * \brief Gets the fatigue alpha coefficient.
             * \return The fatigue alpha coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            double GetFatigueAlpha() const;

            /*!
             * \brief Gets the fatigue beta coefficient.
             * \return The fatigue beta coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            double GetFatigueBeta() const;

            /*!
             * \brief Gets the impact number c coefficient.
             * \return The impact number c coefficient.
             *         Unit = [-]
             */
            [[nodiscard]]
            double GetImpactNumberC() const;

            /*!
             * \brief Gets the water level.
             * \return The water level.
             *         Unit = [m]
             */
            [[nodiscard]]
            double GetWaterLevel() const;

            /*!
             * \brief Gets the wave height.
             * \return The wave height.
             *         Unit = [m]
             */
            [[nodiscard]]
            double GetWaveHeightHm0() const;

        private:
            double _z;
            const std::vector<std::pair<double, double>>& _widthFactors;
            const std::vector<std::pair<double, double>>& _depthFactors;
            const std::vector<std::pair<double, double>>& _impactFactors;
            double _fatigueAlpha;
            double _fatigueBeta;
            double _impactNumberC;
            double _waterLevel = std::numeric_limits<double>::infinity();
            double _waveHeightHm0 = std::numeric_limits<double>::infinity();
    };
}
