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
#include "GrassRevetmentWaveImpactTimeDependentOutput.h"
#include "HydraulicLoadFunctions.h"
#include "RevetmentFunctions.h"

namespace DiKErnel::Integration
{
    using namespace Core;
    using namespace FunctionLibrary;
    using namespace std;

    GrassRevetmentWaveImpactLocationDependentInput::GrassRevetmentWaveImpactLocationDependentInput(
        const double x,
        const double initialDamage,
        const double failureNumber,
        unique_ptr<GrassRevetmentWaveImpactWaveAngleImpact> waveAngleImpact,
        const double minimumWaveHeightTemax,
        const double maximumWaveHeightTemin,
        unique_ptr<GrassRevetmentWaveImpactTimeLine> timeLine,
        const double upperLimitLoadingAul,
        const double lowerLimitLoadingAll)
        : LocationDependentInput(x, initialDamage, failureNumber),
          _waveAngleImpact(move(waveAngleImpact)),
          _minimumWaveHeightTemax(minimumWaveHeightTemax),
          _maximumWaveHeightTemin(maximumWaveHeightTemin),
          _timeLine(move(timeLine)),
          _upperLimitLoadingAul(upperLimitLoadingAul),
          _lowerLimitLoadingAll(lowerLimitLoadingAll) {}

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

    void GrassRevetmentWaveImpactLocationDependentInput::InitializeDerivedLocationDependentInput(
        const IProfileData& profileData)
    {
        LocationDependentInput::InitializeDerivedLocationDependentInput(profileData);

        const auto timeLineAgwi = _timeLine->GetTimeLineAgwi();
        const auto timeLineBgwi = _timeLine->GetTimeLineBgwi();
        const auto timeLineCgwi = _timeLine->GetTimeLineCgwi();

        _minimumWaveHeight = GrassRevetmentWaveImpact::MinimumWaveHeight(timeLineAgwi, timeLineBgwi, timeLineCgwi, _minimumWaveHeightTemax);
        _maximumWaveHeight = GrassRevetmentWaveImpact::MaximumWaveHeight(timeLineAgwi, timeLineBgwi, timeLineCgwi, _maximumWaveHeightTemin);
    }

    unique_ptr<TimeDependentOutput> GrassRevetmentWaveImpactLocationDependentInput::CalculateTimeDependentOutput(
        const double initialDamage,
        const ITimeDependentInput& timeDependentInput,
        const IProfileData& profileData)
    {
        const auto waterLevel = timeDependentInput.GetWaterLevel();
        const auto waveHeightHm0 = timeDependentInput.GetWaveHeightHm0();

        const auto lowerLimitLoading = GrassRevetmentWaveImpact::LowerLimitLoading(waterLevel, waveHeightHm0, _lowerLimitLoadingAll);
        const auto upperLimitLoading = GrassRevetmentWaveImpact::UpperLimitLoading(waterLevel, waveHeightHm0, _upperLimitLoadingAul);
        const auto loadingRevetment = HydraulicLoadFunctions::LoadingRevetment(lowerLimitLoading, upperLimitLoading, GetZ());

        auto incrementDamage = 0.0;
        auto damage = initialDamage;
        unique_ptr<int> timeOfFailure = nullptr;

        auto minimumWaveHeight = loadingRevetment ? make_unique<double>(_minimumWaveHeight) : nullptr;
        auto maximumWaveHeight = loadingRevetment ? make_unique<double>(_maximumWaveHeight) : nullptr;

        unique_ptr<double> waveAngleImpact = nullptr;
        unique_ptr<double> waveHeightImpact = nullptr;

        if (loadingRevetment)
        {
            const auto beginTime = timeDependentInput.GetBeginTime();

            const auto incrementTime = RevetmentFunctions::IncrementTime(beginTime, timeDependentInput.GetEndTime());
            waveAngleImpact = make_unique<double>(GrassRevetmentWaveImpact::WaveAngleImpact(timeDependentInput.GetWaveAngle(),
                                                                                            _waveAngleImpact->GetWaveAngleImpactNwa(),
                                                                                            _waveAngleImpact->GetWaveAngleImpactQwa(),
                                                                                            _waveAngleImpact->GetWaveAngleImpactRwa()));
            waveHeightImpact = make_unique<double>(GrassRevetmentWaveImpact::WaveHeightImpact(*minimumWaveHeight, *maximumWaveHeight,
                                                                                              *waveAngleImpact, waveHeightHm0));
            const auto timeLine = GrassRevetmentWaveImpact::TimeLine(*waveHeightImpact, _timeLine->GetTimeLineAgwi(), _timeLine->GetTimeLineBgwi(),
                                                                     _timeLine->GetTimeLineCgwi());
            incrementDamage = GrassRevetmentWaveImpact::IncrementDamage(incrementTime, timeLine);

            damage = RevetmentFunctions::Damage(incrementDamage, initialDamage);

            const auto failureNumber = GetFailureNumber();

            if (RevetmentFunctions::FailureRevetment(damage, initialDamage, failureNumber))
            {
                const auto durationInTimeStepFailure = RevetmentFunctions::DurationInTimeStepFailure(
                    incrementTime, incrementDamage, failureNumber, initialDamage);

                timeOfFailure = make_unique<int>(RevetmentFunctions::TimeOfFailure(durationInTimeStepFailure, beginTime));
            }
        }

        return make_unique<GrassRevetmentWaveImpactTimeDependentOutput>(incrementDamage, damage, move(timeOfFailure), loadingRevetment,
                                                                        upperLimitLoading, lowerLimitLoading, move(minimumWaveHeight),
                                                                        move(maximumWaveHeight), move(waveAngleImpact), move(waveHeightImpact));
    }
}
