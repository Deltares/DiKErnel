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
#include "GrassRevetmentWaveImpactDefaults.h"
#include "GrassRevetmentWaveImpactDefaultsFactory.h"
#include "GrassRevetmentWaveImpactLocationDependentInput.h"
#include "GrassRevetmentWaveRunupDefaults.h"
#include "GrassRevetmentWaveRunupDefaultsFactory.h"
#include "GrassRevetmentWaveRunupRayleighDefaults.h"
#include "GrassRevetmentWaveRunupRayleighLocationDependentInput.h"
#include "NaturalStoneRevetmentLocationDependentInputFactory.h"
#include "ProfileData.h"
#include "RevetmentCalculationInputBuilderException.h"
#include "RevetmentDefaults.h"
#include "TimeDependentInput.h"

namespace DiKErnel::Integration
{
    using namespace Core;
    using namespace DomainLibrary;
    using namespace std;

    void RevetmentCalculationInputBuilder::AddDikeProfilePoint(
        const double x,
        const double z,
        const CharacteristicPointType* characteristicPointType)
    {
        _profilePoints.push_back(make_unique<ProfilePoint>(x, z));

        if (characteristicPointType != nullptr)
        {
            _characteristicPoints.push_back(make_unique<CharacteristicPoint>(*_profilePoints.back(), *characteristicPointType));
        }
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
        unique_ptr<IGrassRevetmentWaveImpactTopLayerDefaults> topLayerDefaults;

        try
        {
            topLayerDefaults = GrassRevetmentWaveImpactDefaultsFactory::CreateTopLayerDefaults(constructionProperties.GetTopLayerType());
        }
        catch (const DefaultsFactoryException&)
        {
            ThrowWithMessage();
        }

        auto waveAngleImpact = make_unique<GrassRevetmentWaveImpactWaveAngleImpact>(
            GetValue(constructionProperties.GetWaveAngleImpactNwa(), GrassRevetmentWaveImpactDefaults::GetWaveAngleImpactNwa()),
            GetValue(constructionProperties.GetWaveAngleImpactQwa(), GrassRevetmentWaveImpactDefaults::GetWaveAngleImpactQwa()),
            GetValue(constructionProperties.GetWaveAngleImpactRwa(), GrassRevetmentWaveImpactDefaults::GetWaveAngleImpactRwa()));

        auto timeLine = make_unique<GrassRevetmentWaveImpactTimeLine>(
            GetValue(constructionProperties.GetTimeLineAgwi(), topLayerDefaults->GetTimeLineAgwi()),
            GetValue(constructionProperties.GetTimeLineBgwi(), topLayerDefaults->GetTimeLineBgwi()),
            GetValue(constructionProperties.GetTimeLineCgwi(), topLayerDefaults->GetTimeLineCgwi()));

        _locationDependentInputItems.push_back(
            make_unique<GrassRevetmentWaveImpactLocationDependentInput>(
                constructionProperties.GetX(),
                GetValue(constructionProperties.GetInitialDamage(), RevetmentDefaults::GetInitialDamage()),
                GetValue(constructionProperties.GetFailureNumber(), RevetmentDefaults::GetFailureNumber()),
                move(waveAngleImpact),
                GetValue(constructionProperties.GetMinimumWaveHeightTemax(), GrassRevetmentWaveImpactDefaults::GetMinimumWaveHeightTemax()),
                GetValue(constructionProperties.GetMaximumWaveHeightTemin(), GrassRevetmentWaveImpactDefaults::GetMaximumWaveHeightTemin()),
                move(timeLine),
                GetValue(constructionProperties.GetUpperLimitLoadingAul(), GrassRevetmentWaveImpactDefaults::GetUpperLimitLoadingAul()),
                GetValue(constructionProperties.GetLowerLimitLoadingAll(), GrassRevetmentWaveImpactDefaults::GetLowerLimitLoadingAll())));
    }

    void RevetmentCalculationInputBuilder::AddGrassWaveRunupRayleighLocation(
        const GrassRevetmentWaveRunupRayleighLocationConstructionProperties& constructionProperties)
    {
        unique_ptr<IGrassRevetmentWaveRunupTopLayerDefaults> topLayerDefaults;

        try
        {
            topLayerDefaults = GrassRevetmentWaveRunupDefaultsFactory::CreateTopLayerDefaults(constructionProperties.GetTopLayerType());
        }
        catch (const DefaultsFactoryException&)
        {
            ThrowWithMessage();
        }

        auto representative2P = make_unique<GrassRevetmentWaveRunupRepresentative2P>(
            GetValue(constructionProperties.GetRepresentativeWaveRunup2PAru(), GrassRevetmentWaveRunupDefaults::GetRepresentativeWaveRunup2PAru()),
            GetValue(constructionProperties.GetRepresentativeWaveRunup2PBru(), GrassRevetmentWaveRunupDefaults::GetRepresentativeWaveRunup2PBru()),
            GetValue(constructionProperties.GetRepresentativeWaveRunup2PCru(), GrassRevetmentWaveRunupDefaults::GetRepresentativeWaveRunup2PCru()),
            GetValue(constructionProperties.GetRepresentativeWaveRunup2PGammab(),
                     GrassRevetmentWaveRunupDefaults::GetRepresentativeWaveRunup2PGammab()),
            GetValue(constructionProperties.GetRepresentativeWaveRunup2PGammaf(),
                     GrassRevetmentWaveRunupDefaults::GetRepresentativeWaveRunup2PGammaf()));

        auto waveAngleImpact = make_unique<GrassRevetmentWaveRunupWaveAngleImpact>(
            GetValue(constructionProperties.GetWaveAngleImpactAbeta(), GrassRevetmentWaveRunupDefaults::GetWaveAngleImpactAbeta()),
            GetValue(constructionProperties.GetWaveAngleImpactBetamax(), GrassRevetmentWaveRunupDefaults::GetWaveAngleImpactBetamax()));

        _locationDependentInputItems.push_back(
            make_unique<GrassRevetmentWaveRunupRayleighLocationDependentInput>(
                constructionProperties.GetX(),
                GetValue(constructionProperties.GetInitialDamage(), RevetmentDefaults::GetInitialDamage()),
                GetValue(constructionProperties.GetFailureNumber(), RevetmentDefaults::GetFailureNumber()),
                constructionProperties.GetOuterSlope(),
                GetValue(constructionProperties.GetCriticalCumulativeOverload(), topLayerDefaults->GetCriticalCumulativeOverload()),
                GetValue(constructionProperties.GetCriticalFrontVelocity(), topLayerDefaults->GetCriticalFrontVelocity()),
                GetValue(constructionProperties.GetIncreasedLoadTransitionAlphaM(),
                         GrassRevetmentWaveRunupDefaults::GetIncreasedLoadTransitionAlphaM()),
                GetValue(constructionProperties.GetReducedStrengthTransitionAlphaS(),
                         GrassRevetmentWaveRunupDefaults::GetReducedStrengthTransitionAlphaS()),
                GetValue(constructionProperties.GetAverageNumberOfWavesCtm(), GrassRevetmentWaveRunupDefaults::GetAverageNumberOfWavesCtm()),
                move(representative2P),
                move(waveAngleImpact),
                GetValue(constructionProperties.GetFixedNumberOfWaves(), GrassRevetmentWaveRunupRayleighDefaults::GetFixedNumberOfWaves()),
                GetValue(constructionProperties.GetFrontVelocityCu(), GrassRevetmentWaveRunupRayleighDefaults::GetFrontVelocityCu())));
    }

    void RevetmentCalculationInputBuilder::AddNaturalStoneLocation(
        const NaturalStoneRevetmentLocationConstructionProperties& constructionProperties)
    {
        _locationDependentInputItems.push_back(
            NaturalStoneRevetmentLocationDependentInputFactory::CreateLocationDependentInput(constructionProperties));
    }

    unique_ptr<ICalculationInput> RevetmentCalculationInputBuilder::Build()
    {
        return make_unique<CalculationInput>(make_unique<ProfileData>(move(_profilePoints), move(_characteristicPoints)),
                                             move(_locationDependentInputItems), move(_timeDependentInputItems));
    }

    template <typename TValue>
    TValue RevetmentCalculationInputBuilder::GetValue(
        const TValue* ptrValue,
        const TValue defaultValue)
    {
        return ptrValue != nullptr
                   ? *ptrValue
                   : defaultValue;
    }

    void RevetmentCalculationInputBuilder::ThrowWithMessage()
    {
        throw_with_nested(RevetmentCalculationInputBuilderException("Could not create instance."));
    }
}
