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
#include "GrassRevetmentWaveRunupRayleighLocationDependentOutput.h"
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
    using namespace Util;

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

    unique_ptr<LocationDependentOutput> GrassRevetmentWaveRunupRayleighLocationDependentInput::GetLocationDependentOutput(
        vector<unique_ptr<TimeDependentOutput>> timeDependentOutputItems)
    {
        return make_unique<GrassRevetmentWaveRunupRayleighLocationDependentOutput>(GetZ(), move(timeDependentOutputItems));
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
            GrassRevetmentWaveRunupRepresentative2PInput representativeWaveRunup2PInput{};
            representativeWaveRunup2PInput._surfSimilarityParameter = surfSimilarityParameter;
            representativeWaveRunup2PInput._waveAngleImpact = *waveAngleImpact;
            representativeWaveRunup2PInput._waveHeightHm0 = timeDependentInput.GetWaveHeightHm0();
            representativeWaveRunup2PInput._representativeWaveRunup2PGammab = representative2P.GetGammab();
            representativeWaveRunup2PInput._representativeWaveRunup2PGammaf = representative2P.GetGammaf();
            representativeWaveRunup2PInput._representativeWaveRunup2PAru = representative2P.GetRepresentative2PAru();
            representativeWaveRunup2PInput._representativeWaveRunup2PBru = representative2P.GetRepresentative2PBru();
            representativeWaveRunup2PInput._representativeWaveRunup2PCru = representative2P.GetRepresentative2PCru();

            representativeWaveRunup2P = make_unique<double>(
                GrassRevetmentWaveRunupFunctions::RepresentativeWaveRunup2P(representativeWaveRunup2PInput));

            GrassRevetmentWaveRunupRayleighCumulativeOverloadInput cumulativeOverloadInput{};
            cumulativeOverloadInput._averageNumberOfWaves = averageNumberOfWaves;
            cumulativeOverloadInput._representativeWaveRunup2P = *representativeWaveRunup2P;
            cumulativeOverloadInput._fixedNumberOfWaves = _fixedNumberOfWaves;
            cumulativeOverloadInput._verticalDistanceWaterLevelElevation = verticalDistanceWaterLevelElevation;
            cumulativeOverloadInput._criticalFrontVelocity = GetCriticalFrontVelocity();
            cumulativeOverloadInput._increasedLoadTransitionAlphaM = GetIncreasedLoadTransitionAlphaM();
            cumulativeOverloadInput._reducedStrengthTransitionAlphaS = GetReducedStrengthTransitionAlphaS();
            cumulativeOverloadInput._frontVelocityCu = _frontVelocityCu;
            cumulativeOverloadInput._gravitationalAcceleration = Constants::GetGravitationalAcceleration();

            cumulativeOverload = make_unique<double>(GrassRevetmentWaveRunupRayleighFunctions::CumulativeOverload(cumulativeOverloadInput));

            incrementDamage = GrassRevetmentWaveRunupFunctions::IncrementDamage(*cumulativeOverload, GetCriticalCumulativeOverload());

            damage = RevetmentFunctions::Damage(incrementDamage, initialDamage);

            if (const auto failureNumber = GetFailureNumber(); RevetmentFunctions::FailureRevetment(damage, initialDamage, failureNumber))
            {
                const auto durationInTimeStepFailure = RevetmentFunctions::DurationInTimeStepFailure(incrementTime, incrementDamage, failureNumber,
                    initialDamage);

                timeOfFailure = make_unique<int>(RevetmentFunctions::TimeOfFailure(durationInTimeStepFailure, beginTime));
            }
        }

        GrassRevetmentWaveRunupRayleighTimeDependentOutputConstructionProperties constructionProperties;
        constructionProperties._incrementDamage = make_unique<double>(incrementDamage);
        constructionProperties._damage = make_unique<double>(damage);
        constructionProperties._timeOfFailure = move(timeOfFailure);
        constructionProperties._verticalDistanceWaterLevelElevation = make_unique<double>(verticalDistanceWaterLevelElevation);
        constructionProperties._waveAngleImpact = move(waveAngleImpact);
        constructionProperties._representativeWaveRunup2P = move(representativeWaveRunup2P);
        constructionProperties._cumulativeOverload = move(cumulativeOverload);

        return make_unique<GrassRevetmentWaveRunupRayleighTimeDependentOutput>(constructionProperties);
    }
}
