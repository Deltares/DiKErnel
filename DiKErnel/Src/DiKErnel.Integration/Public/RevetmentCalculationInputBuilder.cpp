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

#include "InvalidCalculationDataException.h"
#include "NaturalStoneRevetmentLocationConstructionProperties.h"
#include "NaturalStoneRevetmentLocationDependentInput.h"
#include "NordicStoneRevetmentDefaults.h"
#include "RevetmentCalculationInputBuilderException.h"

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
                GetValue(constructionProperties.GetHydraulicLoadAp(), NordicStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NATURAL_STONE_AP),
                GetValue(constructionProperties.GetHydraulicLoadBp(), NordicStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NATURAL_STONE_BP),
                GetValue(constructionProperties.GetHydraulicLoadCp(), NordicStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NATURAL_STONE_CP),
                GetValue(constructionProperties.GetHydraulicLoadNp(), NordicStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NATURAL_STONE_NP),
                GetValue(constructionProperties.GetHydraulicLoadAs(), NordicStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NATURAL_STONE_AS),
                GetValue(constructionProperties.GetHydraulicLoadBs(), NordicStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NATURAL_STONE_BS),
                GetValue(constructionProperties.GetHydraulicLoadCs(), NordicStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NATURAL_STONE_CS),
                GetValue(constructionProperties.GetHydraulicLoadNs(), NordicStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NATURAL_STONE_NS),
                GetValue(constructionProperties.GetHydraulicLoadXib(),
                         NordicStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NATURAL_STONE_XIB));

            upperLimitLoading = make_unique<NaturalStoneRevetmentUpperLimitLoading>(
                GetValue(constructionProperties.GetUpperLimitLoadingAul(), NordicStoneRevetmentDefaults::UPPER_LIMIT_LOADING_OF_NATURAL_STONE_AUL),
                GetValue(constructionProperties.GetUpperLimitLoadingBul(), NordicStoneRevetmentDefaults::UPPER_LIMIT_LOADING_OF_NATURAL_STONE_BUL),
                GetValue(constructionProperties.GetUpperLimitLoadingCul(), NordicStoneRevetmentDefaults::UPPER_LIMIT_LOADING_OF_NATURAL_STONE_CUL));

            lowerLimitLoading = make_unique<NaturalStoneRevetmentLowerLimitLoading>(
                GetValue(constructionProperties.GetLowerLimitLoadingAll(), NordicStoneRevetmentDefaults::LOWER_LIMIT_LOADING_OF_NATURAL_STONE_ALL),
                GetValue(constructionProperties.GetLowerLimitLoadingBll(), NordicStoneRevetmentDefaults::LOWER_LIMIT_LOADING_OF_NATURAL_STONE_BLL),
                GetValue(constructionProperties.GetLowerLimitLoadingCll(), NordicStoneRevetmentDefaults::LOWER_LIMIT_LOADING_OF_NATURAL_STONE_CLL));

            distanceMaximumWaveElevation = make_unique<NaturalStoneRevetmentDistanceMaximumWaveElevation>(
                GetValue(constructionProperties.GetDistanceMaximumWaveElevationAsmax(),
                         NordicStoneRevetmentDefaults::DISTANCE_MAXIMUM_WAVE_ELEVATION_NATURAL_STONE_ASMAX),
                GetValue(constructionProperties.GetDistanceMaximumWaveElevationBsmax(),
                         NordicStoneRevetmentDefaults::DISTANCE_MAXIMUM_WAVE_ELEVATION_NATURAL_STONE_BSMAX));

            normativeWidthOfWaveImpact = make_unique<NaturalStoneRevetmentNormativeWidthOfWaveImpact>(
                GetValue(constructionProperties.GetNormativeWidthOfWaveImpactAwi(),
                         NordicStoneRevetmentDefaults::NORMATIVE_WIDTH_OF_WAVE_IMPACT_ON_NATURAL_STONE_AWI),
                GetValue(constructionProperties.GetNormativeWidthOfWaveImpactBwi(),
                         NordicStoneRevetmentDefaults::NORMATIVE_WIDTH_OF_WAVE_IMPACT_ON_NATURAL_STONE_BWI));

            waveAngleImpact = make_unique<NaturalStoneRevetmentWaveAngleImpact>(
                GetValue(constructionProperties.GetWaveAngleImpactBetamax(),
                         NordicStoneRevetmentDefaults::WAVE_ANGLE_IMPACT_ON_NATURAL_STONE_BETAMAX));
        }

        _locationDependentInputItems.push_back(
            make_unique<NaturalStoneRevetmentLocationDependentInput>(
                constructionProperties.GetName(),
                0,
                constructionProperties.GetSlopeAngle(),
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
