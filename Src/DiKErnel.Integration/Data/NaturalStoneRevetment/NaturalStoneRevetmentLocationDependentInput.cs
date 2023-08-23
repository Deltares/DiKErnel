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

using System;
using System.Collections.Generic;
using DiKErnel.Core.Data;
using DiKErnel.DomainLibrary.Validators.NaturalStoneRevetment;
using DiKErnel.FunctionLibrary.NaturalStoneRevetment;
using DiKErnel.Integration.Helpers;
using DiKErnel.Util.Validation;

namespace DiKErnel.Integration.Data.NaturalStoneRevetment
{
    internal class NaturalStoneRevetmentLocationDependentInput : LocationDependentInput
    {
        private double outerToeHeight = double.PositiveInfinity;
        private double outerCrestHeight = double.PositiveInfinity;
        private (double, double)? notchOuterBerm;
        private (double, double)? crestOuterBerm;
        private double resistance = double.PositiveInfinity;
        private double slopeLowerPosition = double.PositiveInfinity;
        private double slopeLowerLevel = double.PositiveInfinity;
        private double slopeUpperPosition = double.PositiveInfinity;
        private double slopeUpperLevel = double.PositiveInfinity;
        private double outerSlope = double.PositiveInfinity;
        private double waveSteepnessDeepWater = double.PositiveInfinity;
        private double distanceMaximumWaveElevation = double.PositiveInfinity;
        private double surfSimilarityParameter = double.PositiveInfinity;
        private double normativeWidthWaveImpact = double.PositiveInfinity;
        private double depthMaximumWaveLoad = double.PositiveInfinity;
        private double upperLimitLoading = double.PositiveInfinity;
        private double lowerLimitLoading = double.PositiveInfinity;
        private bool loadingRevetment = false;
        private double hydraulicLoad = double.PositiveInfinity;
        private double waveAngleImpact = double.PositiveInfinity;
        private double referenceTimeDegradation = double.PositiveInfinity;
        private double referenceDegradation = double.PositiveInfinity;

        public NaturalStoneRevetmentLocationDependentInput(double x, double initialDamage, double failureNumber,
                                                           double relativeDensity, double thicknessTopLayer,
                                                           NaturalStoneRevetmentHydraulicLoads hydraulicLoads,
                                                           NaturalStoneRevetmentSlope slope,
                                                           NaturalStoneRevetmentUpperLimitLoading upperLimitLoading,
                                                           NaturalStoneRevetmentLowerLimitLoading lowerLimitLoading,
                                                           NaturalStoneRevetmentDistanceMaximumWaveElevation distanceMaximumWaveElevation,
                                                           NaturalStoneRevetmentNormativeWidthOfWaveImpact normativeWidthOfWaveImpact,
                                                           NaturalStoneRevetmentWaveAngleImpact waveAngleImpact)
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

        public NaturalStoneRevetmentHydraulicLoads HydraulicLoads { get; }

        public NaturalStoneRevetmentSlope Slope { get; }

        public NaturalStoneRevetmentUpperLimitLoading UpperLimitLoading { get; }

        public NaturalStoneRevetmentLowerLimitLoading LowerLimitLoading { get; }

        public NaturalStoneRevetmentDistanceMaximumWaveElevation DistanceMaximumWaveElevation { get; }

        public NaturalStoneRevetmentNormativeWidthOfWaveImpact NormativeWidthOfWaveImpact { get; }

        public NaturalStoneRevetmentWaveAngleImpact WaveAngleImpact { get; }

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
            return new NaturalStoneRevetmentLocationDependentOutput(timeDependentOutputItems, Z);
        }

        protected override void InitializeDerivedLocationDependentInput(IProfileData profileData)
        {
            base.InitializeDerivedLocationDependentInput(profileData);

            IReadOnlyList<CharacteristicPoint> characteristicPoints = profileData.CharacteristicPoints;

            outerToeHeight = CharacteristicPointsHelper.GetCoordinatesForType(
                characteristicPoints, CharacteristicPointType.OuterToe).Item2;
            outerCrestHeight = CharacteristicPointsHelper.GetCoordinatesForType(
                characteristicPoints, CharacteristicPointType.OuterCrest).Item2;
            notchOuterBerm = CharacteristicPointsHelper.TryGetCoordinatesForType(
                characteristicPoints, CharacteristicPointType.NotchOuterBerm);
            crestOuterBerm = CharacteristicPointsHelper.TryGetCoordinatesForType(
                characteristicPoints, CharacteristicPointType.CrestOuterBerm);

            resistance = NaturalStoneRevetmentFunctions.Resistance(RelativeDensity, ThicknessTopLayer);
        }

        protected override TimeDependentOutput CalculateTimeDependentOutput(double initialDamage,
                                                                            ITimeDependentInput timeDependentInput,
                                                                            IProfileData profileData)
        {
            throw new NotImplementedException();
        }

        private double CalculateOuterSlope(double waterLevel, double waveHeightHm0, IProfileData profileData)
        {
            throw new NotImplementedException();
        }

        private bool CalculateLoadingRevetment(double depthMaximumWaveLoad, double surfSimilarityParameter,
                                               double waterLevel, double waveHeightHm0)
        {
            throw new NotImplementedException();
        }

        private double CalculateHydraulicLoad(double surfSimilarityParameter, double waveHeightHm0)
        {
            throw new NotImplementedException();
        }

        private int CalculateTimeOfFailure(double failureNumber, double wavePeriodTm10, double beginTime)
        {
            throw new NotImplementedException();
        }

        private NaturalStoneRevetmentTimeDependentOutputConstructionProperties CreateConstructionProperties(
            double incrementDamage, double damage, int? timeOfFailure)
        {
            throw new NotImplementedException();
        }
    }
}