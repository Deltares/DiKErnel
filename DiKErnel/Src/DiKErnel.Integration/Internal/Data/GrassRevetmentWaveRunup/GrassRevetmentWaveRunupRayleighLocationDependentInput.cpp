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

#include "GrassRevetmentWaveRunupRayleighLocationDependentInput.h"

#include "Constants.h"
#include "GrassRevetmentWaveRunup.h"
#include "GrassRevetmentWaveRunupRayleigh.h"
#include "GrassRevetmentWaveRunupRayleighTimeDependentOutput.h"
#include "HydraulicLoad.h"
#include "Revetment.h"

namespace DiKErnel::Integration
{
    using namespace Core;
    using namespace DomainLibrary;
    using namespace FunctionLibrary;
    using namespace std;

    GrassRevetmentWaveRunupRayleighLocationDependentInput::GrassRevetmentWaveRunupRayleighLocationDependentInput(
        string name,
        const double initialDamage,
        const double failureNumber,
        const double tanA,
        const double positionZ,
        const double criticalCumulativeOverload,
        const double criticalFrontVelocity,
        const double increasedLoadTransitionAlphaM,
        const double reducedStrengthTransitionAlphaS,
        const double averageNumberOfWavesCtm,
        unique_ptr<GrassRevetmentWaveRunupRepresentative2P> representative2P,
        unique_ptr<GrassRevetmentWaveRunupWaveAngleImpact> waveAngleImpact,
        const int fixedNumberOfWaves,
        const double frontVelocityCu)
        : GrassRevetmentWaveRunupLocationDependentInput(move(name), initialDamage, failureNumber, tanA, positionZ, criticalCumulativeOverload,
                                                        criticalFrontVelocity, increasedLoadTransitionAlphaM, reducedStrengthTransitionAlphaS,
                                                        averageNumberOfWavesCtm, move(representative2P), move(waveAngleImpact)),
          _fixedNumberOfWaves(fixedNumberOfWaves),
          _frontVelocityCu(frontVelocityCu) {}

    unique_ptr<TimeDependentOutput> GrassRevetmentWaveRunupRayleighLocationDependentInput::Calculate(
        const double initialDamage,
        const ITimeDependentInput& timeDependentInput)
    {
        const auto beginTime = timeDependentInput.GetBeginTime();

        const auto incrementTime = Revetment::IncrementTime(beginTime, timeDependentInput.GetEndTime());
        const auto averageNumberOfWaves = Revetment::AverageNumberOfWaves(incrementTime, timeDependentInput.GetWavePeriodTm10(),
                                                                          GetAverageNumberOfWavesCtm());

        const auto surfSimilarityParameter = HydraulicLoad::SurfSimilarityParameter(GetTanA(), timeDependentInput.GetWaveHeightHm0(),
                                                                                    timeDependentInput.GetWavePeriodTm10(),
                                                                                    Constants::GRAVITATIONAL_ACCELERATION);

        const auto waveAngleImpact = GrassRevetmentWaveRunup::WaveAngleImpact(timeDependentInput.GetWaveAngle(), GetWaveAngleImpact().GetAbeta(),
                                                                              GetWaveAngleImpact().GetBetamax());

        const auto& representative2P = GetRepresentative2P();
        const auto representativeWaveRunup2P = GrassRevetmentWaveRunup::RepresentativeWaveRunup2P(surfSimilarityParameter, waveAngleImpact,
            timeDependentInput.GetWaveHeightHm0(), representative2P.GetGammaB(), representative2P.GetGammaF(),
            representative2P.GetRepresentative2PAru(), representative2P.GetRepresentative2PBru(), representative2P.GetRepresentative2PCru());

        const auto cumulativeOverload = GrassRevetmentWaveRunupRayleigh::CumulativeOverload(averageNumberOfWaves, representativeWaveRunup2P,
                                                                                            _fixedNumberOfWaves, GetPositionZ(),
                                                                                            timeDependentInput.GetWaterLevel(),
                                                                                            GetCriticalFrontVelocity(),
                                                                                            GetIncreasedLoadTransitionAlphaM(),
                                                                                            GetReducedStrengthTransitionAlphaS(), _frontVelocityCu,
                                                                                            Constants::GRAVITATIONAL_ACCELERATION);

        const auto incrementDamage = GrassRevetmentWaveRunup::IncrementDamage(cumulativeOverload, GetCriticalCumulativeOverload());

        const auto damage = Revetment::Damage(incrementDamage, initialDamage);

        const auto failureNumber = GetFailureNumber();
        unique_ptr<int> timeOfFailure = nullptr;

        if (Revetment::FailureRevetment(damage, initialDamage, failureNumber))
        {
            const auto durationInTimeStepFailure = Revetment::DurationInTimeStepFailure(incrementTime, incrementDamage, failureNumber,
                                                                                        initialDamage);

            timeOfFailure = make_unique<int>(Revetment::TimeOfFailure(durationInTimeStepFailure, beginTime));
        }

        return make_unique<GrassRevetmentWaveRunupRayleighTimeDependentOutput>(incrementDamage, damage, move(timeOfFailure), waveAngleImpact,
                                                                               representativeWaveRunup2P, cumulativeOverload);
    }

    int GrassRevetmentWaveRunupRayleighLocationDependentInput::GetFixedNumberOfWaves() const
    {
        return _fixedNumberOfWaves;
    }

    double GrassRevetmentWaveRunupRayleighLocationDependentInput::GetFrontVelocityCu() const
    {
        return _frontVelocityCu;
    }
}
