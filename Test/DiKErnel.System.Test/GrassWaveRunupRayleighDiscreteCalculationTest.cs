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

using DiKErnel.Core;
using DiKErnel.Core.Data;
using DiKErnel.Integration;
using DiKErnel.Integration.Data.Grass;
using DiKErnel.Integration.Data.GrassWaveRunup;
using DiKErnel.Util;
using NUnit.Framework;

namespace DiKErnel.System.Test
{
    [TestFixture]
    public class GrassWaveRunupRayleighDiscreteCalculationTest : CalculationTest
    {
        [Test]
        public void GivenCalculationInputForSchematization3Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization3();

            var locationConstructionProperties = new GrassWaveRunupRayleighDiscreteLocationConstructionProperties(
                15, GrassTopLayerType.ClosedSod);

            builder.AddGrassWaveRunupRayleighDiscreteLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            var calculator = new Calculator(calculationInput.Data);
            calculator.WaitForCompletion();

            // Then
            AssertOutput(calculator, 0.69846474391984);
        }

        [Test]
        public void GivenCalculationInputForSchematization3Testcase2_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization3(20);

            var locationConstructionProperties = new GrassWaveRunupRayleighDiscreteLocationConstructionProperties(
                15, GrassTopLayerType.OpenSod);

            builder.AddGrassWaveRunupRayleighDiscreteLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            var calculator = new Calculator(calculationInput.Data);
            calculator.WaitForCompletion();

            // Then
            AssertOutput(calculator, 7.24141421738371, 23824);
        }

        [Test]
        public void GivenCalculationInputForSchematization3Testcase3_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization3(20, 0.5, 0.7, 0.8);

            var locationConstructionProperties = new GrassWaveRunupRayleighDiscreteLocationConstructionProperties(
                15, GrassTopLayerType.ClosedSod)
            {
                AverageNumberOfWavesCtm = 1
            };

            builder.AddGrassWaveRunupRayleighDiscreteLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            var calculator = new Calculator(calculationInput.Data);
            calculator.WaitForCompletion();

            // Then
            AssertOutput(calculator, 0.01075989442725);
        }

        private static CalculationInputBuilder CreateBuilderForSchematization3(double orientation = 0,
                                                                               double roughnessCoefficient1 = 1,
                                                                               double roughnessCoefficient2 = 1,
                                                                               double roughnessCoefficient3 = 1)
        {
            var builder = new CalculationInputBuilder(orientation);

            builder.AddTimeStep(0, 3600, 3, 0.5, 3, 50);
            builder.AddTimeStep(3600, 7200, 3.1, 0.7, 3.5, 45);
            builder.AddTimeStep(7200, 10800, 3.2, 1, 4, 40);
            builder.AddTimeStep(10800, 14400, 3.3, 1.3, 4.3, 35);
            builder.AddTimeStep(14400, 18000, 3.4, 1.5, 4.5, 30);
            builder.AddTimeStep(18000, 21600, 3.5, 1.8, 4.8, 25);
            builder.AddTimeStep(21600, 25200, 3.6, 2.1, 5.2, 20);
            builder.AddTimeStep(25200, 28800, 3.7, 2.5, 5.5, 15);
            builder.AddTimeStep(28800, 32400, 3.7, 2.8, 5.8, 10);
            builder.AddTimeStep(32400, 36000, 3.6, 2.8, 6, 5);
            builder.AddTimeStep(36000, 39600, 3.5, 2.5, 6, 0);
            builder.AddTimeStep(39600, 43200, 3.4, 2.1, 5.8, 0);
            builder.AddTimeStep(43200, 46800, 3.3, 1.8, 5.5, 5);
            builder.AddTimeStep(46800, 50400, 3.2, 1.5, 5.2, 10);
            builder.AddTimeStep(50400, 54000, 3.1, 1.3, 4.8, 15);
            builder.AddTimeStep(54000, 57600, 3, 1, 4.5, 20);

            builder.AddDikeProfileSegment(0, 0, 15, 4, roughnessCoefficient1);
            builder.AddDikeProfileSegment(15, 4, 20, 4.1, roughnessCoefficient2);
            builder.AddDikeProfileSegment(20, 4.1, 25, 7.5, roughnessCoefficient3);

            builder.AddDikeProfilePoint(0, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(25, CharacteristicPointType.OuterCrest);

            return builder;
        }
    }
}