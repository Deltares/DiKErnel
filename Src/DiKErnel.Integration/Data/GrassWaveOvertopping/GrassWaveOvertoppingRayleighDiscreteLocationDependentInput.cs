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
using DiKErnel.DomainLibrary.Constants;
using DiKErnel.DomainLibrary.Validators.Grass;
using DiKErnel.DomainLibrary.Validators.GrassWaveOvertopping;
using DiKErnel.FunctionLibrary.GrassWaveOvertopping;
using DiKErnel.Integration.Data.Grass;
using DiKErnel.Integration.Helpers;
using DiKErnel.Util.Validation;

namespace DiKErnel.Integration.Data.GrassWaveOvertopping
{
    internal class GrassWaveOvertoppingRayleighDiscreteLocationDependentInput
        : GrassCumulativeOverloadLocationDependentInput
    {
        private double accelerationAlphaA = double.NaN;

        public GrassWaveOvertoppingRayleighDiscreteLocationDependentInput(
            double x, double initialDamage, double failureNumber, double criticalCumulativeOverload,
            double criticalFrontVelocity, double increasedLoadTransitionAlphaM, double reducedStrengthTransitionAlphaS,
            double averageNumberOfWavesCtm, int fixedNumberOfWaves, double frontVelocityCwo,
            GrassWaveOvertoppingRayleighDiscreteAccelerationAlphaA accelerationAlphaA, double? enforcedDikeHeight)
            : base(x, initialDamage, failureNumber, criticalCumulativeOverload, criticalFrontVelocity,
                   increasedLoadTransitionAlphaM, reducedStrengthTransitionAlphaS, averageNumberOfWavesCtm)
        {
            FixedNumberOfWaves = fixedNumberOfWaves;
            FrontVelocityCwo = frontVelocityCwo;
            AccelerationAlphaA = accelerationAlphaA;
            EnforcedDikeHeight = enforcedDikeHeight;
        }

        public int FixedNumberOfWaves { get; }

        public double FrontVelocityCwo { get; }

        public GrassWaveOvertoppingRayleighDiscreteAccelerationAlphaA AccelerationAlphaA { get; }

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

            validationIssues.Add(GrassRayleighDiscreteValidator.FixedNumberOfWaves(FixedNumberOfWaves));
            validationIssues.Add(GrassWaveOvertoppingRayleighDiscreteValidator.FrontVelocityCwo(FrontVelocityCwo));
            validationIssues.Add(GrassWaveOvertoppingRayleighDiscreteValidator.AccelerationAlphaA(
                                     AccelerationAlphaA.ValueAtCrest));
            validationIssues.Add(GrassWaveOvertoppingRayleighDiscreteValidator.AccelerationAlphaA(
                                     AccelerationAlphaA.ValueAtInnerSlope));

            return ValidationHelper.RegisterValidationIssues(validationIssues) && baseValidationSuccessful;
        }

        public override LocationDependentOutput GetLocationDependentOutput(
            IReadOnlyList<TimeDependentOutput> timeDependentOutputItems)
        {
            return new GrassWaveOvertoppingRayleighDiscreteLocationDependentOutput(timeDependentOutputItems);
        }

        protected override void InitializeDerivedLocationDependentInput(IProfileData profileData)
        {
            base.InitializeDerivedLocationDependentInput(profileData);

            InitializeAccelerationAlphaA(profileData);
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

        protected override double GetRunupHeight()
        {
            return DikeHeight;
        }

        protected override double CalculateCumulativeOverload(double averageNumberOfWaves,
                                                              double representativeWaveRunup2P,
                                                              double verticalDistanceWaterLevelElevation,
                                                              ITimeDependentInput timeDependentInput,
                                                              IProfileData profileData)
        {
            return GrassWaveOvertoppingRayleighDiscreteFunctions.CumulativeOverload(
                new GrassWaveOvertoppingRayleighDiscreteCumulativeOverloadInput(averageNumberOfWaves,
                                                                                representativeWaveRunup2P,
                                                                                FixedNumberOfWaves,
                                                                                verticalDistanceWaterLevelElevation,
                                                                                CriticalFrontVelocity,
                                                                                IncreasedLoadTransitionAlphaM,
                                                                                ReducedStrengthTransitionAlphaS,
                                                                                NaturalConstants.GravitationalAcceleration,
                                                                                accelerationAlphaA,
                                                                                FrontVelocityCwo));
        }

        private void InitializeAccelerationAlphaA(IProfileData profileData)
        {
            (double, double) outerCrest = CharacteristicPointsHelper.GetCoordinatesForType(
                profileData.CharacteristicPoints, CharacteristicPointType.OuterCrest);
            (double, double) innerCrest = CharacteristicPointsHelper.GetCoordinatesForType(
                profileData.CharacteristicPoints, CharacteristicPointType.InnerCrest);

            accelerationAlphaA = X >= outerCrest.Item1 && X <= innerCrest.Item1
                                     ? AccelerationAlphaA.ValueAtCrest
                                     : AccelerationAlphaA.ValueAtInnerSlope;
        }
    }
}