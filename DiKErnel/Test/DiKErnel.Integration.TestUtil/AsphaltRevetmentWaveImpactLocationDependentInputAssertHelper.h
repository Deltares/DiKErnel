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

#include "AsphaltRevetmentWaveImpactLocationDependentInput.h"

namespace DiKErnel::Integration::TestUtil
{
    class AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper
    {
        public:
            static void AssertGeneralProperties(
                const std::string& name,
                double x,
                double outerSlope,
                double failureTension,
                double densityOfWater,
                double soilElasticity,
                double averageNumberOfWavesCtm,
                double impactNumberC,
                double stiffnessRelationNu,
                const AsphaltRevetmentWaveImpactLocationDependentInput& locationDependentInput);

            static void AssertLayer(
                double thickness,
                double elasticModulus,
                const AsphaltRevetmentWaveImpactLayer& layer);

            static void AssertFatigue(
                double alpha,
                double beta,
                const AsphaltRevetmentWaveImpactFatigue& fatigue);

            static void AssertFactors(
                const std::vector<std::tuple<double, double>>& widthFactors,
                const std::vector<std::tuple<double, double>>& depthFactors,
                const std::vector<std::tuple<double, double>>& impactFactors,
                const AsphaltRevetmentWaveImpactLocationDependentInput& locationDependentInput);
    };
}
