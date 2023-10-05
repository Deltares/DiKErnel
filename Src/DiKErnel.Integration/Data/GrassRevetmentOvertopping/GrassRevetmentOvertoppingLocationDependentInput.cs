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

using System;
using System.Collections.Generic;
using System.Linq;
using DiKErnel.Core.Data;
using DiKErnel.DomainLibrary;
using DiKErnel.DomainLibrary.Validators;
using DiKErnel.DomainLibrary.Validators.GrassRevetment;
using DiKErnel.DomainLibrary.Validators.GrassRevetmentOvertopping;
using DiKErnel.FunctionLibrary;
using DiKErnel.FunctionLibrary.GrassRevetment;
using DiKErnel.FunctionLibrary.GrassRevetmentOvertopping;
using DiKErnel.Integration.Helpers;
using DiKErnel.Util.Validation;

namespace DiKErnel.Integration.Data.GrassRevetmentOvertopping
{
    internal class GrassRevetmentOvertoppingLocationDependentInput : LocationDependentInput
    {
        private readonly List<double> xValuesProfile = new List<double>();
        private readonly List<double> zValuesProfile = new List<double>();
        private readonly List<double> roughnessCoefficients = new List<double>();
        private double dikeHeight = double.NaN;
        private double accelerationAlphaA = double.NaN;

        private double verticalDistanceWaterLevelElevation = double.NaN;
        private double representativeWaveRunup2P = double.NaN;
        private double cumulativeOverload = double.NaN;

        public GrassRevetmentOvertoppingLocationDependentInput(
            double x, double initialDamage, double failureNumber, double criticalCumulativeOverload,
            double criticalFrontVelocity, double increasedLoadTransitionAlphaM, double reducedStrengthTransitionAlphaS,
            double averageNumberOfWavesCtm, int fixedNumberOfWaves, double frontVelocityCwo,
            GrassRevetmentOvertoppingLocationDependentAccelerationAlphaA locationDependentAccelerationAlphaA,
            double? enforcedDikeHeight)
            : base(x, initialDamage, failureNumber)
        {
            CriticalCumulativeOverload = criticalCumulativeOverload;
            CriticalFrontVelocity = criticalFrontVelocity;
            IncreasedLoadTransitionAlphaM = increasedLoadTransitionAlphaM;
            ReducedStrengthTransitionAlphaS = reducedStrengthTransitionAlphaS;
            AverageNumberOfWavesCtm = averageNumberOfWavesCtm;
            FixedNumberOfWaves = fixedNumberOfWaves;
            FrontVelocityCwo = frontVelocityCwo;
            LocationDependentAccelerationAlphaA = locationDependentAccelerationAlphaA;
            EnforcedDikeHeight = enforcedDikeHeight;
        }

        public double CriticalCumulativeOverload { get; }

        public double CriticalFrontVelocity { get; }

        public double IncreasedLoadTransitionAlphaM { get; }

        public double ReducedStrengthTransitionAlphaS { get; }

        public double AverageNumberOfWavesCtm { get; }

        public int FixedNumberOfWaves { get; }

        public double FrontVelocityCwo { get; }

        public GrassRevetmentOvertoppingLocationDependentAccelerationAlphaA LocationDependentAccelerationAlphaA { get; }

        public double? EnforcedDikeHeight { get; }

        public override bool Validate(IReadOnlyList<ITimeDependentInput> timeDependentInputItems,
                                      IProfileData profileData)
        {
            bool baseValidationSuccessful = base.Validate(timeDependentInputItems, profileData);

            (double, double) outerCrest = CharacteristicPointsHelper.GetCoordinatesForType(
                profileData.CharacteristicPoints, CharacteristicPointType.OuterCrest);

            double calculatedDikeHeight = CalculateDikeHeight(outerCrest, profileData.ProfileSegments,
                                                              profileData.GetVerticalHeight(X));

            var validationIssues = new List<ValidationIssue>();

            if (timeDependentInputItems.Any(timeDependentInput => timeDependentInput.WaterLevel > calculatedDikeHeight))
            {
                validationIssues.Add(new ValidationIssue(ValidationIssueType.Warning,
                                                         "For one or more time steps the water level exceeds the " +
                                                         "dike height. No damage will be calculated for these " +
                                                         "time steps."));
            }

            validationIssues.Add(GrassRevetmentValidator.CriticalCumulativeOverload(CriticalCumulativeOverload));
            validationIssues.Add(GrassRevetmentValidator.CriticalFrontVelocity(CriticalFrontVelocity));
            validationIssues.Add(GrassRevetmentOvertoppingValidator.AccelerationAlphaA(
                                     LocationDependentAccelerationAlphaA.ValueAtCrest));
            validationIssues.Add(GrassRevetmentOvertoppingValidator.AccelerationAlphaA(
                                     LocationDependentAccelerationAlphaA.ValueAtInnerSlope));
            validationIssues.Add(GrassRevetmentValidator.FixedNumberOfWaves(FixedNumberOfWaves));
            validationIssues.Add(GrassRevetmentOvertoppingValidator.FrontVelocityCwo(FrontVelocityCwo));
            validationIssues.Add(RevetmentValidator.AverageNumberOfWavesCtm(AverageNumberOfWavesCtm));
            validationIssues.Add(GrassRevetmentValidator.IncreasedLoadTransitionAlphaM(IncreasedLoadTransitionAlphaM));
            validationIssues.Add(GrassRevetmentValidator.ReducedStrengthTransitionAlphaS(
                                     ReducedStrengthTransitionAlphaS));

            return ValidationHelper.RegisterValidationIssues(validationIssues) && baseValidationSuccessful;
        }

        public override LocationDependentOutput GetLocationDependentOutput(
            IReadOnlyList<TimeDependentOutput> timeDependentOutputItems)
        {
            return new GrassRevetmentOvertoppingLocationDependentOutput(timeDependentOutputItems);
        }

        protected override void InitializeDerivedLocationDependentInput(IProfileData profileData)
        {
            base.InitializeDerivedLocationDependentInput(profileData);

            (double, double) outerToe = CharacteristicPointsHelper.GetCoordinatesForType(
                profileData.CharacteristicPoints, CharacteristicPointType.OuterToe);
            (double, double) outerCrest = CharacteristicPointsHelper.GetCoordinatesForType(
                profileData.CharacteristicPoints, CharacteristicPointType.OuterCrest);
            (double, double) innerCrest = CharacteristicPointsHelper.GetCoordinatesForType(
                profileData.CharacteristicPoints, CharacteristicPointType.InnerCrest);

            InitializeCalculationProfile(outerToe, outerCrest, profileData.ProfileSegments);
            InitializeDikeHeight(outerCrest, profileData.ProfileSegments);
            InitializeAccelerationAlphaA(outerCrest, innerCrest);
        }

        protected override TimeDependentOutput CalculateTimeDependentOutput(double initialDamage,
                                                                            ITimeDependentInput timeDependentInput,
                                                                            IProfileData profileData)
        {
            var incrementDamage = 0.0;
            double damage = initialDamage;
            int? timeOfFailure = null;
            double? averageNumberOfWaves = null;

            verticalDistanceWaterLevelElevation = HydraulicLoadFunctions.VerticalDistanceWaterLevelElevation(
                dikeHeight, timeDependentInput.WaterLevel);

            if (verticalDistanceWaterLevelElevation >= 0.0)
            {
                int incrementTime = RevetmentFunctions.IncrementTime(timeDependentInput.BeginTime,
                                                                     timeDependentInput.EndTime);
                averageNumberOfWaves = RevetmentFunctions.AverageNumberOfWaves(incrementTime,
                                                                               timeDependentInput.WavePeriodTm10,
                                                                               AverageNumberOfWavesCtm);
                double waveDirection = HydraulicLoadFunctions.WaveDirection(timeDependentInput.WaveAngle);

                representativeWaveRunup2P = CalculateRepresentativeWaveRunup2P(timeDependentInput.WaterLevel,
                                                                               timeDependentInput.WaveHeightHm0,
                                                                               timeDependentInput.WavePeriodTm10,
                                                                               waveDirection);

                cumulativeOverload = CalculateCumulativeOverload(averageNumberOfWaves.Value);

                incrementDamage = GrassRevetmentFunctions.IncrementDamage(cumulativeOverload,
                                                                          CriticalCumulativeOverload);

                damage = RevetmentFunctions.Damage(incrementDamage, initialDamage);

                if (RevetmentFunctions.FailureRevetment(damage, initialDamage, FailureNumber))
                {
                    double durationInTimeStepFailure = RevetmentFunctions.DurationInTimeStepFailure(
                        incrementTime, incrementDamage, FailureNumber, initialDamage);

                    timeOfFailure = RevetmentFunctions.TimeOfFailure(durationInTimeStepFailure,
                                                                     timeDependentInput.BeginTime);
                }
            }

            return new GrassRevetmentOvertoppingTimeDependentOutput(
                CreateConstructionProperties(incrementDamage, damage, averageNumberOfWaves, timeOfFailure));
        }

        private void InitializeCalculationProfile((double, double) outerToe, (double, double) outerCrest,
                                                  IReadOnlyList<ProfileSegment> profileSegments)
        {
            foreach (ProfileSegment profileSegment in profileSegments)
            {
                if (profileSegment.StartPoint.X >= outerToe.Item1 && profileSegment.StartPoint.X < outerCrest.Item1)
                {
                    xValuesProfile.Add(profileSegment.StartPoint.X);
                    zValuesProfile.Add(profileSegment.StartPoint.Z);
                    roughnessCoefficients.Add(profileSegment.RoughnessCoefficient);
                }
            }

            xValuesProfile.Add(outerCrest.Item1);
            zValuesProfile.Add(outerCrest.Item2);
        }

        private void InitializeDikeHeight((double, double) outerCrest, IReadOnlyList<ProfileSegment> profileSegments)
        {
            dikeHeight = CalculateDikeHeight(outerCrest, profileSegments, Z);
        }

        private void InitializeAccelerationAlphaA((double, double) outerCrest, (double, double) innerCrest)
        {
            accelerationAlphaA = X >= outerCrest.Item1 && X <= innerCrest.Item1
                                     ? LocationDependentAccelerationAlphaA.ValueAtCrest
                                     : LocationDependentAccelerationAlphaA.ValueAtInnerSlope;
        }

        private double CalculateRepresentativeWaveRunup2P(double waterLevel, double waveHeightHm0,
                                                          double wavePeriodTm10, double waveDirection)
        {
            return GrassRevetmentOvertoppingFunctions.RepresentativeWaveRunup2P(
                new GrassRevetmentOvertoppingRepresentative2PInput(waterLevel, waveHeightHm0, wavePeriodTm10,
                                                                   waveDirection, xValuesProfile, zValuesProfile,
                                                                   roughnessCoefficients, dikeHeight));
        }

        private double CalculateCumulativeOverload(double averageNumberOfWaves)
        {
            return GrassRevetmentOvertoppingFunctions.CumulativeOverload(
                new GrassRevetmentOvertoppingCumulativeOverloadInput(averageNumberOfWaves,
                                                                     representativeWaveRunup2P,
                                                                     FixedNumberOfWaves,
                                                                     verticalDistanceWaterLevelElevation,
                                                                     CriticalFrontVelocity,
                                                                     IncreasedLoadTransitionAlphaM,
                                                                     ReducedStrengthTransitionAlphaS,
                                                                     Constants.GravitationalAcceleration,
                                                                     accelerationAlphaA,
                                                                     FrontVelocityCwo));
        }

        private double CalculateDikeHeight((double, double) outerCrest, IReadOnlyList<ProfileSegment> profileSegments,
                                           double locationHeight)
        {
            if (EnforcedDikeHeight != null)
            {
                return EnforcedDikeHeight.Value;
            }

            double calculateDikeHeight = locationHeight;

            foreach (ProfilePoint segmentStartPoint in profileSegments.Select(s => s.StartPoint))
            {
                if (segmentStartPoint.X >= outerCrest.Item1 && segmentStartPoint.X < X)
                {
                    calculateDikeHeight = Math.Max(calculateDikeHeight, segmentStartPoint.Z);
                }
            }

            return calculateDikeHeight;
        }

        private GrassRevetmentOvertoppingTimeDependentOutputConstructionProperties CreateConstructionProperties(
            double incrementDamage, double damage, double? averageNumberOfWaves, int? timeOfFailure)
        {
            var constructionProperties = new GrassRevetmentOvertoppingTimeDependentOutputConstructionProperties
            {
                IncrementDamage = incrementDamage,
                Damage = damage,
                TimeOfFailure = timeOfFailure,
                VerticalDistanceWaterLevelElevation = verticalDistanceWaterLevelElevation,
                AverageNumberOfWaves = averageNumberOfWaves
            };

            if (verticalDistanceWaterLevelElevation >= 0.0)
            {
                constructionProperties.RepresentativeWaveRunup2P = representativeWaveRunup2P;
                constructionProperties.CumulativeOverload = cumulativeOverload;
            }

            return constructionProperties;
        }
    }
}