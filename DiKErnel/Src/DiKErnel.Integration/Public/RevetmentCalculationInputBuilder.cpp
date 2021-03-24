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
#include "NordicStoneRevetmentDefaults.h"
#include "NaturalStoneRevetmentLocationConstructionProperties.h"
#include "NaturalStoneRevetmentLocationDependentInput.h"
#include "RevetmentCalculationInputBuilderException.h"

namespace DiKErnel::Integration
{
    using namespace Core;
    using namespace DomainLibrary;
    using namespace std;

    RevetmentCalculationInputBuilder::RevetmentCalculationInputBuilder(
        const double maximumWaveAngle)
        : _maximumWaveAngle(maximumWaveAngle) { }

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

        if (constructionProperties.GetTopLayerType() == NaturalStoneRevetmentLocationConstructionProperties::TopLayerType::NordicStone)
        {
            hydraulicLoads = make_unique<NaturalStoneRevetmentHydraulicLoads>(
                GetValue(constructionProperties.GetPlungingCoefficientA(), NaturalStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NORDIC_STONE_AP),
                GetValue(constructionProperties.GetPlungingCoefficientB(), NaturalStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NORDIC_STONE_BP),
                GetValue(constructionProperties.GetPlungingCoefficientC(), NaturalStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NORDIC_STONE_CP),
                GetValue(constructionProperties.GetPlungingCoefficientN(), NaturalStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NORDIC_STONE_NP),
                GetValue(constructionProperties.GetSurgingCoefficientA(), NaturalStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NORDIC_STONE_AS),
                GetValue(constructionProperties.GetSurgingCoefficientB(), NaturalStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NORDIC_STONE_BS),
                GetValue(constructionProperties.GetSurgingCoefficientC(), NaturalStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NORDIC_STONE_CS),
                GetValue(constructionProperties.GetSurgingCoefficientN(), NaturalStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NORDIC_STONE_NS),
                GetValue(constructionProperties.GetSimilarityParameterThreshold(), NaturalStoneRevetmentDefaults::HYDRAULIC_LOAD_ON_NORDIC_STONE_XIB));

            upperLimitLoading = make_unique<NaturalStoneRevetmentUpperLimitLoading>(
                GetValue(constructionProperties.GetUpperLimitLoadingAul(), NaturalStoneRevetmentDefaults::UPPER_LIMIT_LOADING_OF_NORDIC_STONE_AUL),
                GetValue(constructionProperties.GetUpperLimitLoadingBul(), NaturalStoneRevetmentDefaults::UPPER_LIMIT_LOADING_OF_NORDIC_STONE_BUL),
                GetValue(constructionProperties.GetUpperLimitLoadingCul(), NaturalStoneRevetmentDefaults::UPPER_LIMIT_LOADING_OF_NORDIC_STONE_CUL));

            lowerLimitLoading = make_unique<NaturalStoneRevetmentLowerLimitLoading>(
                GetValue(constructionProperties.GetLowerLimitLoadingAll(), NaturalStoneRevetmentDefaults::LOWER_LIMIT_LOADING_OF_NORDIC_STONE_ALL),
                GetValue(constructionProperties.GetLowerLimitLoadingBll(), NaturalStoneRevetmentDefaults::LOWER_LIMIT_LOADING_OF_NORDIC_STONE_BLL),
                GetValue(constructionProperties.GetLowerLimitLoadingCll(), NaturalStoneRevetmentDefaults::LOWER_LIMIT_LOADING_OF_NORDIC_STONE_CLL));

            distanceMaximumWaveElevation = make_unique<NaturalStoneRevetmentDistanceMaximumWaveElevation>(
                GetValue(constructionProperties.GetDistanceMaximumWaveElevationAsmax(),
                    NaturalStoneRevetmentDefaults::DISTANCE_MAXIMUM_WAVE_ELEVATION_NORDIC_STONE_ASMAX),
                GetValue(constructionProperties.GetDistanceMaximumWaveElevationBsmax(),
                    NaturalStoneRevetmentDefaults::DISTANCE_MAXIMUM_WAVE_ELEVATION_NORDIC_STONE_BSMAX));

            normativeWidthOfWaveImpact = make_unique<NaturalStoneRevetmentNormativeWidthOfWaveImpact>(
                GetValue(constructionProperties.GetNormativeWidthOfWaveImpactAwi(),
                    NaturalStoneRevetmentDefaults::NORMATIVE_WIDTH_OF_WAVE_IMPACT_NORDIC_STONE_AWI),
                GetValue(constructionProperties.GetNormativeWidthOfWaveImpactBwi(),
                    NaturalStoneRevetmentDefaults::NORMATIVE_WIDTH_OF_WAVE_IMPACT_NORDIC_STONE_BWI));
        }

        _locationDependentInputItems.push_back(
            make_unique<NaturalStoneRevetmentLocationDependentInput>(
                constructionProperties.GetInitialDamage(),
                constructionProperties.GetSlopeAngle(),
                constructionProperties.GetRelativeDensity(),
                constructionProperties.GetThicknessTopLayer(),
                move(hydraulicLoads),
                move(upperLimitLoading),
                move(lowerLimitLoading),
                move(distanceMaximumWaveElevation),
                move(normativeWidthOfWaveImpact)));
    }

    unique_ptr<ICalculationInput> RevetmentCalculationInputBuilder::Build()
    {
        try
        {
            return make_unique<CalculationInput>(move(_locationDependentInputItems), move(_timeDependentInputItems), _maximumWaveAngle);
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
