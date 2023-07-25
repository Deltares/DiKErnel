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
using DiKErnel.DomainLibrary.Validators.GrassRevetmentWaveImpact;
using DiKErnel.Util.TestUtil;
using DiKErnel.Util.Validation;
using NUnit.Framework;

namespace DiKErnel.DomainLibrary.Test.Validators.GrassRevetmentWaveImpact
{
    [TestFixture]
    public class GrassRevetmentWaveImpactValidatorTest
    {
        [Test]
        public void TimeLineAgwi_VariousScenarios_ExpectedValues()
        {
            ValidationIssue ValidationFunc(double timeLineAgwi) => GrassRevetmentWaveImpactValidator.TimeLineAgwi(timeLineAgwi, 3);

            const string errorMessage = "TimeLineAgwi must be larger than TimeLineCgwi.";

            ValidatorAssertHelper.AssertValue(ValidationFunc, ValidatorAssertHelper.DoubleMin, ValidationIssueType.Error, errorMessage);

            ValidatorAssertHelper.AssertValue(ValidationFunc, 3.0 - ValidatorAssertHelper.Epsilon, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(ValidationFunc, 3.0, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(ValidationFunc, 3.0 + ValidatorAssertHelper.Epsilon);

            ValidatorAssertHelper.AssertValue(ValidationFunc, ValidatorAssertHelper.DoubleMax);
        }

        [Test]
        public void TimeLineBgwi_VariousScenarios_ExpectedValues()
        {
            Func<double, ValidationIssue> validationFunc = GrassRevetmentWaveImpactValidator.TimeLineBgwi;

            const string errorMessage = "TimeLineBgwi must be smaller than 0.";

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMin);

            ValidatorAssertHelper.AssertValue(validationFunc, 0.0 - ValidatorAssertHelper.Epsilon);
            ValidatorAssertHelper.AssertValue(validationFunc, 0.0, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0.0 + ValidatorAssertHelper.Epsilon, ValidationIssueType.Error, errorMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMax, ValidationIssueType.Error, errorMessage);
        }

        [Test]
        public void TimeLineCgwi_VariousScenarios_ExpectedValues()
        {
            Func<double, ValidationIssue> validationFunc = GrassRevetmentWaveImpactValidator.TimeLineCgwi;

            const string errorMessage = "TimeLineCgwi must be equal to 0 or larger.";

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMin, ValidationIssueType.Error, errorMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, 0.0 - ValidatorAssertHelper.Epsilon, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0.0);
            ValidatorAssertHelper.AssertValue(validationFunc, 0.0 + ValidatorAssertHelper.Epsilon);

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMax);
        }

        [Test]
        public void MinimumWaveHeightTemax_VariousScenarios_ExpectedValues()
        {
            Func<double, ValidationIssue> validationFunc = GrassRevetmentWaveImpactValidator.MinimumWaveHeightTemax;

            const string errorMessage = "MinimumWaveHeightTemax must be equal to 3600000 or smaller.";
            const string warningMessage = "MinimumWaveHeightTemax should be in range {1000000, 3600000].";

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMin, ValidationIssueType.Warning, warningMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, 1000000.0 - ValidatorAssertHelper.Epsilon, ValidationIssueType.Warning,
                                              warningMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 1000000.0, ValidationIssueType.Warning, warningMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 1000000.0 + ValidatorAssertHelper.Epsilon);

            ValidatorAssertHelper.AssertValue(validationFunc, 3600000.0 - ValidatorAssertHelper.Epsilon);
            ValidatorAssertHelper.AssertValue(validationFunc, 3600000.0);
            ValidatorAssertHelper.AssertValue(validationFunc, 3600000.0 + ValidatorAssertHelper.Epsilon, ValidationIssueType.Error,
                                              errorMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMax, ValidationIssueType.Error, errorMessage);
        }

        [Test]
        public void MaximumWaveHeightTemin_VariousScenarios_ExpectedValues()
        {
            Func<double, ValidationIssue> validationFunc = GrassRevetmentWaveImpactValidator.MaximumWaveHeightTemin;

            const string errorMessage = "MaximumWaveHeightTemin must be equal to 3.6 or larger.";
            const string warningMessage = "MaximumWaveHeightTemin should be in range [3.6, 10}.";

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMin, ValidationIssueType.Error, errorMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, 3.6 - ValidatorAssertHelper.Epsilon, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 3.6);
            ValidatorAssertHelper.AssertValue(validationFunc, 3.6 + ValidatorAssertHelper.Epsilon);

            ValidatorAssertHelper.AssertValue(validationFunc, 10.0 - ValidatorAssertHelper.Epsilon);
            ValidatorAssertHelper.AssertValue(validationFunc, 10.0, ValidationIssueType.Warning, warningMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 10.0 + ValidatorAssertHelper.Epsilon, ValidationIssueType.Warning,
                                              warningMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMax, ValidationIssueType.Warning, warningMessage);
        }

        [Test]
        public void WaveAngleImpactNwa_VariousScenarios_ExpectedValues()
        {
            Func<double, ValidationIssue> validationFunc = GrassRevetmentWaveImpactValidator.WaveAngleImpactNwa;

            const string errorMessage = "WaveAngleImpactNwa must be equal to 1 or smaller.";

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMin);

            ValidatorAssertHelper.AssertValue(validationFunc, 1.0 - ValidatorAssertHelper.Epsilon);
            ValidatorAssertHelper.AssertValue(validationFunc, 1.0);
            ValidatorAssertHelper.AssertValue(validationFunc, 1.0 + ValidatorAssertHelper.Epsilon, ValidationIssueType.Error, errorMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMax, ValidationIssueType.Error, errorMessage);
        }

        [Test]
        public void WaveAngleImpactQwa_VariousScenarios_ExpectedValues()
        {
            Func<double, ValidationIssue> validationFunc = GrassRevetmentWaveImpactValidator.WaveAngleImpactQwa;

            const string errorMessage = "WaveAngleImpactQwa must be in range [0, 1].";

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMin, ValidationIssueType.Error, errorMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, 0.0 - ValidatorAssertHelper.Epsilon, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0.0);
            ValidatorAssertHelper.AssertValue(validationFunc, 0.0 + ValidatorAssertHelper.Epsilon);

            ValidatorAssertHelper.AssertValue(validationFunc, 1.0 - ValidatorAssertHelper.Epsilon);
            ValidatorAssertHelper.AssertValue(validationFunc, 1.0);
            ValidatorAssertHelper.AssertValue(validationFunc, 1.0 + ValidatorAssertHelper.Epsilon, ValidationIssueType.Error, errorMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMax, ValidationIssueType.Error, errorMessage);
        }

        [Test]
        public void WaveAngleImpactRwa_VariousScenarios_ExpectedValues()
        {
            Func<double, ValidationIssue> validationFunc = GrassRevetmentWaveImpactValidator.WaveAngleImpactRwa;

            const string errorMessage = "WaveAngleImpactRwa must be larger than 0.";

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMin, ValidationIssueType.Error, errorMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, 0.0 - ValidatorAssertHelper.Epsilon, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0.0, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0.0 + ValidatorAssertHelper.Epsilon);

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMax);
        }

        [Test]
        public void UpperLimitLoadingAul_VariousScenarios_ExpectedValues()
        {
            ValidationIssue ValidationFunc(double upperLimitLoadingAul) =>
                GrassRevetmentWaveImpactValidator.UpperLimitLoadingAul(upperLimitLoadingAul, 2);

            const string errorMessage = "UpperLimitLoadingAul must be smaller than LowerLimitLoadingAll.";

            ValidatorAssertHelper.AssertValue(ValidationFunc, ValidatorAssertHelper.DoubleMin);

            ValidatorAssertHelper.AssertValue(ValidationFunc, 2.0 - ValidatorAssertHelper.Epsilon);
            ValidatorAssertHelper.AssertValue(ValidationFunc, 2.0, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(ValidationFunc, 2.0 + ValidatorAssertHelper.Epsilon, ValidationIssueType.Error, errorMessage);

            ValidatorAssertHelper.AssertValue(ValidationFunc, ValidatorAssertHelper.DoubleMax, ValidationIssueType.Error, errorMessage);
        }
    }
}