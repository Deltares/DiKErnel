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
        const double positionZ,
        unique_ptr<GrassRevetmentWaveImpactWaveAngleImpact> waveAngleImpact,
        const double minimumWaveHeightTemax,
        const double maximumWaveHeightTemin,
        unique_ptr<GrassRevetmentWaveImpactTimeLine> timeLine,
        const double upperLimitLoadingAul,
        const double lowerLimitLoadingAll)
        : LocationDependentInput(move(name), initialDamage, failureNumber, positionZ),
          _waveAngleImpact(move(waveAngleImpact)),
          _minimumWaveHeightTemax(minimumWaveHeightTemax),
          _maximumWaveHeightTemin(maximumWaveHeightTemin),
          _timeLine(move(timeLine)),
          _upperLimitLoadingAul(upperLimitLoadingAul),
          _lowerLimitLoadingAll(lowerLimitLoadingAll) {}

    unique_ptr<TimeDependentOutput> GrassRevetmentWaveImpactLocationDependentInput::Calculate(
        const double initialDamage,
        const ITimeDependentInput& timeDependentInput)
    {
        const auto waterLevel = timeDependentInput.GetWaterLevel();
        const auto waveHeightHm0 = timeDependentInput.GetWaveHeightHm0();
        const auto positionZ = GetPositionZ();

        const auto lowerLimitLoading = GrassRevetmentWaveImpact::LowerLimitLoading(waterLevel, waveHeightHm0, _lowerLimitLoadingAll);
        const auto upperLimitLoading = GrassRevetmentWaveImpact::UpperLimitLoading(waterLevel, waveHeightHm0, _upperLimitLoadingAul);
        const auto loadingOfRevetment = HydraulicLoad::LoadingRevetment(lowerLimitLoading, upperLimitLoading, positionZ);

        auto damage = initialDamage;
        unique_ptr<int> timeOfFailure = nullptr;

        if (loadingOfRevetment)
        {
            const auto incrementTime = Revetment::IncrementTime(timeDependentInput.GetBeginTime(), timeDependentInput.GetEndTime());
            const auto minimumWaveHeight = GrassRevetmentWaveImpact::MinimumWaveHeight(
                _timeLine->GetTimeLineAgwi(), _timeLine->GetTimeLineBgwi(), _timeLine->GetTimeLineCgwi(), _minimumWaveHeightTemax);
            const auto maximumWaveHeight = GrassRevetmentWaveImpact::MaximumWaveHeight(
                _timeLine->GetTimeLineAgwi(), _timeLine->GetTimeLineBgwi(), _timeLine->GetTimeLineCgwi(), _maximumWaveHeightTemin);
            const auto waveAngleImpact = GrassRevetmentWaveImpact::WaveAngleImpact(
                timeDependentInput.GetWaveAngle(), _waveAngleImpact->GetWaveAngleImpactNwa(), _waveAngleImpact->GetWaveAngleImpactQwa(),
                _waveAngleImpact->GetWaveAngleImpactRwa());
            const auto waveHeightImpact = GrassRevetmentWaveImpact::WaveHeightImpact(
                minimumWaveHeight, maximumWaveHeight, waveAngleImpact, waveHeightHm0);
            const auto timeLine = GrassRevetmentWaveImpact::TimeLine(
                waveHeightImpact, _timeLine->GetTimeLineAgwi(), _timeLine->GetTimeLineBgwi(), _timeLine->GetTimeLineCgwi());
            const auto incrementOfDamage = GrassRevetmentWaveImpact::IncrementDamage(incrementTime, timeLine);

            damage = Revetment::Damage(incrementOfDamage, initialDamage);

            const auto failureNumber = GetFailureNumber();

            if (Revetment::FailureRevetment(damage, initialDamage, failureNumber))
            {
                const auto durationInTimeStepFailure = GrassRevetmentWaveImpact::DurationInTimeStepFailure(timeLine, failureNumber, initialDamage);

                timeOfFailure = make_unique<int>(Revetment::TimeOfFailure(durationInTimeStepFailure, timeDependentInput.GetBeginTime()));
            }
        }

        return make_unique<TimeDependentOutput>(damage, move(timeOfFailure));
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

    GrassRevetmentWaveImpactTimeLine& GrassRevetmentWaveImpactLocationDependentInput::GetTimeLine() const
    {
        return *_timeLine;
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
