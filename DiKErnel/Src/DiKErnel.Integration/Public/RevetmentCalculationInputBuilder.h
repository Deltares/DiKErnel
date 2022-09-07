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

#include "AsphaltRevetmentWaveImpactLocationConstructionProperties.h"
#include "ICalculationInput.h"
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
             * \brief Adds a dike profile point.
             * \param x
             *        The x coordinate.
             * \param z
             *        The z coordinate.
             * \param characteristicPointType
             *        The characteristic point type.
             */
            void AddDikeProfilePoint(
                double x,
                double z,
                const Core::CharacteristicPointType* characteristicPointType);

            /*!
             * \brief Adds data for a profile point.
             * \param profilePoint
             *        The profile point.
             * \param characteristicPointType
             *        The characteristic point type.
             */
            void AddDikeProfilePointData(
                const std::shared_ptr<Core::ProfilePoint>& profilePoint,
                Core::CharacteristicPointType characteristicPointType);

            /*!
             * \brief Adds a new dike segment.
             * \param lowerPoint
             *        The lower profile point.
             * \param upperPoint
             *        The upper profile point.
             * \param roughness
             *        The roughness.
             */
            void AddDikeProfileSegment(
                const std::shared_ptr<Core::ProfilePoint>& lowerPoint,
                const std::shared_ptr<Core::ProfilePoint>& upperPoint,
                double roughness);

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
             */
            void AddTimeStep(
                int beginTime,
                int endTime,
                double waterLevel,
                double waveHeightHm0,
                double wavePeriodTm10,
                double waveAngle);

            /*!
             * \brief Adds an asphalt wave impact location.
             * \param constructionProperties
             *        The properties to construct the asphalt wave impact location dependent input.
             * \exception RevetmentCalculationInputBuilderException
             *            Thrown when the top layer type is invalid.
             */
            void AddAsphaltWaveImpactLocation(
                const AsphaltRevetmentWaveImpactLocationConstructionProperties& constructionProperties);

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
             * \brief Adds a grass wave run-up location with Rayleigh protocol.
             * \param constructionProperties
             *        The properties to construct the grass wave run-up Rayleigh location dependent input.
             * \exception RevetmentCalculationInputBuilderException
             *            Thrown when the top layer type is invalid.
             */
            void AddGrassWaveRunupRayleighLocation(
                const GrassRevetmentWaveRunupRayleighLocationConstructionProperties& constructionProperties);

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
             * \brief Builds the calculation input.
             * \return The created calculation input.
             */
            std::unique_ptr<Core::ICalculationInput> Build();

        private:
            std::vector<std::unique_ptr<Core::ProfilePoint>> _profilePoints = std::vector<std::unique_ptr<Core::ProfilePoint>>();
            std::vector<std::unique_ptr<Core::ProfileSegment>> _profileSegments = std::vector<std::unique_ptr<Core::ProfileSegment>>();
            std::vector<std::unique_ptr<Core::CharacteristicPoint>> _characteristicPoints
                    = std::vector<std::unique_ptr<Core::CharacteristicPoint>>();
            std::vector<std::unique_ptr<Core::ITimeDependentInput>> _timeDependentInputItems
                    = std::vector<std::unique_ptr<Core::ITimeDependentInput>>();
            std::vector<std::unique_ptr<Core::ILocationDependentInput>> _locationDependentInputItems
                    = std::vector<std::unique_ptr<Core::ILocationDependentInput>>();

    };
}
