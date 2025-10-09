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
    internal sealed class RevetmentValidatorTest
    {
        [Test]
        public void InitialDamage_VariousScenarios_ExpectedValues()
        {
            Func<double, ValidationIssue> validationFunc = RevetmentValidator.InitialDamage;

            const string errorMessage = "InitialDamage must be equal to 0 or larger.";
            const string warningMessage = "InitialDamage should be in range [0, 1}.";

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMin, ValidationIssueType.Error, errorMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, 0 - ValidatorAssertHelper.Epsilon, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0);
            ValidatorAssertHelper.AssertValue(validationFunc, 0 + ValidatorAssertHelper.Epsilon);

            ValidatorAssertHelper.AssertValue(validationFunc, 1 - ValidatorAssertHelper.Epsilon);
            ValidatorAssertHelper.AssertValue(validationFunc, 1, ValidationIssueType.Warning, warningMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 1 + ValidatorAssertHelper.Epsilon, ValidationIssueType.Warning,
                                              warningMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMax, ValidationIssueType.Warning, warningMessage);
        }

        [Test]
        public void FailureNumber_VariousScenarios_ExpectedValues()
        {
            ValidationIssue ValidationFunc(double failureNumber) => RevetmentValidator.FailureNumber(failureNumber, 0);

            const string errorMessage = "FailureNumber must be equal to InitialDamage or larger.";

            ValidatorAssertHelper.AssertValue(ValidationFunc, ValidatorAssertHelper.DoubleMin, ValidationIssueType.Error, errorMessage);

            ValidatorAssertHelper.AssertValue(ValidationFunc, 0 - ValidatorAssertHelper.Epsilon, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(ValidationFunc, 0d);
            ValidatorAssertHelper.AssertValue(ValidationFunc, 0 + ValidatorAssertHelper.Epsilon);

            ValidatorAssertHelper.AssertValue(ValidationFunc, ValidatorAssertHelper.DoubleMax);
        }

        [Test]
        public void AverageNumberOfWavesCtm_VariousScenarios_ExpectedValues()
        {
            Func<double, ValidationIssue> validationFunc = RevetmentValidator.AverageNumberOfWavesCtm;

            const string errorMessage = "AverageNumberOfWavesCtm must be larger than 0.";

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMin, ValidationIssueType.Error, errorMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, 0 - ValidatorAssertHelper.Epsilon, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0 + ValidatorAssertHelper.Epsilon);

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMax);
        }
    }
}