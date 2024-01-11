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
using DiKErnel.DomainLibrary.Validators.GrassRevetment;
using DiKErnel.DomainLibrary.Validators.GrassRevetmentWaveRunup;
using DiKErnel.FunctionLibrary;
using DiKErnel.FunctionLibrary.GrassRevetment;
using DiKErnel.FunctionLibrary.GrassRevetmentWaveRunup;
using DiKErnel.Integration.Helpers;
using DiKErnel.Util.Validation;

namespace DiKErnel.Integration.Data.GrassRevetmentWaveRunup
{
    internal class GrassRevetmentWaveRunupRayleighLocationDependentInput : GrassRevetmentWaveRunupLocationDependentInput
    {
        private readonly List<double> xValuesProfile = new List<double>();
        private readonly List<double> zValuesProfile = new List<double>();
        private readonly List<double> roughnessCoefficients = new List<double>();

        private double dikeHeight = double.NaN;
        private double verticalDistanceWaterLevelElevation = double.NaN;
        private double representativeWaveRunup2P = double.NaN;
        private double cumulativeOverload = double.NaN;
        private double averageNumberOfWaves = double.NaN;

        public GrassRevetmentWaveRunupRayleighLocationDependentInput(double x, double initialDamage,
                                                                     double failureNumber,
                                                                     double criticalCumulativeOverload,
                                                                     double criticalFrontVelocity,
                                                                     double increasedLoadTransitionAlphaM,
                                                                     double reducedStrengthTransitionAlphaS,
                                                                     double averageNumberOfWavesCtm,
                                                                     int fixedNumberOfWaves, double frontVelocityCu)
            : base(x, initialDamage, failureNumber, criticalCumulativeOverload, criticalFrontVelocity,
                   increasedLoadTransitionAlphaM, reducedStrengthTransitionAlphaS, averageNumberOfWavesCtm)
        {
            FixedNumberOfWaves = fixedNumberOfWaves;
            FrontVelocityCu = frontVelocityCu;
        }

        public int FixedNumberOfWaves { get; }

        public double FrontVelocityCu { get; }

        public override bool Validate(IReadOnlyList<ITimeDependentInput> timeDependentInputItems,
                                      IProfileData profileData)
        {
            bool baseValidationSuccessful = base.Validate(timeDependentInputItems, profileData);

            var validationIssues = new List<ValidationIssue>
            {
                GrassRevetmentValidator.FixedNumberOfWaves(FixedNumberOfWaves),
                GrassRevetmentWaveRunupRayleighValidator.FrontVelocityCu(FrontVelocityCu)
            };

            return ValidationHelper.RegisterValidationIssues(validationIssues) && baseValidationSuccessful;
        }

        public override LocationDependentOutput GetLocationDependentOutput(
            IReadOnlyList<TimeDependentOutput> timeDependentOutputItems)
        {
            return new GrassRevetmentWaveRunupRayleighLocationDependentOutput(timeDependentOutputItems, Z);
        }

        protected override void InitializeDerivedLocationDependentInput(IProfileData profileData)
        {
            base.InitializeDerivedLocationDependentInput(profileData);

            (double, double) outerToe = CharacteristicPointsHelper.GetCoordinatesForType(
                profileData.CharacteristicPoints, CharacteristicPointType.OuterToe);
            (double, double) outerCrest = CharacteristicPointsHelper.GetCoordinatesForType(
                profileData.CharacteristicPoints, CharacteristicPointType.OuterCrest);

            InitializeCalculationProfile(outerToe, outerCrest, profileData.ProfileSegments);

            dikeHeight = outerCrest.Item2;
        }

        protected override TimeDependentOutput CalculateTimeDependentOutput(double initialDamage,
                                                                            ITimeDependentInput timeDependentInput,
                                                                            IProfileData profileData)
        {
            var incrementDamage = 0.0;
            double damage = initialDamage;
            double? timeOfFailure = null;

            verticalDistanceWaterLevelElevation = HydraulicLoadFunctions.VerticalDistanceWaterLevelElevation(
                Z, timeDependentInput.WaterLevel);

            if (verticalDistanceWaterLevelElevation > 0.0)
            {
                double incrementTime = RevetmentFunctions.IncrementTime(timeDependentInput.BeginTime,
                                                                        timeDependentInput.EndTime);

                averageNumberOfWaves = RevetmentFunctions.AverageNumberOfWaves(incrementTime,
                                                                               timeDependentInput.WavePeriodTm10,
                                                                               AverageNumberOfWavesCtm);

                representativeWaveRunup2P = CalculateRepresentativeWaveRunup2P(timeDependentInput.WaterLevel,
                                                                               timeDependentInput.WaveHeightHm0,
                                                                               timeDependentInput.WavePeriodTm10,
                                                                               timeDependentInput.WaveDirection,
                                                                               profileData.DikeOrientation);

                cumulativeOverload = CalculateCumulativeOverload();

                incrementDamage = GrassRevetmentFunctions.IncrementDamage(cumulativeOverload,
                                                                          CriticalCumulativeOverload);

                damage = RevetmentFunctions.Damage(incrementDamage, initialDamage);

                if (RevetmentFunctions.FailureRevetment(damage, initialDamage, FailureNumber))
                {
                    double durationInTimeStepFailure = RevetmentFunctions.DurationInTimeStepFailure(
                        incrementTime, incrementDamage, FailureNumber,
                        initialDamage);

                    timeOfFailure = RevetmentFunctions.TimeOfFailure(durationInTimeStepFailure,
                                                                     timeDependentInput.BeginTime);
                }
            }

            return new GrassRevetmentWaveRunupRayleighTimeDependentOutput(
                CreateConstructionProperties(incrementDamage, damage, timeOfFailure));
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

        private double CalculateRepresentativeWaveRunup2P(double waterLevel, double waveHeightHm0,
                                                          double wavePeriodTm10, double waveDirection,
                                                          double dikeOrientation)
        {
            return GrassRevetmentFunctions.RepresentativeWaveRunup2P(
                new GrassRevetmentRepresentative2PInput(waterLevel, waveHeightHm0, wavePeriodTm10, waveDirection,
                                                        xValuesProfile, zValuesProfile, roughnessCoefficients,
                                                        dikeHeight, dikeOrientation));
        }

        private double CalculateCumulativeOverload()
        {
            return GrassRevetmentWaveRunupRayleighFunctions.CumulativeOverload(
                new GrassRevetmentWaveRunupRayleighCumulativeOverloadInput(averageNumberOfWaves,
                                                                           representativeWaveRunup2P,
                                                                           FixedNumberOfWaves,
                                                                           verticalDistanceWaterLevelElevation,
                                                                           CriticalFrontVelocity,
                                                                           IncreasedLoadTransitionAlphaM,
                                                                           ReducedStrengthTransitionAlphaS,
                                                                           Constants.GravitationalAcceleration,
                                                                           FrontVelocityCu));
        }

        private GrassRevetmentWaveRunupRayleighTimeDependentOutputConstructionProperties CreateConstructionProperties(
            double incrementDamage, double damage, double? timeOfFailure)
        {
            var constructionProperties = new GrassRevetmentWaveRunupRayleighTimeDependentOutputConstructionProperties
            {
                IncrementDamage = incrementDamage,
                Damage = damage,
                TimeOfFailure = timeOfFailure,
                VerticalDistanceWaterLevelElevation = verticalDistanceWaterLevelElevation
            };

            if (verticalDistanceWaterLevelElevation > 0.0)
            {
                constructionProperties.RepresentativeWaveRunup2P = representativeWaveRunup2P;
                constructionProperties.CumulativeOverload = cumulativeOverload;
                constructionProperties.AverageNumberOfWaves = averageNumberOfWaves;
            }

            return constructionProperties;
        }
    }
}