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
using DiKErnel.DomainLibrary.Validators.GrassRevetment;
using DiKErnel.FunctionLibrary.GrassRevetment;
using DiKErnel.Integration.Helpers;
using DiKErnel.Util.Validation;

namespace DiKErnel.Integration.Data.GrassRevetment
{
    internal abstract class GrassRevetmentRayleighDiscreteLocationDependentInput : LocationDependentInput
    {
        private readonly List<double> xValuesProfile = new List<double>();
        private readonly List<double> zValuesProfile = new List<double>();
        private readonly List<double> roughnessCoefficients = new List<double>();

        protected GrassRevetmentRayleighDiscreteLocationDependentInput(double x, double initialDamage,
                                                                       double failureNumber,
                                                                       double criticalCumulativeOverload,
                                                                       double criticalFrontVelocity,
                                                                       double increasedLoadTransitionAlphaM,
                                                                       double reducedStrengthTransitionAlphaS,
                                                                       double averageNumberOfWavesCtm,
                                                                       int fixedNumberOfWaves)
            : base(x, initialDamage, failureNumber)
        {
            CriticalCumulativeOverload = criticalCumulativeOverload;
            CriticalFrontVelocity = criticalFrontVelocity;
            IncreasedLoadTransitionAlphaM = increasedLoadTransitionAlphaM;
            ReducedStrengthTransitionAlphaS = reducedStrengthTransitionAlphaS;
            AverageNumberOfWavesCtm = averageNumberOfWavesCtm;
            FixedNumberOfWaves = fixedNumberOfWaves;
        }

        public double CriticalCumulativeOverload { get; }

        public double CriticalFrontVelocity { get; }

        public double IncreasedLoadTransitionAlphaM { get; }

        public double ReducedStrengthTransitionAlphaS { get; }

        public double AverageNumberOfWavesCtm { get; }

        public int FixedNumberOfWaves { get; }

        public override bool Validate(IReadOnlyList<ITimeDependentInput> timeDependentInputItems,
                                      IProfileData profileData)
        {
            bool baseValidationSuccessful = base.Validate(timeDependentInputItems, profileData);

            var validationIssues = new List<ValidationIssue>
            {
                GrassRevetmentRayleighDiscreteValidator.CriticalCumulativeOverload(CriticalCumulativeOverload),
                GrassRevetmentRayleighDiscreteValidator.CriticalFrontVelocity(CriticalFrontVelocity),
                GrassRevetmentRayleighDiscreteValidator.IncreasedLoadTransitionAlphaM(IncreasedLoadTransitionAlphaM),
                GrassRevetmentRayleighDiscreteValidator.ReducedStrengthTransitionAlphaS(ReducedStrengthTransitionAlphaS),
                RevetmentValidator.AverageNumberOfWavesCtm(AverageNumberOfWavesCtm),
                GrassRevetmentRayleighDiscreteValidator.FixedNumberOfWaves(FixedNumberOfWaves)
            };

            return ValidationHelper.RegisterValidationIssues(validationIssues) && baseValidationSuccessful;
        }

        protected double DikeHeight { get; private set; } = double.NaN;

        protected override void InitializeDerivedLocationDependentInput(IProfileData profileData)
        {
            base.InitializeDerivedLocationDependentInput(profileData);

            InitializeCalculationProfile(profileData);

            DikeHeight = CalculateDikeHeight(profileData);
        }

        protected virtual double CalculateDikeHeight(IProfileData profileData)
        {
            (double, double) outerCrest = CharacteristicPointsHelper.GetCoordinatesForType(
                profileData.CharacteristicPoints, CharacteristicPointType.OuterCrest);

            return outerCrest.Item2;
        }

        protected double CalculateRepresentativeWaveRunup2P(ITimeDependentInput timeDependentInput,
                                                            IProfileData profileData)
        {
            return GrassRevetmentFunctions.RepresentativeWaveRunup2P(
                new GrassRevetmentRepresentative2PInput(timeDependentInput.WaterLevel, timeDependentInput.WaveHeightHm0,
                                                        timeDependentInput.WavePeriodTm10, timeDependentInput.WaveDirection,
                                                        xValuesProfile, zValuesProfile, roughnessCoefficients,
                                                        DikeHeight, profileData.DikeOrientation));
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
    }
}