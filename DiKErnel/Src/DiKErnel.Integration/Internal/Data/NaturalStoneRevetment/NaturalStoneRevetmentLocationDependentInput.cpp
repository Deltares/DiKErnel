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

#include "NaturalStoneRevetmentLocationDependentInput.h"

#include "Constants.h"
#include "HydraulicLoad.h"
#include "NaturalStoneRevetment.h"
#include "NaturalStoneRevetmentTimeDependentOutput.h"
#include "Revetment.h"
#include "TimeDependentInput.h"

namespace DiKErnel::Integration
{
    using namespace Core;
    using namespace DomainLibrary::Constants;
    using namespace FunctionLibrary;
    using namespace std;

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
          _upperLimitLoading(move(upperLimitLoading)),
          _lowerLimitLoading(move(lowerLimitLoading)),
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
        return *_upperLimitLoading;
    }

    NaturalStoneRevetmentLowerLimitLoading& NaturalStoneRevetmentLocationDependentInput::GetLowerLimitLoading() const
    {
        return *_lowerLimitLoading;
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

    void NaturalStoneRevetmentLocationDependentInput::InitializeDerivedLocationDependentInput(
        const IProfileData& profileData)
    {
        LocationDependentInput::InitializeDerivedLocationDependentInput(profileData);

        const auto& characteristicPoints = profileData.GetCharacteristicPoints();

        _outerToeHeight = GetCharacteristicPointCoordinates(characteristicPoints, CharacteristicPointType::OuterToe)->second;
        _outerCrestHeight = GetCharacteristicPointCoordinates(characteristicPoints, CharacteristicPointType::OuterCrest)->second;
        _notchOuterBerm = GetCharacteristicPointCoordinates(characteristicPoints, CharacteristicPointType::NotchOuterBerm);
        _crestOuterBerm = GetCharacteristicPointCoordinates(characteristicPoints, CharacteristicPointType::CrestOuterBerm);

        _resistance = NaturalStoneRevetment::Resistance(_relativeDensity, _thicknessTopLayer);
    }

    unique_ptr<TimeDependentOutput> NaturalStoneRevetmentLocationDependentInput::CalculateTimeDependentOutput(
        const double initialDamage,
        const ITimeDependentInput& timeDependentInput,
        const IProfileData& profileData)
    {
        const auto& dikeProfilePoints = GetDikeProfilePoints();
        const auto waterLevel = timeDependentInput.GetWaterLevel();
        const auto waveHeightHm0 = timeDependentInput.GetWaveHeightHm0();
        const auto wavePeriodTm10 = timeDependentInput.GetWavePeriodTm10();

        const auto& naturalStoneRevetmentSlope = GetSlope();

        const auto slopeUpperLevel = NaturalStoneRevetment::SlopeUpperLevel(_outerToeHeight, _outerCrestHeight, waterLevel, waveHeightHm0,
                                                                            naturalStoneRevetmentSlope.GetUpperLevelAus());
        const auto slopeLowerLevel = NaturalStoneRevetment::SlopeLowerLevel(_outerToeHeight, slopeUpperLevel, waveHeightHm0,
                                                                            naturalStoneRevetmentSlope.GetLowerLevelAls());
        const auto slopeUpperPosition = Revetment::InterpolationHorizontalPosition(slopeUpperLevel, dikeProfilePoints);
        const auto slopeLowerPosition = Revetment::InterpolationHorizontalPosition(slopeLowerLevel, dikeProfilePoints);

        const auto outerSlope = _notchOuterBerm != nullptr && _crestOuterBerm != nullptr
                                    ? NaturalStoneRevetment::OuterSlope(_outerToeHeight, _outerCrestHeight, _notchOuterBerm->first,
                                                                        _notchOuterBerm->second, _crestOuterBerm->first, _crestOuterBerm->second,
                                                                        slopeUpperLevel, slopeLowerLevel, slopeUpperPosition, slopeLowerPosition)
                                    : NaturalStoneRevetment::OuterSlope(slopeUpperLevel, slopeLowerLevel, slopeUpperPosition, slopeLowerPosition);

        const auto waveSteepnessDeepWater = HydraulicLoad::WaveSteepnessDeepWater(waveHeightHm0, wavePeriodTm10,
                                                                                  Constants::GetGravitationalAcceleration());
        const auto distanceMaximumWaveElevation = NaturalStoneRevetment::DistanceMaximumWaveElevation(
            1.0, waveSteepnessDeepWater, waveHeightHm0, _distanceMaximumWaveElevation->GetDistanceMaximumWaveElevationAsmax(),
            _distanceMaximumWaveElevation->GetDistanceMaximumWaveElevationBsmax());
        const auto surfSimilarityParameter = HydraulicLoad::SurfSimilarityParameter(outerSlope, waveHeightHm0, wavePeriodTm10,
                                                                                    Constants::GetGravitationalAcceleration());
        const auto normativeWidthWaveImpact = NaturalStoneRevetment::NormativeWidthWaveImpact(
            surfSimilarityParameter, waveHeightHm0, _normativeWidthOfWaveImpact->GetNormativeWidthOfWaveImpactAwi(),
            _normativeWidthOfWaveImpact->GetNormativeWidthOfWaveImpactBwi());
        const auto slopeAngle = HydraulicLoad::SlopeAngle(outerSlope);
        const auto depthMaximumWaveLoad = NaturalStoneRevetment::DepthMaximumWaveLoad(distanceMaximumWaveElevation, normativeWidthWaveImpact,
                                                                                      slopeAngle);
        const auto lowerLimitLoading = NaturalStoneRevetment::LowerLimitLoading(depthMaximumWaveLoad, surfSimilarityParameter, waterLevel,
                                                                                waveHeightHm0, _lowerLimitLoading->GetLowerLimitAll(),
                                                                                _lowerLimitLoading->GetLowerLimitBll(),
                                                                                _lowerLimitLoading->GetLowerLimitCll());
        const auto upperLimitLoading = NaturalStoneRevetment::UpperLimitLoading(depthMaximumWaveLoad, surfSimilarityParameter, waterLevel,
                                                                                waveHeightHm0, _upperLimitLoading->GetUpperLimitAul(),
                                                                                _upperLimitLoading->GetUpperLimitBul(),
                                                                                _upperLimitLoading->GetUpperLimitCul());
        const auto loadingRevetment = HydraulicLoad::LoadingRevetment(lowerLimitLoading, upperLimitLoading, GetZ());

        auto incrementDamage = 0.0;
        auto damage = initialDamage;
        unique_ptr<int> timeOfFailure = nullptr;

        auto resistance = loadingRevetment ? make_unique<double>(_resistance) : nullptr;

        unique_ptr<double> hydraulicLoad = nullptr;
        unique_ptr<double> waveAngleImpact = nullptr;
        unique_ptr<double> referenceTimeDegradation = nullptr;
        unique_ptr<double> referenceDegradation = nullptr;

        if (loadingRevetment)
        {
            const auto usePlungingBreakers = _hydraulicLoads->GetHydraulicLoadXib() >= surfSimilarityParameter;
            const auto hydraulicLoadA = usePlungingBreakers
                                            ? _hydraulicLoads->GetHydraulicLoadAp()
                                            : _hydraulicLoads->GetHydraulicLoadAs();
            const auto hydraulicLoadB = usePlungingBreakers
                                            ? _hydraulicLoads->GetHydraulicLoadBp()
                                            : _hydraulicLoads->GetHydraulicLoadBs();
            const auto hydraulicLoadC = usePlungingBreakers
                                            ? _hydraulicLoads->GetHydraulicLoadCp()
                                            : _hydraulicLoads->GetHydraulicLoadCs();
            const auto hydraulicLoadN = usePlungingBreakers
                                            ? _hydraulicLoads->GetHydraulicLoadNp()
                                            : _hydraulicLoads->GetHydraulicLoadNs();

            hydraulicLoad = make_unique<double>(NaturalStoneRevetment::HydraulicLoad(surfSimilarityParameter, waveHeightHm0, hydraulicLoadA,
                                                                                     hydraulicLoadB, hydraulicLoadC, hydraulicLoadN));
            waveAngleImpact = make_unique<double>(NaturalStoneRevetment::WaveAngleImpact(timeDependentInput.GetWaveAngle(),
                                                                                         _waveAngleImpact->GetBetamax()));
            referenceDegradation = make_unique<double>(
                NaturalStoneRevetment::ReferenceDegradation(*resistance, *hydraulicLoad, *waveAngleImpact, initialDamage));
            referenceTimeDegradation = make_unique<double>(NaturalStoneRevetment::ReferenceTimeDegradation(*referenceDegradation, wavePeriodTm10));
            const auto incrementTime = Revetment::IncrementTime(timeDependentInput.GetBeginTime(), timeDependentInput.GetEndTime());
            const auto incrementDegradation = NaturalStoneRevetment::IncrementDegradation(*referenceTimeDegradation, incrementTime, wavePeriodTm10);
            incrementDamage = NaturalStoneRevetment::IncrementDamage(*hydraulicLoad, *resistance, incrementDegradation, *waveAngleImpact);

            damage = Revetment::Damage(incrementDamage, initialDamage);

            const auto failureNumber = GetFailureNumber();

            if (Revetment::FailureRevetment(damage, initialDamage, failureNumber))
            {
                const auto referenceFailure = NaturalStoneRevetment::ReferenceFailure(*resistance, *hydraulicLoad, *waveAngleImpact, failureNumber);
                const auto referenceTimeFailure = NaturalStoneRevetment::ReferenceTimeFailure(referenceFailure, wavePeriodTm10);
                const auto durationInTimeStepFailure = NaturalStoneRevetment::DurationInTimeStepFailure(
                    referenceTimeFailure, *referenceTimeDegradation);

                timeOfFailure = make_unique<int>(Revetment::TimeOfFailure(durationInTimeStepFailure, timeDependentInput.GetBeginTime()));
            }
        }

        return make_unique<NaturalStoneRevetmentTimeDependentOutput>(
            incrementDamage, damage, move(timeOfFailure), outerSlope, slopeUpperLevel, slopeUpperPosition, slopeLowerLevel, slopeLowerPosition,
            loadingRevetment, surfSimilarityParameter, waveSteepnessDeepWater, upperLimitLoading, lowerLimitLoading, depthMaximumWaveLoad,
            distanceMaximumWaveElevation, normativeWidthWaveImpact, move(hydraulicLoad), move(waveAngleImpact), move(resistance),
            move(referenceTimeDegradation), move(referenceDegradation));
    }

    unique_ptr<pair<double, double>> NaturalStoneRevetmentLocationDependentInput::GetCharacteristicPointCoordinates(
        const vector<reference_wrapper<CharacteristicPoint>>& characteristicPoints,
        const CharacteristicPointType characteristicPointType)
    {
        for (const auto& characteristicPointReference : characteristicPoints)
        {
            if (const auto characteristicPoint = characteristicPointReference.get(); characteristicPoint.GetCharacteristicPointType() ==
                characteristicPointType)
            {
                const auto& profilePoint = characteristicPoint.GetProfilePoint();

                return make_unique<pair<double, double>>(pair(profilePoint.GetX(), profilePoint.GetZ()));
            }
        }

        return nullptr;
    }
}
