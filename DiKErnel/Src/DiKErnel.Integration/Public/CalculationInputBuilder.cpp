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
#include "CalculationInputBuildException.h"
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
    }

    void CalculationInputBuilder::AddAsphaltWaveImpactLocation(
        unique_ptr<AsphaltRevetmentWaveImpactLocationConstructionProperties> constructionProperties)
    {
        _locationConstructionPropertiesItems.push_back(move(constructionProperties));
    }

    void CalculationInputBuilder::AddGrassOvertoppingLocation(
        std::unique_ptr<GrassRevetmentOvertoppingLocationConstructionProperties> constructionProperties)
    {
        _locationConstructionPropertiesItems.push_back(move(constructionProperties));
    }

    void CalculationInputBuilder::AddGrassWaveImpactLocation(
        unique_ptr<GrassRevetmentWaveImpactLocationConstructionProperties> constructionProperties)
    {
        _locationConstructionPropertiesItems.push_back(move(constructionProperties));
    }

    void CalculationInputBuilder::AddGrassWaveRunupRayleighLocation(
        unique_ptr<GrassRevetmentWaveRunupRayleighLocationConstructionProperties> constructionProperties)
    {
        _locationConstructionPropertiesItems.push_back(move(constructionProperties));
    }

    void CalculationInputBuilder::AddNaturalStoneLocation(
        unique_ptr<NaturalStoneRevetmentLocationConstructionProperties> constructionProperties)
    {
        _locationConstructionPropertiesItems.push_back(move(constructionProperties));
    }

    unique_ptr<DataResult<ICalculationInput>> CalculationInputBuilder::Build() const
    {
        auto profileSegmentDataReferences = vector<reference_wrapper<ProfileDataFactorySegment>>();

        for (const auto& profileSegmentDataItem : _profileSegmentDataItems)
        {
            profileSegmentDataReferences.emplace_back(*profileSegmentDataItem);
        }

        auto profilePointDataReferences = vector<reference_wrapper<ProfileDataFactoryPoint>>();

        for (const auto& profilePointDataItem : _profilePointDataItems)
        {
            profilePointDataReferences.emplace_back(*profilePointDataItem);
        }

        auto locationConstructionPropertiesItemReferences = vector<reference_wrapper<RevetmentLocationConstructionPropertiesBase>>();

        for (const auto& locationConstructionPropertiesItem : _locationConstructionPropertiesItems)
        {
            locationConstructionPropertiesItemReferences.emplace_back(*locationConstructionPropertiesItem);
        }

        auto timeStepDataItemReferences = vector<reference_wrapper<TimeDependentInputFactoryData>>();

        for (const auto& timeStepDataItem : _timeStepDataItems)
        {
            timeStepDataItemReferences.emplace_back(*timeStepDataItem);
        }

        if(!Validate())
        {
            return make_unique<DataResult<ICalculationInput>>(EventRegistry::Flush());
        }

        try
        {
            auto profileData = ProfileDataFactory::Create(profileSegmentDataReferences, profilePointDataReferences);
            auto locations = LocationDependentInputFactory::Create(locationConstructionPropertiesItemReferences);
            auto timeSteps = TimeDependentInputFactory::Create(timeStepDataItemReferences);

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
        _profileSegmentDataItems.emplace_back(make_unique<ProfileDataFactorySegment>(startPointX, startPointZ, endPointX, endPointZ,
                                                                                     move(roughnessCoefficient)));
    }

    bool CalculationInputBuilder::Validate() const
    {
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

        if (HasOvertoppingLocationDependentInput())
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

    bool CalculationInputBuilder::HasOvertoppingLocationDependentInput() const
    {
        return ranges::any_of(_locationConstructionPropertiesItems, [](
                          const auto& locationConstructionsPropertiesItem)
                              {
                                  return dynamic_cast<const GrassRevetmentOvertoppingLocationConstructionProperties*>(
                                              locationConstructionsPropertiesItem.get())
                                          != nullptr;
                              });
    }
}
