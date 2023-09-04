// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
//
// This file is part of DiKErnel.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <https://www.gnu.org/licenses/>.
//
// All names, logos, and references to "Deltares" are registered trademarks of
// Stichting Deltares and remain full property of Stichting Deltares at all times.
// All rights reserved.

using DiKErnel.Core;
using DiKErnel.Core.Data;
using DiKErnel.Integration;
using DiKErnel.Integration.Data.GrassRevetment;
using DiKErnel.Integration.Data.GrassRevetmentOvertopping;
using DiKErnel.Util;
using NUnit.Framework;

namespace DiKErnel.System.Test
{
    [TestFixture]
    public class GrassRevetmentOvertoppingCalculationTest : CalculationTest
    {
        [Test]
        public void GivenCalculationInputForSchematization1Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization1();

            var locationConstructionProperties = new GrassRevetmentOvertoppingLocationConstructionProperties(
                50, GrassRevetmentTopLayerType.ClosedSod)
            {
                InitialDamage = 0.02
            };

            builder.AddGrassOvertoppingLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            var calculator = new Calculator(calculationInput.Data);
            calculator.WaitForCompletion();

            // Then
            AssertOutput(calculator, 1.48214256643614, 33913);
        }

        [Test]
        public void GivenCalculationInputForSchematization1Testcase2_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization1();

            var locationConstructionProperties = new GrassRevetmentOvertoppingLocationConstructionProperties(
                33, GrassRevetmentTopLayerType.ClosedSod)
            {
                InitialDamage = 0.02
            };

            builder.AddGrassOvertoppingLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            var calculator = new Calculator(calculationInput.Data);
            calculator.WaitForCompletion();

            // Then
            AssertOutput(calculator, 0.07514904750839);
        }

        [Test]
        public void GivenCalculationInputForSchematization1Testcase3_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization1();

            var locationConstructionProperties = new GrassRevetmentOvertoppingLocationConstructionProperties(
                33, GrassRevetmentTopLayerType.ClosedSod)
            {
                InitialDamage = 0.02,
                DikeHeight = 8
            };

            builder.AddGrassOvertoppingLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            var calculator = new Calculator(calculationInput.Data);
            calculator.WaitForCompletion();

            // Then
            AssertOutput(calculator, 0.04031327976012);
        }

        [Test]
        public void GivenCalculationInputForSchematization1Testcase4_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization1();

            var locationConstructionProperties = new GrassRevetmentOvertoppingLocationConstructionProperties(
                33, GrassRevetmentTopLayerType.ClosedSod)
            {
                InitialDamage = 0.02,
                DikeHeight = 5.65
            };

            builder.AddGrassOvertoppingLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            var calculator = new Calculator(calculationInput.Data);
            calculator.WaitForCompletion();

            // Then
            AssertOutput(calculator, 0.36080579320214);
        }

        [Test]
        public void GivenCalculationInputForSchematization2Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization2();

            var locationConstructionProperties = new GrassRevetmentOvertoppingLocationConstructionProperties(
                40, GrassRevetmentTopLayerType.OpenSod);

            builder.AddGrassOvertoppingLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            var calculator = new Calculator(calculationInput.Data);
            calculator.WaitForCompletion();

            // Then
            AssertOutput(calculator, 24.68131275788636, 5311);
        }

        [Test]
        public void GivenCalculationInputForSchematization2Testcase2_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization2();

            var locationConstructionProperties = new GrassRevetmentOvertoppingLocationConstructionProperties(
                30, GrassRevetmentTopLayerType.OpenSod)
            {
                DikeHeight = 9.5
            };

            builder.AddGrassOvertoppingLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            var calculator = new Calculator(calculationInput.Data);
            calculator.WaitForCompletion();

            // Then
            AssertOutput(calculator, 0.86861734396724);
        }

        [Test]
        public void GivenCalculationInputForSchematization2Testcase3_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization2();

            var locationConstructionProperties = new GrassRevetmentOvertoppingLocationConstructionProperties(
                35, GrassRevetmentTopLayerType.OpenSod)
            {
                IncreasedLoadTransitionAlphaM = 1.2,
                DikeHeight = 9.6
            };

            builder.AddGrassOvertoppingLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            var calculator = new Calculator(calculationInput.Data);
            calculator.WaitForCompletion();

            // Then
            AssertOutput(calculator, 1.11910058435611, 51672);
        }

        [Test]
        public void GivenCalculationInputForSchematization2Testcase4_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization2();

            var locationConstructionProperties = new GrassRevetmentOvertoppingLocationConstructionProperties(
                35, GrassRevetmentTopLayerType.OpenSod)
            {
                IncreasedLoadTransitionAlphaM = 1.2,
                ReducedStrengthTransitionAlphaS = 1.3,
                FixedNumberOfWaves = 5000,
                DikeHeight = 9.7
            };

            builder.AddGrassOvertoppingLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            var calculator = new Calculator(calculationInput.Data);
            calculator.WaitForCompletion();

            // Then
            AssertOutput(calculator, 0.68842513955306);
        }

        [Test]
        public void GivenCalculationInputForSchematization3Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization3();

            var locationConstructionProperties = new GrassRevetmentOvertoppingLocationConstructionProperties(
                60, GrassRevetmentTopLayerType.OpenSod);

            builder.AddGrassOvertoppingLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            var calculator = new Calculator(calculationInput.Data);
            calculator.WaitForCompletion();

            // Then
            AssertOutput(calculator, 1.99284873782755, 33915);
        }

        [Test]
        public void GivenCalculationInputForSchematization3Testcase2_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization3();

            var locationConstructionProperties = new GrassRevetmentOvertoppingLocationConstructionProperties(
                50, GrassRevetmentTopLayerType.OpenSod)
            {
                DikeHeight = 6.7
            };

            builder.AddGrassOvertoppingLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            var calculator = new Calculator(calculationInput.Data);
            calculator.WaitForCompletion();

            // Then
            AssertOutput(calculator, 12.99435588540268, 23118);
        }

        [Test]
        public void GivenCalculationInputForSchematization3Testcase3_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization3();

            var locationConstructionProperties = new GrassRevetmentOvertoppingLocationConstructionProperties(
                50, GrassRevetmentTopLayerType.OpenSod)
            {
                InitialDamage = 0.9,
                FixedNumberOfWaves = 15000,
                DikeHeight = 9
            };

            builder.AddGrassOvertoppingLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            var calculator = new Calculator(calculationInput.Data);
            calculator.WaitForCompletion();

            // Then
            AssertOutput(calculator, 1.03611132410722, 48552);
        }

        [Test]
        public void GivenCalculationInputForSchematization3Testcase4_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization3();

            var locationConstructionProperties = new GrassRevetmentOvertoppingLocationConstructionProperties(
                50, GrassRevetmentTopLayerType.OpenSod)
            {
                CriticalCumulativeOverload = 7500,
                CriticalFrontVelocity = 5.5,
                IncreasedLoadTransitionAlphaM = 1.25,
                ReducedStrengthTransitionAlphaS = 1.33,
                AverageNumberOfWavesCtm = 0.85,
                FixedNumberOfWaves = 15000,
                FrontVelocityCwo = 1.6,
                AccelerationAlphaAForCrest = 1.1,
                AccelerationAlphaAForInnerSlope = 1.5
            };

            builder.AddGrassOvertoppingLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            var calculator = new Calculator(calculationInput.Data);
            calculator.WaitForCompletion();

            // Then
            AssertOutput(calculator, 0.40767273974729);
        }

        private static CalculationInputBuilder CreateBuilderForSchematization1()
        {
            var builder = new CalculationInputBuilder();

            builder.AddTimeStep(0, 3600, 5.5, 1.9, 4.7, -10);
            builder.AddTimeStep(3600, 7200, 5.6, 1.95, 4.73, -8);
            builder.AddTimeStep(7200, 10800, 5.7, 2, 4.76, -6);
            builder.AddTimeStep(10800, 14400, 5.8, 2.05, 4.79, -4);
            builder.AddTimeStep(14400, 18000, 5.9, 2.1, 4.82, -2);
            builder.AddTimeStep(18000, 21600, 6, 2.15, 4.85, 0);
            builder.AddTimeStep(21600, 25200, 6.1, 2.2, 4.88, 2);
            builder.AddTimeStep(25200, 28800, 6.2, 2.25, 4.91, 4);
            builder.AddTimeStep(28800, 32400, 6.2, 2.3, 4.94, 6);
            builder.AddTimeStep(32400, 36000, 6.1, 2.35, 4.97, 8);
            builder.AddTimeStep(36000, 39600, 6, 2.4, 5, 10);
            builder.AddTimeStep(39600, 43200, 5.9, 2.45, 5.03, 12);
            builder.AddTimeStep(43200, 46800, 5.8, 2.5, 5.06, 14);
            builder.AddTimeStep(46800, 50400, 5.7, 2.55, 5.09, 16);
            builder.AddTimeStep(50400, 54000, 5.6, 2.6, 5.12, 18);
            builder.AddTimeStep(54000, 57600, 5.5, 2.65, 5.15, 20);

            builder.AddDikeProfileSegment(0, -0.1, 5, 0, 1);
            builder.AddDikeProfileSegment(5, 0, 15, 3, 1);
            builder.AddDikeProfileSegment(15, 3, 22, 3.2, 0.75);
            builder.AddDikeProfileSegment(22, 3.2, 30, 7.5, 0.5);
            builder.AddDikeProfileSegment(30, 7.5, 31, 7.6, 0.8);
            builder.AddDikeProfileSegment(31, 7.6, 34, 7.7, 0.8);
            builder.AddDikeProfileSegment(34, 7.7, 35, 7.4, 0.8);
            builder.AddDikeProfileSegment(35, 7.4, 45, 5, 0.8);
            builder.AddDikeProfileSegment(45, 5, 60, 0.5, 0.8);
            builder.AddDikeProfileSegment(60, 0.5, 70, 0.5, 0.8);

            builder.AddDikeProfilePoint(5, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(15, CharacteristicPointType.CrestOuterBerm);
            builder.AddDikeProfilePoint(22, CharacteristicPointType.NotchOuterBerm);
            builder.AddDikeProfilePoint(30, CharacteristicPointType.OuterCrest);
            builder.AddDikeProfilePoint(35, CharacteristicPointType.InnerCrest);
            builder.AddDikeProfilePoint(60, CharacteristicPointType.InnerToe);

            return builder;
        }

        private static CalculationInputBuilder CreateBuilderForSchematization2()
        {
            var builder = new CalculationInputBuilder();

            builder.AddTimeStep(0, 3600, 5, 2.35, 5.2, -10);
            builder.AddTimeStep(3600, 7200, 5.1, 2.4, 5.23, -8);
            builder.AddTimeStep(7200, 10800, 5.2, 2.45, 5.26, -6);
            builder.AddTimeStep(10800, 14400, 5.3, 2.5, 5.29, -4);
            builder.AddTimeStep(14400, 18000, 5.4, 2.55, 5.32, -2);
            builder.AddTimeStep(18000, 21600, 5.5, 2.6, 5.35, 0);
            builder.AddTimeStep(21600, 25200, 5.6, 2.65, 5.38, 2);
            builder.AddTimeStep(25200, 28800, 5.7, 2.7, 5.41, 4);
            builder.AddTimeStep(28800, 32400, 5.7, 2.75, 5.44, 6);
            builder.AddTimeStep(32400, 36000, 5.6, 2.8, 5.47, 8);
            builder.AddTimeStep(36000, 39600, 5.5, 2.85, 5.5, 10);
            builder.AddTimeStep(39600, 43200, 5.4, 2.9, 5.53, 12);
            builder.AddTimeStep(43200, 46800, 5.3, 2.95, 5.56, 14);
            builder.AddTimeStep(46800, 50400, 5.2, 3, 5.59, 16);
            builder.AddTimeStep(50400, 54000, 5.1, 3.05, 5.62, 18);
            builder.AddTimeStep(54000, 57600, 5, 3.1, 5.65, 20);

            builder.AddDikeProfileSegment(0, -0.1, 5, 0, 1);
            builder.AddDikeProfileSegment(5, 0, 30, 7.5, 1);
            builder.AddDikeProfileSegment(30, 7.5, 31, 7.6, 0.8);
            builder.AddDikeProfileSegment(31, 7.6, 34, 7.7, 0.8);
            builder.AddDikeProfileSegment(34, 7.7, 35, 7.4, 0.8);
            builder.AddDikeProfileSegment(35, 7.4, 45, 5, 0.8);
            builder.AddDikeProfileSegment(45, 5, 60, 0.5, 0.8);
            builder.AddDikeProfileSegment(60, 0.5, 70, 0.5, 0.8);

            builder.AddDikeProfilePoint(5, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(30, CharacteristicPointType.OuterCrest);
            builder.AddDikeProfilePoint(35, CharacteristicPointType.InnerCrest);
            builder.AddDikeProfilePoint(60, CharacteristicPointType.InnerToe);

            return builder;
        }

        private static CalculationInputBuilder CreateBuilderForSchematization3()
        {
            var builder = new CalculationInputBuilder();

            builder.AddTimeStep(0, 3600, 5.7, 2.05, 5.2, -10);
            builder.AddTimeStep(3600, 7200, 6.2, 2.1, 5.23, -8);
            builder.AddTimeStep(7200, 10800, 6.8, 2.15, 5.26, -6);
            builder.AddTimeStep(10800, 14400, 6.8, 2.2, 5.29, -4);
            builder.AddTimeStep(14400, 21600, 6.8, 2.25, 5.32, -2);
            builder.AddTimeStep(21600, 32400, 6.7, 2.3, 5.35, 0);
            builder.AddTimeStep(32400, 46800, 6.6, 2.35, 5.38, 2);
            builder.AddTimeStep(46800, 50400, 6.4, 2.4, 5.41, 4);
            builder.AddTimeStep(50400, 54000, 6.2, 2.45, 5.44, 6);
            builder.AddTimeStep(54000, 57600, 6.1, 2.5, 5.47, 8);
            builder.AddTimeStep(57600, 75600, 6, 2.55, 5.5, 10);
            builder.AddTimeStep(75600, 79200, 5.7, 2.6, 5.53, 12);

            builder.AddDikeProfileSegment(-5, -4, -1.73, -2.89, 1);
            builder.AddDikeProfileSegment(-1.73, -2.89, 33.82, 6.03, 1);
            builder.AddDikeProfileSegment(33.82, 6.03, 38.16, 6.31, 0.9);
            builder.AddDikeProfileSegment(38.16, 6.31, 47.34, 8.64, 0.8);
            builder.AddDikeProfileSegment(47.34, 8.64, 52, 8.7, 1);
            builder.AddDikeProfileSegment(52, 8.7, 70, 5, 1);
            builder.AddDikeProfileSegment(70, 5, 85, 1, 1);
            builder.AddDikeProfileSegment(85, 1, 95, 0, 1);

            builder.AddDikeProfilePoint(-1.73, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(33.82, CharacteristicPointType.CrestOuterBerm);
            builder.AddDikeProfilePoint(38.16, CharacteristicPointType.NotchOuterBerm);
            builder.AddDikeProfilePoint(47.34, CharacteristicPointType.OuterCrest);
            builder.AddDikeProfilePoint(52, CharacteristicPointType.InnerCrest);
            builder.AddDikeProfilePoint(85, CharacteristicPointType.InnerToe);

            return builder;
        }
    }
}