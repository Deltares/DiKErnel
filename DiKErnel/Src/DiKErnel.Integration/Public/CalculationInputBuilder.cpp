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

#include "AsphaltRevetmentWaveImpactDefaults.h"
#include "AsphaltRevetmentWaveImpactDefaultsFactory.h"
#include "AsphaltRevetmentWaveImpactLocationDependentInputFactory.h"
#include "CalculationInput.h"
#include "CalculationInputBuildException.h"
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

namespace DiKErnel::Integration
{
    using namespace Core;
    using namespace DomainLibrary;
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
        double startPointX,
        double startPointZ,
        double endPointX,
        double endPointZ,
        const double* roughnessCoefficient)
    {
        _profileSegmentDataItems.emplace_back(make_unique<ProfileDataFactorySegment>(startPointX, startPointZ, endPointX, endPointZ,
                                                                                     roughnessCoefficient));
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

    unique_ptr<ICalculationInput> CalculationInputBuilder::Build() const
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

        try
        {
            auto profileData = ProfileDataFactory::Create(profileSegmentDataReferences, profilePointDataReferences);
            auto locations = LocationDependentInputFactory::Create(locationConstructionPropertiesItemReferences);
            auto timeSteps = TimeDependentInputFactory::Create(timeStepDataItemReferences);

            return make_unique<CalculationInput>(move(profileData), move(locations), move(timeSteps));
        }
        catch (const InputFactoryException&)
        {
            throw_with_nested(CalculationInputBuildException(_exceptionMessage));
        }
    }
}
