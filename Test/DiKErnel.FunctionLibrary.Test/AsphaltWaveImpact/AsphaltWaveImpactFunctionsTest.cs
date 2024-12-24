// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
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

using DiKErnel.FunctionLibrary.AsphaltWaveImpact;
using DiKErnel.FunctionLibrary.TestUtil;
using NUnit.Framework;

namespace DiKErnel.FunctionLibrary.Test.AsphaltWaveImpact
{
    [TestFixture]
    public class AsphaltWaveImpactFunctionsTest
    {
        [Test]
        public void IncrementDamage_ValidInput_ExpectedValue()
        {
            // Setup
            (float, float)[] widthFactors =
            {
                (0.1f, 0.0392f),
                (0.2f, 0.0738f),
                (0.3f, 0.1002f),
                (0.4f, 0.1162f),
                (0.5f, 0.1213f),
                (0.6f, 0.1168f),
                (0.7f, 0.1051f),
                (0.8f, 0.089f),
                (0.9f, 0.0712f),
                (1, 0.0541f),
                (1.1f, 0.0391f),
                (1.2f, 0.0269f),
                (1.3f, 0.0216f),
                (1.4f, 0.015f),
                (1.5f, 0.0105f)
            };

            (float, float)[] depthFactors =
            {
                (-1, 0.0244f),
                (-0.875f, 0.0544f),
                (-0.75f, 0.0938f),
                (-0.625f, 0.1407f),
                (-0.5f, 0.1801f),
                (-0.375f, 0.1632f),
                (-0.25f, 0.1426f),
                (-0.125f, 0.0994f),
                (0, 0.06f),
                (0.125f, 0.0244f),
                (0.25f, 0.0169f)
            };

            (float, float)[] impactFactors =
            {
                (2, 0.039f),
                (2.4f, 0.1f),
                (2.8f, 0.18f),
                (3.2f, 0.235f),
                (3.6f, 0.2f),
                (4, 0.13f),
                (4.4f, 0.08f),
                (4.8f, 0.02f),
                (5.2f, 0.01f),
                (5.6f, 0.005f),
                (6, 0.001f)
            };

            const float logFlexuralStrength = 0.193124598f;
            const float averageNumberOfWaves = 6492.937853f;
            const float maximumPeakStress = 0.0160884f;
            const float stiffnessRelation = 1.185626183f;
            const float computationalThickness = 0.16f;
            const float outerSlope = 0.232914161f;

            const float z = 2.988f;
            const float waterLevel = 3.8f;
            const float waveHeightHm0 = 1.6f;
            const float fatigueAlpha = 0.42f;
            const float fatigueBeta = 4.76f;
            const float impactNumberC = 1;

            var input = new AsphaltWaveImpactInput(logFlexuralStrength, averageNumberOfWaves, maximumPeakStress,
                                                   stiffnessRelation, computationalThickness, outerSlope, widthFactors,
                                                   depthFactors, impactFactors, z, waterLevel, waveHeightHm0,
                                                   fatigueAlpha, fatigueBeta, impactNumberC);

            // Call
            float incrementDamage = AsphaltWaveImpactFunctions.IncrementDamage(input);

            // Assert
            AssertHelper.AreEqual(7.94813500019044, incrementDamage);
        }

        [Test]
        public void LogFlexuralStrength_ValidInput_ExpectedValue()
        {
            // Setup
            const float flexuralStrength = 1.56f;

            // Call
            float logFlexuralStrength = AsphaltWaveImpactFunctions.LogFlexuralStrength(flexuralStrength);

            // Assert
            AssertHelper.AreEqual(0.19312459835446, logFlexuralStrength);
        }

        [Test]
        public void MaximumPeakStress_ValidInput_ExpectedValue()
        {
            // Setup
            const float waveHeightHm0 = 1.6f;
            const float gravitationalAcceleration = 9.81f;
            const float densityOfWater = 1025;

            // Call
            float maximumPeakStress = AsphaltWaveImpactFunctions.MaximumPeakStress(
                waveHeightHm0, gravitationalAcceleration, densityOfWater);

            // Assert
            AssertHelper.AreEqual(0.0160884, maximumPeakStress);
        }

        [Test]
        public void StiffnessRelation_ValidInput_ExpectedValue()
        {
            // Setup
            const float computationalThickness = 0.16f;
            const float equivalentElasticModulus = 18214;
            const float soilElasticity = 56;
            const float stiffnessRelationNu = 0.35f;

            // Call
            float stiffnessRelation = AsphaltWaveImpactFunctions.StiffnessRelation(
                computationalThickness, equivalentElasticModulus, soilElasticity, stiffnessRelationNu);

            // Assert
            AssertHelper.AreEqual(1.18562618326908, stiffnessRelation);
        }

        [Test]
        public void ComputationalThickness_ValidInput_ExpectedValue()
        {
            // Setup
            const float thicknessUpperLayer = 0.16f;
            const float thicknessSubLayer = 0.23f;
            const float elasticModulusUpperLayer = 18214;
            const float elasticModulusSubLayer = 19214;

            // Call
            float computationalThickness = AsphaltWaveImpactFunctions.ComputationalThickness(
                thicknessUpperLayer, thicknessSubLayer, elasticModulusUpperLayer, elasticModulusSubLayer);

            // Assert
            AssertHelper.AreEqual(0.38717464855982, computationalThickness);
        }

        [Test]
        public void OuterSlope_ValidInput_ExpectedValue()
        {
            // Setup
            const float slopeLowerPosition = 2.4f;
            const float slopeLowerLevel = 1.75f;
            const float slopeUpperPosition = 10.2f;
            const float slopeUpperLevel = 2.95f;

            // Call
            float outerSlope = AsphaltWaveImpactFunctions.OuterSlope(
                slopeLowerPosition, slopeLowerLevel, slopeUpperPosition, slopeUpperLevel);

            // Assert
            AssertHelper.AreEqual(0.15384615384615, outerSlope);
        }
    }
}