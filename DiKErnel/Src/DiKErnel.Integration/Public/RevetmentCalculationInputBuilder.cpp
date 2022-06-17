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

#include "AsphaltRevetmentWaveImpactDefaultsFactory.h"
#include "AsphaltRevetmentWaveImpactLocationDependentInput.h"
#include "CalculationInput.h"
#include "DefaultsFactoryException.h"
#include "GrassRevetmentWaveImpactDefaultsFactory.h"
#include "GrassRevetmentWaveImpactLocationDependentInput.h"
#include "GrassRevetmentWaveRunupDefaultsFactory.h"
#include "GrassRevetmentWaveRunupRayleighLocationDependentInput.h"
#include "IAsphaltRevetmentWaveImpactDefaults.h"
#include "IGrassRevetmentWaveRunupRayleighDefaults.h"
#include "NaturalStoneRevetmentDefaults.h"
#include "NaturalStoneRevetmentDefaultsFactory.h"
#include "NaturalStoneRevetmentLocationConstructionProperties.h"
#include "NaturalStoneRevetmentLocationDependentInput.h"
#include "NordicStoneRevetmentTopLayerDefaults.h"
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
        unique_ptr<IAsphaltRevetmentWaveImpactDefaults> defaults;

        try
        {
            defaults = AsphaltRevetmentWaveImpactDefaultsFactory::Create(
                constructionProperties.GetTopLayerType());
        }
        catch (const DefaultsFactoryException&)
        {
            ThrowWithMessage();
        }

        const auto elasticModulusUpperLayer = constructionProperties.GetElasticModulusUpperLayer();
        auto upperLayer = make_unique<AsphaltRevetmentWaveImpactLayer>(
            constructionProperties.GetThicknessUpperLayer(),
            elasticModulusUpperLayer);

        const auto thicknessSubLayer = constructionProperties.GetThicknessSubLayer();
        const auto elasticModulusSubLayer = constructionProperties.GetElasticModulusSubLayer();
        unique_ptr<AsphaltRevetmentWaveImpactLayer> subLayer = nullptr;
        if (thicknessSubLayer != nullptr && elasticModulusSubLayer != nullptr)
        {
            subLayer = make_unique<AsphaltRevetmentWaveImpactLayer>(*thicknessSubLayer, *elasticModulusSubLayer);
        }

        auto fatigue = make_unique<AsphaltRevetmentWaveImpactFatigue>(
            GetValue(constructionProperties.GetFatigueAlpha(), defaults->GetFatigueAlpha()),
            GetValue(constructionProperties.GetFatigueBeta(), defaults->GetFatigueBeta()));

        _locationDependentInputItems.push_back(
            make_unique<AsphaltRevetmentWaveImpactLocationDependentInput>(
                constructionProperties.GetX(),
                GetValue(constructionProperties.GetInitialDamage(), RevetmentDefaults::GetInitialDamage()),
                GetValue(constructionProperties.GetFailureNumber(), RevetmentDefaults::GetFailureNumber()),
                constructionProperties.GetOuterSlope(),
                constructionProperties.GetFailureTension(),
                GetValue(constructionProperties.GetDensityOfWater(), defaults->GetDensityOfWater()),
                constructionProperties.GetSoilElasticity(),
                move(upperLayer),
                move(subLayer),
                GetValue(constructionProperties.GetAverageNumberOfWavesCtm(), defaults->GetAverageNumberOfWavesCtm()),
                move(fatigue),
                GetValue(constructionProperties.GetImpactNumberC(), defaults->GetImpactNumberC()),
                GetValue(constructionProperties.GetStiffnessRelationNu(), defaults->GetStiffnessRelationNu()),
                GetValue(constructionProperties.GetWidthFactors(), defaults->GetWidthFactors()),
                GetValue(constructionProperties.GetDepthFactors(), defaults->GetDepthFactors()),
                GetValue(constructionProperties.GetImpactFactors(), defaults->GetImpactFactors())));
    }

    void RevetmentCalculationInputBuilder::AddGrassWaveImpactLocation(
        const GrassRevetmentWaveImpactLocationConstructionProperties& constructionProperties)
    {
        unique_ptr<IGrassRevetmentWaveImpactDefaults> defaults;

        try
        {
            defaults = GrassRevetmentWaveImpactDefaultsFactory::Create(constructionProperties.GetTopLayerType());
        }
        catch (const DefaultsFactoryException&)
        {
            ThrowWithMessage();
        }

        auto waveAngleImpact = make_unique<GrassRevetmentWaveImpactWaveAngleImpact>(
            GetValue(constructionProperties.GetWaveAngleImpactNwa(), defaults->GetWaveAngleImpactNwa()),
            GetValue(constructionProperties.GetWaveAngleImpactQwa(), defaults->GetWaveAngleImpactQwa()),
            GetValue(constructionProperties.GetWaveAngleImpactRwa(), defaults->GetWaveAngleImpactRwa()));

        auto timeLine = make_unique<GrassRevetmentWaveImpactTimeLine>(
            GetValue(constructionProperties.GetTimeLineAgwi(), defaults->GetTimeLineAgwi()),
            GetValue(constructionProperties.GetTimeLineBgwi(), defaults->GetTimeLineBgwi()),
            GetValue(constructionProperties.GetTimeLineCgwi(), defaults->GetTimeLineCgwi()));

        _locationDependentInputItems.push_back(
            make_unique<GrassRevetmentWaveImpactLocationDependentInput>(
                constructionProperties.GetX(),
                GetValue(constructionProperties.GetInitialDamage(), RevetmentDefaults::GetInitialDamage()),
                GetValue(constructionProperties.GetFailureNumber(), RevetmentDefaults::GetFailureNumber()),
                move(waveAngleImpact),
                GetValue(constructionProperties.GetMinimumWaveHeightTemax(), defaults->GetMinimumWaveHeightTemax()),
                GetValue(constructionProperties.GetMaximumWaveHeightTemin(), defaults->GetMaximumWaveHeightTemin()),
                move(timeLine),
                GetValue(constructionProperties.GetUpperLimitLoadingAul(), defaults->GetUpperLimitLoadingAul()),
                GetValue(constructionProperties.GetLowerLimitLoadingAll(), defaults->GetLowerLimitLoadingAll())));
    }

    void RevetmentCalculationInputBuilder::AddGrassWaveRunupRayleighLocation(
        const GrassRevetmentWaveRunupRayleighLocationConstructionProperties& constructionProperties)
    {
        unique_ptr<IGrassRevetmentWaveRunupRayleighDefaults> defaults;

        try
        {
            defaults = GrassRevetmentWaveRunupDefaultsFactory::CreateForRayleigh(constructionProperties.GetTopLayerType());
        }
        catch (const DefaultsFactoryException&)
        {
            ThrowWithMessage();
        }

        auto representative2P = make_unique<GrassRevetmentWaveRunupRepresentative2P>(
            GetValue(constructionProperties.GetRepresentativeWaveRunup2PAru(), defaults->GetRepresentativeWaveRunup2PAru()),
            GetValue(constructionProperties.GetRepresentativeWaveRunup2PBru(), defaults->GetRepresentativeWaveRunup2PBru()),
            GetValue(constructionProperties.GetRepresentativeWaveRunup2PCru(), defaults->GetRepresentativeWaveRunup2PCru()),
            GetValue(constructionProperties.GetRepresentativeWaveRunup2PGammab(), defaults->GetRepresentativeWaveRunup2PGammab()),
            GetValue(constructionProperties.GetRepresentativeWaveRunup2PGammaf(), defaults->GetRepresentativeWaveRunup2PGammaf()));

        auto waveAngleImpact = make_unique<GrassRevetmentWaveRunupWaveAngleImpact>(
            GetValue(constructionProperties.GetWaveAngleImpactAbeta(), defaults->GetWaveAngleImpactAbeta()),
            GetValue(constructionProperties.GetWaveAngleImpactBetamax(), defaults->GetWaveAngleImpactBetamax()));

        _locationDependentInputItems.push_back(
            make_unique<GrassRevetmentWaveRunupRayleighLocationDependentInput>(
                constructionProperties.GetX(),
                GetValue(constructionProperties.GetInitialDamage(), RevetmentDefaults::GetInitialDamage()),
                GetValue(constructionProperties.GetFailureNumber(), RevetmentDefaults::GetFailureNumber()),
                constructionProperties.GetOuterSlope(),
                GetValue(constructionProperties.GetCriticalCumulativeOverload(), defaults->GetCriticalCumulativeOverload()),
                GetValue(constructionProperties.GetCriticalFrontVelocity(), defaults->GetCriticalFrontVelocity()),
                GetValue(constructionProperties.GetIncreasedLoadTransitionAlphaM(), defaults->GetIncreasedLoadTransitionAlphaM()),
                GetValue(constructionProperties.GetReducedStrengthTransitionAlphaS(), defaults->GetReducedStrengthTransitionAlphaS()),
                GetValue(constructionProperties.GetAverageNumberOfWavesCtm(), defaults->GetAverageNumberOfWavesCtm()),
                move(representative2P),
                move(waveAngleImpact),
                GetValue(constructionProperties.GetFixedNumberOfWaves(), defaults->GetFixedNumberOfWaves()),
                GetValue(constructionProperties.GetFrontVelocityCu(), defaults->GetFrontVelocityCu())));
    }

    void RevetmentCalculationInputBuilder::AddNaturalStoneLocation(
        const NaturalStoneRevetmentLocationConstructionProperties& constructionProperties)
    {
        unique_ptr<INaturalStoneRevetmentTopLayerDefaults> topLayerDefaults;

        try
        {
            topLayerDefaults = NaturalStoneRevetmentDefaultsFactory::CreateTopLayerDefaults(constructionProperties.GetTopLayerType());
        }
        catch (const DefaultsFactoryException&)
        {
            ThrowWithMessage();
        }

        auto hydraulicLoads = make_unique<NaturalStoneRevetmentHydraulicLoads>(
            GetValue(constructionProperties.GetHydraulicLoadAp(), topLayerDefaults->GetHydraulicLoadAp()),
            GetValue(constructionProperties.GetHydraulicLoadBp(), topLayerDefaults->GetHydraulicLoadBp()),
            GetValue(constructionProperties.GetHydraulicLoadCp(), topLayerDefaults->GetHydraulicLoadCp()),
            GetValue(constructionProperties.GetHydraulicLoadNp(), topLayerDefaults->GetHydraulicLoadNp()),
            GetValue(constructionProperties.GetHydraulicLoadAs(), topLayerDefaults->GetHydraulicLoadAs()),
            GetValue(constructionProperties.GetHydraulicLoadBs(), topLayerDefaults->GetHydraulicLoadBs()),
            GetValue(constructionProperties.GetHydraulicLoadCs(), topLayerDefaults->GetHydraulicLoadCs()),
            GetValue(constructionProperties.GetHydraulicLoadNs(), topLayerDefaults->GetHydraulicLoadNs()),
            GetValue(constructionProperties.GetHydraulicLoadXib(), topLayerDefaults->GetHydraulicLoadXib()));

        auto slope = make_unique<NaturalStoneRevetmentSlope>(
            GetValue(constructionProperties.GetSlopeUpperLevelAus(), NaturalStoneRevetmentDefaults::GetSlopeUpperLevelAus()),
            GetValue(constructionProperties.GetSlopeLowerLevelAls(), NaturalStoneRevetmentDefaults::GetSlopeLowerLevelAls()));

        auto upperLimitLoading = make_unique<NaturalStoneRevetmentUpperLimitLoading>(
            GetValue(constructionProperties.GetUpperLimitLoadingAul(), NaturalStoneRevetmentDefaults::GetUpperLimitLoadingAul()),
            GetValue(constructionProperties.GetUpperLimitLoadingBul(), NaturalStoneRevetmentDefaults::GetUpperLimitLoadingBul()),
            GetValue(constructionProperties.GetUpperLimitLoadingCul(), NaturalStoneRevetmentDefaults::GetUpperLimitLoadingCul()));

        auto lowerLimitLoading = make_unique<NaturalStoneRevetmentLowerLimitLoading>(
            GetValue(constructionProperties.GetLowerLimitLoadingAll(), NaturalStoneRevetmentDefaults::GetLowerLimitLoadingAll()),
            GetValue(constructionProperties.GetLowerLimitLoadingBll(), NaturalStoneRevetmentDefaults::GetLowerLimitLoadingBll()),
            GetValue(constructionProperties.GetLowerLimitLoadingCll(), NaturalStoneRevetmentDefaults::GetLowerLimitLoadingCll()));

        auto distanceMaximumWaveElevation = make_unique<
            NaturalStoneRevetmentDistanceMaximumWaveElevation>(
            GetValue(constructionProperties.GetDistanceMaximumWaveElevationAsmax(),
                     NaturalStoneRevetmentDefaults::GetDistanceMaximumWaveElevationAsmax()),
            GetValue(constructionProperties.GetDistanceMaximumWaveElevationBsmax(),
                     NaturalStoneRevetmentDefaults::GetDistanceMaximumWaveElevationBsmax()));

        auto normativeWidthOfWaveImpact = make_unique<
            NaturalStoneRevetmentNormativeWidthOfWaveImpact>(
            GetValue(constructionProperties.GetNormativeWidthOfWaveImpactAwi(), NaturalStoneRevetmentDefaults::GetNormativeWidthOfWaveImpactAwi()),
            GetValue(constructionProperties.GetNormativeWidthOfWaveImpactBwi(), NaturalStoneRevetmentDefaults::GetNormativeWidthOfWaveImpactBwi()));

        auto waveAngleImpact = make_unique<NaturalStoneRevetmentWaveAngleImpact>(
            GetValue(constructionProperties.GetWaveAngleImpactBetamax(), NaturalStoneRevetmentDefaults::GetWaveAngleImpactBetamax()));

        _locationDependentInputItems.push_back(
            make_unique<NaturalStoneRevetmentLocationDependentInput>(
                constructionProperties.GetX(),
                GetValue(constructionProperties.GetInitialDamage(), RevetmentDefaults::GetInitialDamage()),
                GetValue(constructionProperties.GetFailureNumber(), RevetmentDefaults::GetFailureNumber()),
                constructionProperties.GetRelativeDensity(),
                constructionProperties.GetThicknessTopLayer(),
                move(hydraulicLoads),
                move(slope),
                move(upperLimitLoading),
                move(lowerLimitLoading),
                move(distanceMaximumWaveElevation),
                move(normativeWidthOfWaveImpact),
                move(waveAngleImpact)));
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
