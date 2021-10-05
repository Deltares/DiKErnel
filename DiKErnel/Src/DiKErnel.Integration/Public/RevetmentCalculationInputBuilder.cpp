// Copyright (C) Stichting Deltares 2020. All rights reserved.
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
#include "DefaultsFactoryException.h"
#include "GrassRevetmentWaveImpactDefaultsFactory.h"
#include "GrassRevetmentWaveImpactLocationDependentInput.h"
#include "GrassRevetmentWaveRunupDefaultsFactory.h"
#include "GrassRevetmentWaveRunupRayleighLocationDependentInput.h"
#include "IAsphaltRevetmentWaveImpactDefaults.h"
#include "IGrassRevetmentWaveRunupRayleighDefaults.h"
#include "InvalidCalculationDataException.h"
#include "NaturalStoneRevetmentDefaultsFactory.h"
#include "NaturalStoneRevetmentLocationConstructionProperties.h"
#include "NaturalStoneRevetmentLocationDependentInput.h"
#include "NordicStoneRevetmentDefaults.h"
#include "ProfileData.h"
#include "RevetmentCalculationInputBuilderException.h"
#include "RevetmentDefaults.h"

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
        try
        {
            _timeDependentInputItems.push_back(
                make_unique<TimeDependentInput>(beginTime, endTime, waterLevel, waveHeightHm0, wavePeriodTm10, waveAngle));
        }
        catch (const InvalidCalculationDataException&)
        {
            ThrowWithMessage();
        }
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

        auto elasticModulusUpperLayer = constructionProperties.GetElasticModulusUpperLayer();
        auto upperLayer = make_unique<AsphaltRevetmentWaveImpactLayer>(
            constructionProperties.GetThicknessUpperLayer(),
            elasticModulusUpperLayer);

        auto subLayer = make_unique<AsphaltRevetmentWaveImpactLayer>(
            GetValue(constructionProperties.GetThicknessSubLayer(), defaults->GetSubLayerThickness()),
            GetValue(constructionProperties.GetElasticModulusSubLayer(), elasticModulusUpperLayer));

        auto fatigue = make_unique<AsphaltRevetmentWaveImpactFatigue>(
            GetValue(constructionProperties.GetFatigueAlpha(), defaults->GetFatigueAlpha()),
            GetValue(constructionProperties.GetFatigueBeta(), defaults->GetFatigueBeta()));

        _locationDependentInputItems.push_back(
            make_unique<AsphaltRevetmentWaveImpactLocationDependentInput>(
                constructionProperties.GetName(),
                constructionProperties.GetX(),
                GetValue(constructionProperties.GetInitialDamage(), RevetmentDefaults::INITIAL_DAMAGE),
                GetValue(constructionProperties.GetFailureNumber(), RevetmentDefaults::FAILURE_NUMBER),
                constructionProperties.GetTanA(),
                constructionProperties.GetPositionZ(),
                constructionProperties.GetFailureTension(),
                constructionProperties.GetDensityOfWater(),
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
                constructionProperties.GetName(),
                constructionProperties.GetX(),
                GetValue(constructionProperties.GetInitialDamage(), RevetmentDefaults::INITIAL_DAMAGE),
                GetValue(constructionProperties.GetFailureNumber(), RevetmentDefaults::FAILURE_NUMBER),
                constructionProperties.GetPositionZ(),
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
                constructionProperties.GetName(),
                constructionProperties.GetX(),
                GetValue(constructionProperties.GetInitialDamage(), RevetmentDefaults::INITIAL_DAMAGE),
                GetValue(constructionProperties.GetFailureNumber(), RevetmentDefaults::FAILURE_NUMBER),
                constructionProperties.GetTanA(),
                constructionProperties.GetPositionZ(),
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
        unique_ptr<INaturalStoneRevetmentDefaults> defaults;

        try
        {
            defaults = NaturalStoneRevetmentDefaultsFactory::Create(constructionProperties.GetTopLayerType());
        }
        catch (const DefaultsFactoryException&)
        {
            ThrowWithMessage();
        }

        auto hydraulicLoads = make_unique<NaturalStoneRevetmentHydraulicLoads>(
            GetValue(constructionProperties.GetHydraulicLoadAp(), defaults->GetHydraulicLoadAp()),
            GetValue(constructionProperties.GetHydraulicLoadBp(), defaults->GetHydraulicLoadBp()),
            GetValue(constructionProperties.GetHydraulicLoadCp(), defaults->GetHydraulicLoadCp()),
            GetValue(constructionProperties.GetHydraulicLoadNp(), defaults->GetHydraulicLoadNp()),
            GetValue(constructionProperties.GetHydraulicLoadAs(), defaults->GetHydraulicLoadAs()),
            GetValue(constructionProperties.GetHydraulicLoadBs(), defaults->GetHydraulicLoadBs()),
            GetValue(constructionProperties.GetHydraulicLoadCs(), defaults->GetHydraulicLoadCs()),
            GetValue(constructionProperties.GetHydraulicLoadNs(), defaults->GetHydraulicLoadNs()),
            GetValue(constructionProperties.GetHydraulicLoadXib(), defaults->GetHydraulicLoadXib()));

        auto upperLimitLoading = make_unique<NaturalStoneRevetmentUpperLimitLoading>(
            GetValue(constructionProperties.GetUpperLimitLoadingAul(), defaults->GetUpperLimitLoadingAul()),
            GetValue(constructionProperties.GetUpperLimitLoadingBul(), defaults->GetUpperLimitLoadingBul()),
            GetValue(constructionProperties.GetUpperLimitLoadingCul(), defaults->GetUpperLimitLoadingCul()));

        auto lowerLimitLoading = make_unique<NaturalStoneRevetmentLowerLimitLoading>(
            GetValue(constructionProperties.GetLowerLimitLoadingAll(), defaults->GetLowerLimitLoadingAll()),
            GetValue(constructionProperties.GetLowerLimitLoadingBll(), defaults->GetLowerLimitLoadingBll()),
            GetValue(constructionProperties.GetLowerLimitLoadingCll(), defaults->GetLowerLimitLoadingCll()));

        auto distanceMaximumWaveElevation = make_unique<
            NaturalStoneRevetmentDistanceMaximumWaveElevation>(
            GetValue(constructionProperties.GetDistanceMaximumWaveElevationAsmax(), defaults->GetDistanceMaximumWaveElevationAsmax()),
            GetValue(constructionProperties.GetDistanceMaximumWaveElevationBsmax(), defaults->GetDistanceMaximumWaveElevationBsmax()));

        auto normativeWidthOfWaveImpact = make_unique<
            NaturalStoneRevetmentNormativeWidthOfWaveImpact>(
            GetValue(constructionProperties.GetNormativeWidthOfWaveImpactAwi(), defaults->GetNormativeWidthOfWaveImpactAwi()),
            GetValue(constructionProperties.GetNormativeWidthOfWaveImpactBwi(), defaults->GetNormativeWidthOfWaveImpactBwi()));

        auto waveAngleImpact = make_unique<NaturalStoneRevetmentWaveAngleImpact>(
            GetValue(constructionProperties.GetWaveAngleImpactBetamax(), defaults->GetWaveAngleImpactBetamax()));

        _locationDependentInputItems.push_back(
            make_unique<NaturalStoneRevetmentLocationDependentInput>(
                constructionProperties.GetName(),
                constructionProperties.GetX(),
                GetValue(constructionProperties.GetInitialDamage(), RevetmentDefaults::INITIAL_DAMAGE),
                GetValue(constructionProperties.GetFailureNumber(), RevetmentDefaults::FAILURE_NUMBER),
                constructionProperties.GetTanA(),
                constructionProperties.GetPositionZ(),
                constructionProperties.GetRelativeDensity(),
                constructionProperties.GetThicknessTopLayer(),
                move(hydraulicLoads),
                move(upperLimitLoading),
                move(lowerLimitLoading),
                move(distanceMaximumWaveElevation),
                move(normativeWidthOfWaveImpact),
                move(waveAngleImpact)));
    }

    unique_ptr<ICalculationInput> RevetmentCalculationInputBuilder::Build()
    {
        try
        {
            return make_unique<CalculationInput>(
                make_unique<ProfileData>(move(_profilePoints), move(_characteristicPoints)),
                move(_locationDependentInputItems), move(_timeDependentInputItems));
        }
        catch (const InvalidCalculationDataException&)
        {
            ThrowWithMessage();
        }
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
