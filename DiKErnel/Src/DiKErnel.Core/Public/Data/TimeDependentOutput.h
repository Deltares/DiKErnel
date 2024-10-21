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

#include <memory>
#include <string>

#include "InvalidTimeDependentOutputException.h"
#include "TimeDependentOutputConstructionProperties.h"

namespace DiKErnel::Core
{
    /*!
     * \brief Class containing time dependent output of a location.
     */
    class TimeDependentOutput
    {
        public:
            /*!
             * \brief Destructs the instance.
             */
            virtual ~TimeDependentOutput() = default;

            /*!
             * \brief Gets the increment damage.
             * \return The increment damage.
             */
            [[nodiscard]]
            double GetIncrementDamage() const;

        protected:
            /*!
             * \brief Creates a new instance.
             * \param constructionProperties
             *        The TimeDependentOutputConstructionProperties.
             * \exception InvalidTimeDependentOutputException
             *            Thrown when mandatory properties are nullptr.
             */
            explicit TimeDependentOutput(
                TimeDependentOutputConstructionProperties& constructionProperties);

            /*!
             * \brief Throws an InvalidTimeDependentOutputException when the given property value
             *        is nullptr.
             * \tparam T
             *         The type of the given property value.
             * \param propertyValue
             *        The value to check.
             * \param propertyName
             *        The name of the property.
             */
            template <typename T>
            static void ThrowExceptionWhenPropertyIsNullPtr(
                const T* propertyValue,
                const std::string& propertyName)
            {
                if (propertyValue == nullptr)
                {
                    throw InvalidTimeDependentOutputException(propertyName + " must be set.");
                }
            }

        private:
            std::unique_ptr<double> _incrementDamage = nullptr;
    };
}
