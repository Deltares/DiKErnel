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

#include "GrassRevetmentWaveImpactClosedSodDefaults.h"
#include "GrassRevetmentWaveImpactLocationDependentInput.h"
#include "GrassRevetmentWaveImpactOpenSodDefaults.h"
#include "InvalidCalculationDataException.h"
#include "NaturalStoneRevetmentLocationConstructionProperties.h"
#include "NaturalStoneRevetmentLocationDependentInput.h"
#include "NordicStoneRevetmentDefaults.h"
#include "RevetmentCalculationInputBuilderException.h"
#include "RevetmentDefaults.h"

namespace DiKErnel::Integration
{
    using namespace Core;
    using namespace DomainLibrary;
    using namespace std;

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

    void RevetmentCalculationInputBuilder::AddNaturalStoneLocation(
        const NaturalStoneRevetmentLocationConstructionProperties& constructionProperties)
    {
        unique_ptr<INaturalStoneRevetmentDefaults> defaults;

        if (constructionProperties.GetTopLayerType() == NaturalStoneRevetmentTopLayerType::NordicStone)
        {
            defaults = make_unique<NordicStoneRevetmentDefaults>();
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

    void RevetmentCalculationInputBuilder::AddGrassWaveImpactLocation(
        const GrassRevetmentWaveImpactLocationConstructionProperties& constructionProperties)
    {
        unique_ptr<GrassRevetmentWaveImpactWaveAngleImpact> waveAngleImpact;
        unique_ptr<GrassRevetmentWaveImpactTimeLine> timeLine;

        double minimumWaveHeightTemax;
        double maximumWaveHeightTemin;
        double upperLimitLoadingAul;
        double lowerLimitLoadingAll;

        const auto topLayerType = constructionProperties.GetTopLayerType();
        if (topLayerType == GrassRevetmentTopLayerType::ClosedSod)
        {
            waveAngleImpact = make_unique<GrassRevetmentWaveImpactWaveAngleImpact>(
                GetValue(constructionProperties.GetWaveAngleImpactNwa(), GrassRevetmentWaveImpactClosedSodDefaults::WAVE_ANGLE_IMPACT_NWA),
                GetValue(constructionProperties.GetWaveAngleImpactQwa(), GrassRevetmentWaveImpactClosedSodDefaults::WAVE_ANGLE_IMPACT_QWA),
                GetValue(constructionProperties.GetWaveAngleImpactRwa(), GrassRevetmentWaveImpactClosedSodDefaults::WAVE_ANGLE_IMPACT_RWA));

            timeLine = make_unique<GrassRevetmentWaveImpactTimeLine>(
                GetValue(constructionProperties.GetTimeLineAgwi(), GrassRevetmentWaveImpactClosedSodDefaults::TIME_LINE_AGWI),
                GetValue(constructionProperties.GetTimeLineBgwi(), GrassRevetmentWaveImpactClosedSodDefaults::TIME_LINE_BGWI),
                GetValue(constructionProperties.GetTimeLineCgwi(), GrassRevetmentWaveImpactClosedSodDefaults::TIME_LINE_CGWI));

            minimumWaveHeightTemax = GetValue(constructionProperties.GetMinimumWaveHeightTemax(),
                                              GrassRevetmentWaveImpactClosedSodDefaults::MINIMUM_WAVE_HEIGHT_TEMAX);
            maximumWaveHeightTemin = GetValue(constructionProperties.GetMaximumWaveHeightTemin(),
                                              GrassRevetmentWaveImpactClosedSodDefaults::MAXIMUM_WAVE_HEIGHT_TEMIN);
            upperLimitLoadingAul = GetValue(constructionProperties.GetUpperLimitLoadingAul(),
                                            GrassRevetmentWaveImpactClosedSodDefaults::UPPER_LIMIT_LOADING_AUL);
            lowerLimitLoadingAll = GetValue(constructionProperties.GetLowerLimitLoadingAll(),
                                            GrassRevetmentWaveImpactClosedSodDefaults::LOWER_LIMIT_LOADING_ALL);
        }

        if (topLayerType == GrassRevetmentTopLayerType::OpenSod)
        {
            waveAngleImpact = make_unique<GrassRevetmentWaveImpactWaveAngleImpact>(
                GetValue(constructionProperties.GetWaveAngleImpactNwa(), GrassRevetmentWaveImpactOpenSodDefaults::WAVE_ANGLE_IMPACT_NWA),
                GetValue(constructionProperties.GetWaveAngleImpactQwa(), GrassRevetmentWaveImpactOpenSodDefaults::WAVE_ANGLE_IMPACT_QWA),
                GetValue(constructionProperties.GetWaveAngleImpactRwa(), GrassRevetmentWaveImpactOpenSodDefaults::WAVE_ANGLE_IMPACT_RWA));

            timeLine = make_unique<GrassRevetmentWaveImpactTimeLine>(
                GetValue(constructionProperties.GetTimeLineAgwi(), GrassRevetmentWaveImpactOpenSodDefaults::TIME_LINE_AGWI),
                GetValue(constructionProperties.GetTimeLineBgwi(), GrassRevetmentWaveImpactOpenSodDefaults::TIME_LINE_BGWI),
                GetValue(constructionProperties.GetTimeLineCgwi(), GrassRevetmentWaveImpactOpenSodDefaults::TIME_LINE_CGWI));

            minimumWaveHeightTemax = GetValue(constructionProperties.GetMinimumWaveHeightTemax(),
                                              GrassRevetmentWaveImpactOpenSodDefaults::MINIMUM_WAVE_HEIGHT_TEMAX);
            maximumWaveHeightTemin = GetValue(constructionProperties.GetMaximumWaveHeightTemin(),
                                              GrassRevetmentWaveImpactOpenSodDefaults::MAXIMUM_WAVE_HEIGHT_TEMIN);
            upperLimitLoadingAul = GetValue(constructionProperties.GetUpperLimitLoadingAul(),
                                            GrassRevetmentWaveImpactOpenSodDefaults::UPPER_LIMIT_LOADING_AUL);
            lowerLimitLoadingAll = GetValue(constructionProperties.GetLowerLimitLoadingAll(),
                                            GrassRevetmentWaveImpactOpenSodDefaults::LOWER_LIMIT_LOADING_ALL);
        }

        _locationDependentInputItems.push_back(
            make_unique<GrassRevetmentWaveImpactLocationDependentInput>(
                constructionProperties.GetName(),
                GetValue(constructionProperties.GetInitialDamage(), RevetmentDefaults::INITIAL_DAMAGE),
                GetValue(constructionProperties.GetFailureNumber(), RevetmentDefaults::FAILURE_NUMBER),
                constructionProperties.GetPositionZ(),
                move(waveAngleImpact),
                minimumWaveHeightTemax,
                maximumWaveHeightTemin,
                move(timeLine),
                upperLimitLoadingAul,
                lowerLimitLoadingAll));
    }

    unique_ptr<ICalculationInput> RevetmentCalculationInputBuilder::Build()
    {
        try
        {
            return make_unique<CalculationInput>(move(_locationDependentInputItems), move(_timeDependentInputItems));
        }
        catch (const InvalidCalculationDataException&)
        {
            ThrowWithMessage();
        }
    }

    double RevetmentCalculationInputBuilder::GetValue(
        const double* doublePtr,
        const double defaultValue)
    {
        return doublePtr != nullptr
                   ? *doublePtr
                   : defaultValue;
    }

    void RevetmentCalculationInputBuilder::ThrowWithMessage()
    {
        throw_with_nested(RevetmentCalculationInputBuilderException("Could not create TimeDependentInput."));
    }
}
