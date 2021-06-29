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

#include <vector>
#include <tuple>

#include "IAsphaltRevetmentWaveImpactDefaults.h"

namespace DiKErnel::DomainLibrary
{
    /*!
     * \brief Class that contains default values for asphalt revetment wave impact with hydraulic
     *        asphalt concrete.
     */
    class AsphaltRevetmentWaveImpactHydraulicAsphaltConcreteDefaults : public IAsphaltRevetmentWaveImpactDefaults
    {
        public:
            /*!
             * \brief Gets the default value of the sub layer thickness.
             * \return The default value of the sub layer thickness.
             *         Unit = [m]
             */
            double GetSubLayerThickness() const override;

            /*!
             * \brief Gets the default value of the Ctm coefficient.
             * \return The default value of the Ctm coefficient.
             *         Unit = [-]
             */
            double GetAverageNumberOfWavesCtm() const override;

            /*!
             * \brief Gets the default value of the fatigue alpha coefficient.
             * \return The default value of the fatigue alpha coefficient.
             *         Unit = [-]
             */
            double GetFatigueAlpha() const override;

            /*!
             * \brief Gets the default value of the fatigue beta coefficient.
             * \return The default value of the fatigue beta coefficient.
             *         Unit = [-]
             */
            double GetFatigueBeta() const override;

            /*!
             * \brief Gets the default value of the impact number C coefficient.
             * \return The default value of the impact number C coefficient.
             *         Unit = [-]
             */
            double GetImpactNumberC() const override;

            /*!
             * \brief Gets the default value of the stiffness relation Nu coefficient.
             * \return The default value of the stiffness relation Nu coefficient.
             *         Unit = [-]
             */
            double GetStiffnessRelationNu() const override;

            /*!
             * \brief Gets the default values of the width factors.
             * \return The default values of the width factors.
             *         Unit = [-]
             */
            const std::vector<std::tuple<double, double>>& GetWidthFactors() const override;

            /*!
             * \brief Gets the default values of the depth factors.
             * \return The default values of the depth factors.
             *         Unit = [-]
             */
            const std::vector<std::tuple<double, double>>& GetDepthFactors() const override;

            /*!
             * \brief Gets the default values of the impact factors.
             * \return The default values of the impact factors.
             *         Unit = [-]
             */
            const std::vector<std::tuple<double, double>>& GetImpactFactors() const override;

        private:
            std::vector<std::tuple<double, double>> _widthFactors = std::vector<std::tuple<double, double>>
            {
                std::tuple(0.1, 0.0392),
                std::tuple(0.2, 0.0738),
                std::tuple(0.3, 0.1002),
                std::tuple(0.4, 0.1162),
                std::tuple(0.5, 0.1213),
                std::tuple(0.6, 0.1168),
                std::tuple(0.7, 0.1051),
                std::tuple(0.8, 0.0890),
                std::tuple(0.9, 0.0712),
                std::tuple(1.0, 0.0541),
                std::tuple(1.1, 0.0391),
                std::tuple(1.2, 0.0269),
                std::tuple(1.3, 0.0216),
                std::tuple(1.4, 0.0150),
                std::tuple(1.5, 0.0105)
            };
            std::vector<std::tuple<double, double>> _depthFactors = std::vector<std::tuple<double, double>>
            {
                std::tuple(-1.0, 0.0244),
                std::tuple(-0.875, 0.0544),
                std::tuple(-0.750, 0.0938),
                std::tuple(-0.625, 0.1407),
                std::tuple(-0.500, 0.1801),
                std::tuple(-0.375, 0.1632),
                std::tuple(-0.250, 0.1426),
                std::tuple(-0.125, 0.0994),
                std::tuple(0.0, 0.06),
                std::tuple(0.125, 0.0244),
                std::tuple(0.250, 0.0169)

            };
            std::vector<std::tuple<double, double>> _impactFactors = std::vector<std::tuple<double, double>>
            {
                std::tuple(2.0, 0.039),
                std::tuple(2.4, 0.1),
                std::tuple(2.8, 0.18),
                std::tuple(3.2, 0.235),
                std::tuple(3.6, 0.2),
                std::tuple(4.0, 0.13),
                std::tuple(4.4, 0.08),
                std::tuple(4.8, 0.02),
                std::tuple(5.2, 0.01),
                std::tuple(5.6, 0.005),
                std::tuple(6.0, 0.001)
            };
    };
}
