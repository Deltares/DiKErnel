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

#include "ProfileSchematization.h"
#include "Revetment.h"

namespace DiKErnel::KernelWrapper::Json
{
    /*!
     * \brief Container for location data.
     */
    class CalculationLocation
    {
        std::string name;
        std::unique_ptr<Revetment> revetment;
        std::unique_ptr<ProfileSchematization> profileSchematization;

        public:
            /*!
             * \brief Creates a new instance.
             * \param name
             *        The name of the location.
             * \param revetment
             *        The revetment definition.
             * \param profileSchematization
             *        The profile schematization.
             */
            explicit CalculationLocation(
                const std::string& name,
                std::unique_ptr<Revetment> revetment,
                std::unique_ptr<ProfileSchematization> profileSchematization);

            /*!
             * \brief Gets the name of the location.
             * \return The name of the location.
             */
            const std::string& GetName() const;

            /*!
             * \brief Gets the revetment definition.
             * \return The revetment definition.
             */
            const Revetment& GetRevetment() const;

            /*!
             * \brief Gets the profile schematization.
             * \return The profile schematization.
             */
            const ProfileSchematization& GetProfileSchematization() const;
    };
}
