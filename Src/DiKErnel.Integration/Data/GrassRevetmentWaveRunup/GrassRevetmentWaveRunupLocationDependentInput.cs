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

namespace DiKErnel.Integration.Data.GrassRevetmentWaveRunup
{
    internal abstract class GrassRevetmentWaveRunupLocationDependentInput : LocationDependentInput
    {
        private readonly List<double> xValuesProfile = new List<double>();
        private readonly List<double> zValuesProfile = new List<double>();
        private readonly List<double> roughnessCoefficients = new List<double>();

        private double dikeHeight = double.NaN;

        protected GrassRevetmentWaveRunupLocationDependentInput(double x, double initialDamage, double failureNumber,
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
                GrassRevetmentValidator.CriticalCumulativeOverload(CriticalCumulativeOverload),
                GrassRevetmentValidator.CriticalFrontVelocity(CriticalFrontVelocity),
                GrassRevetmentValidator.IncreasedLoadTransitionAlphaM(IncreasedLoadTransitionAlphaM),
                GrassRevetmentValidator.ReducedStrengthTransitionAlphaS(ReducedStrengthTransitionAlphaS),
                RevetmentValidator.AverageNumberOfWavesCtm(AverageNumberOfWavesCtm)
            };

            return ValidationHelper.RegisterValidationIssues(validationIssues) && baseValidationSuccessful;
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

        protected double CalculateRepresentativeWaveRunup2P(double waterLevel, double waveHeightHm0,
                                                            double wavePeriodTm10, double waveDirection,
                                                            double dikeOrientation)
        {
            return GrassRevetmentFunctions.RepresentativeWaveRunup2P(
                new GrassRevetmentRepresentative2PInput(waterLevel, waveHeightHm0, wavePeriodTm10, waveDirection,
                                                        xValuesProfile, zValuesProfile, roughnessCoefficients,
                                                        dikeHeight, dikeOrientation));
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
    }
}