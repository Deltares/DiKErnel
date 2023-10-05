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

using System.Collections.Generic;
using DiKErnel.Core;
using DiKErnel.Core.Data;
using DiKErnel.Integration;
using DiKErnel.Integration.Data.AsphaltRevetmentWaveImpact;
using DiKErnel.Util;
using NUnit.Framework;

namespace DiKErnel.System.Test
{
    [TestFixture]
    public class AsphaltRevetmentWaveImpactCalculationTest : CalculationTest
    {
        [Test]
        public void GivenCalculationInputForSchematization1Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization1();

            var locationConstructionProperties = new AsphaltRevetmentWaveImpactLocationConstructionProperties(
                10, AsphaltRevetmentTopLayerType.HydraulicAsphaltConcrete, 1.6, 55, 0.4, 18000);

            builder.AddAsphaltWaveImpactLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            var calculator = new Calculator(calculationInput.Data);
            calculator.WaitForCompletion();

            // Then
            AssertOutput(calculator, 1.09045507114147, 28730);
        }

        [Test]
        public void GivenCalculationInputForSchematization1Testcase2_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization1();

            var locationConstructionProperties = new AsphaltRevetmentWaveImpactLocationConstructionProperties(
                10, AsphaltRevetmentTopLayerType.HydraulicAsphaltConcrete, 1.75, 60, 0.3, 16000)
            {
                InitialDamage = 0.4
            };

            builder.AddAsphaltWaveImpactLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            var calculator = new Calculator(calculationInput.Data);
            calculator.WaitForCompletion();

            // Then
            AssertOutput(calculator, 1.59946302845746, 21784);
        }

        [Test]
        public void GivenCalculationInputForSchematization1Testcase3_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization1();

            var locationConstructionProperties = new AsphaltRevetmentWaveImpactLocationConstructionProperties(
                10, AsphaltRevetmentTopLayerType.HydraulicAsphaltConcrete, 1.6, 55, 0.15, 18000)
            {
                ThicknessSubLayer = 0.18,
                ElasticModulusSubLayer = 15000
            };

            builder.AddAsphaltWaveImpactLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            var calculator = new Calculator(calculationInput.Data);
            calculator.WaitForCompletion();

            // Then
            AssertOutput(calculator, 1.45048223968934, 24186);
        }

        [Test]
        public void GivenCalculationInputForSchematization1Testcase4_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization1();

            var locationConstructionProperties = new AsphaltRevetmentWaveImpactLocationConstructionProperties(
                10, AsphaltRevetmentTopLayerType.HydraulicAsphaltConcrete, 1.6, 55, 0.3, 18000)
            {
                ImpactFactors = new List<(double, double)>
                {
                    (0.4, 0.349),
                    (0.8, 0.123),
                    (1.2, 0.152),
                    (1.6, 0.125),
                    (2.0, 0.088),
                    (2.4, 0.059),
                    (2.8, 0.038),
                    (3.2, 0.024),
                    (3.6, 0.016),
                    (4.0, 0.01),
                    (4.4, 0.007),
                    (4.8, 0.004),
                    (5.2, 0.003),
                    (5.6, 0.002),
                    (6.0, 0.001)
                }
            };

            builder.AddAsphaltWaveImpactLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            var calculator = new Calculator(calculationInput.Data);
            calculator.WaitForCompletion();

            // Then
            AssertOutput(calculator, 1.12097513403652, 28534);
        }

        [Test]
        public void GivenCalculationInputForSchematization1Testcase5_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization1();

            var locationConstructionProperties = new AsphaltRevetmentWaveImpactLocationConstructionProperties(
                10, AsphaltRevetmentTopLayerType.HydraulicAsphaltConcrete, 1.6, 55, 0.38, 18000)
            {
                DepthFactors = new List<(double, double)>
                {
                    (-0.99, 0.00009647),
                    (-0.9, 0.0007544),
                    (-0.81, 0.004299),
                    (-0.72, 0.01785),
                    (-0.63, 0.05403),
                    (-0.54, 0.1192),
                    (-0.45, 0.1916),
                    (-0.36, 0.2244),
                    (-0.27, 0.1916),
                    (-0.18, 0.1192),
                    (-0.09, 0.05403),
                    (0.0, 0.01785),
                    (0.09, 0.004299),
                    (0.18, 0.0007544),
                    (0.27, 0.00009647)
                }
            };

            builder.AddAsphaltWaveImpactLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            var calculator = new Calculator(calculationInput.Data);
            calculator.WaitForCompletion();

            // Then
            AssertOutput(calculator, 1.33022336665883, 22915);
        }

        [Test]
        public void GivenCalculationInputForSchematization1Testcase6_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization1();

            var locationConstructionProperties = new AsphaltRevetmentWaveImpactLocationConstructionProperties(
                10, AsphaltRevetmentTopLayerType.HydraulicAsphaltConcrete, 1.6, 55, 0.45, 18000)
            {
                WidthFactors = new List<(double, double)>
                {
                    (0.1, 0.0),
                    (0.25, 0.018),
                    (0.4, 0.09),
                    (0.55, 0.153),
                    (0.7, 0.168),
                    (0.85, 0.15),
                    (1.0, 0.119),
                    (1.15, 0.089),
                    (1.3, 0.064),
                    (1.45, 0.045),
                    (1.6, 0.031),
                    (1.75, 0.022),
                    (1.9, 0.015),
                    (2.05, 0.01),
                    (2.2, 0.007)
                }
            };

            builder.AddAsphaltWaveImpactLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            var calculator = new Calculator(calculationInput.Data);
            calculator.WaitForCompletion();

            // Then
            AssertOutput(calculator, 1.39298363995088, 24516);
        }

        [Test]
        public void GivenCalculationInputForSchematization1Testcase7_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization1();

            var locationConstructionProperties = new AsphaltRevetmentWaveImpactLocationConstructionProperties(
                10, AsphaltRevetmentTopLayerType.HydraulicAsphaltConcrete, 1.6, 55, 0.35, 18000)
            {
                StiffnessRelationNu = 0.3,
                FatigueAlpha = 0.4,
                FatigueBeta = 4.5,
                AverageNumberOfWavesCtm = 0.9,
                ImpactNumberC = 0.95,
                DensityOfWater = 1000
            };

            builder.AddAsphaltWaveImpactLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            var calculator = new Calculator(calculationInput.Data);
            calculator.WaitForCompletion();

            // Then
            AssertOutput(calculator, 1.28607774443342, 25376);
        }

        [Test]
        public void GivenCalculationInputForSchematization2Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization2();

            var locationConstructionProperties = new AsphaltRevetmentWaveImpactLocationConstructionProperties(
                10, AsphaltRevetmentTopLayerType.HydraulicAsphaltConcrete, 1.6, 55, 0.4, 18000);

            builder.AddAsphaltWaveImpactLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            var calculator = new Calculator(calculationInput.Data);
            calculator.WaitForCompletion();

            // Then
            AssertOutput(calculator, 1.42481731059929, 16415);
        }

        [Test]
        public void GivenCalculationInputForSchematization3Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization3();

            var locationConstructionProperties = new AsphaltRevetmentWaveImpactLocationConstructionProperties(
                12.5, AsphaltRevetmentTopLayerType.HydraulicAsphaltConcrete, 1.6, 55, 0.4, 18000);

            builder.AddAsphaltWaveImpactLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            var calculator = new Calculator(calculationInput.Data);
            calculator.WaitForCompletion();

            // Then
            AssertOutput(calculator, 1.09045507114147, 28730);
        }

        private static CalculationInputBuilder CreateBuilderForSchematization1()
        {
            var builder = new CalculationInputBuilder();

            builder.AddTimeStep(0, 3600, 2, 1, 4, 0);
            builder.AddTimeStep(3600, 7200, 2.2, 1.5, 5, 0);
            builder.AddTimeStep(7200, 10800, 2.4, 2, 5.5, 0);
            builder.AddTimeStep(10800, 14400, 2.6, 2.4, 6, 0);
            builder.AddTimeStep(14400, 18000, 2.8, 2.5, 6.2, 0);
            builder.AddTimeStep(18000, 21600, 3, 2.6, 6.3, 0);
            builder.AddTimeStep(21600, 25200, 2.8, 2.7, 6.5, 0);
            builder.AddTimeStep(25200, 28800, 2.6, 2.6, 6.6, 0);
            builder.AddTimeStep(28800, 32400, 2.4, 2.5, 6.3, 0);
            builder.AddTimeStep(32400, 36000, 2, 2.4, 6.2, 0);

            builder.AddDikeProfileSegment(0, 0, 30, 7.5);

            builder.AddDikeProfilePoint(0, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(30, CharacteristicPointType.OuterCrest);

            return builder;
        }

        private static CalculationInputBuilder CreateBuilderForSchematization2()
        {
            var builder = new CalculationInputBuilder();

            builder.AddTimeStep(-3600, -2880, 2, 1, 4, 0);
            builder.AddTimeStep(-2880, -1440, 2.2, 1.5, 5, 0);
            builder.AddTimeStep(-1440, 720, 2.4, 2, 5.5, 0);
            builder.AddTimeStep(720, 3600, 2.6, 2.4, 6, 0);
            builder.AddTimeStep(3600, 7200, 2.8, 2.5, 6.2, 0);
            builder.AddTimeStep(7200, 11520, 3, 2.6, 6.3, 0);
            builder.AddTimeStep(11520, 16560, 2.8, 2.7, 6.5, 0);
            builder.AddTimeStep(16560, 22320, 2.6, 2.6, 6.6, 0);
            builder.AddTimeStep(22320, 28800, 2.4, 2.5, 6.3, 0);
            builder.AddTimeStep(28800, 36000, 2, 2.4, 6.2, 0);

            builder.AddDikeProfileSegment(0, 0, 30, 7.5);

            builder.AddDikeProfilePoint(0, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(30, CharacteristicPointType.OuterCrest);

            return builder;
        }

        private static CalculationInputBuilder CreateBuilderForSchematization3()
        {
            var builder = new CalculationInputBuilder();

            builder.AddTimeStep(0, 3600, 2, 1, 4, 0);
            builder.AddTimeStep(3600, 7200, 2.2, 1.5, 5, 0);
            builder.AddTimeStep(7200, 10800, 2.4, 2, 5.5, 0);
            builder.AddTimeStep(10800, 14400, 2.6, 2.4, 6, 0);
            builder.AddTimeStep(14400, 18000, 2.8, 2.5, 6.2, 0);
            builder.AddTimeStep(18000, 21600, 3, 2.6, 6.3, 0);
            builder.AddTimeStep(21600, 25200, 2.8, 2.7, 6.5, 0);
            builder.AddTimeStep(25200, 28800, 2.6, 2.6, 6.6, 0);
            builder.AddTimeStep(28800, 32400, 2.4, 2.5, 6.3, 0);
            builder.AddTimeStep(32400, 36000, 2, 2.4, 6.2, 0);

            builder.AddDikeProfileSegment(0, 0, 8, 2);
            builder.AddDikeProfileSegment(8, 2, 17, 3);
            builder.AddDikeProfileSegment(17, 3, 35, 7.5);

            builder.AddDikeProfilePoint(0, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(8, CharacteristicPointType.CrestOuterBerm);
            builder.AddDikeProfilePoint(17, CharacteristicPointType.NotchOuterBerm);
            builder.AddDikeProfilePoint(35, CharacteristicPointType.OuterCrest);

            return builder;
        }
    }
}