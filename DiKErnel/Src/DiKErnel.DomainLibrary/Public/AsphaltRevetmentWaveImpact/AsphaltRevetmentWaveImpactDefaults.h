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

#include "IAsphaltRevetmentWaveImpactDefaults.h"

namespace DiKErnel::DomainLibrary
{
    /*!
     * \brief Class that contains default value definitions for asphalt revetment wave impact.
     */
    class AsphaltRevetmentWaveImpactDefaults : public IAsphaltRevetmentWaveImpactDefaults
    {
        public:
            explicit AsphaltRevetmentWaveImpactDefaults();

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
            std::vector<std::tuple<double, double>> _widthFactors;
            std::vector<std::tuple<double, double>> _depthFactors;
            std::vector<std::tuple<double, double>> _impactFactors;
    };
}
