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
        private double verticalDistanceWaterLevelElevation = double.NaN;
        private double waveAngle = double.NaN;
        private double waveAngleImpact = double.NaN;
        private double representativeWaveRunup2P = double.NaN;
        private double cumulativeOverload = double.NaN;
        private double averageNumberOfWaves = double.NaN;

        public GrassRevetmentWaveRunupRayleighLocationDependentInput(double x, double initialDamage,
                                                                     double failureNumber, double outerSlope,
                                                                     double criticalCumulativeOverload,
                                                                     double criticalFrontVelocity,
                                                                     double increasedLoadTransitionAlphaM,
                                                                     double reducedStrengthTransitionAlphaS,
                                                                     double averageNumberOfWavesCtm,
                                                                     GrassRevetmentWaveRunupRepresentative2P representative2P,
                                                                     GrassRevetmentWaveRunupWaveAngleImpact waveAngleImpact,
                                                                     int fixedNumberOfWaves, double frontVelocityCu)
            : base(x, initialDamage, failureNumber, outerSlope, criticalCumulativeOverload, criticalFrontVelocity,
                   increasedLoadTransitionAlphaM, reducedStrengthTransitionAlphaS, averageNumberOfWavesCtm,
                   representative2P, waveAngleImpact)
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

                double surfSimilarityParameter = HydraulicLoadFunctions.SurfSimilarityParameter(
                    OuterSlope, timeDependentInput.WaveHeightHm0, timeDependentInput.WavePeriodTm10,
                    Constants.GravitationalAcceleration);

                waveAngle = HydraulicLoadFunctions.WaveAngle(timeDependentInput.WaveDirection, profileData.DikeOrientation);

                waveAngleImpact = GrassRevetmentWaveRunupFunctions.WaveAngleImpact(waveAngle,
                                                                                   WaveAngleImpact.Abeta,
                                                                                   WaveAngleImpact.Betamax);

                representativeWaveRunup2P = CalculateRepresentativeWaveRunup2P(surfSimilarityParameter,
                                                                               timeDependentInput.WaveHeightHm0);

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

        private double CalculateRepresentativeWaveRunup2P(double surfSimilarityParameter, double waveHeightHm0)
        {
            return GrassRevetmentWaveRunupFunctions.RepresentativeWaveRunup2P(
                new GrassRevetmentWaveRunupRepresentative2PInput(surfSimilarityParameter, waveAngleImpact,
                                                                 waveHeightHm0, Representative2P.Gammab,
                                                                 Representative2P.Gammaf,
                                                                 Representative2P.Representative2PAru,
                                                                 Representative2P.Representative2PBru,
                                                                 Representative2P.Representative2PCru));
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
                constructionProperties.WaveAngle = waveAngle;
                constructionProperties.WaveAngleImpact = waveAngleImpact;
                constructionProperties.RepresentativeWaveRunup2P = representativeWaveRunup2P;
                constructionProperties.CumulativeOverload = cumulativeOverload;
                constructionProperties.AverageNumberOfWaves = averageNumberOfWaves;
            }

            return constructionProperties;
        }
    }
}