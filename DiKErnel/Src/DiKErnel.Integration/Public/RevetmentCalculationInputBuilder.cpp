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
        double x,
        double z,
        CharacteristicPointType characteristicPointType)
    {
        const auto profilePoint = make_unique<ProfilePoint>(x, z);
        _characteristicPoints.push_back(make_unique<CharacteristicPoint>(*profilePoint, characteristicPointType));
    }

    void RevetmentCalculationInputBuilder::AddDikeProfileSegment(
        double lowerPointX,
        double lowerPointZ,
        double upperPointX,
        double upperPointZ,
        const double* roughnessCoefficient)
    {
        auto upperPoint = make_unique<ProfilePoint>(upperPointX, upperPointZ);
        _profileSegmentPoints.emplace_back(make_unique<ProfilePoint>(lowerPointX, lowerPointZ));
        _profileSegmentPoints.emplace_back(make_unique<ProfilePoint>(upperPointX, upperPointZ));

        double segmentRoughnessCoefficient = ProfileSegmentDefaults::GetRoughnessCoefficient();
        if (roughnessCoefficient != nullptr)
        {
            segmentRoughnessCoefficient = *roughnessCoefficient;
        }
        _profileSegmentRoughnessCoefficients.emplace_back(segmentRoughnessCoefficient);
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
        return make_unique<CalculationInput>(make_unique<ProfileData>(CreateProfileSegments(), move(_characteristicPoints)),
                                             move(_locationDependentInputItems), move(_timeDependentInputItems));
    }

    vector<unique_ptr<ProfileSegment>> RevetmentCalculationInputBuilder::CreateProfileSegments()
    {
        vector<unique_ptr<ProfileSegment>> segments;

        if(!_profileSegmentPoints.empty())
        {
            auto lowerPoint = make_shared<ProfilePoint>(*_profileSegmentPoints.at(0));
            for (int i = 1; i < static_cast<int>(_profileSegmentPoints.size()); ++i)
            {
                auto upperPoint = make_shared<ProfilePoint>(*_profileSegmentPoints.at(i));
                segments.emplace_back(make_unique<ProfileSegment>(lowerPoint, upperPoint, _profileSegmentRoughnessCoefficients.at(i - 1)));

                lowerPoint = upperPoint;
            }
        }

        return segments;
    }
}
