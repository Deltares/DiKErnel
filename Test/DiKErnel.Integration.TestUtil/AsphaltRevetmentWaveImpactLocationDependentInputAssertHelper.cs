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
using DiKErnel.Integration.Data.AsphaltRevetmentWaveImpact;

namespace DiKErnel.Integration.TestUtil
{
    internal static class AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper
    {
        public static void AssertGeneralProperties(double x, double failureTension, double densityOfWater,
                                                   double soilElasticity, double averageNumberOfWavesCtm,
                                                   double impactNumberC, double stiffnessRelationNu,
                                                   AsphaltRevetmentWaveImpactLocationDependentInput locationDependentInput) {}

        public static void AssertLayer(double thickness, double elasticModulus, AsphaltRevetmentWaveImpactLayer layer) {}

        public static void AssertFatigue(double alpha, double beta, AsphaltRevetmentWaveImpactFatigue fatigue) {}

        public static void AssertFactors(IReadOnlyList<(double, double)> widthFactors,
                                         IReadOnlyList<(double, double)> depthFactors,
                                         IReadOnlyList<(double, double)> impactFactors,
                                         AsphaltRevetmentWaveImpactLocationDependentInput locationDependentInput) {}
    }
}