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
    using namespace std;

    NaturalStoneRevetmentLocationDependentData::NaturalStoneRevetmentLocationDependentData(
        const double initialDamage,
        const double slopeAngle,
        const double relativeDensity,
        const double thicknessTopLayer,
        unique_ptr<NaturalStoneRevetmentHydraulicLoads> hydraulicLoads,
        unique_ptr<NaturalStoneRevetmentUpperLimitLoading> upperLimitLoading,
        unique_ptr<NaturalStoneRevetmentLowerLimitLoading> lowerLimitLoading,
        unique_ptr<NaturalStoneRevetmentDistanceMaximumWaveElevation> distanceMaximumWaveElevation,
        unique_ptr<NaturalStoneRevetmentNormativeWidthOfWaveImpact> normativeWidthOfWaveImpact)
        : LocationDependentData(initialDamage),
          _slopeAngle(slopeAngle),
          _relativeDensity(relativeDensity),
          _thicknessTopLayer(thicknessTopLayer),
          _hydraulicLoads(move(hydraulicLoads)),
          _upperLimitLoading(move(upperLimitLoading)),
          _lowerLimitLoading(move(lowerLimitLoading)),
          _distanceMaximumWaveElevation(move(distanceMaximumWaveElevation)),
          _normativeWidthOfWaveImpact(move(normativeWidthOfWaveImpact)) {}

    double NaturalStoneRevetmentLocationDependentData::Calculate(
        const double startDamage,
        const ITimeDependentData& timeDependentData,
        const double maximumWaveAngle)
    {
        return NaturalStoneRevetment::CalculateDamage(
            startDamage, _slopeAngle, _relativeDensity, _thicknessTopLayer,
            timeDependentData.GetWaveHeightHm0(), timeDependentData.GetWavePeriodTm10(),
            timeDependentData.GetWaveAngle(), timeDependentData.GetBeginTime(), timeDependentData.GetEndTime(),
            _hydraulicLoads->GetHydraulicLoadAp(), _hydraulicLoads->GetHydraulicLoadBp(), _hydraulicLoads->GetHydraulicLoadCp(),
            _hydraulicLoads->GetHydraulicLoadNp(), _hydraulicLoads->GetHydraulicLoadAs(), _hydraulicLoads->GetHydraulicLoadBs(),
            _hydraulicLoads->GetHydraulicLoadCs(), _hydraulicLoads->GetHydraulicLoadNs(), maximumWaveAngle, _hydraulicLoads->GetHydraulicLoadXib());
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

    NaturalStoneRevetmentHydraulicLoads& NaturalStoneRevetmentLocationDependentData::GetHydraulicLoads() const
    {
        return *_hydraulicLoads;
    }

    NaturalStoneRevetmentUpperLimitLoading& NaturalStoneRevetmentLocationDependentData::GetUpperLimitLoading() const
    {
        return *_upperLimitLoading;
    }

    NaturalStoneRevetmentLowerLimitLoading& NaturalStoneRevetmentLocationDependentData::GetLowerLimitLoading() const
    {
        return *_lowerLimitLoading;
    }

    NaturalStoneRevetmentDistanceMaximumWaveElevation& NaturalStoneRevetmentLocationDependentData::GetDistanceMaximumWaveElevation() const
    {
        return *_distanceMaximumWaveElevation;
    }

    NaturalStoneRevetmentNormativeWidthOfWaveImpact& NaturalStoneRevetmentLocationDependentData::GetNormativeWidthOfWaveImpact() const
    {
        return *_normativeWidthOfWaveImpact;
    }
}
