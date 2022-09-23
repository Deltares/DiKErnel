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
#include "DataResult.h"
#include "GrassRevetmentOvertoppingLocationConstructionProperties.h"
#include "GrassRevetmentWaveImpactLocationConstructionProperties.h"
#include "GrassRevetmentWaveRunupRayleighLocationConstructionProperties.h"
#include "ICalculationInput.h"
#include "NaturalStoneRevetmentLocationConstructionProperties.h"

namespace DiKErnel::Integration
{
    class ProfileDataFactoryPoint;
    class ProfileDataFactorySegment;
    class TimeDependentInputFactoryData;

    /*!
     * \brief Builder to configure and create calculation input.
     */
    class CalculationInputBuilder
    {
        public:
            /*!
             * \brief Creates a new instance.
             */
            explicit CalculationInputBuilder();

            /*!
             * \brief Destructs the instance.
             */
            virtual ~CalculationInputBuilder();

            /*!
             * \brief Adds a dike profile point.
             * \param x
             *        The x coordinate.
             * \param characteristicPointType
             *        The characteristic point type.
             */
            void AddDikeProfilePointData(
                double x,
                Core::CharacteristicPointType characteristicPointType);

            /*!
             * \brief Adds a new dike segment.
             * \param startPointX
             *        The x coordinate for the lower profile point.
             * \param startPointZ
             *        The z coordinate for the lower profile point.
             * \param endPointX
             *        The x coordinate for the upper profile point.
             * \param endPointZ
             *        The z coordinate for the upper profile point.
             */
            void AddDikeProfileSegment(
                double startPointX,
                double startPointZ,
                double endPointX,
                double endPointZ);

            /*!
             * \brief Adds a new dike segment.
             * \param startPointX
             *        The x coordinate for the lower profile point.
             * \param startPointZ
             *        The z coordinate for the lower profile point.
             * \param endPointX
             *        The x coordinate for the upper profile point.
             * \param endPointZ
             *        The z coordinate for the upper profile point.
             * \param roughnessCoefficient
             *        The roughness coefficient.
             */
            void AddDikeProfileSegment(
                double startPointX,
                double startPointZ,
                double endPointX,
                double endPointZ,
                double roughnessCoefficient);

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
             */
            void AddAsphaltWaveImpactLocation(
                std::unique_ptr<AsphaltRevetmentWaveImpactLocationConstructionProperties> constructionProperties);

            /*!
             * \brief Adds a grass overtopping location.
             * \param constructionProperties
             *        The properties to construct the grass overtopping location dependent input.
             */
            void AddGrassOvertoppingLocation(
                std::unique_ptr<GrassRevetmentOvertoppingLocationConstructionProperties> constructionProperties);

            /*!
             * \brief Adds a grass wave impact location.
             * \param constructionProperties
             *        The properties to construct the grass wave impact location dependent input.
             */
            void AddGrassWaveImpactLocation(
                std::unique_ptr<GrassRevetmentWaveImpactLocationConstructionProperties> constructionProperties);

            /*!
             * \brief Adds a grass wave run-up location with Rayleigh protocol.
             * \param constructionProperties
             *        The properties to construct the grass wave run-up Rayleigh location dependent input.
             */
            void AddGrassWaveRunupRayleighLocation(
                std::unique_ptr<GrassRevetmentWaveRunupRayleighLocationConstructionProperties> constructionProperties);

            /*!
             * \brief Adds a natural stone location.
             * \param constructionProperties
             *        The properties to construct the natural stone location dependent input.
             */
            void AddNaturalStoneLocation(
                std::unique_ptr<NaturalStoneRevetmentLocationConstructionProperties> constructionProperties);

            /*!
             * \brief Builds the calculation input.
             * \return The result with the created calculation input.
             */
            [[nodiscard]]
            std::unique_ptr<Util::DataResult<Core::ICalculationInput>> Build() const;

        private:
            void AddDikeProfileSegment(
                double startPointX,
                double startPointZ,
                double endPointX,
                double endPointZ,
                std::unique_ptr<double> roughnessCoefficient);

            void AddLocation(
                std::unique_ptr<RevetmentLocationConstructionPropertiesBase> constructionProperties);

            [[nodiscard]]
            bool Validate() const;

            [[nodiscard]]
            bool HasOvertoppingLocationDependentInput() const;

            [[nodiscard]]
            bool HasCharacteristicPointType(
                Core::CharacteristicPointType characteristicPointType) const;

            void RegisterValidationError(
                const std::string& message) const;

            std::vector<std::unique_ptr<ProfileDataFactoryPoint>> _profilePointDataItems;
            std::vector<std::reference_wrapper<ProfileDataFactoryPoint>> _profilePointDataItemReferences;
            std::vector<std::unique_ptr<ProfileDataFactorySegment>> _profileSegmentDataItems;
            std::vector<std::reference_wrapper<ProfileDataFactorySegment>> _profileSegmentDataItemReferences;
            std::vector<std::unique_ptr<TimeDependentInputFactoryData>> _timeStepDataItems;
            std::vector<std::reference_wrapper<TimeDependentInputFactoryData>> _timeStepDataItemReferences;
            std::vector<std::unique_ptr<RevetmentLocationConstructionPropertiesBase>> _locationConstructionPropertiesItems;
            std::vector<std::reference_wrapper<RevetmentLocationConstructionPropertiesBase>> _locationConstructionPropertiesItemReferences;

            inline static std::string _exceptionMessage = "Could not create calculation input.";
    };
}
