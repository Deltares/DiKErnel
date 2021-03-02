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

#include "LocationDependentData.h"

namespace DiKErnel::Integration
{
    /*!
     * \brief Class containing all natural stone revetment location related data to perform a calculation.
     */
    class NaturalStoneRevetmentLocationDependentData : public Core::LocationDependentData
    {
        public:
            /*!
             * \brief Creates a new instance.
             * \param initialDamage
             *        The damage at the start of the calculation.
             *        Unit = [-]
             * \param slopeAngle
             *        The slope angle at the current location.
             *        Unit = [°]
             * \param relativeDensity
             *        The relative density at the current location.
             *        Unit = [-]
             * \param thicknessTopLayer
             *        The thickness of the top layer at the current location.
             *        Unit = [m]
             * \param plungingCoefficientA
             *        The A coefficient for plunging.
             *        Unit = [-]
             * \param plungingCoefficientB
             *        The B coefficient for plunging.
             *        Unit = [-]
             * \param plungingCoefficientC
             *        The C coefficient for plunging.
             *        Unit = [-]
             * \param plungingCoefficientN
             *        The N coefficient for plunging.
             *        Unit = [-]
             * \param surgingCoefficientA
             *        The A coefficient for surging.
             *        Unit = [-]
             * \param surgingCoefficientB
             *        The B coefficient for surging.
             *        Unit = [-]
             * \param surgingCoefficientC
             *        The C coefficient for surging.
             *        Unit = [-]
             * \param surgingCoefficientN
             *        The N coefficient for surging.
             *        Unit = [-]
             * \param similarityParameterThreshold
             *        The similarity parameter threshold, which determines whether there is
             *        plunging or surging.
             *        Unit = [-]
             */
            explicit NaturalStoneRevetmentLocationDependentData(
                double initialDamage,
                double slopeAngle,
                double relativeDensity,
                double thicknessTopLayer,
                double plungingCoefficientA,
                double plungingCoefficientB,
                double plungingCoefficientC,
                double plungingCoefficientN,
                double surgingCoefficientA,
                double surgingCoefficientB,
                double surgingCoefficientC,
                double surgingCoefficientN,
                double similarityParameterThreshold);

            /*!
             * \brief Performs a calculation.
             * \param startDamage
             *        The damage at the start of the calculation.
             * \param timeDependentData
             *        The time dependent data to use in the calculation.
             * \param maximumWaveAngle
             *        The maximum wave angle.
             * \return The calculated damage.
             */
            double Calculate(
                double startDamage,
                const Core::TimeDependentData& timeDependentData,
                double maximumWaveAngle) override;

        private:
            double _slopeAngle;
            double _relativeDensity;
            double _thicknessTopLayer;
            double _plungingCoefficientA;
            double _plungingCoefficientB;
            double _plungingCoefficientC;
            double _plungingCoefficientN;
            double _surgingCoefficientA;
            double _surgingCoefficientB;
            double _surgingCoefficientC;
            double _surgingCoefficientN;
            double _similarityParameterThreshold;
    };
}
