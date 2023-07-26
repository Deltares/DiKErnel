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
                std::unique_ptr<AsphaltRevetmentWaveImpactLayer> upperLayer,
                std::unique_ptr<AsphaltRevetmentWaveImpactLayer> subLayer,
                double averageNumberOfWavesCtm,
                std::unique_ptr<AsphaltRevetmentWaveImpactFatigue> fatigue,
                double impactNumberC,
                double stiffnessRelationNu,
                std::vector<std::pair<double, double>> widthFactors,
                std::vector<std::pair<double, double>> depthFactors,
                std::vector<std::pair<double, double>> impactFactors);

    public double GetFailureTension();

    public double GetDensityOfWater();

    public double GetSoilElasticity();

    public AsphaltRevetmentWaveImpactLayer& GetUpperLayer();

    public AsphaltRevetmentWaveImpactLayer* GetSubLayer();

    public double GetAverageNumberOfWavesCtm();

    public AsphaltRevetmentWaveImpactFatigue& GetFatigue();

    public double GetImpactNumberC();

    public double GetStiffnessRelationNu();

    public const std::vector<std::pair<double, double>>& GetWidthFactors();

    public const std::vector<std::pair<double, double>>& GetDepthFactors();

    public const std::vector<std::pair<double, double>>& GetImpactFactors();

    public bool Validate(
                const std::vector<std::reference_wrapper<Core::ITimeDependentInput>>& timeDependentInputs,
                const Core::IProfileData& profileData) const override;

    public std::unique_ptr<Core::LocationDependentOutput> GetLocationDependentOutput(
                std::vector<std::unique_ptr<Core::TimeDependentOutput>> timeDependentOutputItems) override;

    protected void InitializeDerivedLocationDependentInput(
                const Core::IProfileData& profileData) override;

    protected std::unique_ptr<Core::TimeDependentOutput> CalculateTimeDependentOutput(
                double initialDamage,
                const Core::ITimeDependentInput& timeDependentInput,
                const Core::IProfileData& profileData) override;

            private const double _failureTension;
            private const double _densityOfWater;
            private const double _soilElasticity;
            private std::unique_ptr<AsphaltRevetmentWaveImpactLayer> _upperLayer;
            private std::unique_ptr<AsphaltRevetmentWaveImpactLayer> _subLayer;
            private const double _averageNumberOfWavesCtm;
            private std::unique_ptr<AsphaltRevetmentWaveImpactFatigue> _fatigue;
            private const double _impactNumberC;
            private const double _stiffnessRelationNu;
            private std::vector<std::pair<double, double>> _widthFactors;
            private std::vector<std::pair<double, double>> _depthFactors;
            private std::vector<std::pair<double, double>> _impactFactors;
            private double _outerSlope = std::numeric_limits<double>::infinity();
            private double _logFailureTension = std::numeric_limits<double>::infinity();
            private double _computationalThickness = std::numeric_limits<double>::infinity();
            private double _stiffnessRelation = std::numeric_limits<double>::infinity();
            private double _subLayerElasticModulus = std::numeric_limits<double>::infinity();
            private double _averageNumberOfWaves = std::numeric_limits<double>::infinity();
            private double _maximumPeakStress = std::numeric_limits<double>::infinity();

    private FunctionLibrary::AsphaltRevetmentWaveImpactFunctionsInput CreateIncrementDamageInput(
                double waterLevel,
                double waveHeightHm0);

    private std::unique_ptr<AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties> CreateConstructionProperties(
                double incrementDamage,
                double damage,
                std::unique_ptr<int> timeOfFailure);
    }
}
