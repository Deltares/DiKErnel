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
using System.Collections.Generic;
using DiKErnel.Core;
using DiKErnel.Core.Data;
using DiKErnel.Core.Extensions;
using DiKErnel.Util;
using NUnit.Framework;

namespace DiKErnel.System.Test
{
    public abstract class CalculationTest
    {
        protected static void AssertOutput(Calculator calculator, double expectedDamage,
                                           int? expectedTimeOfFailure = null)
        {
            if (calculator == null)
            {
                throw new ArgumentNullException(nameof(calculator));
            }
            
            Assert.AreEqual(CalculationState.FinishedSuccessfully, calculator.CalculationState);

            DataResult<CalculationOutput> calculatorResult = calculator.Result;
            Assert.IsTrue(calculatorResult.Successful);
            CollectionAssert.IsEmpty(calculatorResult.Events);

            IReadOnlyList<double> damages = calculatorResult.Data.LocationDependentOutputItems[0].GetDamages();
            Assert.AreEqual(expectedDamage, damages[damages.Count - 1], 1e-14);

            Assert.AreEqual(expectedTimeOfFailure,
                            calculatorResult.Data.LocationDependentOutputItems[0].GetTimeOfFailure());
        }
    }
}