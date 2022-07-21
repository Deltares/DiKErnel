// Copyright (C) Stichting Deltares 2022. All rights reserved.
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

#include "GrassRevetmentWaveImpactFunctions.h"
#include "GrassRevetmentWaveImpactLocationDependentOutput.h"
#include "GrassRevetmentWaveImpactTimeDependentOutput.h"
#include "GrassRevetmentWaveImpactValidator.h"
#include "HydraulicLoadFunctions.h"
#include "RevetmentFunctions.h"
#include "ValidationHelper.h"

namespace DiKErnel::Integration
{
    using namespace Core;
    using namespace DomainLibrary;
    using namespace FunctionLibrary;
    using namespace std;
    using namespace Util;

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
          _waveAngleImpactInput(move(waveAngleImpact)),
          _minimumWaveHeightTemax(minimumWaveHeightTemax),
          _maximumWaveHeightTemin(maximumWaveHeightTemin),
          _timeLine(move(timeLine)),
          _upperLimitLoadingAul(upperLimitLoadingAul),
          _lowerLimitLoadingAll(lowerLimitLoadingAll) {}

    GrassRevetmentWaveImpactWaveAngleImpact& GrassRevetmentWaveImpactLocationDependentInput::GetWaveAngleImpact() const
    {
        return *_waveAngleImpactInput;
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

    bool GrassRevetmentWaveImpactLocationDependentInput::Validate(
        const IProfileData& profileData) const
    {
        const auto baseValidationSuccessful = LocationDependentInput::Validate(profileData);

        vector<unique_ptr<ValidationIssue>> validationIssues;
        validationIssues.emplace_back(GrassRevetmentWaveImpactValidator::TimeLineAgwi(_timeLine->GetTimeLineAgwi(), _timeLine->GetTimeLineCgwi()));
        validationIssues.emplace_back(GrassRevetmentWaveImpactValidator::TimeLineBgwi(_timeLine->GetTimeLineBgwi()));
        validationIssues.emplace_back(GrassRevetmentWaveImpactValidator::TimeLineCgwi(_timeLine->GetTimeLineCgwi()));
        validationIssues.emplace_back(GrassRevetmentWaveImpactValidator::MinimumWaveHeightTemax(_minimumWaveHeightTemax));
        validationIssues.emplace_back(GrassRevetmentWaveImpactValidator::MaximumWaveHeightTemin(_maximumWaveHeightTemin));
        validationIssues.emplace_back(GrassRevetmentWaveImpactValidator::WaveAngleImpactNwa(_waveAngleImpactInput->GetWaveAngleImpactNwa()));
        validationIssues.emplace_back(GrassRevetmentWaveImpactValidator::WaveAngleImpactQwa(_waveAngleImpactInput->GetWaveAngleImpactQwa()));
        validationIssues.emplace_back(GrassRevetmentWaveImpactValidator::WaveAngleImpactRwa(_waveAngleImpactInput->GetWaveAngleImpactRwa()));
        validationIssues.emplace_back(GrassRevetmentWaveImpactValidator::UpperLimitLoadingAul(_upperLimitLoadingAul, _lowerLimitLoadingAll));

        return ValidationHelper::RegisterValidationIssues(validationIssues) && baseValidationSuccessful;
    }

    unique_ptr<LocationDependentOutput> GrassRevetmentWaveImpactLocationDependentInput::GetLocationDependentOutput(
        vector<unique_ptr<TimeDependentOutput>> timeDependentOutputItems)
    {
        return make_unique<GrassRevetmentWaveImpactLocationDependentOutput>(GetZ(), move(timeDependentOutputItems));
    }

    void GrassRevetmentWaveImpactLocationDependentInput::InitializeDerivedLocationDependentInput(
        const IProfileData& profileData)
    {
        LocationDependentInput::InitializeDerivedLocationDependentInput(profileData);

        const auto timeLineAgwi = _timeLine->GetTimeLineAgwi();
        const auto timeLineBgwi = _timeLine->GetTimeLineBgwi();
        const auto timeLineCgwi = _timeLine->GetTimeLineCgwi();

        _minimumWaveHeight = GrassRevetmentWaveImpactFunctions::MinimumWaveHeight(timeLineAgwi, timeLineBgwi, timeLineCgwi,
                                                                                  _minimumWaveHeightTemax);
        _maximumWaveHeight = GrassRevetmentWaveImpactFunctions::MaximumWaveHeight(timeLineAgwi, timeLineBgwi, timeLineCgwi,
                                                                                  _maximumWaveHeightTemin);
    }

    unique_ptr<TimeDependentOutput> GrassRevetmentWaveImpactLocationDependentInput::CalculateTimeDependentOutput(
        const double initialDamage,
        const ITimeDependentInput& timeDependentInput,
        const IProfileData& profileData)
    {
        const auto waveHeightHm0 = timeDependentInput.GetWaveHeightHm0();

        _loadingRevetment = CalculateLoadingRevetment(timeDependentInput.GetWaterLevel(), waveHeightHm0);

        auto incrementDamage = 0.0;
        auto damage = initialDamage;
        unique_ptr<int> timeOfFailure = nullptr;

        if (_loadingRevetment)
        {
            const auto beginTime = timeDependentInput.GetBeginTime();

            const auto incrementTime = RevetmentFunctions::IncrementTime(beginTime, timeDependentInput.GetEndTime());
            _waveAngleImpact = GrassRevetmentWaveImpactFunctions::WaveAngleImpact(timeDependentInput.GetWaveAngle(),
                                                                                  _waveAngleImpactInput->GetWaveAngleImpactNwa(),
                                                                                  _waveAngleImpactInput->GetWaveAngleImpactQwa(),
                                                                                  _waveAngleImpactInput->GetWaveAngleImpactRwa());
            _waveHeightImpact = GrassRevetmentWaveImpactFunctions::WaveHeightImpact(_minimumWaveHeight, _maximumWaveHeight, _waveAngleImpact,
                                                                                    waveHeightHm0);
            const auto timeLine = GrassRevetmentWaveImpactFunctions::TimeLine(_waveHeightImpact, _timeLine->GetTimeLineAgwi(),
                                                                              _timeLine->GetTimeLineBgwi(), _timeLine->GetTimeLineCgwi());
            incrementDamage = GrassRevetmentWaveImpactFunctions::IncrementDamage(incrementTime, timeLine);

            damage = RevetmentFunctions::Damage(incrementDamage, initialDamage);

            if (const auto failureNumber = GetFailureNumber(); RevetmentFunctions::FailureRevetment(damage, initialDamage, failureNumber))
            {
                const auto durationInTimeStepFailure = RevetmentFunctions::DurationInTimeStepFailure(
                    incrementTime, incrementDamage, failureNumber, initialDamage);

                timeOfFailure = make_unique<int>(RevetmentFunctions::TimeOfFailure(durationInTimeStepFailure, beginTime));
            }
        }

        return make_unique<GrassRevetmentWaveImpactTimeDependentOutput>(
            *CreateConstructionProperties(incrementDamage, damage, move(timeOfFailure)));
    }

    bool GrassRevetmentWaveImpactLocationDependentInput::CalculateLoadingRevetment(
        const double waterLevel,
        const double waveHeightHm0)
    {
        _lowerLimitLoading = GrassRevetmentWaveImpactFunctions::LowerLimitLoading(waterLevel, waveHeightHm0, _lowerLimitLoadingAll);
        _upperLimitLoading = GrassRevetmentWaveImpactFunctions::UpperLimitLoading(waterLevel, waveHeightHm0, _upperLimitLoadingAul);

        return HydraulicLoadFunctions::LoadingRevetment(_lowerLimitLoading, _upperLimitLoading, GetZ());
    }

    unique_ptr<GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties> GrassRevetmentWaveImpactLocationDependentInput::
    CreateConstructionProperties(
        double incrementDamage,
        double damage,
        unique_ptr<int> timeOfFailure)
    {
        auto constructionProperties = make_unique<GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties>();
        constructionProperties->_incrementDamage = make_unique<double>(incrementDamage);
        constructionProperties->_damage = make_unique<double>(damage);
        constructionProperties->_timeOfFailure = move(timeOfFailure);
        constructionProperties->_loadingRevetment = make_unique<bool>(_loadingRevetment);
        constructionProperties->_upperLimitLoading = make_unique<double>(_upperLimitLoading);
        constructionProperties->_lowerLimitLoading = make_unique<double>(_lowerLimitLoading);

        if (_loadingRevetment)
        {
            constructionProperties->_minimumWaveHeight = make_unique<double>(_minimumWaveHeight);
            constructionProperties->_maximumWaveHeight = make_unique<double>(_maximumWaveHeight);
            constructionProperties->_waveAngleImpact = make_unique<double>(_waveAngleImpact);
            constructionProperties->_waveHeightImpact = make_unique<double>(_waveHeightImpact);
        }

        return constructionProperties;
    }
}
