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
using DiKErnel.DomainLibrary.Validators;
using DiKErnel.DomainLibrary.Validators.AsphaltRevetmentWaveImpact;
using DiKErnel.FunctionLibrary;
using DiKErnel.FunctionLibrary.AsphaltRevetmentWaveImpact;
using DiKErnel.Integration.Helpers;
using DiKErnel.Util.Validation;

namespace DiKErnel.Integration.Data.AsphaltWaveImpact
{
    internal class AsphaltWaveImpactLocationDependentInput : LocationDependentInput
    {
        private double outerSlope = double.NaN;
        private double logFlexuralStrength = double.NaN;
        private double computationalThickness = double.NaN;
        private double stiffnessRelation = double.NaN;
        private double subLayerElasticModulus = double.NaN;
        private double averageNumberOfWaves = double.NaN;
        private double maximumPeakStress = double.NaN;

        public AsphaltWaveImpactLocationDependentInput(double x, double initialDamage, double failureNumber,
                                                       double flexuralStrength, double densityOfWater,
                                                       double soilElasticity,
                                                       AsphaltWaveImpactLayer upperLayer,
                                                       AsphaltWaveImpactLayer subLayer,
                                                       double averageNumberOfWavesCtm,
                                                       AsphaltWaveImpactFatigue fatigue,
                                                       double impactNumberC, double stiffnessRelationNu,
                                                       IReadOnlyList<(double, double)> widthFactors,
                                                       IReadOnlyList<(double, double)> depthFactors,
                                                       IReadOnlyList<(double, double)> impactFactors)
            : base(x, initialDamage, failureNumber)
        {
            FlexuralStrength = flexuralStrength;
            DensityOfWater = densityOfWater;
            SoilElasticity = soilElasticity;
            UpperLayer = upperLayer;
            SubLayer = subLayer;
            AverageNumberOfWavesCtm = averageNumberOfWavesCtm;
            Fatigue = fatigue;
            ImpactNumberC = impactNumberC;
            StiffnessRelationNu = stiffnessRelationNu;
            WidthFactors = widthFactors;
            DepthFactors = depthFactors;
            ImpactFactors = impactFactors;
        }

        public double FlexuralStrength { get; }

        public double DensityOfWater { get; }

        public double SoilElasticity { get; }

        public AsphaltWaveImpactLayer UpperLayer { get; }

        public AsphaltWaveImpactLayer SubLayer { get; }

        public double AverageNumberOfWavesCtm { get; }

        public AsphaltWaveImpactFatigue Fatigue { get; }

        public double ImpactNumberC { get; }

        public double StiffnessRelationNu { get; }

        public IReadOnlyList<(double, double)> WidthFactors { get; }

        public IReadOnlyList<(double, double)> DepthFactors { get; }

        public IReadOnlyList<(double, double)> ImpactFactors { get; }

        public override bool Validate(IReadOnlyList<ITimeDependentInput> timeDependentInputItems,
                                      IProfileData profileData)
        {
            bool baseValidationSuccessful = base.Validate(timeDependentInputItems, profileData);

            var validationIssues = new List<ValidationIssue>
            {
                AsphaltRevetmentWaveImpactValidator.FatigueAlpha(Fatigue.Alpha),
                AsphaltRevetmentWaveImpactValidator.FatigueBeta(Fatigue.Beta),
                AsphaltRevetmentWaveImpactValidator.FlexuralStrength(FlexuralStrength),
                AsphaltRevetmentWaveImpactValidator.ImpactNumberC(ImpactNumberC),
                AsphaltRevetmentWaveImpactValidator.DensityOfWater(DensityOfWater),
                AsphaltRevetmentWaveImpactValidator.SoilElasticity(SoilElasticity),
                AsphaltRevetmentWaveImpactValidator.StiffnessRelationNu(StiffnessRelationNu),
                AsphaltRevetmentWaveImpactValidator.Thickness(UpperLayer.Thickness),
                AsphaltRevetmentWaveImpactValidator.ElasticModulus(UpperLayer.ElasticModulus)
            };

            if (SubLayer != null)
            {
                validationIssues.Add(AsphaltRevetmentWaveImpactValidator.Thickness(SubLayer.Thickness));
                validationIssues.Add(AsphaltRevetmentWaveImpactValidator.ElasticModulus(SubLayer.ElasticModulus));
            }

            validationIssues.Add(RevetmentValidator.AverageNumberOfWavesCtm(AverageNumberOfWavesCtm));

            return ValidationHelper.RegisterValidationIssues(validationIssues) && baseValidationSuccessful;
        }

        public override LocationDependentOutput GetLocationDependentOutput(
            IReadOnlyList<TimeDependentOutput> timeDependentOutputItems)
        {
            return new AsphaltRevetmentWaveImpactLocationDependentOutput(timeDependentOutputItems, Z, outerSlope,
                                                                         logFlexuralStrength, stiffnessRelation,
                                                                         computationalThickness, subLayerElasticModulus);
        }

        protected override void InitializeDerivedLocationDependentInput(IProfileData profileData)
        {
            base.InitializeDerivedLocationDependentInput(profileData);

            double subLayerThickness;

            if (SubLayer != null)
            {
                subLayerThickness = SubLayer.Thickness;
                subLayerElasticModulus = SubLayer.ElasticModulus;
            }
            else
            {
                subLayerThickness = 0;
                subLayerElasticModulus = UpperLayer.ElasticModulus;
            }

            logFlexuralStrength = AsphaltRevetmentWaveImpactFunctions.LogFlexuralStrength(FlexuralStrength);

            computationalThickness = AsphaltRevetmentWaveImpactFunctions.ComputationalThickness(UpperLayer.Thickness,
                subLayerThickness,
                UpperLayer.ElasticModulus,
                subLayerElasticModulus);

            stiffnessRelation = AsphaltRevetmentWaveImpactFunctions.StiffnessRelation(computationalThickness,
                                                                                      subLayerElasticModulus,
                                                                                      SoilElasticity,
                                                                                      StiffnessRelationNu);

            (double, double)? notchOuterBerm = CharacteristicPointsHelper.TryGetCoordinatesForType(
                profileData.CharacteristicPoints, CharacteristicPointType.NotchOuterBerm);
            (double, double)? crestOuterBerm = CharacteristicPointsHelper.TryGetCoordinatesForType(
                profileData.CharacteristicPoints, CharacteristicPointType.CrestOuterBerm);

            double horizontalPosition = X;
            if (notchOuterBerm != null && crestOuterBerm != null && horizontalPosition > crestOuterBerm.Value.Item1
                && horizontalPosition <= notchOuterBerm.Value.Item1)
            {
                horizontalPosition = crestOuterBerm.Value.Item1;
            }

            ProfileSegment profileSegment = profileData.GetProfileSegment(horizontalPosition);

            outerSlope = AsphaltRevetmentWaveImpactFunctions.OuterSlope(profileSegment.StartPoint.X,
                                                                        profileSegment.StartPoint.Z,
                                                                        profileSegment.EndPoint.X,
                                                                        profileSegment.EndPoint.Z);
        }

        protected override TimeDependentOutput CalculateTimeDependentOutput(double initialDamage,
                                                                            ITimeDependentInput timeDependentInput,
                                                                            IProfileData profileData)
        {
            double incrementTime = RevetmentFunctions.IncrementTime(timeDependentInput.BeginTime,
                                                                    timeDependentInput.EndTime);

            averageNumberOfWaves = RevetmentFunctions.AverageNumberOfWaves(incrementTime,
                                                                           timeDependentInput.WavePeriodTm10,
                                                                           AverageNumberOfWavesCtm);

            maximumPeakStress = AsphaltRevetmentWaveImpactFunctions.MaximumPeakStress(timeDependentInput.WaveHeightHm0,
                                                                                      Constants.GravitationalAcceleration,
                                                                                      DensityOfWater);

            AsphaltRevetmentWaveImpactFunctionsInput input = CreateIncrementDamageInput(timeDependentInput.WaterLevel,
                                                                                        timeDependentInput.WaveHeightHm0);
            double incrementDamage = AsphaltRevetmentWaveImpactFunctions.IncrementDamage(input);
            double damage = RevetmentFunctions.Damage(incrementDamage, initialDamage);

            double? timeOfFailure = null;

            if (RevetmentFunctions.FailureRevetment(damage, initialDamage, FailureNumber))
            {
                double durationInTimeStepFailure = RevetmentFunctions.DurationInTimeStepFailure(
                    incrementTime, incrementDamage, FailureNumber, initialDamage);
                timeOfFailure = RevetmentFunctions.TimeOfFailure(durationInTimeStepFailure,
                                                                 timeDependentInput.BeginTime);
            }

            return new AsphaltRevetmentWaveImpactTimeDependentOutput(
                CreateConstructionProperties(incrementDamage, damage, timeOfFailure));
        }

        private AsphaltRevetmentWaveImpactFunctionsInput CreateIncrementDamageInput(double waterLevel,
                                                                                    double waveHeightHm0)
        {
            return new AsphaltRevetmentWaveImpactFunctionsInput(logFlexuralStrength, averageNumberOfWaves,
                                                                maximumPeakStress, stiffnessRelation,
                                                                computationalThickness, outerSlope, WidthFactors,
                                                                DepthFactors, ImpactFactors, Z, waterLevel,
                                                                waveHeightHm0, Fatigue.Alpha, Fatigue.Beta,
                                                                ImpactNumberC);
        }

        private AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties CreateConstructionProperties(
            double incrementDamage, double damage, double? timeOfFailure)
        {
            return new AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties
            {
                IncrementDamage = incrementDamage,
                Damage = damage,
                TimeOfFailure = timeOfFailure,
                MaximumPeakStress = maximumPeakStress,
                AverageNumberOfWaves = averageNumberOfWaves
            };
        }
    }
}