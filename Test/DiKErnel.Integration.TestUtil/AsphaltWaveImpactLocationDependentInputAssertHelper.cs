// Copyright (C) Stichting Deltares and State of the Netherlands 2025. All rights reserved.
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
using DiKErnel.Integration.Data.AsphaltWaveImpact;
using NUnit.Framework;

namespace DiKErnel.Integration.TestUtil
{
    internal static class AsphaltWaveImpactLocationDependentInputAssertHelper
    {
        public static void AssertGeneralProperties(double flexuralStrength, double densityOfWater,
                                                   double soilElasticity, double averageNumberOfWavesCtm,
                                                   double impactNumberC, double stiffnessRelationNu,
                                                   AsphaltWaveImpactLocationDependentInput locationDependentInput)
        {
            Assert.That(locationDependentInput.FlexuralStrength, Is.EqualTo(flexuralStrength));
            Assert.That(locationDependentInput.DensityOfWater, Is.EqualTo(densityOfWater));
            Assert.That(locationDependentInput.SoilElasticity, Is.EqualTo(soilElasticity));
            Assert.That(locationDependentInput.AverageNumberOfWavesCtm, Is.EqualTo(averageNumberOfWavesCtm));
            Assert.That(locationDependentInput.ImpactNumberC, Is.EqualTo(impactNumberC));
            Assert.That(locationDependentInput.StiffnessRelationNu, Is.EqualTo(stiffnessRelationNu));
        }

        public static void AssertLayer(double thickness, double elasticModulus, AsphaltWaveImpactLayer layer)
        {
            Assert.That(layer.Thickness, Is.EqualTo(thickness));
            Assert.That(layer.ElasticModulus, Is.EqualTo(elasticModulus));
        }

        public static void AssertFatigue(double alpha, double beta, AsphaltWaveImpactFatigue fatigue)
        {
            Assert.That(fatigue.Alpha, Is.EqualTo(alpha));
            Assert.That(fatigue.Beta, Is.EqualTo(beta));
        }

        public static void AssertFactors(IReadOnlyList<(double, double)> widthFactors,
                                         IReadOnlyList<(double, double)> depthFactors,
                                         IReadOnlyList<(double, double)> impactFactors,
                                         AsphaltWaveImpactLocationDependentInput locationDependentInput)
        {
            Assert.That(locationDependentInput.WidthFactors, Is.EqualTo(widthFactors));
            Assert.That(locationDependentInput.DepthFactors, Is.EqualTo(depthFactors));
            Assert.That(locationDependentInput.ImpactFactors, Is.EqualTo(impactFactors));
        }
    }
}