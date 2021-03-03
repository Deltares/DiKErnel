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
#include "NaturalStoneRevetmentLocationDependentData.h"
#include "RevetmentCalculationInputBuilderException.h"

namespace DiKErnel::Integration
{
    using namespace Core;
    using namespace DomainLibrary;
    using namespace std;

    RevetmentCalculationInputBuilder::RevetmentCalculationInputBuilder(
        const double maximumWaveAngle)
        : _maximumWaveAngle(maximumWaveAngle),
          _timeSteps(vector<unique_ptr<TimeDependentData>>()),
          _locations(vector<unique_ptr<LocationDependentData>>()) {}

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
        catch (InvalidCalculationDataException&)
        {
            throw_with_nested(RevetmentCalculationInputBuilderException("Could not create TimeDependentData."));
        }
    }

    void RevetmentCalculationInputBuilder::AddNaturalStoneLocation(
        double initialDamage,
        double slopeAngle,
        const double* relativeDensityPtr,
        double thicknessTopLayer,
        const double* plungingCoefficientAPtr,
        const double* plungingCoefficientBPtr,
        const double* plungingCoefficientCPtr,
        const double* plungingCoefficientNPtr,
        const double* surgingCoefficientAPtr,
        const double* surgingCoefficientBPtr,
        const double* surgingCoefficientCPtr,
        const double* surgingCoefficientNPtr,
        const double* similarityParameterThresholdPtr)
    {
        const auto relativeDensity = GetValue(relativeDensityPtr, NaturalStoneRevetmentDefaults::RELATIVE_DENSITY);
        const auto plungingCoefficientA = GetValue(plungingCoefficientAPtr, NaturalStoneRevetmentDefaults::PLUNGING_COEFFICIENT_A);
        const auto plungingCoefficientB = GetValue(plungingCoefficientBPtr, NaturalStoneRevetmentDefaults::PLUNGING_COEFFICIENT_B);
        const auto plungingCoefficientC = GetValue(plungingCoefficientCPtr, NaturalStoneRevetmentDefaults::PLUNGING_COEFFICIENT_C);
        const auto plungingCoefficientN = GetValue(plungingCoefficientNPtr, NaturalStoneRevetmentDefaults::PLUNGING_COEFFICIENT_N);
        const auto surgingCoefficientA = GetValue(surgingCoefficientAPtr, NaturalStoneRevetmentDefaults::SURGING_COEFFICIENT_A);
        const auto surgingCoefficientB = GetValue(surgingCoefficientBPtr, NaturalStoneRevetmentDefaults::SURGING_COEFFICIENT_B);
        const auto surgingCoefficientC = GetValue(surgingCoefficientCPtr, NaturalStoneRevetmentDefaults::SURGING_COEFFICIENT_C);
        const auto surgingCoefficientN = GetValue(surgingCoefficientNPtr, NaturalStoneRevetmentDefaults::SURGING_COEFFICIENT_N);
        const auto similarityParameterThreshold = GetValue(
            similarityParameterThresholdPtr, NaturalStoneRevetmentDefaults::SIMILARITY_PARAMETER_THRESHOLD);

        _locations.push_back(make_unique<NaturalStoneRevetmentLocationDependentData>(
            initialDamage, slopeAngle, relativeDensity, thicknessTopLayer, plungingCoefficientA,
            plungingCoefficientB, plungingCoefficientC, plungingCoefficientN, surgingCoefficientA,
            surgingCoefficientB, surgingCoefficientC, surgingCoefficientN, similarityParameterThreshold));
    }

    unique_ptr<CalculationInput> RevetmentCalculationInputBuilder::Build()
    {
        return make_unique<CalculationInput>(move(_locations), move(_timeSteps), _maximumWaveAngle);
    }

    double RevetmentCalculationInputBuilder::GetValue(
        const double* doublePtr,
        const double defaultValue)
    {
        return doublePtr != nullptr
                   ? *doublePtr
                   : defaultValue;
    }
}
