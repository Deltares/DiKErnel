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

namespace DiKErnel.Integration.Data.AsphaltRevetmentWaveImpact
{
    internal class AsphaltRevetmentWaveImpactLocationDependentInput : LocationDependentInput
    {
        public void AsphaltRevetmentWaveImpactLocationDependentInput(
                double x,
                double initialDamage,
                double failureNumber,
                double failureTension,
                double densityOfWater,
                double soilElasticity,
                unique_ptr<AsphaltRevetmentWaveImpactLayer> upperLayer,
                unique_ptr<AsphaltRevetmentWaveImpactLayer> subLayer,
                double averageNumberOfWavesCtm,
                unique_ptr<AsphaltRevetmentWaveImpactFatigue> fatigue,
                double impactNumberC,
                double stiffnessRelationNu,
                vector<pair<double, double>> widthFactors,
                vector<pair<double, double>> depthFactors,
                vector<pair<double, double>> impactFactors);

    public double GetFailureTension();

    public double GetDensityOfWater();

    public double GetSoilElasticity();

    public AsphaltRevetmentWaveImpactLayer& GetUpperLayer();

    public AsphaltRevetmentWaveImpactLayer* GetSubLayer();

    public double GetAverageNumberOfWavesCtm();

    public AsphaltRevetmentWaveImpactFatigue& GetFatigue();

    public double GetImpactNumberC();

    public double GetStiffnessRelationNu();

    public vector<pair<double, double>>& GetWidthFactors();

    public vector<pair<double, double>>& GetDepthFactors();

    public vector<pair<double, double>>& GetImpactFactors();

    public bool Validate(
                vector<reference_wrapper<ITimeDependentInput>>& timeDependentInputs,
                IProfileData& profileData) override;

    public unique_ptr<LocationDependentOutput> GetLocationDependentOutput(
                vector<unique_ptr<TimeDependentOutput>> timeDependentOutputItems) override;

    protected void InitializeDerivedLocationDependentInput(
                IProfileData& profileData) override;

    protected unique_ptr<TimeDependentOutput> CalculateTimeDependentOutput(
                double initialDamage,
                ITimeDependentInput& timeDependentInput,
                IProfileData& profileData) override;

            private double _failureTension;
            private double _densityOfWater;
            private double _soilElasticity;
            private unique_ptr<AsphaltRevetmentWaveImpactLayer> _upperLayer;
            private unique_ptr<AsphaltRevetmentWaveImpactLayer> _subLayer;
            private double _averageNumberOfWavesCtm;
            private unique_ptr<AsphaltRevetmentWaveImpactFatigue> _fatigue;
            private double _impactNumberC;
            private double _stiffnessRelationNu;
            private vector<pair<double, double>> _widthFactors;
            private vector<pair<double, double>> _depthFactors;
            private vector<pair<double, double>> _impactFactors;
            private double _outerSlope = numeric_limits<double>::infinity();
            private double _logFailureTension = numeric_limits<double>::infinity();
            private double _computationalThickness = numeric_limits<double>::infinity();
            private double _stiffnessRelation = numeric_limits<double>::infinity();
            private double _subLayerElasticModulus = numeric_limits<double>::infinity();
            private double _averageNumberOfWaves = numeric_limits<double>::infinity();
            private double _maximumPeakStress = numeric_limits<double>::infinity();

    private FunctionLibrary::AsphaltRevetmentWaveImpactFunctionsInput CreateIncrementDamageInput(
                double waterLevel,
                double waveHeightHm0);

    private unique_ptr<AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties> CreateConstructionProperties(
                double incrementDamage,
                double damage,
                unique_ptr<int> timeOfFailure);
    }
}
