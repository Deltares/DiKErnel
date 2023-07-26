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
using DiKErnel.FunctionLibrary.AsphaltRevetmentWaveImpact;

namespace DiKErnel.Integration.Data.AsphaltRevetmentWaveImpact
{
    internal class AsphaltRevetmentWaveImpactLocationDependentInput : LocationDependentInput
    {
        public AsphaltRevetmentWaveImpactLocationDependentInput(double x, double initialDamage, double failureNumber,
                                                                double failureTension, double densityOfWater,
                                                                double soilElasticity,
                                                                AsphaltRevetmentWaveImpactLayer upperLayer,
                                                                AsphaltRevetmentWaveImpactLayer subLayer,
                                                                double averageNumberOfWavesCtm,
                                                                AsphaltRevetmentWaveImpactFatigue fatigue,
                                                                double impactNumberC, double stiffnessRelationNu,
                                                                IReadOnlyList<(double, double)> widthFactors,
                                                                IReadOnlyList<(double, double)> depthFactors,
                                                                IReadOnlyList<(double, double)> impactFactors)
            : base(x, initialDamage, failureNumber)
        {
            FailureTension = failureTension;
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
            OuterSlope = double.PositiveInfinity;
            LogFailureTension = double.PositiveInfinity;
            ComputationalThickness = double.PositiveInfinity;
            StiffnessRelation = double.PositiveInfinity;
            SubLayerElasticModulus = double.PositiveInfinity;
            AverageNumberOfWaves = double.PositiveInfinity;
            MaximumPeakStress = double.PositiveInfinity;
        }

        public double FailureTension { get; }

        public double DensityOfWater { get; }

        public double SoilElasticity { get; }

        public AsphaltRevetmentWaveImpactLayer UpperLayer { get; }

        public AsphaltRevetmentWaveImpactLayer SubLayer { get; }

        public double AverageNumberOfWavesCtm { get; }

        public AsphaltRevetmentWaveImpactFatigue Fatigue { get; }

        public double ImpactNumberC { get; }

        public double StiffnessRelationNu { get; }

        public IReadOnlyList<(double, double)> WidthFactors { get; }

        public IReadOnlyList<(double, double)> DepthFactors { get; }

        public IReadOnlyList<(double, double)> ImpactFactors { get; }

        public double OuterSlope { get; private set; }

        public double LogFailureTension { get; private set; }

        public double ComputationalThickness { get; private set; }

        public double StiffnessRelation { get; private set; }

        public double SubLayerElasticModulus { get; private set; }

        public double AverageNumberOfWaves { get; private set; }

        public double MaximumPeakStress { get; private set; }

        public override bool Validate(IReadOnlyList<ITimeDependentInput> timeDependentInputItems,
                                      IProfileData profileData)
        {
            return base.Validate(timeDependentInputItems, profileData);
        }

        public override LocationDependentOutput GetLocationDependentOutput(
            IReadOnlyList<TimeDependentOutput> timeDependentOutputItems)
        {
            return base.GetLocationDependentOutput(timeDependentOutputItems);
        }

        protected override void InitializeDerivedLocationDependentInput(IProfileData profileData)
        {
            base.InitializeDerivedLocationDependentInput(profileData);
        }

        protected override TimeDependentOutput CalculateTimeDependentOutput(double initialDamage,
                                                                            ITimeDependentInput timeDependentInput,
                                                                            IProfileData profileData)
        {
            throw new NotImplementedException();
        }

        private AsphaltRevetmentWaveImpactFunctionsInput CreateIncrementDamageInput(double waterLevel,
                                                                                    double waveHeightHm0)
        {
            throw new NotImplementedException();
        }

        private AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties CreateConstructionProperties(
            double incrementDamage,
            double damage,
            int? timeOfFailure)
        {
            throw new NotImplementedException();
        }

        private class AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties {}
    }
}