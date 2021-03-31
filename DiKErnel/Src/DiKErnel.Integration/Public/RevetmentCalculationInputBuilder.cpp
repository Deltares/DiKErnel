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
        unique_ptr<NaturalStoneRevetmentHydraulicLoads> hydraulicLoads;
        unique_ptr<NaturalStoneRevetmentUpperLimitLoading> upperLimitLoading;
        unique_ptr<NaturalStoneRevetmentLowerLimitLoading> lowerLimitLoading;
        unique_ptr<NaturalStoneRevetmentDistanceMaximumWaveElevation> distanceMaximumWaveElevation;
        unique_ptr<NaturalStoneRevetmentNormativeWidthOfWaveImpact> normativeWidthOfWaveImpact;
        unique_ptr<NaturalStoneRevetmentWaveAngleImpact> waveAngleImpact;

        if (constructionProperties.GetTopLayerType() == NaturalStoneRevetmentLocationConstructionProperties::TopLayerType::NordicStone)
        {
            hydraulicLoads = make_unique<NaturalStoneRevetmentHydraulicLoads>(
                GetValue(constructionProperties.GetHydraulicLoadAp(), NordicStoneRevetmentDefaults::HYDRAULIC_LOAD_AP),
                GetValue(constructionProperties.GetHydraulicLoadBp(), NordicStoneRevetmentDefaults::HYDRAULIC_LOAD_BP),
                GetValue(constructionProperties.GetHydraulicLoadCp(), NordicStoneRevetmentDefaults::HYDRAULIC_LOAD_CP),
                GetValue(constructionProperties.GetHydraulicLoadNp(), NordicStoneRevetmentDefaults::HYDRAULIC_LOAD_NP),
                GetValue(constructionProperties.GetHydraulicLoadAs(), NordicStoneRevetmentDefaults::HYDRAULIC_LOAD_AS),
                GetValue(constructionProperties.GetHydraulicLoadBs(), NordicStoneRevetmentDefaults::HYDRAULIC_LOAD_BS),
                GetValue(constructionProperties.GetHydraulicLoadCs(), NordicStoneRevetmentDefaults::HYDRAULIC_LOAD_CS),
                GetValue(constructionProperties.GetHydraulicLoadNs(), NordicStoneRevetmentDefaults::HYDRAULIC_LOAD_NS),
                GetValue(constructionProperties.GetHydraulicLoadXib(), NordicStoneRevetmentDefaults::HYDRAULIC_LOAD_XIB));

            upperLimitLoading = make_unique<NaturalStoneRevetmentUpperLimitLoading>(
                GetValue(constructionProperties.GetUpperLimitLoadingAul(), NordicStoneRevetmentDefaults::UPPER_LIMIT_LOADING_AUL),
                GetValue(constructionProperties.GetUpperLimitLoadingBul(), NordicStoneRevetmentDefaults::UPPER_LIMIT_LOADING_BUL),
                GetValue(constructionProperties.GetUpperLimitLoadingCul(), NordicStoneRevetmentDefaults::UPPER_LIMIT_LOADING_CUL));

            lowerLimitLoading = make_unique<NaturalStoneRevetmentLowerLimitLoading>(
                GetValue(constructionProperties.GetLowerLimitLoadingAll(), NordicStoneRevetmentDefaults::LOWER_LIMIT_LOADING_ALL),
                GetValue(constructionProperties.GetLowerLimitLoadingBll(), NordicStoneRevetmentDefaults::LOWER_LIMIT_LOADING_BLL),
                GetValue(constructionProperties.GetLowerLimitLoadingCll(), NordicStoneRevetmentDefaults::LOWER_LIMIT_LOADING_CLL));

            distanceMaximumWaveElevation = make_unique<NaturalStoneRevetmentDistanceMaximumWaveElevation>(
                GetValue(constructionProperties.GetDistanceMaximumWaveElevationAsmax(),
                         NordicStoneRevetmentDefaults::DISTANCE_MAXIMUM_WAVE_ELEVATION_ASMAX),
                GetValue(constructionProperties.GetDistanceMaximumWaveElevationBsmax(),
                         NordicStoneRevetmentDefaults::DISTANCE_MAXIMUM_WAVE_ELEVATION_BSMAX));

            normativeWidthOfWaveImpact = make_unique<NaturalStoneRevetmentNormativeWidthOfWaveImpact>(
                GetValue(constructionProperties.GetNormativeWidthOfWaveImpactAwi(),
                         NordicStoneRevetmentDefaults::NORMATIVE_WIDTH_OF_WAVE_IMPACT_AWI),
                GetValue(constructionProperties.GetNormativeWidthOfWaveImpactBwi(),
                         NordicStoneRevetmentDefaults::NORMATIVE_WIDTH_OF_WAVE_IMPACT_BWI));

            waveAngleImpact = make_unique<NaturalStoneRevetmentWaveAngleImpact>(
                GetValue(constructionProperties.GetWaveAngleImpactBetamax(), NordicStoneRevetmentDefaults::WAVE_ANGLE_IMPACT_BETAMAX));
        }

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
        unique_ptr<GrassRevetmentWaveImpactTimeLine> failureTime;

        double minimumWaveHeightTemax;
        double maximumWaveHeightTemin;
        double upperLimitLoadingAul;
        double lowerLimitLoadingAll;

        const auto topLayerType = constructionProperties.GetTopLayerType();
        if (topLayerType == GrassRevetmentWaveImpactLocationConstructionProperties::TopLayerType::ClosedSod)
        {
            waveAngleImpact = make_unique<GrassRevetmentWaveImpactWaveAngleImpact>(
                GetValue(constructionProperties.GetWaveAngleImpactNwa(), GrassRevetmentWaveImpactClosedSodDefaults::WAVE_ANGLE_IMPACT_NWA),
                GetValue(constructionProperties.GetWaveAngleImpactQwa(), GrassRevetmentWaveImpactClosedSodDefaults::WAVE_ANGLE_IMPACT_QWA),
                GetValue(constructionProperties.GetWaveAngleImpactRwa(), GrassRevetmentWaveImpactClosedSodDefaults::WAVE_ANGLE_IMPACT_RWA));

            failureTime = make_unique<GrassRevetmentWaveImpactTimeLine>(
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

        if (topLayerType == GrassRevetmentWaveImpactLocationConstructionProperties::TopLayerType::OpenSod)
        {
            waveAngleImpact = make_unique<GrassRevetmentWaveImpactWaveAngleImpact>(
                GetValue(constructionProperties.GetWaveAngleImpactNwa(), GrassRevetmentWaveImpactOpenSodDefaults::WAVE_ANGLE_IMPACT_NWA),
                GetValue(constructionProperties.GetWaveAngleImpactQwa(), GrassRevetmentWaveImpactOpenSodDefaults::WAVE_ANGLE_IMPACT_QWA),
                GetValue(constructionProperties.GetWaveAngleImpactRwa(), GrassRevetmentWaveImpactOpenSodDefaults::WAVE_ANGLE_IMPACT_RWA));

            failureTime = make_unique<GrassRevetmentWaveImpactTimeLine>(
                GetValue(constructionProperties.GetTimeLineAgwi(), GrassRevetmentWaveImpactOpenSodDefaults::FAILURE_TIME_AGWI),
                GetValue(constructionProperties.GetTimeLineBgwi(), GrassRevetmentWaveImpactOpenSodDefaults::FAILURE_TIME_BGWI),
                GetValue(constructionProperties.GetTimeLineCgwi(), GrassRevetmentWaveImpactOpenSodDefaults::FAILURE_TIME_CGWI));

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
                constructionProperties.GetTanA(),
                constructionProperties.GetPositionZ(),
                move(waveAngleImpact),
                minimumWaveHeightTemax,
                maximumWaveHeightTemin,
                move(failureTime),
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
