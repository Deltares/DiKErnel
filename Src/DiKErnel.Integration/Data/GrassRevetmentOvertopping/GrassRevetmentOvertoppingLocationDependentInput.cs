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
using DiKErnel.DomainLibrary.Validators.GrassRevetmentOvertopping;
using DiKErnel.FunctionLibrary;
using DiKErnel.FunctionLibrary.GrassRevetment;
using DiKErnel.FunctionLibrary.GrassRevetmentOvertopping;
using DiKErnel.Integration.Data.GrassRevetment;
using DiKErnel.Integration.Helpers;
using DiKErnel.Util.Validation;

namespace DiKErnel.Integration.Data.GrassRevetmentOvertopping
{
    internal class GrassRevetmentOvertoppingLocationDependentInput : GrassRevetmentRayleighDiscreteLocationDependentInput
    {
        private double accelerationAlphaA = double.NaN;
        private double verticalDistanceWaterLevelElevation = double.NaN;
        private double representativeWaveRunup2P = double.NaN;
        private double cumulativeOverload = double.NaN;
        private double averageNumberOfWaves = double.NaN;

        public GrassRevetmentOvertoppingLocationDependentInput(
            double x, double initialDamage, double failureNumber, double criticalCumulativeOverload,
            double criticalFrontVelocity, double increasedLoadTransitionAlphaM, double reducedStrengthTransitionAlphaS,
            double averageNumberOfWavesCtm, int fixedNumberOfWaves, double frontVelocityCwo,
            GrassRevetmentOvertoppingLocationDependentAccelerationAlphaA locationDependentAccelerationAlphaA,
            double? enforcedDikeHeight)
            : base(x, initialDamage, failureNumber, criticalCumulativeOverload, criticalFrontVelocity,
                   increasedLoadTransitionAlphaM, reducedStrengthTransitionAlphaS, averageNumberOfWavesCtm,
                   fixedNumberOfWaves)
        {
            FrontVelocityCwo = frontVelocityCwo;
            LocationDependentAccelerationAlphaA = locationDependentAccelerationAlphaA;
            EnforcedDikeHeight = enforcedDikeHeight;
        }

        public double FrontVelocityCwo { get; }

        public GrassRevetmentOvertoppingLocationDependentAccelerationAlphaA LocationDependentAccelerationAlphaA { get; }

        public double? EnforcedDikeHeight { get; }

        public override bool Validate(IReadOnlyList<ITimeDependentInput> timeDependentInputItems,
                                      IProfileData profileData)
        {
            bool baseValidationSuccessful = base.Validate(timeDependentInputItems, profileData);

            double calculatedDikeHeight = CalculateDikeHeight(profileData);

            var validationIssues = new List<ValidationIssue>();

            if (timeDependentInputItems.Any(timeDependentInput => timeDependentInput.WaterLevel > calculatedDikeHeight))
            {
                validationIssues.Add(new ValidationIssue(ValidationIssueType.Warning,
                                                         "For one or more time steps the water level exceeds the " +
                                                         "dike height. No damage will be calculated for these " +
                                                         "time steps."));
            }

            validationIssues.Add(GrassRevetmentOvertoppingValidator.AccelerationAlphaA(
                                     LocationDependentAccelerationAlphaA.ValueAtCrest));
            validationIssues.Add(GrassRevetmentOvertoppingValidator.AccelerationAlphaA(
                                     LocationDependentAccelerationAlphaA.ValueAtInnerSlope));
            validationIssues.Add(GrassRevetmentOvertoppingValidator.FrontVelocityCwo(FrontVelocityCwo));

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

            InitializeAccelerationAlphaA(profileData);
        }

        protected override TimeDependentOutput CalculateTimeDependentOutput(double initialDamage,
                                                                            ITimeDependentInput timeDependentInput,
                                                                            IProfileData profileData)
        {
            var incrementDamage = 0.0;
            double damage = initialDamage;
            double? timeOfFailure = null;

            verticalDistanceWaterLevelElevation = HydraulicLoadFunctions.VerticalDistanceWaterLevelElevation(
                DikeHeight, timeDependentInput.WaterLevel);

            if (verticalDistanceWaterLevelElevation >= 0.0)
            {
                double incrementTime = RevetmentFunctions.IncrementTime(timeDependentInput.BeginTime,
                                                                        timeDependentInput.EndTime);

                averageNumberOfWaves = RevetmentFunctions.AverageNumberOfWaves(incrementTime,
                                                                               timeDependentInput.WavePeriodTm10,
                                                                               AverageNumberOfWavesCtm);

                representativeWaveRunup2P = CalculateRepresentativeWaveRunup2P(timeDependentInput, profileData);

                cumulativeOverload = CalculateCumulativeOverload();

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
                CreateConstructionProperties(incrementDamage, damage, timeOfFailure));
        }

        protected override double CalculateDikeHeight(IProfileData profileData)
        {
            if (EnforcedDikeHeight != null)
            {
                return EnforcedDikeHeight.Value;
            }

            (double, double) outerCrest = CharacteristicPointsHelper.GetCoordinatesForType(
                profileData.CharacteristicPoints, CharacteristicPointType.OuterCrest);

            double calculatedDikeHeight = profileData.GetVerticalHeight(X);

            foreach (ProfilePoint segmentStartPoint in profileData.ProfileSegments.Select(s => s.StartPoint))
            {
                if (segmentStartPoint.X >= outerCrest.Item1 && segmentStartPoint.X < X)
                {
                    calculatedDikeHeight = Math.Max(calculatedDikeHeight, segmentStartPoint.Z);
                }
            }

            return calculatedDikeHeight;
        }

        private void InitializeAccelerationAlphaA(IProfileData profileData)
        {
            (double, double) outerCrest = CharacteristicPointsHelper.GetCoordinatesForType(
                profileData.CharacteristicPoints, CharacteristicPointType.OuterCrest);
            (double, double) innerCrest = CharacteristicPointsHelper.GetCoordinatesForType(
                profileData.CharacteristicPoints, CharacteristicPointType.InnerCrest);

            accelerationAlphaA = X >= outerCrest.Item1 && X <= innerCrest.Item1
                                     ? LocationDependentAccelerationAlphaA.ValueAtCrest
                                     : LocationDependentAccelerationAlphaA.ValueAtInnerSlope;
        }

        private double CalculateCumulativeOverload()
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

        private GrassRevetmentOvertoppingTimeDependentOutputConstructionProperties CreateConstructionProperties(
            double incrementDamage, double damage, double? timeOfFailure)
        {
            var constructionProperties = new GrassRevetmentOvertoppingTimeDependentOutputConstructionProperties
            {
                IncrementDamage = incrementDamage,
                Damage = damage,
                TimeOfFailure = timeOfFailure,
                VerticalDistanceWaterLevelElevation = verticalDistanceWaterLevelElevation
            };

            if (verticalDistanceWaterLevelElevation >= 0.0)
            {
                constructionProperties.RepresentativeWaveRunup2P = representativeWaveRunup2P;
                constructionProperties.CumulativeOverload = cumulativeOverload;
                constructionProperties.AverageNumberOfWaves = averageNumberOfWaves;
            }

            return constructionProperties;
        }
    }
}