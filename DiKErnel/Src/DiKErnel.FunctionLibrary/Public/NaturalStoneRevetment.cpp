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

#include "NaturalStoneRevetment.h"

#include <algorithm>
#include <cmath>

#include "Generic.h"

namespace DiKErnel::FunctionLibrary
{
    using namespace std;

    double NaturalStoneRevetment::IncrementDamage(
        const double hydraulicLoad,
        const double resistance,
        const double incrementDegradation,
        const double waveAngleImpact)
    {
        return hydraulicLoad / resistance * incrementDegradation * waveAngleImpact;
    }

    double NaturalStoneRevetment::HydraulicLoad(
        const double surfSimilarityParameter,
        const double waveHeightHm0,
        const double hydraulicLoadA,
        const double hydraulicLoadB,
        const double hydraulicLoadC,
        const double hydraulicLoadN)
    {
        return waveHeightHm0 / (hydraulicLoadA * pow(surfSimilarityParameter, hydraulicLoadN)
            + hydraulicLoadB * surfSimilarityParameter
            + hydraulicLoadC);
    }

    double NaturalStoneRevetment::OuterSlope(
        const bool hasBerm,
        const double outerToeHeight,
        const double outerCrestHeight,
        const std::pair<double, double> notchOuterBerm,
        const std::pair<double, double> crestOuterBerm,
        const double slopeUpperLevel,
        const double slopeLowerLevel,
        const double slopeUpperPosition,
        const double slopeLowerPosition)
    {
        auto tanA = numeric_limits<double>::infinity();

        if (!hasBerm)
        {
            if (outerToeHeight <= slopeLowerLevel && slopeLowerLevel < outerCrestHeight
                && outerToeHeight < slopeUpperLevel && slopeUpperLevel < outerCrestHeight)
            {
                tanA = SingleSlopePart(slopeUpperLevel, slopeLowerLevel, slopeUpperPosition, slopeLowerPosition);
            }
        }
        else
        {
            const auto crestOuterBermPosition = crestOuterBerm.first;
            const auto crestOuterBermHeight = crestOuterBerm.second;

            const auto notchOuterBermPosition = notchOuterBerm.first;
            const auto notchOuterBermHeight = notchOuterBerm.second;

            // Ondertalud-Ondertalud
            if (outerToeHeight <= slopeLowerLevel && slopeLowerLevel < crestOuterBermHeight
                && outerToeHeight <= slopeUpperLevel && slopeUpperLevel < crestOuterBermHeight)
            {
                tanA = SingleSlopePart(slopeUpperLevel, slopeLowerLevel, slopeUpperPosition, slopeLowerPosition);
            }

            // Ondertalud-Berm
            if (outerToeHeight <= slopeLowerLevel && slopeLowerLevel < crestOuterBermHeight
                && crestOuterBermHeight <= slopeUpperLevel && slopeUpperLevel <= notchOuterBermHeight)
            {
                tanA = SlopeLowerSlopeBerm(crestOuterBermPosition, crestOuterBermHeight, slopeLowerLevel, slopeLowerPosition);
            }

            // Ondertalud-Boventalud
            if (outerToeHeight <= slopeLowerLevel && slopeLowerLevel < crestOuterBermHeight
                && notchOuterBermHeight < slopeUpperLevel && slopeUpperLevel <= outerCrestHeight)
            {
                const auto distanceBermUpperSlope = DistanceBermUpperSlope(crestOuterBermHeight, notchOuterBermPosition, notchOuterBermHeight,
                                                                           slopeUpperLevel, slopeUpperPosition);
                const auto distanceBermLowerSlope = DistanceBermLowerSlope(crestOuterBermPosition, crestOuterBermHeight, notchOuterBermHeight,
                                                                           slopeLowerLevel, slopeLowerPosition);

                tanA = SlopeLowerUpperSlope(slopeUpperLevel, slopeLowerLevel, distanceBermUpperSlope, distanceBermLowerSlope);
            }

            // Berm-Berm
            if (crestOuterBermHeight <= slopeLowerLevel && slopeLowerLevel <= notchOuterBermHeight
                && crestOuterBermHeight <= slopeUpperLevel && slopeUpperLevel <= notchOuterBermHeight)
            {
                tanA = SingleSlopePart(slopeUpperLevel, slopeLowerLevel, slopeUpperPosition, slopeLowerPosition);
            }

            // Berm-Boventalud
            if (crestOuterBermHeight <= slopeLowerLevel && slopeLowerLevel <= notchOuterBermHeight
                && notchOuterBermHeight <= slopeUpperLevel && slopeUpperLevel <= outerCrestHeight)
            {
                tanA = SlopeBermUpperSlope(notchOuterBermPosition, notchOuterBermHeight, slopeUpperLevel, slopeUpperPosition);
            }

            // Boventalud-BovenTalud
            if (notchOuterBermHeight < slopeLowerLevel && slopeLowerLevel <= outerCrestHeight
                && notchOuterBermHeight < slopeUpperLevel && slopeUpperLevel <= outerCrestHeight)
            {
                tanA = SingleSlopePart(slopeUpperLevel, slopeLowerLevel, slopeUpperPosition, slopeLowerPosition);
            }
        }

        return tanA;
    }

    double NaturalStoneRevetment::SlopeUpperLevel(
        const double outerToeHeight,
        const double outerCrestHeight,
        const double waterLevel,
        const double waveHeightHm0,
        const double slopeUpperLevelAus)
    {
        return min(outerCrestHeight,
                   max(outerToeHeight + slopeUpperLevelAus * waveHeightHm0,
                       waterLevel));
    }

    double NaturalStoneRevetment::SlopeLowerLevel(
        const double outerToeHeight,
        const double slopeUpperLevel,
        const double waveHeightHm0,
        const double slopeLowerLevelAls)
    {
        return max(slopeUpperLevel - slopeLowerLevelAls * waveHeightHm0,
                   outerToeHeight);
    }

    double NaturalStoneRevetment::UpperLimitLoading(
        const double depthMaximumWaveLoad,
        const double surfSimilarityParameter,
        const double waterLevel,
        const double waveHeightHm0,
        const double upperLimitLoadingAul,
        const double upperLimitLoadingBul,
        const double upperLimitLoadingCul)
    {
        return waterLevel
                - 2.0 * depthMaximumWaveLoad
                + max(depthMaximumWaveLoad + upperLimitLoadingAul,
                      upperLimitLoadingBul * waveHeightHm0 * min(surfSimilarityParameter, upperLimitLoadingCul));
    }

    double NaturalStoneRevetment::LowerLimitLoading(
        const double depthMaximumWaveLoad,
        const double surfSimilarityParameter,
        const double waterLevel,
        const double waveHeightHm0,
        const double lowerLimitLoadingAll,
        const double lowerLimitLoadingBll,
        const double lowerLimitLoadingCll)
    {
        return waterLevel
                - 2.0 * depthMaximumWaveLoad
                + min(depthMaximumWaveLoad - lowerLimitLoadingAll,
                      lowerLimitLoadingBll * waveHeightHm0 * min(surfSimilarityParameter, lowerLimitLoadingCll));
    }

    double NaturalStoneRevetment::DepthMaximumWaveLoad(
        const double distanceMaximumWaveElevation,
        const double normativeWidthWaveImpact,
        const double slopeAngle)
    {
        const auto slopeAngleRadians = Generic::Radians(slopeAngle);

        return (distanceMaximumWaveElevation - 0.5 * normativeWidthWaveImpact * cos(slopeAngleRadians)) * tan(slopeAngleRadians);
    }

    double NaturalStoneRevetment::DistanceMaximumWaveElevation(
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

    double NaturalStoneRevetment::NormativeWidthWaveImpact(
        const double surfSimilarityParameter,
        const double waveHeightHm0,
        const double normativeWidthWaveImpactAwi,
        const double normativeWidthWaveImpactBwi)
    {
        return (normativeWidthWaveImpactAwi - normativeWidthWaveImpactBwi * surfSimilarityParameter) * waveHeightHm0;
    }

    double NaturalStoneRevetment::WaveAngleImpact(
        const double waveAngle,
        const double waveAngleImpactBetamax)
    {
        return pow(cos(Generic::Radians(min(waveAngleImpactBetamax, abs(waveAngle)))), 2.0 / 3.0);
    }

    double NaturalStoneRevetment::Resistance(
        const double relativeDensity,
        const double thicknessTopLayer)
    {
        return relativeDensity * thicknessTopLayer;
    }

    double NaturalStoneRevetment::IncrementDegradation(
        const double referenceTimeDegradation,
        const double incrementTime,
        const double wavePeriodTm10)
    {
        return Degradation(referenceTimeDegradation + incrementTime, wavePeriodTm10) - Degradation(referenceTimeDegradation, wavePeriodTm10);
    }

    double NaturalStoneRevetment::ReferenceTimeDegradation(
        const double referenceDegradation,
        const double wavePeriodTm10)
    {
        return ReferenceTime(referenceDegradation, wavePeriodTm10);
    }

    double NaturalStoneRevetment::ReferenceDegradation(
        const double resistance,
        const double hydraulicLoad,
        const double waveAngleImpact,
        const double initialDamage)
    {
        return Reference(resistance, hydraulicLoad, waveAngleImpact, initialDamage);
    }

    double NaturalStoneRevetment::DurationInTimeStepFailure(
        const double referenceTimeFailure,
        const double referenceTimeDegradation)
    {
        return referenceTimeFailure - referenceTimeDegradation;
    }

    double NaturalStoneRevetment::ReferenceTimeFailure(
        const double referenceFailure,
        const double wavePeriodTm10)
    {
        return ReferenceTime(referenceFailure, wavePeriodTm10);
    }

    double NaturalStoneRevetment::ReferenceFailure(
        const double resistance,
        const double hydraulicLoad,
        const double waveAngleImpact,
        const double failureNumber)
    {
        return Reference(resistance, hydraulicLoad, waveAngleImpact, failureNumber);
    }

    double NaturalStoneRevetment::SingleSlopePart(
        const double slopeUpperLevel,
        const double slopeLowerLevel,
        const double slopeUpperPosition,
        const double slopeLowerPosition)
    {
        return (slopeUpperLevel - slopeLowerLevel) / (slopeUpperPosition - slopeLowerPosition);
    }

    double NaturalStoneRevetment::SlopeLowerSlopeBerm(
        const double crestOuterBermPosition,
        const double crestOuterBermHeight,
        const double slopeLowerLevel,
        const double slopeLowerPosition)
    {
        return (crestOuterBermHeight - slopeLowerLevel) / (crestOuterBermPosition - slopeLowerPosition);
    }

    double NaturalStoneRevetment::SlopeBermUpperSlope(
        const double notchOuterBermPosition,
        const double notchOuterBermHeight,
        const double slopeUpperLevel,
        const double slopeUpperPosition)
    {
        return (slopeUpperLevel - notchOuterBermHeight) / (slopeUpperPosition - notchOuterBermPosition);
    }

    double NaturalStoneRevetment::SlopeLowerUpperSlope(
        const double slopeUpperLevel,
        const double slopeLowerLevel,
        const double distanceBermUpperSlope,
        const double distanceBermLowerSlope)
    {
        return (slopeUpperLevel - slopeLowerLevel) / (distanceBermUpperSlope + distanceBermLowerSlope);
    }

    double NaturalStoneRevetment::DistanceBermUpperSlope(
        const double crestOuterBermHeight,
        const double notchOuterBermPosition,
        const double notchOuterBermHeight,
        const double slopeUpperLevel,
        const double slopeUpperPosition)
    {
        return (slopeUpperLevel - 0.5 * (crestOuterBermHeight + notchOuterBermHeight))
                * ((slopeUpperPosition - notchOuterBermPosition) / (slopeUpperLevel - notchOuterBermHeight));
    }

    double NaturalStoneRevetment::DistanceBermLowerSlope(
        const double crestOuterBermPosition,
        const double crestOuterBermHeight,
        const double notchOuterBermHeight,
        const double slopeLowerLevel,
        const double slopeLowerPosition)
    {
        return (0.5 * (crestOuterBermHeight + notchOuterBermHeight) - slopeLowerLevel)
                * ((crestOuterBermPosition - slopeLowerPosition) / (crestOuterBermHeight - slopeLowerLevel));
    }

    double NaturalStoneRevetment::Degradation(
        const double referenceTimeDegradation,
        const double wavePeriodTm10)
    {
        return pow(referenceTimeDegradation / (wavePeriodTm10 * 1000.0), 0.1);
    }

    double NaturalStoneRevetment::ReferenceTime(
        const double reference,
        const double wavePeriodTm10)
    {
        return 1000.0 * wavePeriodTm10 * pow(reference, 10.0);
    }

    double NaturalStoneRevetment::Reference(
        const double resistance,
        const double hydraulicLoad,
        const double waveAngleImpact,
        const double value)
    {
        return value * (resistance / hydraulicLoad) * (1.0 / waveAngleImpact);
    }
}
