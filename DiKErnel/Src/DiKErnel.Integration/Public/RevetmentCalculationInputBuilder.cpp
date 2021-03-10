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

#include "Defaults.h"
#include "InvalidCalculationDataException.h"
#include "NaturalStoneRevetmentDefaults.h"
#include "NaturalStoneRevetmentLocationConstructionProperties.h"
#include "NaturalStoneRevetmentLocationDependentData.h"
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
            _timeSteps.push_back(make_unique<TimeDependentData>(beginTime, endTime, waterLevel, waveHeightHm0, wavePeriodTm10, waveAngle));
        }
        catch (const InvalidCalculationDataException&)
        {
            ThrowWithMessage();
        }
    }

    void RevetmentCalculationInputBuilder::AddNaturalStoneLocation(
        const NaturalStoneRevetmentLocationConstructionProperties& constructionProperties)
    {
        auto hydraulicLoads = make_unique<NaturalStoneRevetmentHydraulicLoads>(
            GetValue(constructionProperties.GetPlungingCoefficientA(), NaturalStoneRevetmentDefaults::PLUNGING_COEFFICIENT_A),
            GetValue(constructionProperties.GetPlungingCoefficientB(), NaturalStoneRevetmentDefaults::PLUNGING_COEFFICIENT_B),
            GetValue(constructionProperties.GetPlungingCoefficientC(), NaturalStoneRevetmentDefaults::PLUNGING_COEFFICIENT_C),
            GetValue(constructionProperties.GetPlungingCoefficientN(), NaturalStoneRevetmentDefaults::PLUNGING_COEFFICIENT_N),
            GetValue(constructionProperties.GetSurgingCoefficientA(), NaturalStoneRevetmentDefaults::SURGING_COEFFICIENT_A),
            GetValue(constructionProperties.GetSurgingCoefficientB(), NaturalStoneRevetmentDefaults::SURGING_COEFFICIENT_B),
            GetValue(constructionProperties.GetSurgingCoefficientC(), NaturalStoneRevetmentDefaults::SURGING_COEFFICIENT_C),
            GetValue(constructionProperties.GetSurgingCoefficientN(), NaturalStoneRevetmentDefaults::SURGING_COEFFICIENT_N),
            GetValue(constructionProperties.GetSimilarityParameterThreshold(), NaturalStoneRevetmentDefaults::SIMILARITY_PARAMETER_THRESHOLD));

        auto upperLimitLoading = make_unique<NaturalStoneRevetmentUpperLimitLoading>(
            GetValue(constructionProperties.GetUpperLimitLoadingAul(), Defaults::UPPER_LIMIT_LOADING_OF_NORDIC_STONE_AUL),
            GetValue(constructionProperties.GetUpperLimitLoadingBul(), Defaults::UPPER_LIMIT_LOADING_OF_NORDIC_STONE_BUL),
            GetValue(constructionProperties.GetUpperLimitLoadingCul(), Defaults::UPPER_LIMIT_LOADING_OF_NORDIC_STONE_CUL));

        auto lowerLimitLoading = make_unique<NaturalStoneRevetmentLowerLimitLoading>(
            GetValue(constructionProperties.GetLowerLimitLoadingAll(), Defaults::LOWER_LIMIT_LOADING_OF_NORDIC_STONE_ALL),
            GetValue(constructionProperties.GetLowerLimitLoadingBll(), Defaults::LOWER_LIMIT_LOADING_OF_NORDIC_STONE_BLL),
            GetValue(constructionProperties.GetLowerLimitLoadingCll(), Defaults::LOWER_LIMIT_LOADING_OF_NORDIC_STONE_CLL));

        auto distanceMaximumWaveElevation = make_unique<NaturalStoneRevetmentDistanceMaximumWaveElevation>(
            GetValue(constructionProperties.GetDistanceMaximumWaveElevationAsmax(), Defaults::DISTANCE_MAXIMUM_WAVE_ELEVATION_NORDIC_STONE_ASMAX),
            GetValue(constructionProperties.GetDistanceMaximumWaveElevationBsmax(), Defaults::DISTANCE_MAXIMUM_WAVE_ELEVATION_NORDIC_STONE_BSMAX));

        auto normativeWidthOfWaveImpact = make_unique<NaturalStoneRevetmentNormativeWidthOfWaveImpact>(
            GetValue(constructionProperties.GetNormativeWidthOfWaveImpactAwi(), Defaults::NORMATIVE_WIDTH_OF_WAVE_IMPACT_AWI),
            GetValue(constructionProperties.GetNormativeWidthOfWaveImpactBwi(), Defaults::NORMATIVE_WIDTH_OF_WAVE_IMPACT_BWI));

        _locations.push_back(make_unique<NaturalStoneRevetmentLocationDependentData>(
            constructionProperties.GetInitialDamage(), constructionProperties.GetSlopeAngle(), constructionProperties.GetRelativeDensity(),
            constructionProperties.GetThicknessTopLayer(), move(hydraulicLoads), move(upperLimitLoading), move(lowerLimitLoading),
            move(distanceMaximumWaveElevation), move(normativeWidthOfWaveImpact)));
    }

    unique_ptr<ICalculationInput> RevetmentCalculationInputBuilder::Build()
    {
        try
        {
            return make_unique<CalculationInput>(move(_locations), move(_timeSteps), _maximumWaveAngle);
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
        throw_with_nested(RevetmentCalculationInputBuilderException("Could not create TimeDependentData."));
    }
}
