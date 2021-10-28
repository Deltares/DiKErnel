// Copyright (C) Stichting Deltares 2020. All rights reserved.
//
// This file is part of DiKErnel.
//
// DiKErnel is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, version 3.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/lgpl-3.0.html>.
//
// All names, logos, and references to "Deltares" are registered trademarks of
// Stichting Deltares and remain full property of Stichting Deltares at all times.
// All rights reserved.

#pragma once

#include <memory>
#include <vector>

#include "AsphaltRevetmentWaveImpactFatigue.h"
#include "AsphaltRevetmentWaveImpactLayer.h"
#include "LocationDependentInput.h"

namespace DiKErnel::Integration
{
    class AsphaltRevetmentWaveImpactLocationDependentInput : public LocationDependentInput
    {
        public:
            explicit AsphaltRevetmentWaveImpactLocationDependentInput(
                double x,
                double initialDamage,
                double failureNumber,
                double outerSlope,
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

            double GetOuterSlope() const;

            double GetFailureTension() const;

            double GetDensityOfWater() const;

            double GetSoilElasticity() const;

            AsphaltRevetmentWaveImpactLayer& GetUpperLayer() const;

            AsphaltRevetmentWaveImpactLayer* GetSubLayer() const;

            double GetAverageNumberOfWavesCtm() const;

            AsphaltRevetmentWaveImpactFatigue& GetFatigue() const;

            double GetImpactNumberC() const;

            double GetStiffnessRelationNu() const;

            const std::vector<std::pair<double, double>>& GetWidthFactors() const;

            const std::vector<std::pair<double, double>>& GetDepthFactors() const;

            const std::vector<std::pair<double, double>>& GetImpactFactors() const;

            bool Validate(
                const Core::IProfileData& profileData) const override;

        protected:
            void InitializeDerivedLocationDependentInput(
                const Core::IProfileData& profileData) override;

            std::unique_ptr<Core::TimeDependentOutput> CalculateTimeDependentOutput(
                double initialDamage,
                const Core::ITimeDependentInput& timeDependentInput,
                const Core::IProfileData& profileData) override;

        private:
            const double _outerSlope;
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
            double _logFailureTension = std::numeric_limits<double>::infinity();
            double _computationalThickness = std::numeric_limits<double>::infinity();
            double _stiffnessRelation = std::numeric_limits<double>::infinity();
            double _subLayerElasticModulus = std::numeric_limits<double>::infinity();
    };
}
