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

#include "RevetmentCalculationInputBuilder.h"

#include "AsphaltRevetmentWaveImpactDefaults.h"
#include "AsphaltRevetmentWaveImpactDefaultsFactory.h"
#include "AsphaltRevetmentWaveImpactLocationDependentInputFactory.h"
#include "CalculationInput.h"
#include "DefaultsFactoryException.h"
#include "GrassRevetmentWaveImpactLocationDependentInputFactory.h"
#include "GrassRevetmentWaveRunupRayleighLocationDependentInputFactory.h"
#include "NaturalStoneRevetmentLocationDependentInputFactory.h"
#include "ProfileData.h"
#include "ProfileSegmentDefaults.h"
#include "TimeDependentInput.h"

namespace DiKErnel::Integration
{
    using namespace Core;
    using namespace DomainLibrary;
    using namespace std;

    void RevetmentCalculationInputBuilder::AddDikeProfilePointData(
        const double x,
        const double z,
        const CharacteristicPointType* characteristicPointType)
    {
        if (characteristicPointType != nullptr)
        {
            _profilePointData.push_back(make_unique<ProfilePointData>(x, z, *characteristicPointType));
        }
    }

    void RevetmentCalculationInputBuilder::AddDikeProfileSegment(
        double lowerPointX,
        double lowerPointZ,
        double upperPointX,
        double upperPointZ,
        const double* roughnessCoefficient)
    {
        double segmentRoughnessCoefficient = ProfileSegmentDefaults::GetRoughnessCoefficient();
        if (roughnessCoefficient != nullptr)
        {
            segmentRoughnessCoefficient = *roughnessCoefficient;
        }
        _profileSegmentData.emplace_back(make_unique<ProfileSegmentData>(lowerPointX, lowerPointZ, upperPointX, upperPointZ,
                                                                         segmentRoughnessCoefficient));
    }

    void RevetmentCalculationInputBuilder::AddTimeStep(
        int beginTime,
        int endTime,
        double waterLevel,
        double waveHeightHm0,
        double wavePeriodTm10,
        double waveAngle)
    {
        _timeDependentInputItems.push_back(
            make_unique<TimeDependentInput>(beginTime, endTime, waterLevel, waveHeightHm0, wavePeriodTm10, waveAngle));
    }

    void RevetmentCalculationInputBuilder::AddAsphaltWaveImpactLocation(
        const AsphaltRevetmentWaveImpactLocationConstructionProperties& constructionProperties)
    {
        _locationDependentInputItems.push_back(
            AsphaltRevetmentWaveImpactLocationDependentInputFactory::CreateLocationDependentInput(constructionProperties));
    }

    void RevetmentCalculationInputBuilder::AddGrassWaveImpactLocation(
        const GrassRevetmentWaveImpactLocationConstructionProperties& constructionProperties)
    {
        _locationDependentInputItems.push_back(
            GrassRevetmentWaveImpactLocationDependentInputFactory::CreateLocationDependentInput(constructionProperties));
    }

    void RevetmentCalculationInputBuilder::AddGrassWaveRunupRayleighLocation(
        const GrassRevetmentWaveRunupRayleighLocationConstructionProperties& constructionProperties)
    {
        _locationDependentInputItems.push_back(
            GrassRevetmentWaveRunupRayleighLocationDependentInputFactory::CreateLocationDependentInput(constructionProperties));
    }

    void RevetmentCalculationInputBuilder::AddNaturalStoneLocation(
        const NaturalStoneRevetmentLocationConstructionProperties& constructionProperties)
    {
        _locationDependentInputItems.push_back(
            NaturalStoneRevetmentLocationDependentInputFactory::CreateLocationDependentInput(constructionProperties));
    }

    unique_ptr<ICalculationInput> RevetmentCalculationInputBuilder::Build()
    {
        auto segments = CreateProfileSegments();
        auto characteristicPoints = CreateCharacteristicPoints(segments);
        return make_unique<CalculationInput>(make_unique<ProfileData>(move(segments), move(characteristicPoints)),
                                             move(_locationDependentInputItems), move(_timeDependentInputItems));
    }

    vector<unique_ptr<ProfileSegment>> RevetmentCalculationInputBuilder::CreateProfileSegments() const
    {
        vector<unique_ptr<ProfileSegment>> segments;

        if (!_profileSegmentData.empty())
        {
            for (const auto& segmentInfo : _profileSegmentData)
            {
                auto lowerPoint = make_shared<ProfilePoint>(segmentInfo->_lowerPointX, segmentInfo->_lowerPointZ);
                auto upperPoint = make_shared<ProfilePoint>(segmentInfo->_upperPointX, segmentInfo->_upperPointZ);

                segments.emplace_back(make_unique<ProfileSegment>(lowerPoint, upperPoint, segmentInfo->_roughnessCoefficient));
                lowerPoint = upperPoint;
            }
        }

        return segments;
    }

    vector<unique_ptr<CharacteristicPoint>> RevetmentCalculationInputBuilder::CreateCharacteristicPoints(
        const vector<unique_ptr<ProfileSegment>>& segments) const
    {
        vector<unique_ptr<CharacteristicPoint>> characteristicPoints;
        for (const auto& characteristicPoint : _profilePointData)
        {
            for (const auto& segment : segments)
            {
                const double characteristicPointX = characteristicPoint->_x;
                if (const auto& segmentLowerPoint = segment->GetLowerPoint();
                    abs(characteristicPointX - segmentLowerPoint.GetX()) <= numeric_limits<double>::epsilon())
                {
                    characteristicPoints.emplace_back(make_unique<CharacteristicPoint>(segmentLowerPoint,
                                                                                       characteristicPoint->_characteristicPointType));
                    break;
                }

                if (const auto& segmentUpperPoint = segment->GetUpperPoint();
                    abs(characteristicPointX - segmentUpperPoint.GetX()) <= numeric_limits<double>::epsilon())
                {
                    characteristicPoints.emplace_back(make_unique<CharacteristicPoint>(segmentUpperPoint,
                                                                                       characteristicPoint->_characteristicPointType));
                    break;
                }
            }
        }

        return characteristicPoints;
    }
}
