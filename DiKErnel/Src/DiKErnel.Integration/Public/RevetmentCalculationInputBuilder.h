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

#include "AsphaltRevetmentWaveImpactLocationConstructionProperties.h"
#include "CalculationInput.h"
#include "GrassRevetmentWaveImpactLocationConstructionProperties.h"
#include "GrassRevetmentWaveRunupRayleighLocationConstructionProperties.h"
#include "NaturalStoneRevetmentLocationConstructionProperties.h"

namespace DiKErnel::Integration
{
    /*!
     * \brief Builder to configure and create calculation input.
     */
    class RevetmentCalculationInputBuilder
    {
        public:
            /*!
             * \brief Creates a new instance.
             */
            explicit RevetmentCalculationInputBuilder() = default;

            /*!
             * \brief Adds a time step.
             * \param beginTime
             *        The begin time.
             * \param endTime
             *        The end time.
             * \param waterLevel
             *        The water level.
             * \param waveHeightHm0
             *        The wave height.
             * \param wavePeriodTm10
             *        The wave period.
             * \param waveAngle
             *        The wave angle.
             * \exception RevetmentCalculationInputBuilderException
             *            Thrown when beginTime is equal to or larger than endTime.
             */
            void AddTimeStep(
                int beginTime,
                int endTime,
                double waterLevel,
                double waveHeightHm0,
                double wavePeriodTm10,
                double waveAngle);

            /*!
             * \brief Adds a natural stone location.
             * \param constructionProperties
             *        The properties to construct the natural stone location dependent input.
             * \exception RevetmentCalculationInputBuilderException
             *            Thrown when the top layer type is invalid.
             */
            void AddNaturalStoneLocation(
                const NaturalStoneRevetmentLocationConstructionProperties& constructionProperties);

            /*!
             * \brief Adds a grass wave impact location.
             * \param constructionProperties
             *        The properties to construct the grass wave impact location dependent input.
             * \exception RevetmentCalculationInputBuilderException
             *            Thrown when the top layer type is invalid.
             */
            void AddGrassWaveImpactLocation(
                const GrassRevetmentWaveImpactLocationConstructionProperties& constructionProperties);

            /*!
             * \brief Adds a grass wave runup location with Rayleigh protocol.
             * \param constructionProperties
             *        The properties to construct the grass wave runup rayleigh location dependent input.
             * \exception RevetmentCalculationInputBuilderException
             *            Thrown when the top layer type is invalid.
             */
            void AddGrassWaveRunupRayleighLocation(
                const GrassRevetmentWaveRunupRayleighLocationConstructionProperties& constructionProperties);

            /*!
             * \brief Adds a asphalt wave impact location.
             * \param constructionProperties
             *        The properties to construct the asphalt wave impact location dependent input.
             * \exception RevetmentCalculationInputBuilderException
             *            Thrown when the top layer type is invalid.
             */
            void AddAsphaltWaveImpactLocation(
                const AsphaltRevetmentWaveImpactLocationConstructionProperties& constructionProperties);

            /*!
             * \brief Builds the calculation input.
             * \return The created calculation input.
             * \exception RevetmentCalculationInputBuilderException
             *            Thrown when the time steps are not successive.
             */
            std::unique_ptr<Core::ICalculationInput> Build();

        private:
            std::vector<std::unique_ptr<TimeDependentInput>> _timeDependentInputItems = std::vector<std::unique_ptr<TimeDependentInput>>();
            std::vector<std::unique_ptr<LocationDependentInput>> _locationDependentInputItems
                    = std::vector<std::unique_ptr<LocationDependentInput>>();

            template <typename TValue>
            static TValue GetValue(
                const TValue* ptrValue,
                TValue defaultValue);

            [[noreturn]]
            static void ThrowWithMessage();
    };
}
