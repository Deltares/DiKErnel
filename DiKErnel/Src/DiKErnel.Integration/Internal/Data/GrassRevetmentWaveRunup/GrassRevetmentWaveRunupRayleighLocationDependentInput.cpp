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
#include "GrassRevetmentFunctions.h"
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

        _verticalDistanceWaterLevelElevation = HydraulicLoadFunctions::VerticalDistanceWaterLevelElevation(
            GetZ(), timeDependentInput.GetWaterLevel());

        if (_verticalDistanceWaterLevelElevation > 0)
        {
            const auto beginTime = timeDependentInput.GetBeginTime();

            const auto incrementTime = RevetmentFunctions::IncrementTime(beginTime, timeDependentInput.GetEndTime());
            const auto averageNumberOfWaves = RevetmentFunctions::AverageNumberOfWaves(incrementTime, timeDependentInput.GetWavePeriodTm10(),
                                                                                       GetAverageNumberOfWavesCtm());

            const auto surfSimilarityParameter = HydraulicLoadFunctions::SurfSimilarityParameter(GetOuterSlope(),
                                                                                                 timeDependentInput.GetWaveHeightHm0(),
                                                                                                 timeDependentInput.GetWavePeriodTm10(),
                                                                                                 Constants::GetGravitationalAcceleration());

            _waveAngleImpact = GrassRevetmentWaveRunupFunctions::WaveAngleImpact(timeDependentInput.GetWaveAngle(), GetWaveAngleImpact().GetAbeta(),
                                                                                 GetWaveAngleImpact().GetBetamax());

            _representativeWaveRunup2P = CalculateRepresentativeWaveRunup2P(surfSimilarityParameter, timeDependentInput.GetWaveHeightHm0());
            _cumulativeOverload = CalculateCumulativeOverload(averageNumberOfWaves);

            incrementDamage = GrassRevetmentFunctions::IncrementDamage(_cumulativeOverload, GetCriticalCumulativeOverload());

            damage = RevetmentFunctions::Damage(incrementDamage, initialDamage);

            if (const auto failureNumber = GetFailureNumber(); RevetmentFunctions::FailureRevetment(damage, initialDamage, failureNumber))
            {
                const auto durationInTimeStepFailure = RevetmentFunctions::DurationInTimeStepFailure(incrementTime, incrementDamage, failureNumber,
                    initialDamage);

                timeOfFailure = make_unique<int>(RevetmentFunctions::TimeOfFailure(durationInTimeStepFailure, beginTime));
            }
        }

        return make_unique<GrassRevetmentWaveRunupRayleighTimeDependentOutput>(
            *CreateConstructionProperties(incrementDamage, damage, move(timeOfFailure)));
    }

    double GrassRevetmentWaveRunupRayleighLocationDependentInput::CalculateRepresentativeWaveRunup2P(
        const double surfSimilarityParameter,
        const double waveHeightHm0) const
    {
        const auto& representative2P = GetRepresentative2P();
        const GrassRevetmentWaveRunupRepresentative2PInput representativeWaveRunup2PInput
        {
            ._surfSimilarityParameter = surfSimilarityParameter,
            ._waveAngleImpact = _waveAngleImpact,
            ._waveHeightHm0 = waveHeightHm0,
            ._representativeWaveRunup2PGammab = representative2P.GetGammab(),
            ._representativeWaveRunup2PGammaf = representative2P.GetGammaf(),
            ._representativeWaveRunup2PAru = representative2P.GetRepresentative2PAru(),
            ._representativeWaveRunup2PBru = representative2P.GetRepresentative2PBru(),
            ._representativeWaveRunup2PCru = representative2P.GetRepresentative2PCru()
        };

        return GrassRevetmentWaveRunupFunctions::RepresentativeWaveRunup2P(representativeWaveRunup2PInput);
    }

    double GrassRevetmentWaveRunupRayleighLocationDependentInput::CalculateCumulativeOverload(
        const double averageNumberOfWaves) const
    {
        const GrassRevetmentWaveRunupRayleighCumulativeOverloadInput cumulativeOverloadInput
        {
            ._averageNumberOfWaves = averageNumberOfWaves,
            ._representativeWaveRunup2P = _representativeWaveRunup2P,
            ._fixedNumberOfWaves = _fixedNumberOfWaves,
            ._verticalDistanceWaterLevelElevation = _verticalDistanceWaterLevelElevation,
            ._criticalFrontVelocity = GetCriticalFrontVelocity(),
            ._increasedLoadTransitionAlphaM = GetIncreasedLoadTransitionAlphaM(),
            ._reducedStrengthTransitionAlphaS = GetReducedStrengthTransitionAlphaS(),
            ._frontVelocityCu = _frontVelocityCu,
            ._gravitationalAcceleration = Constants::GetGravitationalAcceleration()
        };

        return GrassRevetmentWaveRunupRayleighFunctions::CumulativeOverload(cumulativeOverloadInput);
    }

    unique_ptr<GrassRevetmentWaveRunupRayleighTimeDependentOutputConstructionProperties>
    GrassRevetmentWaveRunupRayleighLocationDependentInput::CreateConstructionProperties(
        double incrementDamage,
        double damage,
        unique_ptr<int> timeOfFailure)
    {
        auto constructionProperties = make_unique<GrassRevetmentWaveRunupRayleighTimeDependentOutputConstructionProperties>();
        constructionProperties->_incrementDamage = make_unique<double>(incrementDamage);
        constructionProperties->_damage = make_unique<double>(damage);
        constructionProperties->_timeOfFailure = move(timeOfFailure);
        constructionProperties->_verticalDistanceWaterLevelElevation = make_unique<double>(_verticalDistanceWaterLevelElevation);

        if (_verticalDistanceWaterLevelElevation > 0)
        {
            constructionProperties->_waveAngleImpact = make_unique<double>(_waveAngleImpact);
            constructionProperties->_representativeWaveRunup2P = make_unique<double>(_representativeWaveRunup2P);
            constructionProperties->_cumulativeOverload = make_unique<double>(_cumulativeOverload);
        }

        return constructionProperties;
    }
}
