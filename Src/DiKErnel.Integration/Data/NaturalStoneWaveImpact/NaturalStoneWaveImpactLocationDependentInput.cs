// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
//
// This file is part of DiKErnel.
//
// This program is free software; you can redistribute it and/or modify it under the terms of
// the GNU Lesser General Public License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with this
// program; if not, see <https://www.gnu.org/licenses/>.
//
// All names, logos, and references to "Deltares" are registered trademarks of Stichting
// Deltares and remain full property of Stichting Deltares at all times. All rights reserved.

using System.Collections.Generic;
using DiKErnel.Core.Data;
using DiKErnel.DomainLibrary.Constants;
using DiKErnel.DomainLibrary.Validators.NaturalStoneWaveImpact;
using DiKErnel.FunctionLibrary;
using DiKErnel.FunctionLibrary.NaturalStoneWaveImpact;
using DiKErnel.Integration.Helpers;
using DiKErnel.Util.Validation;

namespace DiKErnel.Integration.Data.NaturalStoneWaveImpact
{
    internal class NaturalStoneWaveImpactLocationDependentInput : LocationDependentInput
    {
        private double outerToeHeight = double.NaN;
        private double outerCrestHeight = double.NaN;
        private (double, double)? notchOuterBerm;
        private (double, double)? crestOuterBerm;
        private double resistance = double.NaN;

        public NaturalStoneWaveImpactLocationDependentInput(double x, double initialDamage, double failureNumber,
                                                            double relativeDensity, double thicknessTopLayer,
                                                            NaturalStoneWaveImpactHydraulicLoads hydraulicLoads,
                                                            NaturalStoneWaveImpactSlope slope,
                                                            NaturalStoneWaveImpactUpperLimitLoading upperLimitLoading,
                                                            NaturalStoneWaveImpactLowerLimitLoading lowerLimitLoading,
                                                            NaturalStoneWaveImpactDistanceMaximumWaveElevation distanceMaximumWaveElevation,
                                                            NaturalStoneWaveImpactNormativeWidthOfWaveImpact normativeWidthOfWaveImpact,
                                                            NaturalStoneWaveImpactWaveAngleImpact waveAngleImpact)
            : base(x, initialDamage, failureNumber)
        {
            RelativeDensity = relativeDensity;
            ThicknessTopLayer = thicknessTopLayer;
            HydraulicLoads = hydraulicLoads;
            Slope = slope;
            UpperLimitLoading = upperLimitLoading;
            LowerLimitLoading = lowerLimitLoading;
            DistanceMaximumWaveElevation = distanceMaximumWaveElevation;
            NormativeWidthOfWaveImpact = normativeWidthOfWaveImpact;
            WaveAngleImpact = waveAngleImpact;
        }

        public double RelativeDensity { get; }

        public double ThicknessTopLayer { get; }

        public NaturalStoneWaveImpactHydraulicLoads HydraulicLoads { get; }

        public NaturalStoneWaveImpactSlope Slope { get; }

        public NaturalStoneWaveImpactUpperLimitLoading UpperLimitLoading { get; }

        public NaturalStoneWaveImpactLowerLimitLoading LowerLimitLoading { get; }

        public NaturalStoneWaveImpactDistanceMaximumWaveElevation DistanceMaximumWaveElevation { get; }

        public NaturalStoneWaveImpactNormativeWidthOfWaveImpact NormativeWidthOfWaveImpact { get; }

        public NaturalStoneWaveImpactWaveAngleImpact WaveAngleImpact { get; }

        public override bool Validate(IReadOnlyList<ITimeDependentInput> timeDependentInputItems,
                                      IProfileData profileData)
        {
            bool baseValidationSuccessful = base.Validate(timeDependentInputItems, profileData);

            var validationIssues = new List<ValidationIssue>
            {
                NaturalStoneWaveImpactValidator.RelativeDensity(RelativeDensity),
                NaturalStoneWaveImpactValidator.ThicknessTopLayer(ThicknessTopLayer),
                NaturalStoneWaveImpactValidator.SlopeUpperLevelAus(Slope.UpperLevelAus),
                NaturalStoneWaveImpactValidator.SlopeLowerLevelAls(Slope.LowerLevelAls)
            };

            return ValidationHelper.RegisterValidationIssues(validationIssues) && baseValidationSuccessful;
        }

        public override LocationDependentOutput GetLocationDependentOutput(
            IReadOnlyList<TimeDependentOutput> timeDependentOutputItems)
        {
            return new NaturalStoneWaveImpactLocationDependentOutput(timeDependentOutputItems, Z, resistance);
        }

        protected override void InitializeDerivedLocationDependentInput(IProfileData profileData)
        {
            base.InitializeDerivedLocationDependentInput(profileData);

            outerToeHeight = CharacteristicPointsHelper.GetCoordinatesForType(
                profileData.CharacteristicPoints, CharacteristicPointType.OuterToe).Item2;
            outerCrestHeight = CharacteristicPointsHelper.GetCoordinatesForType(
                profileData.CharacteristicPoints, CharacteristicPointType.OuterCrest).Item2;
            notchOuterBerm = CharacteristicPointsHelper.TryGetCoordinatesForType(
                profileData.CharacteristicPoints, CharacteristicPointType.NotchOuterBerm);
            crestOuterBerm = CharacteristicPointsHelper.TryGetCoordinatesForType(
                profileData.CharacteristicPoints, CharacteristicPointType.CrestOuterBerm);

            resistance = NaturalStoneWaveImpactFunctions.Resistance(RelativeDensity, ThicknessTopLayer);
        }

        protected override TimeDependentOutput CalculateTimeDependentOutput(ITimeDependentInput timeDependentInput,
                                                                            IProfileData profileData,
                                                                            double damageAtStartOfCalculation = double.NaN)
        {
            double slopeUpperLevel = NaturalStoneWaveImpactFunctions.SlopeUpperLevel(outerToeHeight, outerCrestHeight,
                                                                                     timeDependentInput.WaterLevel,
                                                                                     timeDependentInput.WaveHeightHm0, Slope.UpperLevelAus);

            double slopeUpperPosition = profileData.GetHorizontalPosition(slopeUpperLevel);

            double slopeLowerLevel = NaturalStoneWaveImpactFunctions.SlopeLowerLevel(outerToeHeight, slopeUpperLevel,
                                                                                     timeDependentInput.WaveHeightHm0, Slope.LowerLevelAls);

            double slopeLowerPosition = profileData.GetHorizontalPosition(slopeLowerLevel);

            var outerSlopeInput = new NaturalStoneWaveImpactOuterSlopeInput(slopeLowerPosition, slopeLowerLevel, slopeUpperPosition,
                                                                            slopeUpperLevel, outerToeHeight, outerCrestHeight);

            if (notchOuterBerm != null && crestOuterBerm != null)
            {
                outerSlopeInput.NotchOuterBermPosition = notchOuterBerm.Value.Item1;
                outerSlopeInput.NotchOuterBermHeight = notchOuterBerm.Value.Item2;
                outerSlopeInput.CrestOuterBermPosition = crestOuterBerm.Value.Item1;
                outerSlopeInput.CrestOuterBermHeight = crestOuterBerm.Value.Item2;
            }

            double outerSlope = NaturalStoneWaveImpactFunctions.OuterSlope(outerSlopeInput);

            double slopeAngle = HydraulicLoadFunctions.SlopeAngle(outerSlope);

            double waveSteepnessDeepWater = HydraulicLoadFunctions.WaveSteepnessDeepWater(
                timeDependentInput.WaveHeightHm0, timeDependentInput.WavePeriodTm10,
                NaturalConstants.GravitationalAcceleration);

            double distanceMaximumWaveElevation = NaturalStoneWaveImpactFunctions.DistanceMaximumWaveElevation(
                1d, waveSteepnessDeepWater, timeDependentInput.WaveHeightHm0,
                DistanceMaximumWaveElevation.DistanceMaximumWaveElevationAsmax,
                DistanceMaximumWaveElevation.DistanceMaximumWaveElevationBsmax);

            double surfSimilarityParameter = HydraulicLoadFunctions.SurfSimilarityParameter(
                outerSlope, timeDependentInput.WaveHeightHm0, timeDependentInput.WavePeriodTm10,
                NaturalConstants.GravitationalAcceleration);

            double normativeWidthWaveImpact = NaturalStoneWaveImpactFunctions.NormativeWidthWaveImpact(
                surfSimilarityParameter, timeDependentInput.WaveHeightHm0,
                NormativeWidthOfWaveImpact.NormativeWidthOfWaveImpactAwi,
                NormativeWidthOfWaveImpact.NormativeWidthOfWaveImpactBwi);

            double depthMaximumWaveLoad = NaturalStoneWaveImpactFunctions.DepthMaximumWaveLoad(
                distanceMaximumWaveElevation, normativeWidthWaveImpact, slopeAngle);

            var lowerLimitLoadingInput = new NaturalStoneWaveImpactLimitLoadingInput(
                depthMaximumWaveLoad, surfSimilarityParameter, timeDependentInput.WaterLevel, timeDependentInput.WaveHeightHm0,
                LowerLimitLoading.LowerLimitAll, LowerLimitLoading.LowerLimitBll, LowerLimitLoading.LowerLimitCll);

            double lowerLimitLoading = NaturalStoneWaveImpactFunctions.LowerLimitLoading(lowerLimitLoadingInput);

            var upperLimitLoadingInput = new NaturalStoneWaveImpactLimitLoadingInput(
                depthMaximumWaveLoad, surfSimilarityParameter, timeDependentInput.WaterLevel, timeDependentInput.WaveHeightHm0,
                UpperLimitLoading.UpperLimitAul, UpperLimitLoading.UpperLimitBul, UpperLimitLoading.UpperLimitCul);

            double upperLimitLoading = NaturalStoneWaveImpactFunctions.UpperLimitLoading(upperLimitLoadingInput);

            bool loadingRevetment = HydraulicLoadFunctions.LoadingRevetment(lowerLimitLoading, upperLimitLoading, Z);

            var incrementDamage = 0d;

            double hydraulicLoad = double.NaN;
            double waveAngle = double.NaN;
            double waveAngleImpact = double.NaN;
            double referenceDegradation = double.NaN;
            double referenceTimeDegradation = double.NaN;

            if (loadingRevetment)
            {
                hydraulicLoad = CalculateHydraulicLoad(timeDependentInput.WaveHeightHm0, surfSimilarityParameter);

                waveAngle = HydraulicLoadFunctions.WaveAngle(timeDependentInput.WaveDirection, profileData.DikeOrientation);

                waveAngleImpact = NaturalStoneWaveImpactFunctions.WaveAngleImpact(waveAngle, WaveAngleImpact.Betamax);

                referenceDegradation = NaturalStoneWaveImpactFunctions.ReferenceDegradation(resistance, hydraulicLoad, waveAngleImpact,
                                                                                            damageAtStartOfCalculation);

                referenceTimeDegradation = NaturalStoneWaveImpactFunctions.ReferenceTimeDegradation(referenceDegradation,
                    timeDependentInput.WavePeriodTm10);

                double incrementTime = RevetmentFunctions.IncrementTime(timeDependentInput.BeginTime, timeDependentInput.EndTime);

                double incrementDegradation = NaturalStoneWaveImpactFunctions.IncrementDegradation(referenceTimeDegradation, incrementTime,
                    timeDependentInput.WavePeriodTm10);

                incrementDamage = NaturalStoneWaveImpactFunctions.IncrementDamage(hydraulicLoad, resistance, incrementDegradation,
                                                                                  waveAngleImpact);
            }

            return new NaturalStoneWaveImpactTimeDependentOutput(
                CreateConstructionProperties(incrementDamage, outerSlope, slopeUpperLevel, slopeUpperPosition, slopeLowerLevel,
                                             slopeLowerPosition, loadingRevetment, surfSimilarityParameter, waveSteepnessDeepWater,
                                             upperLimitLoading, lowerLimitLoading, depthMaximumWaveLoad, distanceMaximumWaveElevation,
                                             normativeWidthWaveImpact, hydraulicLoad, waveAngle, waveAngleImpact,
                                             referenceTimeDegradation, referenceDegradation));
        }

        private double CalculateHydraulicLoad(double waveHeightHm0, double surfSimilarityParameter)
        {
            bool usePlungingBreakers = HydraulicLoads.HydraulicLoadXib >= surfSimilarityParameter;

            return NaturalStoneWaveImpactFunctions.HydraulicLoad(
                new NaturalStoneWaveImpactHydraulicLoadInput(surfSimilarityParameter, waveHeightHm0,
                                                             usePlungingBreakers
                                                                 ? HydraulicLoads.HydraulicLoadAp
                                                                 : HydraulicLoads.HydraulicLoadAs,
                                                             usePlungingBreakers
                                                                 ? HydraulicLoads.HydraulicLoadBp
                                                                 : HydraulicLoads.HydraulicLoadBs,
                                                             usePlungingBreakers
                                                                 ? HydraulicLoads.HydraulicLoadCp
                                                                 : HydraulicLoads.HydraulicLoadCs,
                                                             usePlungingBreakers
                                                                 ? HydraulicLoads.HydraulicLoadNp
                                                                 : HydraulicLoads.HydraulicLoadNs));
        }

        private static NaturalStoneWaveImpactTimeDependentOutputConstructionProperties CreateConstructionProperties(
            double incrementDamage, double outerSlope, double slopeUpperLevel, double slopeUpperPosition, double slopeLowerLevel,
            double slopeLowerPosition, bool loadingRevetment, double surfSimilarityParameter, double waveSteepnessDeepWater,
            double upperLimitLoading, double lowerLimitLoading, double depthMaximumWaveLoad, double distanceMaximumWaveElevation,
            double normativeWidthWaveImpact, double hydraulicLoad, double waveAngle, double waveAngleImpact,
            double referenceTimeDegradation, double referenceDegradation)
        {
            var constructionProperties = new NaturalStoneWaveImpactTimeDependentOutputConstructionProperties
            {
                IncrementDamage = incrementDamage,
                OuterSlope = outerSlope,
                SlopeUpperLevel = slopeUpperLevel,
                SlopeUpperPosition = slopeUpperPosition,
                SlopeLowerLevel = slopeLowerLevel,
                SlopeLowerPosition = slopeLowerPosition,
                LoadingRevetment = loadingRevetment,
                SurfSimilarityParameter = surfSimilarityParameter,
                WaveSteepnessDeepWater = waveSteepnessDeepWater,
                UpperLimitLoading = upperLimitLoading,
                LowerLimitLoading = lowerLimitLoading,
                DepthMaximumWaveLoad = depthMaximumWaveLoad,
                DistanceMaximumWaveElevation = distanceMaximumWaveElevation,
                NormativeWidthOfWaveImpact = normativeWidthWaveImpact
            };

            if (loadingRevetment)
            {
                constructionProperties.HydraulicLoad = hydraulicLoad;
                constructionProperties.WaveAngle = waveAngle;
                constructionProperties.WaveAngleImpact = waveAngleImpact;
                constructionProperties.ReferenceTimeDegradation = referenceTimeDegradation;
                constructionProperties.ReferenceDegradation = referenceDegradation;
            }

            return constructionProperties;
        }
    }
}