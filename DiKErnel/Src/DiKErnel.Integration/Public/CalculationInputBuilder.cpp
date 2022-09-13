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
#include "NaturalStoneRevetmentLocationDependentInputFactory.h"
#include "ProfileData.h"
#include "ProfileFactory.h"
#include "ProfileFactoryException.h"
#include "ProfileFactoryPointData.h"
#include "ProfileFactorySegmentData.h"
#include "TimeDependentInput.h"

namespace DiKErnel::Integration
{
    using namespace Core;
    using namespace DomainLibrary;
    using namespace std;

    void CalculationInputBuilder::AddDikeProfilePointData(
        const double x,
        const double z,
        const CharacteristicPointType characteristicPointType)
    {
        _profilePointData.push_back(make_unique<ProfileFactoryPointData>(x, z, characteristicPointType));
    }

    void CalculationInputBuilder::AddDikeProfileSegment(
        double startPointX,
        double startPointZ,
        double endPointX,
        double endPointZ,
        const double* roughnessCoefficient)
    {
        _profileSegmentData.emplace_back(make_unique<ProfileFactorySegmentData>(startPointX, startPointZ, endPointX, endPointZ,
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
        _timeDependentInputItems.push_back(
            make_unique<TimeDependentInput>(beginTime, endTime, waterLevel, waveHeightHm0, wavePeriodTm10, waveAngle));
    }

    void CalculationInputBuilder::AddAsphaltWaveImpactLocation(
        const AsphaltRevetmentWaveImpactLocationConstructionProperties& constructionProperties)
    {
        _locationDependentInputItems.push_back(
            AsphaltRevetmentWaveImpactLocationDependentInputFactory::CreateLocationDependentInput(constructionProperties));
    }

    void CalculationInputBuilder::AddGrassWaveImpactLocation(
        const GrassRevetmentWaveImpactLocationConstructionProperties& constructionProperties)
    {
        _locationDependentInputItems.push_back(
            GrassRevetmentWaveImpactLocationDependentInputFactory::CreateLocationDependentInput(constructionProperties));
    }

    void CalculationInputBuilder::AddGrassWaveRunupRayleighLocation(
        const GrassRevetmentWaveRunupRayleighLocationConstructionProperties& constructionProperties)
    {
        _locationDependentInputItems.push_back(
            GrassRevetmentWaveRunupRayleighLocationDependentInputFactory::CreateLocationDependentInput(constructionProperties));
    }

    void CalculationInputBuilder::AddNaturalStoneLocation(
        const NaturalStoneRevetmentLocationConstructionProperties& constructionProperties)
    {
        _locationDependentInputItems.push_back(
            NaturalStoneRevetmentLocationDependentInputFactory::CreateLocationDependentInput(constructionProperties));
    }

    unique_ptr<ICalculationInput> CalculationInputBuilder::Build()
    {
        try
        {
            auto segments = ProfileFactory::CreateProfileSegments(_profileSegmentData);
            auto characteristicPoints = ProfileFactory::CreateCharacteristicPoints(_profilePointData, segments);
            return make_unique<CalculationInput>(make_unique<ProfileData>(move(segments), move(characteristicPoints)),
                                                 move(_locationDependentInputItems), move(_timeDependentInputItems));
        }
        catch (const ProfileFactoryException&)
        {
            throw_with_nested(CalculationInputBuildException("Could not create instance."));
        }
    }
}
