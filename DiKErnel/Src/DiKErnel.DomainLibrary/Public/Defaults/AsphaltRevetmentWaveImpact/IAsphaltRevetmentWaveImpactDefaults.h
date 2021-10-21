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

namespace DiKErnel::DomainLibrary
{
    /*!
     * \brief Interface that contains default value definitions for asphalt revetment wave impact.
     */
    class IAsphaltRevetmentWaveImpactDefaults
    {
        public:
            /*!
             * \brief Destructs the instance.
             */
            virtual ~IAsphaltRevetmentWaveImpactDefaults() = default;

            /*!
             * \brief Gets the default value of the sub layer thickness.
             * \return The default value of the sub layer thickness.
             *         Unit = [m]
             */
            virtual double GetSubLayerThickness() const = 0;

            /*!
             * \brief Gets the default value of the Ctm coefficient.
             * \return The default value of the Ctm coefficient.
             *         Unit = [-]
             */
            virtual double GetAverageNumberOfWavesCtm() const = 0;

            /*!
             * \brief Gets the default value of the fatigue alpha coefficient.
             * \return The default value of the fatigue alpha coefficient.
             *         Unit = [-]
             */
            virtual double GetFatigueAlpha() const = 0;

            /*!
             * \brief Gets the default value of the fatigue beta coefficient.
             * \return The default value of the fatigue beta coefficient.
             *         Unit = [-]
             */
            virtual double GetFatigueBeta() const = 0;

            /*!
             * \brief Gets the default value of the impact number C coefficient.
             * \return The default value of the impact number C coefficient.
             *         Unit = [-]
             */
            virtual double GetImpactNumberC() const = 0;

            /*!
             * \brief Gets the default value of the stiffness relation Nu coefficient.
             * \return The default value of the stiffness relation Nu coefficient.
             *         Unit = [-]
             */
            virtual double GetStiffnessRelationNu() const = 0;

            /*!
             * \brief Gets the default values of the width factors.
             * \return The default values of the width factors.
             *         Unit = [-]
             */
            virtual const std::vector<std::tuple<double, double>>& GetWidthFactors() const = 0;

            /*!
             * \brief Gets the default values of the depth factors.
             * \return The default values of the depth factors.
             *         Unit = [-]
             */
            virtual const std::vector<std::tuple<double, double>>& GetDepthFactors() const = 0;

            /*!
             * \brief Gets the default values of the impact factors.
             * \return The default values of the impact factors.
             *         Unit = [-]
             */
            virtual const std::vector<std::tuple<double, double>>& GetImpactFactors() const = 0;
    };
}
