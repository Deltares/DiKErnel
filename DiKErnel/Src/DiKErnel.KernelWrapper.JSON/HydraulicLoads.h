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

#include <memory>
#include <vector>

#include "BoundaryConditionsPerTimeStep.h"

namespace DiKErnel::KernelWrapper::Json
{
    /*!
     * \brief Container for hydraulic loads data.
     */
    class HydraulicLoads
    {
        public:
            /*!
             * \brief Creates a new instance.
             * \param waveAngleMaximum
             *        The maximum wave angle.
             * \param boundaryConditionsPerTimeStep
             *        The boundary conditions on a per time step basis.
             */
            explicit HydraulicLoads(
                int waveAngleMaximum,
                std::vector<std::unique_ptr<BoundaryConditionsPerTimeStep>> boundaryConditionsPerTimeStep);

            /*!
             * \brief Gets the maximum wave angle.
             * \return The maximum wave angle.
             */
            int GetWaveAngleMaximum() const;

            /*!
             * \brief Gets the boundary conditions on a per time step basis.
             * \return The boundary conditions on a per time step basis.
             */
            const std::vector<std::reference_wrapper<BoundaryConditionsPerTimeStep>>& GetBoundaryConditionsPerTimeStep() const;

        private:
            int _waveAngleMaximum;
            std::vector<std::unique_ptr<BoundaryConditionsPerTimeStep>> _boundaryConditionsPerTimeStep;
            std::vector<std::reference_wrapper<BoundaryConditionsPerTimeStep>> _boundaryConditionsPerTimeStepReferences;
    };
}
