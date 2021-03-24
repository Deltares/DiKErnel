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

#include "CalculationMethod.h"

namespace DiKErnel::KernelWrapper::Json
{
    using namespace std;

    CalculationMethod::CalculationMethod(
        string calculationMethodSort,
        unique_ptr<HydraulicLoadOnNaturalStone> hydraulicLoadOnNaturalStone,
        unique_ptr<UpperLimitLoadingOfNaturalStone> upperLimitLoadingOfNaturalStone,
        unique_ptr<LowerLimitLoadingOfNaturalStone> lowerLimitLoadingOfNaturalStone,
        unique_ptr<DistanceMaximumWaveElevationNaturalStone> distanceMaximumWaveElevationNaturalStone,
        unique_ptr<NormativeWidthOfWaveImpact> normativeWidthOfWaveImpact,
        unique_ptr<WaveAngleImpact> waveAngleImpact)
        : _calculationMethodSort(move(calculationMethodSort)),
          _hydraulicLoadOnNaturalStone(move(hydraulicLoadOnNaturalStone)),
          _upperLimitLoadingOfNaturalStone(move(upperLimitLoadingOfNaturalStone)),
          _lowerLimitLoadingOfNaturalStone(move(lowerLimitLoadingOfNaturalStone)),
          _distanceMaximumWaveElevationNaturalStone(move(distanceMaximumWaveElevationNaturalStone)),
          _normativeWidthOfWaveImpact(move(normativeWidthOfWaveImpact)),
          _waveAngleImpact(move(waveAngleImpact)) { }

    const string& CalculationMethod::GetCalculationMethodSort() const
    {
        return _calculationMethodSort;
    }

    const HydraulicLoadOnNaturalStone& CalculationMethod::GetHydraulicLoadOnNaturalStone() const
    {
        return *_hydraulicLoadOnNaturalStone;
    }

    const UpperLimitLoadingOfNaturalStone& CalculationMethod::GetUpperLimitLoadingOfNaturalStone() const
    {
        return *_upperLimitLoadingOfNaturalStone;
    }

    const LowerLimitLoadingOfNaturalStone& CalculationMethod::GetLowerLimitLoadingOfNaturalStone() const
    {
        return *_lowerLimitLoadingOfNaturalStone;
    }

    const DistanceMaximumWaveElevationNaturalStone& CalculationMethod::GetDistanceMaximumWaveElevationNaturalStone() const
    {
        return *_distanceMaximumWaveElevationNaturalStone;
    }

    const NormativeWidthOfWaveImpact& CalculationMethod::GetNormativeWidthOfWaveImpact() const
    {
        return *_normativeWidthOfWaveImpact;
    }

    const WaveAngleImpact& CalculationMethod::GetWaveAngleImpact() const
    {
        return *_waveAngleImpact;
    }
}
