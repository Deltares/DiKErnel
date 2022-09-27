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

#include "NaturalStoneRevetmentLocationDependentInput.h"

#include "CharacteristicPointsHelper.h"
#include "Constants.h"
#include "HydraulicLoadFunctions.h"
#include "NaturalStoneRevetmentFunctions.h"
#include "NaturalStoneRevetmentHydraulicLoadInput.h"
#include "NaturalStoneRevetmentLocationDependentOutput.h"
#include "NaturalStoneRevetmentTimeDependentOutput.h"
#include "NaturalStoneRevetmentValidator.h"
#include "RevetmentFunctions.h"
#include "TimeDependentInput.h"
#include "ValidationHelper.h"

namespace DiKErnel::Integration
{
    using namespace Core;
    using namespace DomainLibrary;
    using namespace FunctionLibrary;
    using namespace std;
    using namespace Util;

    NaturalStoneRevetmentLocationDependentInput::NaturalStoneRevetmentLocationDependentInput(
        const double x,
        const double initialDamage,
        const double failureNumber,
        const double relativeDensity,
        const double thicknessTopLayer,
        unique_ptr<NaturalStoneRevetmentHydraulicLoads> hydraulicLoads,
        unique_ptr<NaturalStoneRevetmentSlope> slope,
        unique_ptr<NaturalStoneRevetmentUpperLimitLoading> upperLimitLoading,
        unique_ptr<NaturalStoneRevetmentLowerLimitLoading> lowerLimitLoading,
        unique_ptr<NaturalStoneRevetmentDistanceMaximumWaveElevation> distanceMaximumWaveElevation,
        unique_ptr<NaturalStoneRevetmentNormativeWidthOfWaveImpact> normativeWidthOfWaveImpact,
        unique_ptr<NaturalStoneRevetmentWaveAngleImpact> waveAngleImpact)
        : LocationDependentInput(x, initialDamage, failureNumber),
          _relativeDensity(relativeDensity),
          _thicknessTopLayer(thicknessTopLayer),
          _hydraulicLoadsInput(move(hydraulicLoads)),
          _slopeInput(move(slope)),
          _upperLimitLoadingInput(move(upperLimitLoading)),
          _lowerLimitLoadingInput(move(lowerLimitLoading)),
          _distanceMaximumWaveElevationInput(move(distanceMaximumWaveElevation)),
          _normativeWidthOfWaveImpactInput(move(normativeWidthOfWaveImpact)),
          _waveAngleImpactInput(move(waveAngleImpact)) {}

    double NaturalStoneRevetmentLocationDependentInput::GetRelativeDensity() const
    {
        return _relativeDensity;
    }

    double NaturalStoneRevetmentLocationDependentInput::GetThicknessTopLayer() const
    {
        return _thicknessTopLayer;
    }

    NaturalStoneRevetmentHydraulicLoads& NaturalStoneRevetmentLocationDependentInput::GetHydraulicLoads() const
    {
        return *_hydraulicLoadsInput;
    }

    NaturalStoneRevetmentSlope& NaturalStoneRevetmentLocationDependentInput::GetSlope() const
    {
        return *_slopeInput;
    }

    NaturalStoneRevetmentUpperLimitLoading& NaturalStoneRevetmentLocationDependentInput::GetUpperLimitLoading() const
    {
        return *_upperLimitLoadingInput;
    }

    NaturalStoneRevetmentLowerLimitLoading& NaturalStoneRevetmentLocationDependentInput::GetLowerLimitLoading() const
    {
        return *_lowerLimitLoadingInput;
    }

    NaturalStoneRevetmentDistanceMaximumWaveElevation& NaturalStoneRevetmentLocationDependentInput::GetDistanceMaximumWaveElevation() const
    {
        return *_distanceMaximumWaveElevationInput;
    }

    NaturalStoneRevetmentNormativeWidthOfWaveImpact& NaturalStoneRevetmentLocationDependentInput::GetNormativeWidthOfWaveImpact() const
    {
        return *_normativeWidthOfWaveImpactInput;
    }

    NaturalStoneRevetmentWaveAngleImpact& NaturalStoneRevetmentLocationDependentInput::GetWaveAngleImpact() const
    {
        return *_waveAngleImpactInput;
    }

    bool NaturalStoneRevetmentLocationDependentInput::Validate(
        const vector<reference_wrapper<ITimeDependentInput>>& timeDependentInputs,
        const IProfileData& profileData) const
    {
        const auto baseValidationSuccessful = LocationDependentInput::Validate(timeDependentInputs, profileData);

        vector<unique_ptr<ValidationIssue>> validationIssues;
        validationIssues.emplace_back(NaturalStoneRevetmentValidator::RelativeDensity(_relativeDensity));
        validationIssues.emplace_back(NaturalStoneRevetmentValidator::ThicknessTopLayer(_thicknessTopLayer));
        validationIssues.emplace_back(NaturalStoneRevetmentValidator::SlopeUpperLevelAus(_slopeInput->GetUpperLevelAus()));
        validationIssues.emplace_back(NaturalStoneRevetmentValidator::SlopeLowerLevelAls(_slopeInput->GetLowerLevelAls()));

        return ValidationHelper::RegisterValidationIssues(validationIssues) && baseValidationSuccessful;
    }

    unique_ptr<LocationDependentOutput> NaturalStoneRevetmentLocationDependentInput::GetLocationDependentOutput(
        vector<unique_ptr<TimeDependentOutput>> timeDependentOutputItems)
    {
        return make_unique<NaturalStoneRevetmentLocationDependentOutput>(move(timeDependentOutputItems), GetZ());
    }

    void NaturalStoneRevetmentLocationDependentInput::InitializeDerivedLocationDependentInput(
        const IProfileData& profileData)
    {
        LocationDependentInput::InitializeDerivedLocationDependentInput(profileData);

        const auto& characteristicPoints = profileData.GetCharacteristicPoints();

        _outerToeHeight = CharacteristicPointsHelper::GetCoordinatesForType(characteristicPoints, CharacteristicPointType::OuterToe)->second;
        _outerCrestHeight = CharacteristicPointsHelper::GetCoordinatesForType(characteristicPoints, CharacteristicPointType::OuterCrest)->second;
        _notchOuterBerm = CharacteristicPointsHelper::GetCoordinatesForType(characteristicPoints, CharacteristicPointType::NotchOuterBerm);
        _crestOuterBerm = CharacteristicPointsHelper::GetCoordinatesForType(characteristicPoints, CharacteristicPointType::CrestOuterBerm);

        _resistance = NaturalStoneRevetmentFunctions::Resistance(_relativeDensity, _thicknessTopLayer);
    }

    unique_ptr<TimeDependentOutput> NaturalStoneRevetmentLocationDependentInput::CalculateTimeDependentOutput(
        const double initialDamage,
        const ITimeDependentInput& timeDependentInput,
        const IProfileData& profileData)
    {
        const auto waterLevel = timeDependentInput.GetWaterLevel();
        const auto waveHeightHm0 = timeDependentInput.GetWaveHeightHm0();
        const auto wavePeriodTm10 = timeDependentInput.GetWavePeriodTm10();

        _outerSlope = CalculateOuterSlope(waterLevel, waveHeightHm0, profileData);

        const auto slopeAngle = HydraulicLoadFunctions::SlopeAngle(_outerSlope);

        _waveSteepnessDeepWater = HydraulicLoadFunctions::WaveSteepnessDeepWater(waveHeightHm0, wavePeriodTm10,
                                                                                 Constants::GetGravitationalAcceleration());

        _distanceMaximumWaveElevation = NaturalStoneRevetmentFunctions::DistanceMaximumWaveElevation(
            1.0, _waveSteepnessDeepWater, waveHeightHm0, _distanceMaximumWaveElevationInput->GetDistanceMaximumWaveElevationAsmax(),
            _distanceMaximumWaveElevationInput->GetDistanceMaximumWaveElevationBsmax());

        _surfSimilarityParameter = HydraulicLoadFunctions::SurfSimilarityParameter(_outerSlope, waveHeightHm0, wavePeriodTm10,
                                                                                   Constants::GetGravitationalAcceleration());

        _normativeWidthWaveImpact = NaturalStoneRevetmentFunctions::NormativeWidthWaveImpact(
            _surfSimilarityParameter, waveHeightHm0, _normativeWidthOfWaveImpactInput->GetNormativeWidthOfWaveImpactAwi(),
            _normativeWidthOfWaveImpactInput->GetNormativeWidthOfWaveImpactBwi());

        _depthMaximumWaveLoad = NaturalStoneRevetmentFunctions::DepthMaximumWaveLoad(_distanceMaximumWaveElevation, _normativeWidthWaveImpact,
                                                                                     slopeAngle);

        _loadingRevetment = CalculateLoadingRevetment(_depthMaximumWaveLoad, _surfSimilarityParameter, waterLevel, waveHeightHm0);

        auto incrementDamage = 0.0;
        auto damage = initialDamage;
        unique_ptr<int> timeOfFailure = nullptr;

        if (_loadingRevetment)
        {
            _hydraulicLoad = CalculateHydraulicLoad(_surfSimilarityParameter, waveHeightHm0);

            _waveAngleImpact = NaturalStoneRevetmentFunctions::WaveAngleImpact(timeDependentInput.GetWaveAngle(),
                                                                               _waveAngleImpactInput->GetBetamax());
            _referenceDegradation = NaturalStoneRevetmentFunctions::ReferenceDegradation(
                _resistance, _hydraulicLoad, _waveAngleImpact, initialDamage);
            _referenceTimeDegradation = NaturalStoneRevetmentFunctions::ReferenceTimeDegradation(_referenceDegradation, wavePeriodTm10);

            const auto incrementTime = RevetmentFunctions::IncrementTime(timeDependentInput.GetBeginTime(), timeDependentInput.GetEndTime());
            const auto incrementDegradation = NaturalStoneRevetmentFunctions::IncrementDegradation(
                _referenceTimeDegradation, incrementTime, wavePeriodTm10);

            incrementDamage = NaturalStoneRevetmentFunctions::IncrementDamage(_hydraulicLoad, _resistance, incrementDegradation, _waveAngleImpact);
            damage = RevetmentFunctions::Damage(incrementDamage, initialDamage);

            if (const auto failureNumber = GetFailureNumber(); RevetmentFunctions::FailureRevetment(damage, initialDamage, failureNumber))
            {
                timeOfFailure = make_unique<int>(CalculateTimeOfFailure(failureNumber, wavePeriodTm10, timeDependentInput.GetBeginTime()));
            }
        }

        return make_unique<NaturalStoneRevetmentTimeDependentOutput>(*CreateConstructionProperties(incrementDamage, damage, move(timeOfFailure)));
    }

    double NaturalStoneRevetmentLocationDependentInput::CalculateOuterSlope(
        const double waterLevel,
        const double waveHeightHm0,
        const IProfileData& profileData)
    {
        const auto& naturalStoneRevetmentSlope = GetSlope();

        _slopeUpperLevel = NaturalStoneRevetmentFunctions::SlopeUpperLevel(_outerToeHeight, _outerCrestHeight, waterLevel, waveHeightHm0,
                                                                           naturalStoneRevetmentSlope.GetUpperLevelAus());
        _slopeUpperPosition = profileData.InterpolationHorizontalPosition(_slopeUpperLevel);
        _slopeLowerLevel = NaturalStoneRevetmentFunctions::SlopeLowerLevel(_outerToeHeight, _slopeUpperLevel, waveHeightHm0,
                                                                           naturalStoneRevetmentSlope.GetLowerLevelAls());
        _slopeLowerPosition = profileData.InterpolationHorizontalPosition(_slopeLowerLevel);

        NaturalStoneRevetmentOuterSlopeInput outerSlopeInput
        {
            ._slopeLowerPosition = _slopeLowerPosition,
            ._slopeLowerLevel = _slopeLowerLevel,
            ._slopeUpperPosition = _slopeUpperPosition,
            ._slopeUpperLevel = _slopeUpperLevel,
            ._outerToeHeight = _outerToeHeight,
            ._outerCrestHeight = _outerCrestHeight
        };

        if (_notchOuterBerm != nullptr && _crestOuterBerm != nullptr)
        {
            outerSlopeInput._notchOuterBermPosition = _notchOuterBerm->first;
            outerSlopeInput._notchOuterBermHeight = _notchOuterBerm->second;
            outerSlopeInput._crestOuterBermPosition = _crestOuterBerm->first;
            outerSlopeInput._crestOuterBermHeight = _crestOuterBerm->second;
        }

        return NaturalStoneRevetmentFunctions::OuterSlope(outerSlopeInput);
    }

    bool NaturalStoneRevetmentLocationDependentInput::CalculateLoadingRevetment(
        const double depthMaximumWaveLoad,
        const double surfSimilarityParameter,
        const double waterLevel,
        const double waveHeightHm0)
    {
        NaturalStoneRevetmentLimitLoadingInput limitLoadingInput
        {
            ._depthMaximumWaveLoad = depthMaximumWaveLoad,
            ._surfSimilarityParameter = surfSimilarityParameter,
            ._waterLevel = waterLevel,
            ._waveHeightHm0 = waveHeightHm0,
            ._a = _lowerLimitLoadingInput->GetLowerLimitAll(),
            ._b = _lowerLimitLoadingInput->GetLowerLimitBll(),
            ._c = _lowerLimitLoadingInput->GetLowerLimitCll()
        };

        _lowerLimitLoading = NaturalStoneRevetmentFunctions::LowerLimitLoading(limitLoadingInput);

        limitLoadingInput._a = _upperLimitLoadingInput->GetUpperLimitAul();
        limitLoadingInput._b = _upperLimitLoadingInput->GetUpperLimitBul();
        limitLoadingInput._c = _upperLimitLoadingInput->GetUpperLimitCul();

        _upperLimitLoading = NaturalStoneRevetmentFunctions::UpperLimitLoading(limitLoadingInput);
        return HydraulicLoadFunctions::LoadingRevetment(_lowerLimitLoading, _upperLimitLoading, GetZ());
    }

    double NaturalStoneRevetmentLocationDependentInput::CalculateHydraulicLoad(
        const double surfSimilarityParameter,
        const double waveHeightHm0) const
    {
        NaturalStoneRevetmentHydraulicLoadInput hydraulicLoadInput
        {
            ._surfSimilarityParameter = surfSimilarityParameter,
            ._waveHeightHm0 = waveHeightHm0
        };

        const auto usePlungingBreakers = _hydraulicLoadsInput->GetHydraulicLoadXib() >= surfSimilarityParameter;
        hydraulicLoadInput._a = usePlungingBreakers
                                    ? _hydraulicLoadsInput->GetHydraulicLoadAp()
                                    : _hydraulicLoadsInput->GetHydraulicLoadAs();
        hydraulicLoadInput._b = usePlungingBreakers
                                    ? _hydraulicLoadsInput->GetHydraulicLoadBp()
                                    : _hydraulicLoadsInput->GetHydraulicLoadBs();
        hydraulicLoadInput._c = usePlungingBreakers
                                    ? _hydraulicLoadsInput->GetHydraulicLoadCp()
                                    : _hydraulicLoadsInput->GetHydraulicLoadCs();
        hydraulicLoadInput._n = usePlungingBreakers
                                    ? _hydraulicLoadsInput->GetHydraulicLoadNp()
                                    : _hydraulicLoadsInput->GetHydraulicLoadNs();

        return NaturalStoneRevetmentFunctions::HydraulicLoad(hydraulicLoadInput);
    }

    int NaturalStoneRevetmentLocationDependentInput::CalculateTimeOfFailure(
        const double failureNumber,
        const double wavePeriodTm10,
        const double beginTime) const
    {
        const auto referenceFailure = NaturalStoneRevetmentFunctions::ReferenceFailure(
            _resistance, _hydraulicLoad, _waveAngleImpact, failureNumber);
        const auto referenceTimeFailure = NaturalStoneRevetmentFunctions::ReferenceTimeFailure(referenceFailure, wavePeriodTm10);
        const auto durationInTimeStepFailure = NaturalStoneRevetmentFunctions::DurationInTimeStepFailure(
            referenceTimeFailure, _referenceTimeDegradation);

        return RevetmentFunctions::TimeOfFailure(durationInTimeStepFailure, beginTime);
    }

    unique_ptr<NaturalStoneRevetmentTimeDependentOutputConstructionProperties> NaturalStoneRevetmentLocationDependentInput::
    CreateConstructionProperties(
        double incrementDamage,
        double damage,
        unique_ptr<int> timeOfFailure)
    {
        auto constructionProperties = make_unique<NaturalStoneRevetmentTimeDependentOutputConstructionProperties>();
        constructionProperties->_incrementDamage = make_unique<double>(incrementDamage);
        constructionProperties->_damage = make_unique<double>(damage);
        constructionProperties->_timeOfFailure = move(timeOfFailure);
        constructionProperties->_outerSlope = make_unique<double>(_outerSlope);
        constructionProperties->_slopeUpperLevel = make_unique<double>(_slopeUpperLevel);
        constructionProperties->_slopeUpperPosition = make_unique<double>(_slopeUpperPosition);
        constructionProperties->_slopeLowerLevel = make_unique<double>(_slopeLowerLevel);
        constructionProperties->_slopeLowerPosition = make_unique<double>(_slopeLowerPosition);
        constructionProperties->_loadingRevetment = make_unique<bool>(_loadingRevetment);
        constructionProperties->_surfSimilarityParameter = make_unique<double>(_surfSimilarityParameter);
        constructionProperties->_waveSteepnessDeepWater = make_unique<double>(_waveSteepnessDeepWater);
        constructionProperties->_upperLimitLoading = make_unique<double>(_upperLimitLoading);
        constructionProperties->_lowerLimitLoading = make_unique<double>(_lowerLimitLoading);
        constructionProperties->_depthMaximumWaveLoad = make_unique<double>(_depthMaximumWaveLoad);
        constructionProperties->_distanceMaximumWaveElevation = make_unique<double>(_distanceMaximumWaveElevation);
        constructionProperties->_normativeWidthOfWaveImpact = make_unique<double>(_normativeWidthWaveImpact);

        if (_loadingRevetment)
        {
            constructionProperties->_hydraulicLoad = make_unique<double>(_hydraulicLoad);
            constructionProperties->_waveAngleImpact = make_unique<double>(_waveAngleImpact);
            constructionProperties->_resistance = make_unique<double>(_resistance);
            constructionProperties->_referenceTimeDegradation = make_unique<double>(_referenceTimeDegradation);
            constructionProperties->_referenceDegradation = make_unique<double>(_referenceDegradation);
        }

        return constructionProperties;
    }
}
