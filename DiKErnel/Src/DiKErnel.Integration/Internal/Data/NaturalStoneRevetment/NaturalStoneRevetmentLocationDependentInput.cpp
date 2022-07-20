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
          _hydraulicLoads(move(hydraulicLoads)),
          _slope(move(slope)),
          _upperLimitLoadingInput(move(upperLimitLoading)),
          _lowerLimitLoadingInput(move(lowerLimitLoading)),
          _distanceMaximumWaveElevation(move(distanceMaximumWaveElevation)),
          _normativeWidthOfWaveImpact(move(normativeWidthOfWaveImpact)),
          _waveAngleImpact(move(waveAngleImpact)) {}

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
        return *_hydraulicLoads;
    }

    NaturalStoneRevetmentSlope& NaturalStoneRevetmentLocationDependentInput::GetSlope() const
    {
        return *_slope;
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
        return *_distanceMaximumWaveElevation;
    }

    NaturalStoneRevetmentNormativeWidthOfWaveImpact& NaturalStoneRevetmentLocationDependentInput::GetNormativeWidthOfWaveImpact() const
    {
        return *_normativeWidthOfWaveImpact;
    }

    NaturalStoneRevetmentWaveAngleImpact& NaturalStoneRevetmentLocationDependentInput::GetWaveAngleImpact() const
    {
        return *_waveAngleImpact;
    }

    bool NaturalStoneRevetmentLocationDependentInput::Validate(
        const IProfileData& profileData) const
    {
        const auto baseValidationSuccessful = LocationDependentInput::Validate(profileData);

        vector<unique_ptr<ValidationIssue>> validationIssues;
        validationIssues.emplace_back(NaturalStoneRevetmentValidator::RelativeDensity(_relativeDensity));
        validationIssues.emplace_back(NaturalStoneRevetmentValidator::ThicknessTopLayer(_thicknessTopLayer));
        validationIssues.emplace_back(NaturalStoneRevetmentValidator::SlopeUpperLevelAus(_slope->GetUpperLevelAus()));
        validationIssues.emplace_back(NaturalStoneRevetmentValidator::SlopeLowerLevelAls(_slope->GetLowerLevelAls()));

        return ValidationHelper::RegisterValidationIssues(validationIssues) && baseValidationSuccessful;
    }

    unique_ptr<LocationDependentOutput> NaturalStoneRevetmentLocationDependentInput::GetLocationDependentOutput(
        vector<unique_ptr<TimeDependentOutput>> timeDependentOutputItems)
    {
        return make_unique<NaturalStoneRevetmentLocationDependentOutput>(GetZ(), move(timeDependentOutputItems));
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

        const auto outerSlope = CalculateOuterSlope(waterLevel, waveHeightHm0, profileData);
        const auto slopeAngle = HydraulicLoadFunctions::SlopeAngle(outerSlope);

        const auto waveSteepnessDeepWater = HydraulicLoadFunctions::WaveSteepnessDeepWater(
            waveHeightHm0, wavePeriodTm10, Constants::GetGravitationalAcceleration());

        const auto distanceMaximumWaveElevation = NaturalStoneRevetmentFunctions::DistanceMaximumWaveElevation(
            1.0, waveSteepnessDeepWater, waveHeightHm0, _distanceMaximumWaveElevation->GetDistanceMaximumWaveElevationAsmax(),
            _distanceMaximumWaveElevation->GetDistanceMaximumWaveElevationBsmax());

        const auto surfSimilarityParameter = HydraulicLoadFunctions::SurfSimilarityParameter(
            outerSlope, waveHeightHm0, wavePeriodTm10, Constants::GetGravitationalAcceleration());

        const auto normativeWidthWaveImpact = NaturalStoneRevetmentFunctions::NormativeWidthWaveImpact(
            surfSimilarityParameter, waveHeightHm0, _normativeWidthOfWaveImpact->GetNormativeWidthOfWaveImpactAwi(),
            _normativeWidthOfWaveImpact->GetNormativeWidthOfWaveImpactBwi());

        const auto depthMaximumWaveLoad = NaturalStoneRevetmentFunctions::DepthMaximumWaveLoad(
            distanceMaximumWaveElevation, normativeWidthWaveImpact, slopeAngle);

        const auto loadingRevetment = CalculateLoadingRevetment(depthMaximumWaveLoad, surfSimilarityParameter, waterLevel, waveHeightHm0);

        auto incrementDamage = 0.0;
        auto damage = initialDamage;
        unique_ptr<int> timeOfFailure = nullptr;

        unique_ptr<double> hydraulicLoad = nullptr;
        unique_ptr<double> waveAngleImpact = nullptr;
        unique_ptr<double> referenceTimeDegradation = nullptr;
        unique_ptr<double> referenceDegradation = nullptr;

        if (loadingRevetment)
        {
            hydraulicLoad = make_unique<double>(CalculateHydraulicLoad(surfSimilarityParameter, waveHeightHm0));

            waveAngleImpact = make_unique<double>(NaturalStoneRevetmentFunctions::WaveAngleImpact(
                timeDependentInput.GetWaveAngle(), _waveAngleImpact->GetBetamax()));

            referenceDegradation = make_unique<double>(
                NaturalStoneRevetmentFunctions::ReferenceDegradation(_resistance, *hydraulicLoad, *waveAngleImpact, initialDamage));

            referenceTimeDegradation = make_unique<double>(
                NaturalStoneRevetmentFunctions::ReferenceTimeDegradation(*referenceDegradation, wavePeriodTm10));

            const auto incrementTime = RevetmentFunctions::IncrementTime(timeDependentInput.GetBeginTime(), timeDependentInput.GetEndTime());
            const auto incrementDegradation = NaturalStoneRevetmentFunctions::IncrementDegradation(
                *referenceTimeDegradation, incrementTime, wavePeriodTm10);

            incrementDamage = NaturalStoneRevetmentFunctions::IncrementDamage(*hydraulicLoad, _resistance, incrementDegradation, *waveAngleImpact);

            damage = RevetmentFunctions::Damage(incrementDamage, initialDamage);

            if (const auto failureNumber = GetFailureNumber(); RevetmentFunctions::FailureRevetment(damage, initialDamage, failureNumber))
            {
                const auto referenceFailure = NaturalStoneRevetmentFunctions::ReferenceFailure(
                    _resistance, *hydraulicLoad, *waveAngleImpact, failureNumber);
                const auto referenceTimeFailure = NaturalStoneRevetmentFunctions::ReferenceTimeFailure(referenceFailure, wavePeriodTm10);
                const auto durationInTimeStepFailure = NaturalStoneRevetmentFunctions::DurationInTimeStepFailure(
                    referenceTimeFailure, *referenceTimeDegradation);

                timeOfFailure = make_unique<int>(RevetmentFunctions::TimeOfFailure(durationInTimeStepFailure, timeDependentInput.GetBeginTime()));
            }
        }

        NaturalStoneRevetmentTimeDependentOutputConstructionProperties constructionProperties;
        constructionProperties._incrementDamage = make_unique<double>(incrementDamage);
        constructionProperties._damage = make_unique<double>(damage);
        constructionProperties._timeOfFailure = move(timeOfFailure);
        constructionProperties._outerSlope = make_unique<double>(outerSlope);
        constructionProperties._slopeUpperLevel = make_unique<double>(_slopeUpperLevel);
        constructionProperties._slopeUpperPosition = make_unique<double>(_slopeUpperPosition);
        constructionProperties._slopeLowerLevel = make_unique<double>(_slopeLowerLevel);
        constructionProperties._slopeLowerPosition = make_unique<double>(_slopeLowerPosition);
        constructionProperties._loadingRevetment = make_unique<bool>(loadingRevetment);
        constructionProperties._surfSimilarityParameter = make_unique<double>(surfSimilarityParameter);
        constructionProperties._waveSteepnessDeepWater = make_unique<double>(waveSteepnessDeepWater);
        constructionProperties._upperLimitLoading = make_unique<double>(_upperLimitLoading);
        constructionProperties._lowerLimitLoading = make_unique<double>(_lowerLimitLoading);
        constructionProperties._depthMaximumWaveLoad = make_unique<double>(depthMaximumWaveLoad);
        constructionProperties._distanceMaximumWaveElevation = make_unique<double>(distanceMaximumWaveElevation);
        constructionProperties._normativeWidthOfWaveImpact = make_unique<double>(normativeWidthWaveImpact);
        constructionProperties._hydraulicLoad = move(hydraulicLoad);
        constructionProperties._waveAngleImpact = move(waveAngleImpact);
        constructionProperties._resistance = loadingRevetment ? make_unique<double>(_resistance) : nullptr;
        constructionProperties._referenceTimeDegradation = move(referenceTimeDegradation);
        constructionProperties._referenceDegradation = move(referenceDegradation);

        return make_unique<NaturalStoneRevetmentTimeDependentOutput>(constructionProperties);
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

        NaturalStoneRevetmentOuterSlopeInput outerSlopeInput{};
        outerSlopeInput._slopeLowerPosition = _slopeLowerPosition;
        outerSlopeInput._slopeLowerLevel = _slopeLowerLevel;
        outerSlopeInput._slopeUpperPosition = _slopeUpperPosition;
        outerSlopeInput._slopeUpperLevel = _slopeUpperLevel;
        outerSlopeInput._outerToeHeight = _outerToeHeight;
        outerSlopeInput._outerCrestHeight = _outerCrestHeight;

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
        NaturalStoneRevetmentLimitLoadingInput limitLoadingInput{};
        limitLoadingInput._depthMaximumWaveLoad = depthMaximumWaveLoad;
        limitLoadingInput._surfSimilarityParameter = surfSimilarityParameter;
        limitLoadingInput._waterLevel = waterLevel;
        limitLoadingInput._waveHeightHm0 = waveHeightHm0;
        limitLoadingInput._a = _lowerLimitLoadingInput->GetLowerLimitAll();
        limitLoadingInput._b = _lowerLimitLoadingInput->GetLowerLimitBll();
        limitLoadingInput._c = _lowerLimitLoadingInput->GetLowerLimitCll();

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
        NaturalStoneRevetmentHydraulicLoadInput hydraulicLoadInput{};
        hydraulicLoadInput._surfSimilarityParameter = surfSimilarityParameter;
        hydraulicLoadInput._waveHeightHm0 = waveHeightHm0;

        const auto usePlungingBreakers = _hydraulicLoads->GetHydraulicLoadXib() >= surfSimilarityParameter;
        hydraulicLoadInput._a = usePlungingBreakers
                                    ? _hydraulicLoads->GetHydraulicLoadAp()
                                    : _hydraulicLoads->GetHydraulicLoadAs();
        hydraulicLoadInput._b = usePlungingBreakers
                                    ? _hydraulicLoads->GetHydraulicLoadBp()
                                    : _hydraulicLoads->GetHydraulicLoadBs();
        hydraulicLoadInput._c = usePlungingBreakers
                                    ? _hydraulicLoads->GetHydraulicLoadCp()
                                    : _hydraulicLoads->GetHydraulicLoadCs();
        hydraulicLoadInput._n = usePlungingBreakers
                                    ? _hydraulicLoads->GetHydraulicLoadNp()
                                    : _hydraulicLoads->GetHydraulicLoadNs();

        return NaturalStoneRevetmentFunctions::HydraulicLoad(hydraulicLoadInput);
    }
}
