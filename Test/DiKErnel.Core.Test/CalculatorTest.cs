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

using DiKErnel.Core.Data;
using NSubstitute;
using NUnit.Framework;

namespace DiKErnel.Core.Test
{
    [TestFixture]
    public class CalculatorTest
    {
        [Test]
        public void GivenCalculatorWithCalculationInput_WhenWaitForCompletion_ThenCalculationPerformed()
        {
            // Given
            var calculationInput = Substitute.For<ICalculationInput>();

            calculationInput.ProfileData.Returns(Substitute.For<IProfileData>());

            calculationInput.LocationDependentInputItems.Returns(new[]
            {
                Substitute.For<ILocationDependentInput>(),
                Substitute.For<ILocationDependentInput>()
            });

            calculationInput.TimeDependentInputItems.Returns(new[]
            {
                Substitute.For<ITimeDependentInput>(),
                Substitute.For<ITimeDependentInput>(),
                Substitute.For<ITimeDependentInput>()
            });

            var calculator = new Calculator(calculationInput);

            // When
            calculator.WaitForCompletion();

            // Then
            Assert.AreEqual(100, calculator.Progress);
            Assert.AreEqual(CalculationState.FinishedSuccessfully, calculator.CalculationState);
        }
    }
}