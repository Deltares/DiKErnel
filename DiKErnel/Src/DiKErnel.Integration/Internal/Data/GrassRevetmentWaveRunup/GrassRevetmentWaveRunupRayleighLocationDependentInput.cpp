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

#include "GrassRevetmentWaveRunupRayleighLocationDependentInput.h"

#include "Constants.h"
#include "GrassRevetmentWaveRunupFunctions.h"
#include "GrassRevetmentWaveRunupRayleighFunctions.h"
#include "GrassRevetmentWaveRunupRayleighTimeDependentOutput.h"
#include "GrassRevetmentWaveRunupRayleighValidator.h"
#include "HydraulicLoadFunctions.h"
#include "RevetmentFunctions.h"
#include "ValidationHelper.h"

namespace DiKErnel::Integration
{
    using namespace Core;
    using namespace DomainLibrary;
    using namespace FunctionLibrary;
    using namespace std;

    GrassRevetmentWaveRunupRayleighLocationDependentInput::GrassRevetmentWaveRunupRayleighLocationDependentInput(
        const double x,
        const double initialDamage,
        const double failureNumber,
        const double outerSlope,
        const double criticalCumulativeOverload,
        const double criticalFrontVelocity,
        const double increasedLoadTransitionAlphaM,
        const double reducedStrengthTransitionAlphaS,
        const double averageNumberOfWavesCtm,
        unique_ptr<GrassRevetmentWaveRunupRepresentative2P> representative2P,
        unique_ptr<GrassRevetmentWaveRunupWaveAngleImpact> waveAngleImpact,
        const int fixedNumberOfWaves,
        const double frontVelocityCu)
        : GrassRevetmentWaveRunupLocationDependentInput(x, initialDamage, failureNumber, outerSlope, criticalCumulativeOverload,
                                                        criticalFrontVelocity, increasedLoadTransitionAlphaM, reducedStrengthTransitionAlphaS,
                                                        averageNumberOfWavesCtm, move(representative2P), move(waveAngleImpact)),
          _fixedNumberOfWaves(fixedNumberOfWaves),
          _frontVelocityCu(frontVelocityCu) {}

    int GrassRevetmentWaveRunupRayleighLocationDependentInput::GetFixedNumberOfWaves() const
    {
        return _fixedNumberOfWaves;
    }

    double GrassRevetmentWaveRunupRayleighLocationDependentInput::GetFrontVelocityCu() const
    {
        return _frontVelocityCu;
    }

    bool GrassRevetmentWaveRunupRayleighLocationDependentInput::Validate(
        const IProfileData& profileData) const
    {
        const auto baseValidationSuccessful = GrassRevetmentWaveRunupLocationDependentInput::Validate(profileData);

        vector<unique_ptr<ValidationIssue>> validationIssues;
        validationIssues.emplace_back(GrassRevetmentWaveRunupRayleighValidator::FixedNumberOfWaves(_fixedNumberOfWaves));
        validationIssues.emplace_back(GrassRevetmentWaveRunupRayleighValidator::FrontVelocityCu(_frontVelocityCu));

        return ValidationHelper::RegisterValidationIssues(validationIssues) && baseValidationSuccessful;
    }

    unique_ptr<TimeDependentOutput> GrassRevetmentWaveRunupRayleighLocationDependentInput::CalculateTimeDependentOutput(
        const double initialDamage,
        const ITimeDependentInput& timeDependentInput,
        const IProfileData& profileData)
    {
        auto incrementDamage = 0.0;
        auto damage = initialDamage;
        unique_ptr<int> timeOfFailure = nullptr;

        unique_ptr<double> waveAngleImpact = nullptr;
        unique_ptr<double> representativeWaveRunup2P = nullptr;
        unique_ptr<double> cumulativeOverload = nullptr;

        const auto verticalDistanceWaterLevelElevation = HydraulicLoadFunctions::VerticalDistanceWaterLevelElevation(
            GetZ(), timeDependentInput.GetWaterLevel());

        if (verticalDistanceWaterLevelElevation > 0)
        {
            const auto beginTime = timeDependentInput.GetBeginTime();

            const auto incrementTime = RevetmentFunctions::IncrementTime(beginTime, timeDependentInput.GetEndTime());
            const auto averageNumberOfWaves = RevetmentFunctions::AverageNumberOfWaves(incrementTime, timeDependentInput.GetWavePeriodTm10(),
                                                                                       GetAverageNumberOfWavesCtm());

            const auto surfSimilarityParameter = HydraulicLoadFunctions::SurfSimilarityParameter(GetOuterSlope(),
                                                                                                 timeDependentInput.GetWaveHeightHm0(),
                                                                                                 timeDependentInput.GetWavePeriodTm10(),
                                                                                                 Constants::GetGravitationalAcceleration());

            waveAngleImpact = make_unique<double>(GrassRevetmentWaveRunupFunctions::WaveAngleImpact(
                timeDependentInput.GetWaveAngle(), GetWaveAngleImpact().GetAbeta(), GetWaveAngleImpact().GetBetamax()));

            const auto& representative2P = GetRepresentative2P();
            representativeWaveRunup2P = make_unique<double>(GrassRevetmentWaveRunupFunctions::RepresentativeWaveRunup2P(
                surfSimilarityParameter, *waveAngleImpact, timeDependentInput.GetWaveHeightHm0(), representative2P.GetGammab(),
                representative2P.GetGammaf(), representative2P.GetRepresentative2PAru(), representative2P.GetRepresentative2PBru(),
                representative2P.GetRepresentative2PCru()));

            cumulativeOverload = make_unique<double>(GrassRevetmentWaveRunupRayleighFunctions::CumulativeOverload(
                averageNumberOfWaves, *representativeWaveRunup2P, _fixedNumberOfWaves, verticalDistanceWaterLevelElevation,
                GetCriticalFrontVelocity(), GetIncreasedLoadTransitionAlphaM(), GetReducedStrengthTransitionAlphaS(), _frontVelocityCu,
                Constants::GetGravitationalAcceleration()));

            incrementDamage = GrassRevetmentWaveRunupFunctions::IncrementDamage(*cumulativeOverload, GetCriticalCumulativeOverload());

            damage = RevetmentFunctions::Damage(incrementDamage, initialDamage);

            const auto failureNumber = GetFailureNumber();

            if (RevetmentFunctions::FailureRevetment(damage, initialDamage, failureNumber))
            {
                const auto durationInTimeStepFailure = RevetmentFunctions::DurationInTimeStepFailure(incrementTime, incrementDamage, failureNumber,
                    initialDamage);

                timeOfFailure = make_unique<int>(RevetmentFunctions::TimeOfFailure(durationInTimeStepFailure, beginTime));
            }
        }

        return make_unique<GrassRevetmentWaveRunupRayleighTimeDependentOutput>(incrementDamage, damage, move(timeOfFailure),
                                                                               verticalDistanceWaterLevelElevation, move(waveAngleImpact),
                                                                               move(representativeWaveRunup2P), move(cumulativeOverload));
    }
}
