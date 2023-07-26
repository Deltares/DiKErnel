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
    class AsphaltRevetmentWaveImpactLocationDependentInput : public LocationDependentInput
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

    public double GetFailureTension() const;

    public double GetDensityOfWater() const;

    public double GetSoilElasticity() const;

    public AsphaltRevetmentWaveImpactLayer& GetUpperLayer() const;

    public AsphaltRevetmentWaveImpactLayer* GetSubLayer() const;

    public double GetAverageNumberOfWavesCtm() const;

    public AsphaltRevetmentWaveImpactFatigue& GetFatigue() const;

    public double GetImpactNumberC() const;

    public double GetStiffnessRelationNu() const;

    public const std::vector<std::pair<double, double>>& GetWidthFactors() const;

    public const std::vector<std::pair<double, double>>& GetDepthFactors() const;

    public const std::vector<std::pair<double, double>>& GetImpactFactors() const;

    public bool Validate(
                const std::vector<std::reference_wrapper<Core::ITimeDependentInput>>& timeDependentInputs,
                const Core::IProfileData& profileData) const override;

    public std::unique_ptr<Core::LocationDependentOutput> GetLocationDependentOutput(
                std::vector<std::unique_ptr<Core::TimeDependentOutput>> timeDependentOutputItems) override;

        protected:
            void InitializeDerivedLocationDependentInput(
                const Core::IProfileData& profileData) override;

            std::unique_ptr<Core::TimeDependentOutput> CalculateTimeDependentOutput(
                double initialDamage,
                const Core::ITimeDependentInput& timeDependentInput,
                const Core::IProfileData& profileData) override;

        private:
            const double _failureTension;
            const double _densityOfWater;
            const double _soilElasticity;
            std::unique_ptr<AsphaltRevetmentWaveImpactLayer> _upperLayer;
            std::unique_ptr<AsphaltRevetmentWaveImpactLayer> _subLayer;
            const double _averageNumberOfWavesCtm;
            std::unique_ptr<AsphaltRevetmentWaveImpactFatigue> _fatigue;
            const double _impactNumberC;
            const double _stiffnessRelationNu;
            std::vector<std::pair<double, double>> _widthFactors;
            std::vector<std::pair<double, double>> _depthFactors;
            std::vector<std::pair<double, double>> _impactFactors;
            double _outerSlope = std::numeric_limits<double>::infinity();
            double _logFailureTension = std::numeric_limits<double>::infinity();
            double _computationalThickness = std::numeric_limits<double>::infinity();
            double _stiffnessRelation = std::numeric_limits<double>::infinity();
            double _subLayerElasticModulus = std::numeric_limits<double>::infinity();
            double _averageNumberOfWaves = std::numeric_limits<double>::infinity();
            double _maximumPeakStress = std::numeric_limits<double>::infinity();

            FunctionLibrary::AsphaltRevetmentWaveImpactFunctionsInput CreateIncrementDamageInput(
                double waterLevel,
                double waveHeightHm0) const;

            std::unique_ptr<AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties> CreateConstructionProperties(
                double incrementDamage,
                double damage,
                std::unique_ptr<int> timeOfFailure);
    };
}
