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

namespace DiKErnel.Integration.Data.AsphaltRevetmentWaveImpact
{
    internal class AsphaltRevetmentWaveImpactLocationDependentInput : LocationDependentInput
    {
        private double _failureTension;
        private double _densityOfWater;
        private double _soilElasticity;
        private AsphaltRevetmentWaveImpactLayer _upperLayer;
        private AsphaltRevetmentWaveImpactLayer _subLayer;
        private double _averageNumberOfWavesCtm;
        private AsphaltRevetmentWaveImpactFatigue _fatigue;
        private double _impactNumberC;
        private double _stiffnessRelationNu;
        private IReadOnlyList<(double, double)> _widthFactors;
        private IReadOnlyList<(double, double)> _depthFactors;
        private IReadOnlyList<(double, double)> _impactFactors;
        private double _outerSlope = double.PositiveInfinity;
        private double _logFailureTension = double.PositiveInfinity;
        private double _computationalThickness = double.PositiveInfinity;
        private double _stiffnessRelation = double.PositiveInfinity;
        private double _subLayerElasticModulus = double.PositiveInfinity;
        private double _averageNumberOfWaves = double.PositiveInfinity;
        private double _maximumPeakStress = double.PositiveInfinity;

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
                                                                IReadOnlyList<(double, double)> impactFactors) {}

        public double GetFailureTension();

        public double GetDensityOfWater();

        public double GetSoilElasticity();

        public AsphaltRevetmentWaveImpactLayer GetUpperLayer();

        public AsphaltRevetmentWaveImpactLayer GetSubLayer();

        public double GetAverageNumberOfWavesCtm();

        public AsphaltRevetmentWaveImpactFatigue GetFatigue();

        public double GetImpactNumberC();

        public double GetStiffnessRelationNu();

        public IReadOnlyList<(double, double)> GetWidthFactors();

        public IReadOnlyList<(double, double)> GetDepthFactors();

        public IReadOnlyList<(double, double)> GetImpactFactors();

        public bool Validate(
            IReadOnlyList<ITimeDependentInput> timeDependentInputs,
            IProfileData profileData)

        public LocationDependentOutput GetLocationDependentOutput(
            IReadOnlyList<TimeDependentOutput> timeDependentOutputItems)

        protected void InitializeDerivedLocationDependentInput(
            IProfileData profileData)

        protected TimeDependentOutput CalculateTimeDependentOutput(
            double initialDamage,
            ITimeDependentInput timeDependentInput,
            IProfileData profileData)override;override;override;override;

        private FunctionLibrary::AsphaltRevetmentWaveImpactFunctionsInput CreateIncrementDamageInput(
            double waterLevel,
            double waveHeightHm0);

        private AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties CreateConstructionProperties(
            double incrementDamage,
            double damage,
            int? timeOfFailure);
    }
}