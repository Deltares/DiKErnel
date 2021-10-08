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
    using namespace DomainLibrary;
    using namespace FunctionLibrary;
    using namespace std;

    NaturalStoneRevetmentLocationDependentInput::NaturalStoneRevetmentLocationDependentInput(
        string name,
        const double x,
        const double initialDamage,
        const double failureNumber,
        const double tanA,
        const double positionZ,
        const double relativeDensity,
        const double thicknessTopLayer,
        unique_ptr<NaturalStoneRevetmentHydraulicLoads> hydraulicLoads,
        unique_ptr<NaturalStoneRevetmentSlope> slope,
        unique_ptr<NaturalStoneRevetmentUpperLimitLoading> upperLimitLoading,
        unique_ptr<NaturalStoneRevetmentLowerLimitLoading> lowerLimitLoading,
        unique_ptr<NaturalStoneRevetmentDistanceMaximumWaveElevation> distanceMaximumWaveElevation,
        unique_ptr<NaturalStoneRevetmentNormativeWidthOfWaveImpact> normativeWidthOfWaveImpact,
        unique_ptr<NaturalStoneRevetmentWaveAngleImpact> waveAngleImpact)
        : LocationDependentInput(move(name), x, initialDamage, failureNumber, positionZ),
          _tanA(tanA),
          _relativeDensity(relativeDensity),
          _thicknessTopLayer(thicknessTopLayer),
          _hydraulicLoads(move(hydraulicLoads)),
          _slope(move(slope)),
          _upperLimitLoading(move(upperLimitLoading)),
          _lowerLimitLoading(move(lowerLimitLoading)),
          _distanceMaximumWaveElevation(move(distanceMaximumWaveElevation)),
          _normativeWidthOfWaveImpact(move(normativeWidthOfWaveImpact)),
          _waveAngleImpact(move(waveAngleImpact)) {}

    double NaturalStoneRevetmentLocationDependentInput::GetTanA() const
    {
        return _tanA;
    }

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

    unique_ptr<TimeDependentOutput> NaturalStoneRevetmentLocationDependentInput::CalculateTimeDependentOutput(
        const double initialDamage,
        const ITimeDependentInput& timeDependentInput,
        const IProfileData& profileData)
    {
        const auto waterLevel = timeDependentInput.GetWaterLevel();
        const auto waveHeightHm0 = timeDependentInput.GetWaveHeightHm0();
        const auto wavePeriodTm10 = timeDependentInput.GetWavePeriodTm10();

        auto tanA = numeric_limits<double>::infinity();

        const auto& characteristicPoints = profileData.GetCharacteristicPoints();

        const auto [outerToePosition, outerToeHeight] = GetCharacteristicPointCoordinates(characteristicPoints, CharacteristicPointType::OuterToe);
        const auto [outerCrestPosition, outerCrestHeight] = GetCharacteristicPointCoordinates(
            characteristicPoints, CharacteristicPointType::OuterCrest);

        const auto slopeUpperLevel = NaturalStoneRevetment::SlopeUpperLevel(outerToeHeight, outerCrestHeight, waterLevel,
                                                                            waveHeightHm0, GetSlope().GetUpperLevelAus());
        const auto slopeLowerLevel = NaturalStoneRevetment::SlopeLowerLevel(outerToeHeight, slopeUpperLevel, waveHeightHm0,
                                                                            GetSlope().GetLowerLevelAls());

        auto dikeProfilePoints = vector<pair<double, double>>();

        for (const auto& profilePointReference : profileData.GetProfilePoints())
        {
            const auto profilePoint = profilePointReference.get();
            dikeProfilePoints.emplace_back(profilePoint.GetX(), profilePoint.GetZ());
        }

        const auto slopeUpperPosition = Revetment::InterpolationHorizontalPosition(slopeUpperLevel, dikeProfilePoints);
        const auto slopeLowerPosition = Revetment::InterpolationHorizontalPosition(slopeLowerLevel, dikeProfilePoints);

        if (!profileData.HasBerm())
        {
            if (outerToeHeight <= slopeLowerLevel && slopeLowerLevel < outerCrestHeight
                && outerToeHeight < slopeUpperLevel && slopeUpperLevel < outerCrestHeight)
            {
                tanA = NaturalStoneRevetment::SingleSlopePart(slopeUpperLevel, slopeLowerLevel, slopeUpperPosition, slopeLowerPosition);
            }
        }
        else
        {
            const auto [notchOuterBermPosition, notchOuterBermHeight] = GetCharacteristicPointCoordinates(
                characteristicPoints, CharacteristicPointType::NotchOuterBerm);
            const auto [crestOuterBermPosition, crestOuterBermHeight] = GetCharacteristicPointCoordinates(
                characteristicPoints, CharacteristicPointType::CrestOuterBerm);

            // Ondertalud-Ondertalud
            if (outerToeHeight <= slopeLowerLevel && slopeLowerLevel < crestOuterBermHeight
                && outerToeHeight <= slopeUpperLevel && slopeUpperLevel < crestOuterBermHeight)
            {
                tanA = NaturalStoneRevetment::SingleSlopePart(slopeUpperLevel, slopeLowerLevel, slopeUpperPosition, slopeLowerPosition);
            }

            // Ondertalud-Berm
            if (outerToeHeight <= slopeLowerLevel && slopeLowerLevel < crestOuterBermHeight
                && crestOuterBermHeight <= slopeUpperLevel && slopeUpperLevel <= notchOuterBermHeight)
            {
                tanA = NaturalStoneRevetment::SlopeLowerSlopeBerm(crestOuterBermPosition, crestOuterBermHeight, slopeLowerLevel,
                                                                  slopeLowerPosition);
            }

            // Ondertalud-Boventalud
            if (outerToeHeight <= slopeLowerLevel && slopeLowerLevel < crestOuterBermHeight
                && notchOuterBermHeight < slopeUpperLevel && slopeUpperLevel <= outerCrestHeight)
            {
                const auto distanceBermUpperSlope = NaturalStoneRevetment::DistanceBermUpperSlope(
                    crestOuterBermHeight, notchOuterBermPosition, notchOuterBermHeight, slopeUpperLevel, slopeUpperPosition);
                const auto distanceBermLowerSlope = NaturalStoneRevetment::DistanceBermLowerSlope(
                    crestOuterBermPosition, crestOuterBermHeight, notchOuterBermHeight, slopeLowerLevel, slopeLowerPosition);

                tanA = NaturalStoneRevetment::SlopeLowerUpperSlope(slopeUpperLevel, slopeLowerLevel, distanceBermUpperSlope,
                                                                   distanceBermLowerSlope);
            }

            // Berm-Berm
            if (crestOuterBermHeight <= slopeLowerLevel && slopeLowerLevel <= notchOuterBermHeight
                && crestOuterBermHeight <= slopeUpperLevel && slopeUpperLevel <= notchOuterBermHeight)
            {
                tanA = NaturalStoneRevetment::SingleSlopePart(slopeUpperLevel, slopeLowerLevel, slopeUpperPosition, slopeLowerPosition);
            }

            // Berm-Boventalud
            if (crestOuterBermHeight <= slopeLowerLevel && slopeLowerLevel <= notchOuterBermHeight
                && notchOuterBermHeight <= slopeUpperLevel && slopeUpperLevel <= outerCrestHeight)
            {
                tanA = NaturalStoneRevetment::SlopeBermUpperSlope(notchOuterBermPosition, notchOuterBermHeight, slopeUpperLevel,
                                                                  slopeUpperPosition);
            }

            // Boventalud-BovenTalud
            if (notchOuterBermHeight < slopeLowerLevel && slopeLowerLevel <= outerCrestHeight
                && notchOuterBermHeight < slopeUpperLevel && slopeUpperLevel <= outerCrestHeight)
            {
                tanA = NaturalStoneRevetment::SingleSlopePart(slopeUpperLevel, slopeLowerLevel, slopeUpperPosition, slopeLowerPosition);
            }
        }

        const auto waveSteepnessDeepWater = HydraulicLoad::WaveSteepnessDeepWater(waveHeightHm0, wavePeriodTm10,
                                                                                  Constants::GRAVITATIONAL_ACCELERATION);
        const auto distanceMaximumWaveElevation = NaturalStoneRevetment::DistanceMaximumWaveElevation(
            1.0, waveSteepnessDeepWater, waveHeightHm0, _distanceMaximumWaveElevation->GetDistanceMaximumWaveElevationAsmax(),
            _distanceMaximumWaveElevation->GetDistanceMaximumWaveElevationBsmax());
        const auto surfSimilarityParameter = HydraulicLoad::SurfSimilarityParameter(tanA, waveHeightHm0, wavePeriodTm10,
                                                                                    Constants::GRAVITATIONAL_ACCELERATION);
        const auto normativeWidthWaveImpact = NaturalStoneRevetment::NormativeWidthWaveImpact(
            surfSimilarityParameter, waveHeightHm0, _normativeWidthOfWaveImpact->GetNormativeWidthOfWaveImpactAwi(),
            _normativeWidthOfWaveImpact->GetNormativeWidthOfWaveImpactBwi());
        const auto slopeAngle = HydraulicLoad::SlopeAngle(tanA);
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
        const auto loadingRevetment = HydraulicLoad::LoadingRevetment(lowerLimitLoading, upperLimitLoading, GetPositionZ());

        auto incrementDamage = 0.0;
        auto damage = initialDamage;
        unique_ptr<int> timeOfFailure = nullptr;

        unique_ptr<double> hydraulicLoad = nullptr;
        unique_ptr<double> waveAngleImpact = nullptr;
        unique_ptr<double> resistance = nullptr;
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
            resistance = make_unique<double>(NaturalStoneRevetment::Resistance(_relativeDensity, _thicknessTopLayer));
            waveAngleImpact = make_unique<double>(
                NaturalStoneRevetment::WaveAngleImpact(timeDependentInput.GetWaveAngle(), _waveAngleImpact->GetBetamax()));
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
            incrementDamage, damage, move(timeOfFailure), loadingRevetment, surfSimilarityParameter, waveSteepnessDeepWater, upperLimitLoading,
            lowerLimitLoading, depthMaximumWaveLoad, distanceMaximumWaveElevation, normativeWidthWaveImpact, move(hydraulicLoad),
            move(waveAngleImpact), move(resistance), move(referenceTimeDegradation), move(referenceDegradation));
    }

    pair<double, double> NaturalStoneRevetmentLocationDependentInput::GetCharacteristicPointCoordinates(
        const vector<reference_wrapper<CharacteristicPoint>>& characteristicPoints,
        const CharacteristicPointType characteristicPointType)
    {
        for (const auto characteristicPointReference : characteristicPoints)
        {
            if (const auto characteristicPoint = characteristicPointReference.get(); characteristicPoint.GetCharacteristicPointType() ==
                characteristicPointType)
            {
                const auto profilePoint = characteristicPoint.GetProfilePoint();
                return pair(profilePoint.GetX(), profilePoint.GetZ());
            }
        }

        return pair(numeric_limits<double>::infinity(), numeric_limits<double>::infinity());
    }
}
