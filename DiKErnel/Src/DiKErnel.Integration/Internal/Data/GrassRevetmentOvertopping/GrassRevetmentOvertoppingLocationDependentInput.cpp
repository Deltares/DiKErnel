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

#include "GrassRevetmentOvertoppingLocationDependentInput.h"

#include "Constants.h"
#include "GrassRevetmentFunctions.h"
#include "GrassRevetmentOvertoppingFunctions.h"
#include "GrassRevetmentWaveRunupRayleighLocationDependentOutput.h"
#include "GrassRevetmentWaveRunupRayleighTimeDependentOutput.h"
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

    GrassRevetmentOvertoppingLocationDependentInput::GrassRevetmentOvertoppingLocationDependentInput(
        const double x,
        const double initialDamage,
        const double failureNumber,
        const double criticalCumulativeOverload,
        const double criticalFrontVelocity,
        const double increasedLoadTransitionAlphaM,
        const double reducedStrengthTransitionAlphaS,
        const double averageNumberOfWavesCtm,
        const int fixedNumberOfWaves,
        const double frontVelocityCwo,
        function<double()>& getAccelerationAlphaA,
        function<double(
            const IProfileData&)>& getDikeHeight)
        : LocationDependentInput(x, initialDamage, failureNumber),
          _criticalCumulativeOverload(criticalCumulativeOverload),
          _criticalFrontVelocity(criticalFrontVelocity),
          _increasedLoadTransitionAlphaM(increasedLoadTransitionAlphaM),
          _reducedStrengthTransitionAlphaS(reducedStrengthTransitionAlphaS),
          _averageNumberOfWavesCtm(averageNumberOfWavesCtm),
          _fixedNumberOfWaves(fixedNumberOfWaves),
          _frontVelocityCwo(frontVelocityCwo),
          _getAccelerationAlphaA(move(getAccelerationAlphaA)),
          _getDikeHeight(move(getDikeHeight)) {}

    double GrassRevetmentOvertoppingLocationDependentInput::GetCriticalCumulativeOverload() const
    {
        return _criticalCumulativeOverload;
    }

    double GrassRevetmentOvertoppingLocationDependentInput::GetCriticalFrontVelocity() const
    {
        return _criticalFrontVelocity;
    }

    double GrassRevetmentOvertoppingLocationDependentInput::GetIncreasedLoadTransitionAlphaM() const
    {
        return _increasedLoadTransitionAlphaM;
    }

    double GrassRevetmentOvertoppingLocationDependentInput::GetReducedStrengthTransitionAlphaS() const
    {
        return _reducedStrengthTransitionAlphaS;
    }

    double GrassRevetmentOvertoppingLocationDependentInput::GetAverageNumberOfWavesCtm() const
    {
        return _averageNumberOfWavesCtm;
    }

    int GrassRevetmentOvertoppingLocationDependentInput::GetFixedNumberOfWaves() const
    {
        return _fixedNumberOfWaves;
    }

    double GrassRevetmentOvertoppingLocationDependentInput::GetFrontVelocityCwo() const
    {
        return _frontVelocityCwo;
    }

    bool GrassRevetmentOvertoppingLocationDependentInput::Validate(
        const IProfileData& profileData) const
    {
        const auto baseValidationSuccessful = LocationDependentInput::Validate(profileData);

        vector<unique_ptr<ValidationIssue>> validationIssues;
        validationIssues.emplace_back(make_unique<ValidationIssue>(ValidationIssueType::Error, "TODO: Implement additional validation"));

        return ValidationHelper::RegisterValidationIssues(validationIssues) && baseValidationSuccessful;
    }

    unique_ptr<LocationDependentOutput> GrassRevetmentOvertoppingLocationDependentInput::GetLocationDependentOutput(
        vector<unique_ptr<TimeDependentOutput>> timeDependentOutputItems)
    {
        return make_unique<GrassRevetmentWaveRunupRayleighLocationDependentOutput>(GetZ(), move(timeDependentOutputItems));
    }

    unique_ptr<TimeDependentOutput> GrassRevetmentOvertoppingLocationDependentInput::CalculateTimeDependentOutput(
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

            constexpr double waveDirection = 0.0;
            vector<double> xValuesProfile;
            vector<double> zValuesProfile;
            vector<double> roughnessCoefficients;

            _representativeWaveRunup2P = CalculateRepresentativeWaveRunup2P(timeDependentInput.GetWaterLevel(),
                                                                            timeDependentInput.GetWaveHeightHm0(),
                                                                            timeDependentInput.GetWavePeriodTm10(),
                                                                            waveDirection,
                                                                            xValuesProfile,
                                                                            zValuesProfile,
                                                                            roughnessCoefficients);

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

    double GrassRevetmentOvertoppingLocationDependentInput::CalculateRepresentativeWaveRunup2P(
        const double waterLevel,
        const double waveHeightHm0,
        const double wavePeriodTm10,
        const double waveDirection,
        vector<double>& xValuesProfile,
        vector<double>& zValuesProfile,
        vector<double>& roughnessCoefficients) const
    {
        const GrassRevetmentOvertoppingRepresentative2PInput representativeWaveRunup2PInput
        {
            ._waterLevel = waterLevel,
            ._waveHeightHm0 = waveHeightHm0,
            ._wavePeriodTm10 = wavePeriodTm10,
            ._waveDirection = waveDirection,
            ._xValuesProfile = xValuesProfile,
            ._zValuesProfile = zValuesProfile,
            ._roughnessCoefficients = roughnessCoefficients,
            ._dikeHeight = _dikeHeight
        };

        return GrassRevetmentOvertoppingFunctions::RepresentativeWaveRunup2P(representativeWaveRunup2PInput);
    }

    double GrassRevetmentOvertoppingLocationDependentInput::CalculateCumulativeOverload(
        const double averageNumberOfWaves) const
    {
        GrassRevetmentOvertoppingCumulativeOverloadInput cumulativeOverloadInput
        {
            ._accelerationAlphaA = _accelerationAlphaA,
            ._frontVelocityCwo = _frontVelocityCwo
        };

        cumulativeOverloadInput._averageNumberOfWaves = averageNumberOfWaves;
        cumulativeOverloadInput._representativeWaveRunup2P = _representativeWaveRunup2P;
        cumulativeOverloadInput._fixedNumberOfWaves = _fixedNumberOfWaves;
        cumulativeOverloadInput._verticalDistanceWaterLevelElevation = _verticalDistanceWaterLevelElevation;
        cumulativeOverloadInput._criticalFrontVelocity = GetCriticalFrontVelocity();
        cumulativeOverloadInput._increasedLoadTransitionAlphaM = GetIncreasedLoadTransitionAlphaM();
        cumulativeOverloadInput._reducedStrengthTransitionAlphaS = GetReducedStrengthTransitionAlphaS();
        cumulativeOverloadInput._gravitationalAcceleration = Constants::GetGravitationalAcceleration();

        return GrassRevetmentOvertoppingFunctions::CumulativeOverload(cumulativeOverloadInput);
    }

    unique_ptr<GrassRevetmentWaveRunupRayleighTimeDependentOutputConstructionProperties>
    GrassRevetmentOvertoppingLocationDependentInput::CreateConstructionProperties(
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
            constructionProperties->_representativeWaveRunup2P = make_unique<double>(_representativeWaveRunup2P);
            constructionProperties->_cumulativeOverload = make_unique<double>(_cumulativeOverload);
        }

        return constructionProperties;
    }
}
