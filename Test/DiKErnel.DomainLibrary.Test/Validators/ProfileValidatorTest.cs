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
using DiKErnel.DomainLibrary.Validators;
using DiKErnel.Util.TestUtil;
using DiKErnel.Util.Validation;
using NUnit.Framework;

namespace DiKErnel.DomainLibrary.Test.Validators
{
    [TestFixture]
    internal sealed class ProfileValidatorTest
    {
        [Test]
        public void DikeOrientation_VariousScenarios_ExpectedValues()
        {
            Func<double, ValidationIssue> validationFunc = ProfileValidator.DikeOrientation;

            const string errorMessage = "Dike orientation must be in range [0, 360].";

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMin, ValidationIssueType.Error, errorMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, 0 - ValidatorAssertHelper.Epsilon, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0);
            ValidatorAssertHelper.AssertValue(validationFunc, 0 + ValidatorAssertHelper.Epsilon);

            ValidatorAssertHelper.AssertValue(validationFunc, 360 - ValidatorAssertHelper.Epsilon);
            ValidatorAssertHelper.AssertValue(validationFunc, 360);
            ValidatorAssertHelper.AssertValue(validationFunc, 360 + ValidatorAssertHelper.Epsilon, ValidationIssueType.Error, errorMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMax, ValidationIssueType.Error, errorMessage);
        }

        [Test]
        public void RoughnessCoefficient_VariousScenarios_ExpectedValues()
        {
            Func<double, ValidationIssue> validationFunc = ProfileValidator.RoughnessCoefficient;

            const string errorMessage = "Roughness coefficient must be in range [0.5, 1].";

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMin, ValidationIssueType.Error, errorMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, 0.5 - ValidatorAssertHelper.Epsilon, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0.5);
            ValidatorAssertHelper.AssertValue(validationFunc, 0.5 + ValidatorAssertHelper.Epsilon);

            ValidatorAssertHelper.AssertValue(validationFunc, 1 - ValidatorAssertHelper.Epsilon);
            ValidatorAssertHelper.AssertValue(validationFunc, 1);
            ValidatorAssertHelper.AssertValue(validationFunc, 1 + ValidatorAssertHelper.Epsilon, ValidationIssueType.Error, errorMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMax, ValidationIssueType.Error, errorMessage);
        }
    }
}