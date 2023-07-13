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
using DiKErnel.DomainLibrary.Validators;
using DiKErnel.Util.TestUtil;
using DiKErnel.Util.Validation;
using NUnit.Framework;

namespace DiKErnel.DomainLibrary.Test.Validators
{
    [TestFixture]
    public class HydraulicLoadsValidatorTest
    {
        [Test]
        public void WaveHeightHm0_VariousScenarios_ExpectedValues()
        {
            Func<double, ValidationIssue> validationFunc = HydraulicLoadsValidator.WaveHeightHm0;

            const string errorMessage = "WaveHeightHm0 must be larger than 0.";
            const string warningMessage = "WaveHeightHm0 should be in range {0.1, 10}.";

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMin, ValidationIssueType.Error, errorMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, 0.0 - ValidatorAssertHelper.Epsilon, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0.0, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0.0 + ValidatorAssertHelper.Epsilon, ValidationIssueType.Warning, warningMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, 0.1 - ValidatorAssertHelper.Epsilon, ValidationIssueType.Warning, warningMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0.1, ValidationIssueType.Warning, warningMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0.1 + ValidatorAssertHelper.Epsilon);

            ValidatorAssertHelper.AssertValue(validationFunc, 10.0 - ValidatorAssertHelper.Epsilon);
            ValidatorAssertHelper.AssertValue(validationFunc, 10.0, ValidationIssueType.Warning, warningMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 10.0 + ValidatorAssertHelper.Epsilon, ValidationIssueType.Warning, warningMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMax, ValidationIssueType.Warning, warningMessage);
        }

        [Test]
        public void WavePeriodTm10_VariousScenarios_ExpectedValues()
        {
            Func<double, ValidationIssue> validationFunc = HydraulicLoadsValidator.WavePeriodTm10;

            const string errorMessage = "WavePeriodTm10 must be larger than 0.";
            const string warningMessage = "WavePeriodTm10 should be in range {0.5, 25}.";

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMin, ValidationIssueType.Error, errorMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, 0.0 - ValidatorAssertHelper.Epsilon, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0.0, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0.0 + ValidatorAssertHelper.Epsilon, ValidationIssueType.Warning, warningMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, 0.5 - ValidatorAssertHelper.Epsilon, ValidationIssueType.Warning, warningMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0.5, ValidationIssueType.Warning, warningMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0.5 + ValidatorAssertHelper.Epsilon);

            ValidatorAssertHelper.AssertValue(validationFunc, 25.0 - ValidatorAssertHelper.Epsilon);
            ValidatorAssertHelper.AssertValue(validationFunc, 25.0, ValidationIssueType.Warning, warningMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 25.0 + ValidatorAssertHelper.Epsilon, ValidationIssueType.Warning, warningMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMax, ValidationIssueType.Warning, warningMessage);
        }

        [Test]
        public void WaveAngle_VariousScenarios_ExpectedValues()
        {
            Func<double, ValidationIssue> validationFunc = HydraulicLoadsValidator.WaveAngle;

            const string errorMessage = "WaveAngle must be in range {-180, 180].";

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMin, ValidationIssueType.Error, errorMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, -180.0 - ValidatorAssertHelper.Epsilon, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, -180.0, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, -180.0 + ValidatorAssertHelper.Epsilon);

            ValidatorAssertHelper.AssertValue(validationFunc, 180.0 - ValidatorAssertHelper.Epsilon);
            ValidatorAssertHelper.AssertValue(validationFunc, 180.0);
            ValidatorAssertHelper.AssertValue(validationFunc, 180.0 + ValidatorAssertHelper.Epsilon, ValidationIssueType.Error, errorMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMax, ValidationIssueType.Error, errorMessage);
        }
    }
}