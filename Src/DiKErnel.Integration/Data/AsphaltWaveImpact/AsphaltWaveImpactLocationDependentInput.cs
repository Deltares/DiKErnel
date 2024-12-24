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
using DiKErnel.DomainLibrary.Constants;
using DiKErnel.DomainLibrary.Validators;
using DiKErnel.DomainLibrary.Validators.AsphaltWaveImpact;
using DiKErnel.FunctionLibrary;
using DiKErnel.FunctionLibrary.AsphaltWaveImpact;
using DiKErnel.Integration.Helpers;
using DiKErnel.Util.Validation;

namespace DiKErnel.Integration.Data.AsphaltWaveImpact
{
    internal class AsphaltWaveImpactLocationDependentInput : LocationDependentInput
    {
        private double outerSlope = double.NaN;
        private double logFlexuralStrength = double.NaN;
        private float computationalThickness = float.NaN;
        private double stiffnessRelation = double.NaN;
        private float subLayerElasticModulus = float.NaN;

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
            FlexuralStrength = (float) flexuralStrength;
            DensityOfWater = densityOfWater;
            SoilElasticity = (float) soilElasticity;
            UpperLayer = upperLayer;
            SubLayer = subLayer;
            AverageNumberOfWavesCtm = averageNumberOfWavesCtm;
            Fatigue = fatigue;
            ImpactNumberC = impactNumberC;
            StiffnessRelationNu = (float) stiffnessRelationNu;
            WidthFactors = widthFactors;
            DepthFactors = depthFactors;
            ImpactFactors = impactFactors;
        }

        public float FlexuralStrength { get; }

        public double DensityOfWater { get; }

        public float SoilElasticity { get; }

        public AsphaltWaveImpactLayer UpperLayer { get; }

        public AsphaltWaveImpactLayer SubLayer { get; }

        public double AverageNumberOfWavesCtm { get; }

        public AsphaltWaveImpactFatigue Fatigue { get; }

        public double ImpactNumberC { get; }

        public float StiffnessRelationNu { get; }

        public IReadOnlyList<(double, double)> WidthFactors { get; }

        public IReadOnlyList<(double, double)> DepthFactors { get; }

        public IReadOnlyList<(double, double)> ImpactFactors { get; }

        public override bool Validate(IReadOnlyList<ITimeDependentInput> timeDependentInputItems,
                                      IProfileData profileData)
        {
            bool baseValidationSuccessful = base.Validate(timeDependentInputItems, profileData);

            var validationIssues = new List<ValidationIssue>
            {
                AsphaltWaveImpactValidator.FatigueAlpha(Fatigue.Alpha),
                AsphaltWaveImpactValidator.FatigueBeta(Fatigue.Beta),
                AsphaltWaveImpactValidator.FlexuralStrength(FlexuralStrength),
                AsphaltWaveImpactValidator.ImpactNumberC(ImpactNumberC),
                AsphaltWaveImpactValidator.DensityOfWater(DensityOfWater),
                AsphaltWaveImpactValidator.SoilElasticity(SoilElasticity),
                AsphaltWaveImpactValidator.StiffnessRelationNu(StiffnessRelationNu),
                AsphaltWaveImpactValidator.Thickness(UpperLayer.Thickness),
                AsphaltWaveImpactValidator.ElasticModulus(UpperLayer.ElasticModulus)
            };

            if (SubLayer != null)
            {
                validationIssues.Add(AsphaltWaveImpactValidator.Thickness(SubLayer.Thickness));
                validationIssues.Add(AsphaltWaveImpactValidator.ElasticModulus(SubLayer.ElasticModulus));
            }

            validationIssues.Add(RevetmentValidator.AverageNumberOfWavesCtm(AverageNumberOfWavesCtm));

            return ValidationHelper.RegisterValidationIssues(validationIssues) && baseValidationSuccessful;
        }

        public override LocationDependentOutput GetLocationDependentOutput(
            IReadOnlyList<TimeDependentOutput> timeDependentOutputItems)
        {
            return new AsphaltWaveImpactLocationDependentOutput(timeDependentOutputItems, Z, outerSlope,
                                                                logFlexuralStrength, stiffnessRelation,
                                                                computationalThickness, subLayerElasticModulus);
        }

        public override void InitializeDerivedLocationDependentInput(IProfileData profileData)
        {
            base.InitializeDerivedLocationDependentInput(profileData);

            float subLayerThickness;

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

            logFlexuralStrength = AsphaltWaveImpactFunctions.LogFlexuralStrength(FlexuralStrength);

            computationalThickness = AsphaltWaveImpactFunctions.ComputationalThickness(UpperLayer.Thickness,
                                                                                       subLayerThickness,
                                                                                       UpperLayer.ElasticModulus,
                                                                                       subLayerElasticModulus);

            stiffnessRelation = AsphaltWaveImpactFunctions.StiffnessRelation(computationalThickness,
                                                                             subLayerElasticModulus,
                                                                             SoilElasticity, StiffnessRelationNu);

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

            outerSlope = AsphaltWaveImpactFunctions.OuterSlope(profileSegment.StartPoint.X, profileSegment.StartPoint.Z,
                                                               profileSegment.EndPoint.X, profileSegment.EndPoint.Z);
        }

        protected override TimeDependentOutput CalculateTimeDependentOutput(ITimeDependentInput timeDependentInput,
                                                                            IProfileData profileData,
                                                                            double damageAtStartOfCalculation = double.NaN)
        {
            double incrementTime = RevetmentFunctions.IncrementTime(timeDependentInput.BeginTime,
                                                                    timeDependentInput.EndTime);

            double averageNumberOfWaves = RevetmentFunctions.AverageNumberOfWaves(incrementTime,
                                                                                  timeDependentInput.WavePeriodTm10,
                                                                                  AverageNumberOfWavesCtm);

            double maximumPeakStress = AsphaltWaveImpactFunctions.MaximumPeakStress(timeDependentInput.WaveHeightHm0,
                                                                                    NaturalConstants.GravitationalAcceleration,
                                                                                    DensityOfWater);

            AsphaltWaveImpactInput input = CreateIncrementDamageInput(timeDependentInput.WaterLevel, timeDependentInput.WaveHeightHm0,
                                                                      averageNumberOfWaves, maximumPeakStress);

            double incrementDamage = AsphaltWaveImpactFunctions.IncrementDamage(input);

            return new AsphaltWaveImpactTimeDependentOutput(
                CreateConstructionProperties(incrementDamage, averageNumberOfWaves, maximumPeakStress));
        }

        private AsphaltWaveImpactInput CreateIncrementDamageInput(double waterLevel, double waveHeightHm0, double averageNumberOfWaves,
                                                                  double maximumPeakStress)
        {
            return new AsphaltWaveImpactInput(logFlexuralStrength, averageNumberOfWaves, maximumPeakStress,
                                              stiffnessRelation, computationalThickness, outerSlope, WidthFactors,
                                              DepthFactors, ImpactFactors, Z, waterLevel, waveHeightHm0, Fatigue.Alpha,
                                              Fatigue.Beta, ImpactNumberC);
        }

        private static AsphaltWaveImpactTimeDependentOutputConstructionProperties CreateConstructionProperties(
            double incrementDamage, double averageNumberOfWaves, double maximumPeakStress)
        {
            return new AsphaltWaveImpactTimeDependentOutputConstructionProperties
            {
                IncrementDamage = incrementDamage,
                MaximumPeakStress = maximumPeakStress,
                AverageNumberOfWaves = averageNumberOfWaves
            };
        }
    }
}