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

#include "NaturalStoneRevetmentFunctions.h"

#include <algorithm>
#include <cmath>

#include "GenericFunctions.h"

namespace DiKErnel::FunctionLibrary
{
    using namespace std;

    double NaturalStoneRevetmentFunctions::IncrementDamage(
        const double hydraulicLoad,
        const double resistance,
        const double incrementDegradation,
        const double waveAngleImpact)
    {
        return hydraulicLoad / resistance * incrementDegradation * waveAngleImpact;
    }

    double NaturalStoneRevetmentFunctions::HydraulicLoad(
        const HydraulicLoadInput& input)
    {
        return input._waveHeightHm0 / (input._a * pow(input._surfSimilarityParameter, input._n)
            + input._b * input._surfSimilarityParameter
            + input._c);
    }

    double NaturalStoneRevetmentFunctions::OuterSlope(
        const OuterSlopeInput& input)
    {
        return !input.HasBerm()
                   ? SingleSlopePart(input._slopeUpperLevel, input._slopeLowerLevel, input._slopeUpperPosition, input._slopeLowerPosition)
                   : OuterSlopeWithBerm(input);
    }

    double NaturalStoneRevetmentFunctions::SlopeUpperLevel(
        const double outerToeHeight,
        const double outerCrestHeight,
        const double waterLevel,
        const double waveHeightHm0,
        const double slopeUpperLevelAus)
    {
        return min(outerCrestHeight,
                   max(waterLevel,
                       outerToeHeight + slopeUpperLevelAus * waveHeightHm0));
    }

    double NaturalStoneRevetmentFunctions::SlopeLowerLevel(
        const double outerToeHeight,
        const double slopeUpperLevel,
        const double waveHeightHm0,
        const double slopeLowerLevelAls)
    {
        return max(outerToeHeight,
                   slopeUpperLevel - slopeLowerLevelAls * waveHeightHm0);
    }

    double NaturalStoneRevetmentFunctions::UpperLimitLoading(
        const LimitLoadingInput& input)
    {
        return input._waterLevel
                - 2.0 * input._depthMaximumWaveLoad
                + max(input._depthMaximumWaveLoad + input._a,
                      input._b * input._waveHeightHm0 * min(input._surfSimilarityParameter, input._c));
    }

    double NaturalStoneRevetmentFunctions::LowerLimitLoading(
        const LimitLoadingInput& input)
    {
        return input._waterLevel
                - 2.0 * input._depthMaximumWaveLoad
                + min(input._depthMaximumWaveLoad - input._a,
                      input._b * input._waveHeightHm0 * min(input._surfSimilarityParameter, input._c));
    }

    double NaturalStoneRevetmentFunctions::DepthMaximumWaveLoad(
        const double distanceMaximumWaveElevation,
        const double normativeWidthWaveImpact,
        const double slopeAngle)
    {
        const auto slopeAngleRadians = GenericFunctions::Radians(slopeAngle);

        return (distanceMaximumWaveElevation - 0.5 * normativeWidthWaveImpact * cos(slopeAngleRadians)) * tan(slopeAngleRadians);
    }

    double NaturalStoneRevetmentFunctions::DistanceMaximumWaveElevation(
        const double impactShallowWater,
        const double waveSteepnessDeepWater,
        const double waveHeightHm0,
        const double distanceMaximumWaveElevationAsmax,
        const double distanceMaximumWaveElevationBsmax)
    {
        return waveHeightHm0
                * (distanceMaximumWaveElevationAsmax / sqrt(waveSteepnessDeepWater) - distanceMaximumWaveElevationBsmax)
                * impactShallowWater;
    }

    double NaturalStoneRevetmentFunctions::NormativeWidthWaveImpact(
        const double surfSimilarityParameter,
        const double waveHeightHm0,
        const double normativeWidthWaveImpactAwi,
        const double normativeWidthWaveImpactBwi)
    {
        return (normativeWidthWaveImpactAwi - normativeWidthWaveImpactBwi * surfSimilarityParameter) * waveHeightHm0;
    }

    double NaturalStoneRevetmentFunctions::WaveAngleImpact(
        const double waveAngle,
        const double waveAngleImpactBetamax)
    {
        return pow(cos(GenericFunctions::Radians(min(waveAngleImpactBetamax, abs(waveAngle)))), 2.0 / 3.0);
    }

    double NaturalStoneRevetmentFunctions::Resistance(
        const double relativeDensity,
        const double thicknessTopLayer)
    {
        return relativeDensity * thicknessTopLayer;
    }

    double NaturalStoneRevetmentFunctions::IncrementDegradation(
        const double referenceTimeDegradation,
        const double incrementTime,
        const double wavePeriodTm10)
    {
        return Degradation(referenceTimeDegradation + incrementTime, wavePeriodTm10) - Degradation(referenceTimeDegradation, wavePeriodTm10);
    }

    double NaturalStoneRevetmentFunctions::ReferenceTimeDegradation(
        const double referenceDegradation,
        const double wavePeriodTm10)
    {
        return ReferenceTime(referenceDegradation, wavePeriodTm10);
    }

    double NaturalStoneRevetmentFunctions::ReferenceDegradation(
        const double resistance,
        const double hydraulicLoad,
        const double waveAngleImpact,
        const double initialDamage)
    {
        return Reference(resistance, hydraulicLoad, waveAngleImpact, initialDamage);
    }

    double NaturalStoneRevetmentFunctions::DurationInTimeStepFailure(
        const double referenceTimeFailure,
        const double referenceTimeDegradation)
    {
        return referenceTimeFailure - referenceTimeDegradation;
    }

    double NaturalStoneRevetmentFunctions::ReferenceTimeFailure(
        const double referenceFailure,
        const double wavePeriodTm10)
    {
        return ReferenceTime(referenceFailure, wavePeriodTm10);
    }

    double NaturalStoneRevetmentFunctions::ReferenceFailure(
        const double resistance,
        const double hydraulicLoad,
        const double waveAngleImpact,
        const double failureNumber)
    {
        return Reference(resistance, hydraulicLoad, waveAngleImpact, failureNumber);
    }

    double NaturalStoneRevetmentFunctions::SingleSlopePart(
        const double slopeUpperLevel,
        const double slopeLowerLevel,
        const double slopeUpperPosition,
        const double slopeLowerPosition)
    {
        return (slopeUpperLevel - slopeLowerLevel) / (slopeUpperPosition - slopeLowerPosition);
    }

    double NaturalStoneRevetmentFunctions::OuterSlopeWithBerm(
        const OuterSlopeInput& input)
    {
        const auto outerToeHeight = input._outerToeHeight;
        const auto crestOuterBermHeight = input._crestOuterBermHeight;
        const auto crestOuterBermPosition = input._crestOuterBermPosition;
        const auto notchOuterBermHeight = input._notchOuterBermHeight;
        const auto notchOuterBermPosition = input._notchOuterBermPosition;
        const auto outerCrestHeight = input._outerCrestHeight;

        const auto slopeLowerPosition = input._slopeLowerPosition;
        const auto slopeLowerLevel = input._slopeLowerLevel;
        const auto slopeUpperPosition = input._slopeUpperPosition;
        const auto slopeUpperLevel = input._slopeUpperLevel;

        const auto slopeLowerLevelOnLowerSlope = outerToeHeight <= slopeLowerLevel && slopeLowerLevel < crestOuterBermHeight;
        const auto slopeUpperLevelOnLowerSlope = outerToeHeight <= slopeUpperLevel && slopeUpperLevel < crestOuterBermHeight;
        const auto slopeLowerLevelOnBerm = crestOuterBermHeight <= slopeLowerLevel && slopeLowerLevel <= notchOuterBermHeight;
        const auto slopeUpperLevelOnBerm = crestOuterBermHeight <= slopeUpperLevel && slopeUpperLevel <= notchOuterBermHeight;
        const auto slopeLowerLevelOnUpperSlope = notchOuterBermHeight < slopeLowerLevel && slopeLowerLevel <= outerCrestHeight;
        const auto slopeUpperLevelOnUpperSlope = notchOuterBermHeight < slopeUpperLevel && slopeUpperLevel <= outerCrestHeight;

        if (slopeLowerLevelOnLowerSlope && slopeUpperLevelOnLowerSlope
            || slopeLowerLevelOnBerm && slopeUpperLevelOnBerm
            || slopeLowerLevelOnUpperSlope && slopeUpperLevelOnUpperSlope)
        {
            return SingleSlopePart(slopeUpperLevel, slopeLowerLevel, slopeUpperPosition, slopeLowerPosition);
        }

        if (slopeLowerLevelOnLowerSlope && slopeUpperLevelOnBerm)
        {
            return SlopeLowerSlopeBerm(crestOuterBermPosition, crestOuterBermHeight, slopeLowerLevel, slopeLowerPosition);
        }

        if (slopeLowerLevelOnLowerSlope && slopeUpperLevelOnUpperSlope)
        {
            const auto distanceBermUpperSlope = DistanceBermUpperSlope(crestOuterBermHeight, notchOuterBermPosition, notchOuterBermHeight,
                                                                       slopeUpperLevel, slopeUpperPosition);
            const auto distanceBermLowerSlope = DistanceBermLowerSlope(crestOuterBermPosition, crestOuterBermHeight, notchOuterBermHeight,
                                                                       slopeLowerLevel, slopeLowerPosition);

            return SlopeLowerUpperSlope(slopeUpperLevel, slopeLowerLevel, distanceBermUpperSlope, distanceBermLowerSlope);
        }

        if (slopeLowerLevelOnBerm && slopeUpperLevelOnUpperSlope)
        {
            return SlopeBermUpperSlope(notchOuterBermPosition, notchOuterBermHeight, slopeUpperLevel, slopeUpperPosition);
        }

        return numeric_limits<double>::infinity();
    }

    double NaturalStoneRevetmentFunctions::SlopeLowerSlopeBerm(
        const double crestOuterBermPosition,
        const double crestOuterBermHeight,
        const double slopeLowerLevel,
        const double slopeLowerPosition)
    {
        return (crestOuterBermHeight - slopeLowerLevel) / (crestOuterBermPosition - slopeLowerPosition);
    }

    double NaturalStoneRevetmentFunctions::SlopeBermUpperSlope(
        const double notchOuterBermPosition,
        const double notchOuterBermHeight,
        const double slopeUpperLevel,
        const double slopeUpperPosition)
    {
        return (slopeUpperLevel - notchOuterBermHeight) / (slopeUpperPosition - notchOuterBermPosition);
    }

    double NaturalStoneRevetmentFunctions::SlopeLowerUpperSlope(
        const double slopeUpperLevel,
        const double slopeLowerLevel,
        const double distanceBermUpperSlope,
        const double distanceBermLowerSlope)
    {
        return (slopeUpperLevel - slopeLowerLevel) / (distanceBermUpperSlope + distanceBermLowerSlope);
    }

    double NaturalStoneRevetmentFunctions::DistanceBermUpperSlope(
        const double crestOuterBermHeight,
        const double notchOuterBermPosition,
        const double notchOuterBermHeight,
        const double slopeUpperLevel,
        const double slopeUpperPosition)
    {
        return (slopeUpperLevel - 0.5 * (crestOuterBermHeight + notchOuterBermHeight))
                * (slopeUpperPosition - notchOuterBermPosition) / (slopeUpperLevel - notchOuterBermHeight);
    }

    double NaturalStoneRevetmentFunctions::DistanceBermLowerSlope(
        const double crestOuterBermPosition,
        const double crestOuterBermHeight,
        const double notchOuterBermHeight,
        const double slopeLowerLevel,
        const double slopeLowerPosition)
    {
        return (0.5 * (crestOuterBermHeight + notchOuterBermHeight) - slopeLowerLevel)
                * (crestOuterBermPosition - slopeLowerPosition) / (crestOuterBermHeight - slopeLowerLevel);
    }

    double NaturalStoneRevetmentFunctions::Degradation(
        const double referenceTimeDegradation,
        const double wavePeriodTm10)
    {
        return pow(referenceTimeDegradation / (wavePeriodTm10 * 1000.0), 0.1);
    }

    double NaturalStoneRevetmentFunctions::ReferenceTime(
        const double reference,
        const double wavePeriodTm10)
    {
        return 1000.0 * wavePeriodTm10 * pow(reference, 10.0);
    }

    double NaturalStoneRevetmentFunctions::Reference(
        const double resistance,
        const double hydraulicLoad,
        const double waveAngleImpact,
        const double value)
    {
        return value * (resistance / hydraulicLoad) * (1.0 / waveAngleImpact);
    }
}
