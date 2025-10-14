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
using DiKErnel.DomainLibrary.Validators;
using DiKErnel.DomainLibrary.Validators.Grass;
using DiKErnel.FunctionLibrary;
using DiKErnel.FunctionLibrary.Grass;
using DiKErnel.Integration.Helpers;
using DiKErnel.Util.Validation;

namespace DiKErnel.Integration.Data.Grass
{
    internal abstract class GrassCumulativeOverloadLocationDependentInput : LocationDependentInput
    {
        private readonly List<double> xValuesProfile = new List<double>();
        private readonly List<double> zValuesProfile = new List<double>();
        private readonly List<double> roughnessCoefficients = new List<double>();

        protected GrassCumulativeOverloadLocationDependentInput(double x, double initialDamage, double failureNumber,
                                                                double criticalCumulativeOverload,
                                                                double criticalFrontVelocity,
                                                                double increasedLoadTransitionAlphaM,
                                                                double reducedStrengthTransitionAlphaS,
                                                                double averageNumberOfWavesCtm)
            : base(x, initialDamage, failureNumber)
        {
            CriticalCumulativeOverload = criticalCumulativeOverload;
            CriticalFrontVelocity = criticalFrontVelocity;
            IncreasedLoadTransitionAlphaM = increasedLoadTransitionAlphaM;
            ReducedStrengthTransitionAlphaS = reducedStrengthTransitionAlphaS;
            AverageNumberOfWavesCtm = averageNumberOfWavesCtm;
        }

        public double CriticalCumulativeOverload { get; }

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
                GrassCumulativeOverloadValidator.CriticalCumulativeOverload(CriticalCumulativeOverload),
                GrassCumulativeOverloadValidator.CriticalFrontVelocity(CriticalFrontVelocity),
                GrassCumulativeOverloadValidator.IncreasedLoadTransitionAlphaM(IncreasedLoadTransitionAlphaM),
                GrassCumulativeOverloadValidator.ReducedStrengthTransitionAlphaS(ReducedStrengthTransitionAlphaS),
                RevetmentValidator.AverageNumberOfWavesCtm(AverageNumberOfWavesCtm)
            };

            return ValidationHelper.RegisterValidationIssues(validationIssues) && baseValidationSuccessful;
        }

        public override void Initialize(IProfileData profileData)
        {
            base.Initialize(profileData);

            InitializeCalculationProfile(profileData);

            DikeHeight = CalculateDikeHeight(profileData);
        }

        public override LocationDependentOutput GetLocationDependentOutput(
            IReadOnlyList<TimeDependentOutput> timeDependentOutputItems)
        {
            return new GrassCumulativeOverloadLocationDependentOutput(InitialDamage, FailureNumber, timeDependentOutputItems, Z);
        }

        protected double DikeHeight { get; private set; } = double.NaN;

        protected override TimeDependentOutput CalculateTimeDependentOutput(ITimeDependentInput timeDependentInput,
                                                                            IProfileData profileData)
        {
            var incrementDamage = 0d;

            double verticalDistanceWaterLevelElevation = HydraulicLoadFunctions.VerticalDistanceWaterLevelElevation(
                GetRunupHeight(), timeDependentInput.WaterLevel);

            double averageNumberOfWaves = double.NaN;
            double representativeWaveRunup2P = double.NaN;
            double cumulativeOverload = double.NaN;

            if (HasLoading(verticalDistanceWaterLevelElevation))
            {
                double incrementTime = RevetmentFunctions.IncrementTime(timeDependentInput.BeginTime, timeDependentInput.EndTime);

                averageNumberOfWaves = RevetmentFunctions.AverageNumberOfWaves(incrementTime, timeDependentInput.WavePeriodTm10,
                                                                               AverageNumberOfWavesCtm);

                representativeWaveRunup2P = CalculateRepresentativeWaveRunup2P(timeDependentInput, profileData);

                cumulativeOverload = CalculateCumulativeOverload(averageNumberOfWaves, representativeWaveRunup2P,
                                                                 verticalDistanceWaterLevelElevation, timeDependentInput, profileData);

                incrementDamage = GrassCumulativeOverloadFunctions.IncrementDamage(cumulativeOverload, CriticalCumulativeOverload);
            }

            return new GrassCumulativeOverloadTimeDependentOutput(
                CreateConstructionProperties(incrementDamage, verticalDistanceWaterLevelElevation, representativeWaveRunup2P,
                                             cumulativeOverload, averageNumberOfWaves));
        }

        protected abstract double CalculateDikeHeight(IProfileData profileData);

        protected abstract double GetRunupHeight();

        protected abstract bool HasLoading(double verticalDistanceWaterLevelElevation);

        protected abstract double CalculateCumulativeOverload(double averageNumberOfWaves,
                                                              double representativeWaveRunup2P,
                                                              double verticalDistanceWaterLevelElevation,
                                                              ITimeDependentInput timeDependentInput,
                                                              IProfileData profileData);

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
            return GrassCumulativeOverloadFunctions.RepresentativeWaveRunup2P(
                new GrassRepresentative2PInput(timeDependentInput.WaterLevel, timeDependentInput.WaveHeightHm0,
                                               timeDependentInput.WavePeriodTm10, timeDependentInput.WaveDirection,
                                               xValuesProfile, zValuesProfile, roughnessCoefficients, DikeHeight,
                                               profileData.DikeOrientation));
        }

        private GrassCumulativeOverloadTimeDependentOutputConstructionProperties CreateConstructionProperties(
            double incrementDamage, double verticalDistanceWaterLevelElevation, double representativeWaveRunup2P, double cumulativeOverload,
            double averageNumberOfWaves)
        {
            var constructionProperties = new GrassCumulativeOverloadTimeDependentOutputConstructionProperties
            {
                IncrementDamage = incrementDamage,
                VerticalDistanceWaterLevelElevation = verticalDistanceWaterLevelElevation
            };

            if (HasLoading(verticalDistanceWaterLevelElevation))
            {
                constructionProperties.RepresentativeWaveRunup2P = representativeWaveRunup2P;
                constructionProperties.CumulativeOverload = cumulativeOverload;
                constructionProperties.AverageNumberOfWaves = averageNumberOfWaves;
            }

            return constructionProperties;
        }
    }
}