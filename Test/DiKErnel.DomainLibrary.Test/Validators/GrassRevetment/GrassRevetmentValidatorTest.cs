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
using DiKErnel.DomainLibrary.Validators.GrassRevetment;
using DiKErnel.Util.TestUtil;
using DiKErnel.Util.Validation;
using NUnit.Framework;

namespace DiKErnel.DomainLibrary.Test.Validators.GrassRevetment
{
    [TestFixture]
    public class GrassRevetmentValidatorTest
    {
        [Test]
        public void CriticalCumulativeOverload_VariousScenarios_ExpectedValues()
        {
            Func<double, ValidationIssue> validationFunc = GrassRevetmentValidator.CriticalCumulativeOverload;

            const string errorMessage = "CriticalCumulativeOverload must be larger than 0.";

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMin, ValidationIssueType.Error, errorMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, 0 - ValidatorAssertHelper.Epsilon, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0 + ValidatorAssertHelper.Epsilon);

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMax);
        }

        [Test]
        public void FixedNumberOfWaves_VariousScenarios_ExpectedValues()
        {
            Func<int, ValidationIssue> validationFunc = GrassRevetmentValidator.FixedNumberOfWaves;

            const string errorMessage = "FixedNumberOfWaves must be larger than 0.";

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.IntegerMin, ValidationIssueType.Error, errorMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, -1, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 1);

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.IntegerMax);
        }

        [Test]
        public void CriticalFrontVelocity_VariousScenarios_ExpectedValues()
        {
            Func<double, ValidationIssue> validationFunc = GrassRevetmentValidator.CriticalFrontVelocity;

            const string errorMessage = "CriticalFrontVelocity must be equal to 0 or larger.";

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMin, ValidationIssueType.Error, errorMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, 0 - ValidatorAssertHelper.Epsilon, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0);
            ValidatorAssertHelper.AssertValue(validationFunc, 0 + ValidatorAssertHelper.Epsilon);

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMax);
        }

        [Test]
        public void IncreasedLoadTransitionAlphaM_VariousScenarios_ExpectedValues()
        {
            Func<double, ValidationIssue> validationFunc = GrassRevetmentValidator.IncreasedLoadTransitionAlphaM;

            const string errorMessage = "IncreasedLoadTransitionAlphaM must be equal to 0 or larger.";

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMin, ValidationIssueType.Error, errorMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, 0 - ValidatorAssertHelper.Epsilon, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0);
            ValidatorAssertHelper.AssertValue(validationFunc, 0 + ValidatorAssertHelper.Epsilon);

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMax);
        }

        [Test]
        public void ReducedStrengthTransitionAlphaS_VariousScenarios_ExpectedValues()
        {
            Func<double, ValidationIssue> validationFunc = GrassRevetmentValidator.ReducedStrengthTransitionAlphaS;

            const string errorMessage = "ReducedStrengthTransitionAlphaS must be equal to 0 or larger.";

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMin, ValidationIssueType.Error, errorMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, 0 - ValidatorAssertHelper.Epsilon, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0);
            ValidatorAssertHelper.AssertValue(validationFunc, 0 + ValidatorAssertHelper.Epsilon);

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMax);
        }
    }
}