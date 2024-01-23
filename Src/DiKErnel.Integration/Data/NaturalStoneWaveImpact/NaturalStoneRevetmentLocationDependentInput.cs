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
using DiKErnel.DomainLibrary;
using DiKErnel.DomainLibrary.Validators.NaturalStoneRevetment;
using DiKErnel.FunctionLibrary;
using DiKErnel.FunctionLibrary.NaturalStoneRevetment;
using DiKErnel.Integration.Helpers;
using DiKErnel.Util.Validation;

namespace DiKErnel.Integration.Data.NaturalStoneWaveImpact
{
    internal class NaturalStoneRevetmentLocationDependentInput : LocationDependentInput
    {
        private double outerToeHeight = double.NaN;
        private double outerCrestHeight = double.NaN;
        private (double, double)? notchOuterBerm;
        private (double, double)? crestOuterBerm;
        private double resistance = double.NaN;
        private double slopeLowerPosition = double.NaN;
        private double slopeLowerLevel = double.NaN;
        private double slopeUpperPosition = double.NaN;
        private double slopeUpperLevel = double.NaN;
        private double outerSlope = double.NaN;
        private double waveSteepnessDeepWater = double.NaN;
        private double distanceMaximumWaveElevation = double.NaN;
        private double surfSimilarityParameter = double.NaN;
        private double normativeWidthWaveImpact = double.NaN;
        private double depthMaximumWaveLoad = double.NaN;
        private double upperLimitLoading = double.NaN;
        private double lowerLimitLoading = double.NaN;
        private bool loadingRevetment;
        private double hydraulicLoad = double.NaN;
        private double waveAngle = double.NaN;
        private double waveAngleImpact = double.NaN;
        private double referenceTimeDegradation = double.NaN;
        private double referenceDegradation = double.NaN;

        public NaturalStoneRevetmentLocationDependentInput(double x, double initialDamage, double failureNumber,
                                                           double relativeDensity, double thicknessTopLayer,
                                                           NaturalStoneWaveImpactHydraulicLoads hydraulicLoads,
                                                           NaturalStoneWaveImpactSlope slope,
                                                           NaturalStoneWaveImpactUpperLimitLoading upperLimitLoading,
                                                           NaturalStoneWaveImpactLowerLimitLoading lowerLimitLoading,
                                                           NaturalStoneWaveImpactDistanceMaximumWaveElevation distanceMaximumWaveElevation,
                                                           NaturalStoneRevetmentNormativeWidthOfWaveImpact normativeWidthOfWaveImpact,
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

        public NaturalStoneRevetmentNormativeWidthOfWaveImpact NormativeWidthOfWaveImpact { get; }

        public NaturalStoneWaveImpactWaveAngleImpact WaveAngleImpact { get; }

        public override bool Validate(IReadOnlyList<ITimeDependentInput> timeDependentInputItems,
                                      IProfileData profileData)
        {
            bool baseValidationSuccessful = base.Validate(timeDependentInputItems, profileData);

            var validationIssues = new List<ValidationIssue>
            {
                NaturalStoneRevetmentValidator.RelativeDensity(RelativeDensity),
                NaturalStoneRevetmentValidator.ThicknessTopLayer(ThicknessTopLayer),
                NaturalStoneRevetmentValidator.SlopeUpperLevelAus(Slope.UpperLevelAus),
                NaturalStoneRevetmentValidator.SlopeLowerLevelAls(Slope.LowerLevelAls)
            };

            return ValidationHelper.RegisterValidationIssues(validationIssues) && baseValidationSuccessful;
        }

        public override LocationDependentOutput GetLocationDependentOutput(
            IReadOnlyList<TimeDependentOutput> timeDependentOutputItems)
        {
            return new NaturalStoneRevetmentLocationDependentOutput(timeDependentOutputItems, Z, resistance);
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

            resistance = NaturalStoneRevetmentFunctions.Resistance(RelativeDensity, ThicknessTopLayer);
        }

        protected override TimeDependentOutput CalculateTimeDependentOutput(double initialDamage,
                                                                            ITimeDependentInput timeDependentInput,
                                                                            IProfileData profileData)
        {
            outerSlope = CalculateOuterSlope(
                timeDependentInput.WaterLevel, timeDependentInput.WaveHeightHm0, profileData);

            double slopeAngle = HydraulicLoadFunctions.SlopeAngle(outerSlope);

            waveSteepnessDeepWater = HydraulicLoadFunctions.WaveSteepnessDeepWater(
                timeDependentInput.WaveHeightHm0, timeDependentInput.WavePeriodTm10,
                Constants.GravitationalAcceleration);

            distanceMaximumWaveElevation = NaturalStoneRevetmentFunctions.DistanceMaximumWaveElevation(
                1.0, waveSteepnessDeepWater, timeDependentInput.WaveHeightHm0,
                DistanceMaximumWaveElevation.DistanceMaximumWaveElevationAsmax,
                DistanceMaximumWaveElevation.DistanceMaximumWaveElevationBsmax);

            surfSimilarityParameter = HydraulicLoadFunctions.SurfSimilarityParameter(
                outerSlope, timeDependentInput.WaveHeightHm0, timeDependentInput.WavePeriodTm10,
                Constants.GravitationalAcceleration);

            normativeWidthWaveImpact = NaturalStoneRevetmentFunctions.NormativeWidthWaveImpact(
                surfSimilarityParameter, timeDependentInput.WaveHeightHm0,
                NormativeWidthOfWaveImpact.NormativeWidthOfWaveImpactAwi,
                NormativeWidthOfWaveImpact.NormativeWidthOfWaveImpactBwi);

            depthMaximumWaveLoad = NaturalStoneRevetmentFunctions.DepthMaximumWaveLoad(
                distanceMaximumWaveElevation, normativeWidthWaveImpact, slopeAngle);

            loadingRevetment = CalculateLoadingRevetment(
                timeDependentInput.WaterLevel, timeDependentInput.WaveHeightHm0);

            var incrementDamage = 0.0;
            double damage = initialDamage;
            double? timeOfFailure = null;

            if (loadingRevetment)
            {
                hydraulicLoad = CalculateHydraulicLoad(timeDependentInput.WaveHeightHm0);

                waveAngle = HydraulicLoadFunctions.WaveAngle(timeDependentInput.WaveDirection, profileData.DikeOrientation);

                waveAngleImpact = NaturalStoneRevetmentFunctions.WaveAngleImpact(waveAngle, WaveAngleImpact.Betamax);

                referenceDegradation = NaturalStoneRevetmentFunctions.ReferenceDegradation(
                    resistance, hydraulicLoad, waveAngleImpact, initialDamage);

                referenceTimeDegradation = NaturalStoneRevetmentFunctions.ReferenceTimeDegradation(
                    referenceDegradation, timeDependentInput.WavePeriodTm10);

                double incrementTime = RevetmentFunctions.IncrementTime(
                    timeDependentInput.BeginTime, timeDependentInput.EndTime);

                double incrementDegradation = NaturalStoneRevetmentFunctions.IncrementDegradation(
                    referenceTimeDegradation, incrementTime, timeDependentInput.WavePeriodTm10);

                incrementDamage = NaturalStoneRevetmentFunctions.IncrementDamage(
                    hydraulicLoad, resistance, incrementDegradation, waveAngleImpact);

                damage = RevetmentFunctions.Damage(incrementDamage, initialDamage);

                if (RevetmentFunctions.FailureRevetment(damage, initialDamage, FailureNumber))
                {
                    timeOfFailure = CalculateTimeOfFailure(timeDependentInput.WavePeriodTm10, timeDependentInput.BeginTime);
                }
            }

            return new NaturalStoneRevetmentTimeDependentOutput(
                CreateConstructionProperties(incrementDamage, damage, timeOfFailure));
        }

        private double CalculateOuterSlope(double waterLevel, double waveHeightHm0, IProfileData profileData)
        {
            slopeUpperLevel = NaturalStoneRevetmentFunctions.SlopeUpperLevel(outerToeHeight, outerCrestHeight,
                                                                             waterLevel, waveHeightHm0,
                                                                             Slope.UpperLevelAus);

            slopeUpperPosition = profileData.GetHorizontalPosition(slopeUpperLevel);

            slopeLowerLevel = NaturalStoneRevetmentFunctions.SlopeLowerLevel(outerToeHeight, slopeUpperLevel,
                                                                             waveHeightHm0, Slope.LowerLevelAls);

            slopeLowerPosition = profileData.GetHorizontalPosition(slopeLowerLevel);

            var outerSlopeInput = new NaturalStoneRevetmentOuterSlopeInput(slopeLowerPosition, slopeLowerLevel,
                                                                           slopeUpperPosition, slopeUpperLevel,
                                                                           outerToeHeight, outerCrestHeight);

            if (notchOuterBerm != null && crestOuterBerm != null)
            {
                outerSlopeInput.NotchOuterBermPosition = notchOuterBerm.Value.Item1;
                outerSlopeInput.NotchOuterBermHeight = notchOuterBerm.Value.Item2;
                outerSlopeInput.CrestOuterBermPosition = crestOuterBerm.Value.Item1;
                outerSlopeInput.CrestOuterBermHeight = crestOuterBerm.Value.Item2;
            }

            return NaturalStoneRevetmentFunctions.OuterSlope(outerSlopeInput);
        }

        private bool CalculateLoadingRevetment(double waterLevel, double waveHeightHm0)
        {
            var lowerLimitLoadingInput = new NaturalStoneRevetmentLimitLoadingInput(
                depthMaximumWaveLoad, surfSimilarityParameter, waterLevel, waveHeightHm0,
                LowerLimitLoading.LowerLimitAll, LowerLimitLoading.LowerLimitBll, LowerLimitLoading.LowerLimitCll);

            lowerLimitLoading = NaturalStoneRevetmentFunctions.LowerLimitLoading(lowerLimitLoadingInput);

            var upperLimitLoadingInput = new NaturalStoneRevetmentLimitLoadingInput(
                depthMaximumWaveLoad, surfSimilarityParameter, waterLevel, waveHeightHm0,
                UpperLimitLoading.UpperLimitAul, UpperLimitLoading.UpperLimitBul, UpperLimitLoading.UpperLimitCul);

            upperLimitLoading = NaturalStoneRevetmentFunctions.UpperLimitLoading(upperLimitLoadingInput);

            return HydraulicLoadFunctions.LoadingRevetment(lowerLimitLoading, upperLimitLoading, Z);
        }

        private double CalculateHydraulicLoad(double waveHeightHm0)
        {
            bool usePlungingBreakers = HydraulicLoads.HydraulicLoadXib >= surfSimilarityParameter;

            return NaturalStoneRevetmentFunctions.HydraulicLoad(
                new NaturalStoneRevetmentHydraulicLoadInput(surfSimilarityParameter, waveHeightHm0,
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

        private double CalculateTimeOfFailure(double wavePeriodTm10, double beginTime)
        {
            double referenceFailure = NaturalStoneRevetmentFunctions.ReferenceFailure(
                resistance, hydraulicLoad, waveAngleImpact, FailureNumber);
            double referenceTimeFailure = NaturalStoneRevetmentFunctions.ReferenceTimeFailure(
                referenceFailure, wavePeriodTm10);
            double durationInTimeStepFailure = NaturalStoneRevetmentFunctions.DurationInTimeStepFailure(
                referenceTimeFailure, referenceTimeDegradation);

            return RevetmentFunctions.TimeOfFailure(durationInTimeStepFailure, beginTime);
        }

        private NaturalStoneRevetmentTimeDependentOutputConstructionProperties CreateConstructionProperties(
            double incrementDamage, double damage, double? timeOfFailure)
        {
            var constructionProperties = new NaturalStoneRevetmentTimeDependentOutputConstructionProperties
            {
                IncrementDamage = incrementDamage,
                Damage = damage,
                TimeOfFailure = timeOfFailure,
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