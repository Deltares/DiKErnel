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
#include "AsphaltRevetmentWaveImpactLocationDependentInput.h"
#include "CalculationInput.h"
#include "DefaultsFactoryException.h"
#include "GrassRevetmentWaveImpactDefaults.h"
#include "GrassRevetmentWaveImpactDefaultsFactory.h"
#include "GrassRevetmentWaveImpactLocationDependentInput.h"
#include "GrassRevetmentWaveRunupDefaultsFactory.h"
#include "GrassRevetmentWaveRunupRayleighDefaults.h"
#include "GrassRevetmentWaveRunupRayleighLocationDependentInput.h"
#include "IAsphaltRevetmentWaveImpactTopLayerDefaults.h"
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
        unique_ptr<IAsphaltRevetmentWaveImpactTopLayerDefaults> topLayerDefaults;

        try
        {
            topLayerDefaults = AsphaltRevetmentWaveImpactDefaultsFactory::CreateTopLayerDefaults(
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
            GetValue(constructionProperties.GetFatigueAlpha(), topLayerDefaults->GetFatigueAlpha()),
            GetValue(constructionProperties.GetFatigueBeta(), topLayerDefaults->GetFatigueBeta()));

        _locationDependentInputItems.push_back(
            make_unique<AsphaltRevetmentWaveImpactLocationDependentInput>(
                constructionProperties.GetX(),
                GetValue(constructionProperties.GetInitialDamage(), RevetmentDefaults::GetInitialDamage()),
                GetValue(constructionProperties.GetFailureNumber(), RevetmentDefaults::GetFailureNumber()),
                constructionProperties.GetOuterSlope(),
                constructionProperties.GetFailureTension(),
                GetValue(constructionProperties.GetDensityOfWater(), AsphaltRevetmentWaveImpactDefaults::GetDensityOfWater()),
                constructionProperties.GetSoilElasticity(),
                move(upperLayer),
                move(subLayer),
                GetValue(constructionProperties.GetAverageNumberOfWavesCtm(), AsphaltRevetmentWaveImpactDefaults::GetAverageNumberOfWavesCtm()),
                move(fatigue),
                GetValue(constructionProperties.GetImpactNumberC(), AsphaltRevetmentWaveImpactDefaults::GetImpactNumberC()),
                GetValue(constructionProperties.GetStiffnessRelationNu(), topLayerDefaults->GetStiffnessRelationNu()),
                GetValue(constructionProperties.GetWidthFactors(), AsphaltRevetmentWaveImpactDefaults::GetWidthFactors()),
                GetValue(constructionProperties.GetDepthFactors(), AsphaltRevetmentWaveImpactDefaults::GetDepthFactors()),
                GetValue(constructionProperties.GetImpactFactors(), AsphaltRevetmentWaveImpactDefaults::GetImpactFactors())));
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
            GetValue(constructionProperties.GetRepresentativeWaveRunup2PAru(), topLayerDefaults->GetRepresentativeWaveRunup2PAru()),
            GetValue(constructionProperties.GetRepresentativeWaveRunup2PBru(), topLayerDefaults->GetRepresentativeWaveRunup2PBru()),
            GetValue(constructionProperties.GetRepresentativeWaveRunup2PCru(), topLayerDefaults->GetRepresentativeWaveRunup2PCru()),
            GetValue(constructionProperties.GetRepresentativeWaveRunup2PGammab(), topLayerDefaults->GetRepresentativeWaveRunup2PGammab()),
            GetValue(constructionProperties.GetRepresentativeWaveRunup2PGammaf(), topLayerDefaults->GetRepresentativeWaveRunup2PGammaf()));

        auto waveAngleImpact = make_unique<GrassRevetmentWaveRunupWaveAngleImpact>(
            GetValue(constructionProperties.GetWaveAngleImpactAbeta(), topLayerDefaults->GetWaveAngleImpactAbeta()),
            GetValue(constructionProperties.GetWaveAngleImpactBetamax(), topLayerDefaults->GetWaveAngleImpactBetamax()));

        _locationDependentInputItems.push_back(
            make_unique<GrassRevetmentWaveRunupRayleighLocationDependentInput>(
                constructionProperties.GetX(),
                GetValue(constructionProperties.GetInitialDamage(), RevetmentDefaults::GetInitialDamage()),
                GetValue(constructionProperties.GetFailureNumber(), RevetmentDefaults::GetFailureNumber()),
                constructionProperties.GetOuterSlope(),
                GetValue(constructionProperties.GetCriticalCumulativeOverload(), topLayerDefaults->GetCriticalCumulativeOverload()),
                GetValue(constructionProperties.GetCriticalFrontVelocity(), topLayerDefaults->GetCriticalFrontVelocity()),
                GetValue(constructionProperties.GetIncreasedLoadTransitionAlphaM(), topLayerDefaults->GetIncreasedLoadTransitionAlphaM()),
                GetValue(constructionProperties.GetReducedStrengthTransitionAlphaS(), topLayerDefaults->GetReducedStrengthTransitionAlphaS()),
                GetValue(constructionProperties.GetAverageNumberOfWavesCtm(), topLayerDefaults->GetAverageNumberOfWavesCtm()),
                move(representative2P),
                move(waveAngleImpact),
                GetValue(constructionProperties.GetFixedNumberOfWaves(), GrassRevetmentWaveRunupRayleighDefaults::GetFixedNumberOfWaves()),
                GetValue(constructionProperties.GetFrontVelocityCu(), GrassRevetmentWaveRunupRayleighDefaults::GetFrontVelocityCu())));
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
