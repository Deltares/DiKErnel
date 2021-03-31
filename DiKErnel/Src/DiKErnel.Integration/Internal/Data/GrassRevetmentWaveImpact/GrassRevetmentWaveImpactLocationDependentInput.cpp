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

#include "GrassRevetmentWaveImpactLocationDependentInput.h"

#include "GrassRevetmentWaveImpact.h"
#include "HydraulicLoad.h"
#include "Revetment.h"

namespace DiKErnel::Integration
{
    using namespace Core;
    using namespace FunctionLibrary;
    using namespace std;

    GrassRevetmentWaveImpactLocationDependentInput::GrassRevetmentWaveImpactLocationDependentInput(
        string name,
        const double initialDamage,
        const double failureNumber,
        const double tanA,
        const double positionZ,
        unique_ptr<GrassRevetmentWaveImpactWaveAngleImpact> waveAngleImpact,
        const double minimumWaveHeightTemax,
        const double maximumWaveHeightTemin,
        unique_ptr<GrassRevetmentWaveImpactTimeLine> failureTime,
        const double upperLimitLoadingAul,
        const double lowerLimitLoadingAll)
        : LocationDependentInput(move(name), initialDamage, failureNumber, tanA, positionZ),
          _waveAngleImpact(move(waveAngleImpact)),
          _minimumWaveHeightTemax(minimumWaveHeightTemax),
          _maximumWaveHeightTemin(maximumWaveHeightTemin),
          _failureTime(move(failureTime)),
          _upperLimitLoadingAul(upperLimitLoadingAul),
          _lowerLimitLoadingAll(lowerLimitLoadingAll) {}

    unique_ptr<TimeDependentOutput> GrassRevetmentWaveImpactLocationDependentInput::Calculate(
        const double initialDamage,
        const ITimeDependentInput& timeDependentInput)
    {
        const auto waterLevel = timeDependentInput.GetWaterLevel();
        const auto waveHeightHm0 = timeDependentInput.GetWaveHeightHm0();
        const auto positionZ = GetPositionZ();

        const auto lowerLimitLoading = GrassRevetmentWaveImpact::LowerLimitLoading(
            waterLevel,
            waveHeightHm0,
            _lowerLimitLoadingAll);

        const auto upperLimitLoading = GrassRevetmentWaveImpact::UpperLimitLoading(
            waterLevel,
            waveHeightHm0,
            _upperLimitLoadingAul);

        const auto loadingOfRevetment = HydraulicLoad::LoadingRevetment(
            lowerLimitLoading,
            upperLimitLoading,
            positionZ);

        auto incrementOfDamage = 0.0;

        if (loadingOfRevetment)
        {
            const auto incrementTime = Revetment::IncrementTime(
                timeDependentInput.GetBeginTime(),
                timeDependentInput.GetEndTime());

            const auto minimumWaveHeight = GrassRevetmentWaveImpact::MinimumWaveHeight(
                _failureTime->GetTimeLineAgwi(),
                _failureTime->GetTimeLineBgwi(),
                _failureTime->GetTimeLineCgwi(),
                _minimumWaveHeightTemax);

            const auto maximumWaveHeight = GrassRevetmentWaveImpact::MaximumWaveHeight(
                _failureTime->GetTimeLineAgwi(),
                _failureTime->GetTimeLineBgwi(),
                _failureTime->GetTimeLineCgwi(),
                _maximumWaveHeightTemin);

            const auto waveAngleImpact = GrassRevetmentWaveImpact::WaveAngleImpact(
                timeDependentInput.GetWaveAngle(),
                _waveAngleImpact->GetWaveAngleImpactNwa(),
                _waveAngleImpact->GetWaveAngleImpactQwa(),
                _waveAngleImpact->GetWaveAngleImpactRwa());

            const auto waveHeight = GrassRevetmentWaveImpact::WaveHeight(
                minimumWaveHeight,
                maximumWaveHeight,
                waveAngleImpact,
                waveHeightHm0);

            const auto failureTime = GrassRevetmentWaveImpact::TimeLine(
                waveHeight,
                _failureTime->GetTimeLineAgwi(),
                _failureTime->GetTimeLineBgwi(),
                _failureTime->GetTimeLineCgwi()
            );

            incrementOfDamage = GrassRevetmentWaveImpact::IncrementDamage(
                incrementTime, failureTime);
        }

        return make_unique<TimeDependentOutput>(Revetment::Damage(incrementOfDamage, initialDamage), nullptr);
    }

    GrassRevetmentWaveImpactWaveAngleImpact& GrassRevetmentWaveImpactLocationDependentInput::GetWaveAngleImpact() const
    {
        return *_waveAngleImpact;
    }

    double GrassRevetmentWaveImpactLocationDependentInput::GetMinimumWaveHeightTemax() const
    {
        return _minimumWaveHeightTemax;
    }

    double GrassRevetmentWaveImpactLocationDependentInput::GetMaximumWaveHeightTemin() const
    {
        return _maximumWaveHeightTemin;
    }

    GrassRevetmentWaveImpactTimeLine& GrassRevetmentWaveImpactLocationDependentInput::GetFailureTime() const
    {
        return *_failureTime;
    }

    double GrassRevetmentWaveImpactLocationDependentInput::GetUpperLimitLoadingAul() const
    {
        return _upperLimitLoadingAul;
    }

    double GrassRevetmentWaveImpactLocationDependentInput::GetLowerLimitLoadingAll() const
    {
        return _lowerLimitLoadingAll;
    }
}
