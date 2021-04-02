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

namespace DiKErnel::Integration
{
    /*!
     * \brief Base construction properties to construct location dependent input.
     */
    class RevetmentLocationConstructionPropertiesBase
    {
        public:
            /*!
             * \brief Creates a new instance.
             * \param name
             *        The name.
             * \param positionZ
             *        The vertical position.
             */
            explicit RevetmentLocationConstructionPropertiesBase(
                std::string name,
                double positionZ);

            /*!
             * \brief Sets the initial damage.
             * \param initialDamage
             *        The initial damage.
             */
            void SetInitialDamage(
                std::unique_ptr<double> initialDamage);

            /*!
             * \brief Sets the failure number.
             * \param failureNumber
             *        The failure number.
             */
            void SetFailureNumber(
                std::unique_ptr<double> failureNumber);

            /*!
             * \brief Gets the name.
             * \return The name.
             */
            std::string GetName() const;

            /*!
             * \brief Gets the vertical position.
             * \return The vertical position.
             */
            double GetPositionZ() const;

            /*!
             * \brief Gets the initial damage.
             * \return The initial damage.
             */
            const double* GetInitialDamage() const;

            /*!
             * \brief Gets the failure number.
             * \return The failure number.
             */
            const double* GetFailureNumber() const;

        private:
            std::string _name;
            double _positionZ;
            std::unique_ptr<double> _initialDamage = nullptr;
            std::unique_ptr<double> _failureNumber = nullptr;
    };
}
