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

#include "CalculationInputBuilder.h"

#include <algorithm>

#include "AsphaltRevetmentWaveImpactDefaults.h"
#include "AsphaltRevetmentWaveImpactDefaultsFactory.h"
#include "AsphaltRevetmentWaveImpactLocationDependentInputFactory.h"
#include "CalculationInput.h"
#include "EventRegistry.h"
#include "GrassRevetmentWaveImpactLocationDependentInputFactory.h"
#include "GrassRevetmentWaveRunupRayleighLocationDependentInputFactory.h"
#include "InputFactoryException.h"
#include "LocationDependentInputFactory.h"
#include "NaturalStoneRevetmentLocationDependentInputFactory.h"
#include "ProfileDataFactory.h"
#include "ProfileDataFactoryPoint.h"
#include "ProfileDataFactorySegment.h"
#include "TimeDependentInputFactory.h"
#include "TimeDependentInputFactoryData.h"
#include "ValidationHelper.h"

namespace DiKErnel::Integration
{
    using namespace Core;
    using namespace DomainLibrary;
    using namespace Util;
    using namespace std;

    CalculationInputBuilder::CalculationInputBuilder() = default;

    CalculationInputBuilder::~CalculationInputBuilder() = default;

    void CalculationInputBuilder::AddDikeProfilePointData(
        const double x,
        const CharacteristicPointType characteristicPointType)
    {
        _profilePointDataItems.push_back(make_unique<ProfileDataFactoryPoint>(x, characteristicPointType));
        _profilePointDataItemReferences.emplace_back(*_profilePointDataItems.back());
    }

    void CalculationInputBuilder::AddDikeProfileSegment(
        const double startPointX,
        const double startPointZ,
        const double endPointX,
        const double endPointZ)
    {
        AddDikeProfileSegment(startPointX, startPointZ, endPointX, endPointZ, nullptr);
    }

    void CalculationInputBuilder::AddDikeProfileSegment(
        const double startPointX,
        const double startPointZ,
        const double endPointX,
        const double endPointZ,
        const double roughnessCoefficient)
    {
        AddDikeProfileSegment(startPointX, startPointZ, endPointX, endPointZ, make_unique<double>(roughnessCoefficient));
    }

    void CalculationInputBuilder::AddTimeStep(
        int beginTime,
        int endTime,
        double waterLevel,
        double waveHeightHm0,
        double wavePeriodTm10,
        double waveAngle)
    {
        _timeStepDataItems.push_back(
            make_unique<TimeDependentInputFactoryData>(beginTime, endTime, waterLevel, waveHeightHm0, wavePeriodTm10, waveAngle));
        _timeStepDataItemReferences.emplace_back(*_timeStepDataItems.back());
    }

    void CalculationInputBuilder::AddAsphaltWaveImpactLocation(
        unique_ptr<AsphaltRevetmentWaveImpactLocationConstructionProperties> constructionProperties)
    {
        AddLocation(move(constructionProperties));
    }

    void CalculationInputBuilder::AddGrassOvertoppingLocation(
        std::unique_ptr<GrassRevetmentOvertoppingLocationConstructionProperties> constructionProperties)
    {
        AddLocation(move(constructionProperties));
        _hasOvertoppingLocationDependentInput = true;
    }

    void CalculationInputBuilder::AddGrassWaveImpactLocation(
        unique_ptr<GrassRevetmentWaveImpactLocationConstructionProperties> constructionProperties)
    {
        AddLocation(move(constructionProperties));
    }

    void CalculationInputBuilder::AddGrassWaveRunupRayleighLocation(
        unique_ptr<GrassRevetmentWaveRunupRayleighLocationConstructionProperties> constructionProperties)
    {
        AddLocation(move(constructionProperties));
    }

    void CalculationInputBuilder::AddNaturalStoneLocation(
        unique_ptr<NaturalStoneRevetmentLocationConstructionProperties> constructionProperties)
    {
        AddLocation(move(constructionProperties));
    }

    unique_ptr<DataResult<ICalculationInput>> CalculationInputBuilder::Build() const
    {
        if (!CanBuildValidCalculationInput())
        {
            return make_unique<DataResult<ICalculationInput>>(EventRegistry::Flush());
        }

        try
        {
            auto profileData = ProfileDataFactory::Create(_profileSegmentDataItemReferences, _profilePointDataItemReferences);
            auto locations = LocationDependentInputFactory::Create(_locationConstructionPropertiesItemReferences);
            auto timeSteps = TimeDependentInputFactory::Create(_timeStepDataItemReferences);

            return make_unique<DataResult<ICalculationInput>>(make_unique<CalculationInput>(move(profileData), move(locations), move(timeSteps)),
                                                              EventRegistry::Flush());
        }
        catch (const InputFactoryException&)
        {
            EventRegistry::Register(make_unique<Event>(_exceptionMessage, EventType::Error));
            return make_unique<DataResult<ICalculationInput>>(EventRegistry::Flush());
        }
    }

    void CalculationInputBuilder::AddDikeProfileSegment(
        double startPointX,
        double startPointZ,
        double endPointX,
        double endPointZ,
        unique_ptr<double> roughnessCoefficient)
    {
        _profileSegmentDataItems.push_back(make_unique<ProfileDataFactorySegment>(startPointX, startPointZ, endPointX, endPointZ,
                                                                                  move(roughnessCoefficient)));
        _profileSegmentDataItemReferences.emplace_back(*_profileSegmentDataItems.back());
    }

    void CalculationInputBuilder::AddLocation(
        unique_ptr<RevetmentLocationConstructionPropertiesBase> constructionProperties)
    {
        _locationConstructionPropertiesItems.push_back(move(constructionProperties));
        _locationConstructionPropertiesItemReferences.emplace_back(*_locationConstructionPropertiesItems.back());
    }

    bool CalculationInputBuilder::CanBuildValidCalculationInput() const
    {
        if (_profileSegmentDataItems.empty())
        {
            RegisterValidationError("At least 1 segment is required.");
            return false;
        }

        const ProfileDataFactorySegment* previousSegment = nullptr;
        for (const auto& profileSegmentDataItem : _profileSegmentDataItems)
        {
            const ProfileDataFactorySegment* currentSegment = profileSegmentDataItem.get();

            if (previousSegment != nullptr
                && (abs(previousSegment->GetEndPointX() - currentSegment->GetStartPointX()) > numeric_limits<double>::epsilon()
                    || abs(previousSegment->GetEndPointZ() - currentSegment->GetStartPointZ()) > numeric_limits<double>::epsilon()))
            {
                RegisterValidationError("The start point of a successive segment must be equal to the end point of the previous segment.");
                return false;
            }

            previousSegment = currentSegment;
        }

        if (!HasCharacteristicPointType(CharacteristicPointType::OuterToe))
        {
            RegisterValidationError("The outer toe is required.");
            return false;
        }

        if (!HasCharacteristicPointType(CharacteristicPointType::OuterCrest))
        {
            RegisterValidationError("The outer crest is required.");
            return false;
        }

        if (_hasOvertoppingLocationDependentInput)
        {
            if (!HasCharacteristicPointType(CharacteristicPointType::InnerToe))
            {
                RegisterValidationError("The inner toe is required.");
                return false;
            }

            if (!HasCharacteristicPointType(CharacteristicPointType::InnerCrest))
            {
                RegisterValidationError("The inner crest is required.");
                return false;
            }
        }

        return true;
    }

    bool CalculationInputBuilder::HasCharacteristicPointType(
        CharacteristicPointType characteristicPointType) const
    {
        return ranges::any_of(_profilePointDataItems, [characteristicPointType](
                          const auto& profilePointDataItem)
                              {
                                  return profilePointDataItem->GetCharacteristicPoint() == characteristicPointType;
                              });
    }

    void CalculationInputBuilder::RegisterValidationError(
        const string& message) const
    {
        EventRegistry::Register(make_unique<Event>(message, EventType::Error));
    }
}
