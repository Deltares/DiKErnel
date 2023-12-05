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

using System;
using DiKErnel.Core.Data;
using DiKErnel.Util;
using NUnit.Framework;

namespace DiKErnel.KernelWrapper.Json.Input.Test
{
    [TestFixture]
    public class ComposedInputDataTest
    {
        [Test]
        public void Constructor_ExpectedValues()
        {
            // Setup
            var calculationInputDataResult = new DataResult<ICalculationInput>(Array.Empty<Event>());
            int?[] locationIds = Array.Empty<int?>();

            // Call
            var composedInputData = new ComposedInputData(calculationInputDataResult, locationIds);

            // Assert
            Assert.That(composedInputData.CalculationInputDataResult, Is.SameAs(calculationInputDataResult));
            Assert.That(composedInputData.LocationIds, Is.SameAs(locationIds));
        }
    }
}