// Copyright (C) Stichting Deltares 2022. All rights reserved.
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

#include <vector>

namespace DiKErnel::FunctionLibrary
{
    class AsphaltRevetmentWaveImpactFunctionsCalculatedInput
    {
        public:
            explicit AsphaltRevetmentWaveImpactFunctionsCalculatedInput(
                double logFailureTension,
                double computationalThickness,
                double stiffnessRelation,
                double equivalentElasticModulus,
                double outerSlope);

            void SetAverageNumberOfWaves(
                double averageNumberOfWaves);

            void SetMaximumPeakStress(
                double maximumPeakStress);

            [[nodiscard]]
            double GetLogFailureTension() const;

            [[nodiscard]]
            double GetComputationalThickness() const;

            [[nodiscard]]
            double GetStiffnessRelation() const;

            [[nodiscard]]
            double GetEquivalentElasticModulus() const;

            [[nodiscard]]
            double GetOuterSlope() const;

            [[nodiscard]]
            double GetAverageNumberOfWaves() const;

            [[nodiscard]]
            double GetMaximumPeakStress() const;

        private:
            double _logFailureTension;
            double _computationalThickness;
            double _stiffnessRelation;
            double _equivalentElasticModulus;
            double _outerSlope;
            double _averageNumberOfWaves = std::numeric_limits<double>::infinity();
            double _maximumPeakStress = std::numeric_limits<double>::infinity();
    };
}
