// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
// 
// This file is part of DiKErnel.
// 
// DiKErnel is free software: you can redistribute it and/or modify it under the terms of the
// GNU Lesser General Public License as published by the Free Software Foundation, either
// version 3 of the License, or (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License along with this
// program. If not, see <http://www.gnu.org/licenses/>.
// 
// All names, logos, and references to "Deltares" are registered trademarks of Stichting
// Deltares and remain full property of Stichting Deltares at all times. All rights reserved.

using System.Collections.Generic;
using DiKErnel.Core.Data;
using DiKErnel.DomainLibrary.Constants;
using DiKErnel.DomainLibrary.Validators;
using DiKErnel.DomainLibrary.Validators.Grass;
using DiKErnel.DomainLibrary.Validators.GrassWaveRunup;
using DiKErnel.FunctionLibrary;
using DiKErnel.FunctionLibrary.Grass;
using DiKErnel.FunctionLibrary.GrassWaveRunup;
using DiKErnel.Integration.Data.Grass;
using DiKErnel.Integration.Helpers;
using DiKErnel.Util.Validation;

namespace DiKErnel.Integration.Data.GrassWaveRunup
{
    internal class GrassWaveRunupBattjesGroenendijkAnalyticalLocationDependentInput : LocationDependentInput
    {
        private readonly List<double> xValuesProfile = new List<double>();
        private readonly List<double> zValuesProfile = new List<double>();
        private readonly List<double> roughnessCoefficients = new List<double>();

        private double verticalDistanceWaterLevelElevation = double.NaN;
        private double averageNumberOfWaves = double.NaN;
        private double representativeWaveRunup2P = double.NaN;
        private double cumulativeOverload = double.NaN;

        public GrassWaveRunupBattjesGroenendijkAnalyticalLocationDependentInput(double x, double initialDamage,
                                                                                double failureNumber,
                                                                                double criticalCumulativeOverload,
                                                                                double frontVelocityCu,
                                                                                double criticalFrontVelocity,
                                                                                double increasedLoadTransitionAlphaM,
                                                                                double reducedStrengthTransitionAlphaS,
                                                                                double averageNumberOfWavesCtm)
            : base(x, initialDamage, failureNumber)
        {
            CriticalCumulativeOverload = criticalCumulativeOverload;
            FrontVelocityCu = frontVelocityCu;
            CriticalFrontVelocity = criticalFrontVelocity;
            IncreasedLoadTransitionAlphaM = increasedLoadTransitionAlphaM;
            ReducedStrengthTransitionAlphaS = reducedStrengthTransitionAlphaS;
            AverageNumberOfWavesCtm = averageNumberOfWavesCtm;
        }

        public double CriticalCumulativeOverload { get; }

        public double FrontVelocityCu { get; }

        public double CriticalFrontVelocity { get; }

        public double IncreasedLoadTransitionAlphaM { get; }

        public double ReducedStrengthTransitionAlphaS { get; }

        public double AverageNumberOfWavesCtm { get; }

        public override bool Validate(IReadOnlyList<ITimeDependentInput> timeDependentInputItems,
                                      IProfileData profileData)
        {
            bool baseValidationSuccessful = base.Validate(timeDependentInputItems, profileData);

            var validationIssues = new List<ValidationIssue>
            {
                GrassWaveRunupBattjesGroenendijkAnalyticalValidator.ForeshoreSlope(profileData.Foreshore.Slope),
                GrassCumulativeOverloadValidator.CriticalCumulativeOverload(CriticalCumulativeOverload),
                GrassWaveRunupValidator.FrontVelocityCu(FrontVelocityCu),
                GrassCumulativeOverloadValidator.CriticalFrontVelocity(CriticalFrontVelocity),
                GrassCumulativeOverloadValidator.IncreasedLoadTransitionAlphaM(IncreasedLoadTransitionAlphaM),
                GrassCumulativeOverloadValidator.ReducedStrengthTransitionAlphaS(ReducedStrengthTransitionAlphaS),
                RevetmentValidator.AverageNumberOfWavesCtm(AverageNumberOfWavesCtm)
            };

            return ValidationHelper.RegisterValidationIssues(validationIssues) && baseValidationSuccessful;
        }

        public override LocationDependentOutput GetLocationDependentOutput(
            IReadOnlyList<TimeDependentOutput> timeDependentOutputItems)
        {
            return new GrassWaveRunupBattjesGroenendijkAnalyticalLocationDependentOutput(timeDependentOutputItems, Z);
        }

        protected override void InitializeDerivedLocationDependentInput(IProfileData profileData)
        {
            base.InitializeDerivedLocationDependentInput(profileData);

            InitializeCalculationProfile(profileData);
        }

        protected override TimeDependentOutput CalculateTimeDependentOutput(double initialDamage,
                                                                            ITimeDependentInput timeDependentInput,
                                                                            IProfileData profileData)
        {
            var incrementDamage = 0d;
            double damage = initialDamage;
            double? timeOfFailure = null;

            verticalDistanceWaterLevelElevation = HydraulicLoadFunctions.VerticalDistanceWaterLevelElevation(
                Z, timeDependentInput.WaterLevel);

            if (verticalDistanceWaterLevelElevation >= 0d)
            {
                double incrementTime = RevetmentFunctions.IncrementTime(timeDependentInput.BeginTime,
                                                                        timeDependentInput.EndTime);

                averageNumberOfWaves = RevetmentFunctions.AverageNumberOfWaves(incrementTime,
                                                                               timeDependentInput.WavePeriodTm10,
                                                                               AverageNumberOfWavesCtm);

                representativeWaveRunup2P = CalculateRepresentativeWaveRunup2P(timeDependentInput, profileData);

                cumulativeOverload = CalculateCumulativeOverload(timeDependentInput, profileData);

                incrementDamage = GrassFunctions.IncrementDamage(cumulativeOverload, CriticalCumulativeOverload);

                damage = RevetmentFunctions.Damage(incrementDamage, initialDamage);

                if (RevetmentFunctions.FailureRevetment(damage, initialDamage, FailureNumber))
                {
                    double durationInTimeStepFailure = RevetmentFunctions.DurationInTimeStepFailure(
                        incrementTime, incrementDamage, FailureNumber, initialDamage);

                    timeOfFailure = RevetmentFunctions.TimeOfFailure(durationInTimeStepFailure,
                                                                     timeDependentInput.BeginTime);
                }
            }

            return new GrassCumulativeOverloadTimeDependentOutput(
                CreateConstructionProperties(incrementDamage, damage, timeOfFailure));
        }

        private double CalculateCumulativeOverload(ITimeDependentInput timeDependentInput, IProfileData profileData)
        {
            Foreshore foreshore = profileData.Foreshore;

            return GrassWaveRunupBattjesGroenendijkAnalyticalFunctions.CumulativeOverload(
                new GrassWaveRunupBattjesGroenendijkAnalyticalCumulativeOverloadInput(
                    averageNumberOfWaves, representativeWaveRunup2P, timeDependentInput.WaterLevel, timeDependentInput.WaveHeightHm0,
                    verticalDistanceWaterLevelElevation, foreshore.Slope, foreshore.Slope, CriticalFrontVelocity, FrontVelocityCu,
                    IncreasedLoadTransitionAlphaM, ReducedStrengthTransitionAlphaS, NaturalConstants.GravitationalAcceleration,
                    GrassWaveRunupBattjesGroenendijkAnalyticalConstants.K1, GrassWaveRunupBattjesGroenendijkAnalyticalConstants.K2));
        }

        private void InitializeCalculationProfile(IProfileData profileData)
        {
            (double, double) outerToe = CharacteristicPointsHelper.GetCoordinatesForType(
                profileData.CharacteristicPoints, CharacteristicPointType.OuterToe);
            (double, double) outerCrest = CharacteristicPointsHelper.GetCoordinatesForType(
                profileData.CharacteristicPoints, CharacteristicPointType.OuterCrest);

            foreach (ProfileSegment profileSegment in profileData.ProfileSegments)
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

        private double CalculateRepresentativeWaveRunup2P(ITimeDependentInput timeDependentInput,
                                                          IProfileData profileData)
        {
            return GrassFunctions.RepresentativeWaveRunup2P(
                new GrassRepresentative2PInput(timeDependentInput.WaterLevel, timeDependentInput.WaveHeightHm0,
                                               timeDependentInput.WavePeriodTm10, timeDependentInput.WaveDirection,
                                               xValuesProfile, zValuesProfile, roughnessCoefficients,
                                               Z, profileData.DikeOrientation));
        }

        private GrassCumulativeOverloadTimeDependentOutputConstructionProperties CreateConstructionProperties(
            double incrementDamage, double damage, double? timeOfFailure)
        {
            var constructionProperties = new GrassCumulativeOverloadTimeDependentOutputConstructionProperties
            {
                IncrementDamage = incrementDamage,
                Damage = damage,
                TimeOfFailure = timeOfFailure,
                VerticalDistanceWaterLevelElevation = verticalDistanceWaterLevelElevation
            };

            if (verticalDistanceWaterLevelElevation >= 0d)
            {
                constructionProperties.RepresentativeWaveRunup2P = representativeWaveRunup2P;
                constructionProperties.CumulativeOverload = cumulativeOverload;
                constructionProperties.AverageNumberOfWaves = averageNumberOfWaves;
            }

            return constructionProperties;
        }
    }
}