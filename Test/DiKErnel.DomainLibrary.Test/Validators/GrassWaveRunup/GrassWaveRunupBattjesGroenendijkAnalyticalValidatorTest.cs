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

using System;
using DiKErnel.DomainLibrary.Validators.GrassWaveRunup;
using DiKErnel.Util.TestUtil;
using DiKErnel.Util.Validation;
using NUnit.Framework;

namespace DiKErnel.DomainLibrary.Test.Validators.GrassWaveRunup
{
    [TestFixture]
    public class GrassWaveRunupBattjesGroenendijkAnalyticalValidatorTest
    {
        [Test]
        public void ForeshoreSlope_VariousScenarios_ExpectedValues()
        {
            Func<double, ValidationIssue> validationFunc = GrassWaveRunupBattjesGroenendijkAnalyticalValidator.ForeshoreSlope;

            const string errorMessage = "ForeshoreSlope must be in range [0.004, 0.05].";

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMin, ValidationIssueType.Error, errorMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, 0.004 - ValidatorAssertHelper.Epsilon, ValidationIssueType.Error,
                                              errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0.004);
            ValidatorAssertHelper.AssertValue(validationFunc, 0.004 + ValidatorAssertHelper.Epsilon);

            ValidatorAssertHelper.AssertValue(validationFunc, 0.05 - ValidatorAssertHelper.Epsilon);
            ValidatorAssertHelper.AssertValue(validationFunc, 0.05);
            ValidatorAssertHelper.AssertValue(validationFunc, 0.05 + ValidatorAssertHelper.Epsilon, ValidationIssueType.Error,
                                              errorMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMax, ValidationIssueType.Error, errorMessage);
        }
    }
}