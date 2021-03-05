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
#include <string>

#include "DistanceMaximumWaveElevationNaturalStone.h"
#include "HydraulicLoadOnNaturalStone.h"
#include "LowerLimitLoadingOfNaturalStone.h"
#include "NormativeWidthOfWaveImpact.h"
#include "UpperLimitLoadingOfNaturalStone.h"

namespace DiKErnel::KernelWrapper::Json
{
    /*!
     * \brief Container for calculation method data.
     */
    class CalculationMethod
    {
        public:
            /*! 
             * \brief Creates a new instance.
             * \param calculationMethodSubSort
             *        The calculation method sub sort.
             * \param hydraulicLoadOnNaturalStone
             *        The hydraulic load on natural stone.
             * \param upperLimitLoadingOfNaturalStone
             *        The upper limit loading of natural stone.
             * \param lowerLimitLoadingOfNaturalStone
             *        The lower limit loading of natural stone.
             * \param distanceMaximumWaveElevationNaturalStone
             *        The distance maximum wave elevation natural stone.
             * \param normativeWidthOfWaveImpact
             *        The normative width of wave impact.
             */
            explicit CalculationMethod(
                std::string calculationMethodSubSort,
                std::unique_ptr<HydraulicLoadOnNaturalStone> hydraulicLoadOnNaturalStone,
                std::unique_ptr<UpperLimitLoadingOfNaturalStone> upperLimitLoadingOfNaturalStone,
                std::unique_ptr<LowerLimitLoadingOfNaturalStone> lowerLimitLoadingOfNaturalStone,
                std::unique_ptr<DistanceMaximumWaveElevationNaturalStone> distanceMaximumWaveElevationNaturalStone,
                std::unique_ptr<NormativeWidthOfWaveImpact> normativeWidthOfWaveImpact
            );

            /*!
             * \brief Gets the calculation method sub sort.
             * \return The calculation method sub sort.
             */
            const std::string& GetCalculationMethodSubSort() const;

            /*!
             * \brief Gets the hydraulic load on natural stone.
             * \return The hydraulic load on natural stone.
             */
            const HydraulicLoadOnNaturalStone& GetHydraulicLoadOnNaturalStone() const;

            /*!
             * \brief Gets the upper limit loading of natural stone.
             * \return The upper limit loading of natural stone.
             */
            const UpperLimitLoadingOfNaturalStone& GetUpperLimitLoadingOfNaturalStone() const;

            /*!
             * \brief Gets the lower limit loading of natural stone.
             * \return The lower limit loading of natural stone.
             */
            const LowerLimitLoadingOfNaturalStone& GetLowerLimitLoadingOfNaturalStone() const;

            /*!
             * \brief Gets the distance maximum wave elevation natural stone.
             * \return The distance maximum wave elevation natural stone.
             */
            const DistanceMaximumWaveElevationNaturalStone& GetDistanceMaximumWaveElevationNaturalStone() const;

            /*!
             * \brief Gets the normative width of wave impact.
             * \return The normative width of wave impact.
             */
            const NormativeWidthOfWaveImpact& GetNormativeWidthOfWaveImpact() const;

        private:
            std::string _calculationMethodSubSort;
            std::unique_ptr<HydraulicLoadOnNaturalStone> _hydraulicLoadOnNaturalStone;
            std::unique_ptr<UpperLimitLoadingOfNaturalStone> _upperLimitLoadingOfNaturalStone;
            std::unique_ptr<LowerLimitLoadingOfNaturalStone> _lowerLimitLoadingOfNaturalStone;
            std::unique_ptr<DistanceMaximumWaveElevationNaturalStone> _distanceMaximumWaveElevationNaturalStone;
            std::unique_ptr<NormativeWidthOfWaveImpact> _normativeWidthOfWaveImpact;
    };
}
