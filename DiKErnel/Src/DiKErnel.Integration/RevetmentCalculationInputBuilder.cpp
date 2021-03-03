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
        : _maximumWaveAngle(maximumWaveAngle)
    {
        _timeSteps = vector<unique_ptr<TimeDependentData>>();
        _locations = vector<unique_ptr<LocationDependentData>>();
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
        const auto relativeDensity = GetValue(constructionProperties._relativeDensityPtr.get(), NaturalStoneRevetmentDefaults::RELATIVE_DENSITY);
        const auto plungingCoefficientA = GetValue(constructionProperties._plungingCoefficientAPtr.get(),
                                                   NaturalStoneRevetmentDefaults::PLUNGING_COEFFICIENT_A);
        const auto plungingCoefficientB = GetValue(constructionProperties._plungingCoefficientBPtr.get(),
                                                   NaturalStoneRevetmentDefaults::PLUNGING_COEFFICIENT_B);
        const auto plungingCoefficientC = GetValue(constructionProperties._plungingCoefficientCPtr.get(),
                                                   NaturalStoneRevetmentDefaults::PLUNGING_COEFFICIENT_C);
        const auto plungingCoefficientN = GetValue(constructionProperties._plungingCoefficientNPtr.get(),
                                                   NaturalStoneRevetmentDefaults::PLUNGING_COEFFICIENT_N);
        const auto surgingCoefficientA = GetValue(constructionProperties._surgingCoefficientAPtr.get(),
                                                  NaturalStoneRevetmentDefaults::SURGING_COEFFICIENT_A);
        const auto surgingCoefficientB = GetValue(constructionProperties._surgingCoefficientBPtr.get(),
                                                  NaturalStoneRevetmentDefaults::SURGING_COEFFICIENT_B);
        const auto surgingCoefficientC = GetValue(constructionProperties._surgingCoefficientCPtr.get(),
                                                  NaturalStoneRevetmentDefaults::SURGING_COEFFICIENT_C);
        const auto surgingCoefficientN = GetValue(constructionProperties._surgingCoefficientNPtr.get(),
                                                  NaturalStoneRevetmentDefaults::SURGING_COEFFICIENT_N);
        const auto similarityParameterThreshold = GetValue(constructionProperties._similarityParameterThresholdPtr.get(),
                                                           NaturalStoneRevetmentDefaults::SIMILARITY_PARAMETER_THRESHOLD);

        _locations.push_back(make_unique<NaturalStoneRevetmentLocationDependentData>(
            constructionProperties.GetInitialDamage(), constructionProperties.GetSlopeAngle(), relativeDensity,
            constructionProperties.GetThicknessTopLayer(), plungingCoefficientA,
            plungingCoefficientB, plungingCoefficientC, plungingCoefficientN, surgingCoefficientA,
            surgingCoefficientB, surgingCoefficientC, surgingCoefficientN, similarityParameterThreshold));
    }

    unique_ptr<CalculationInput> RevetmentCalculationInputBuilder::Build()
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
