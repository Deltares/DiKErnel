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

#include "NaturalStoneRevetmentLocationDependentData.h"

#include "NaturalStoneRevetment.h"
#include "TimeDependentData.h"

namespace DiKErnel::Integration
{
    using namespace Core;
    using namespace FunctionLibrary;

    NaturalStoneRevetmentLocationDependentData::NaturalStoneRevetmentLocationDependentData(
        const double initialDamage,
        const double slopeAngle,
        const double relativeDensity,
        const double thicknessTopLayer,
        const double plungingCoefficientA,
        const double plungingCoefficientB,
        const double plungingCoefficientC,
        const double plungingCoefficientN,
        const double surgingCoefficientA,
        const double surgingCoefficientB,
        const double surgingCoefficientC,
        const double surgingCoefficientN,
        const double similarityParameterThreshold)
        : LocationDependentData(initialDamage),
          _slopeAngle(slopeAngle),
          _relativeDensity(relativeDensity),
          _thicknessTopLayer(thicknessTopLayer),
          _plungingCoefficientA(plungingCoefficientA),
          _plungingCoefficientB(plungingCoefficientB),
          _plungingCoefficientC(plungingCoefficientC),
          _plungingCoefficientN(plungingCoefficientN),
          _surgingCoefficientA(surgingCoefficientA),
          _surgingCoefficientB(surgingCoefficientB),
          _surgingCoefficientC(surgingCoefficientC),
          _surgingCoefficientN(surgingCoefficientN),
          _similarityParameterThreshold(similarityParameterThreshold) {}

    double NaturalStoneRevetmentLocationDependentData::Calculate(
        const double startDamage,
        const TimeDependentData& timeDependentData,
        const double maximumWaveAngle)
    {
        return NaturalStoneRevetment::CalculateDamage(
            startDamage, _slopeAngle, _relativeDensity, _thicknessTopLayer,
            timeDependentData.GetWaveHeightHm0(), timeDependentData.GetWavePeriodTm10(),
            timeDependentData.GetWaveAngle(), timeDependentData.GetBeginTime(),
            timeDependentData.GetEndTime(), _plungingCoefficientA, _plungingCoefficientB,
            _plungingCoefficientC, _plungingCoefficientN, _surgingCoefficientA, _surgingCoefficientB,
            _surgingCoefficientC, _surgingCoefficientN, maximumWaveAngle, _similarityParameterThreshold);
    }

    double NaturalStoneRevetmentLocationDependentData::GetSlopeAngle() const
    {
        return _slopeAngle;
    }

    double NaturalStoneRevetmentLocationDependentData::GetRelativeDensity() const
    {
        return _relativeDensity;
    }

    double NaturalStoneRevetmentLocationDependentData::GetThicknessTopLayer() const
    {
        return _thicknessTopLayer;
    }

    double NaturalStoneRevetmentLocationDependentData::GetPlungingCoefficientA() const
    {
        return _plungingCoefficientA;
    }

    double NaturalStoneRevetmentLocationDependentData::GetPlungingCoefficientB() const
    {
        return _plungingCoefficientB;
    }

    double NaturalStoneRevetmentLocationDependentData::GetPlungingCoefficientC() const
    {
        return _plungingCoefficientC;
    }

    double NaturalStoneRevetmentLocationDependentData::GetPlungingCoefficientN() const
    {
        return _plungingCoefficientN;
    }

    double NaturalStoneRevetmentLocationDependentData::GetSurgingCoefficientA() const
    {
        return _surgingCoefficientA;
    }

    double NaturalStoneRevetmentLocationDependentData::GetSurgingCoefficientB() const
    {
        return _surgingCoefficientB;
    }

    double NaturalStoneRevetmentLocationDependentData::GetSurgingCoefficientC() const
    {
        return _surgingCoefficientC;
    }

    double NaturalStoneRevetmentLocationDependentData::GetSurgingCoefficientN() const
    {
        return _surgingCoefficientN;
    }

    double NaturalStoneRevetmentLocationDependentData::GetSimilarityParameterThreshold() const
    {
        return _similarityParameterThreshold;
    }
}
