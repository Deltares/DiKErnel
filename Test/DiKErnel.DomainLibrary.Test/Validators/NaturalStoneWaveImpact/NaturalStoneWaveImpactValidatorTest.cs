// Copyright (C) Stichting Deltares and State of the Netherlands 2025. All rights reserved.
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
using DiKErnel.DomainLibrary.Validators.NaturalStoneWaveImpact;
using DiKErnel.Util.TestUtil;
using DiKErnel.Util.Validation;
using NUnit.Framework;

namespace DiKErnel.DomainLibrary.Test.Validators.NaturalStoneWaveImpact
{
    [TestFixture]
    internal sealed class NaturalStoneWaveImpactValidatorTest
    {
        [Test]
        public void RelativeDensity_VariousScenarios_ExpectedValues()
        {
            Func<double, ValidationIssue> validationFunc = NaturalStoneWaveImpactValidator.RelativeDensity;

            const string errorMessage = "RelativeDensity must be in range {0, 10}.";
            const string warningMessage = "RelativeDensity should be in range [0.1, 5].";

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMin, ValidationIssueType.Error, errorMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, 0 - ValidatorAssertHelper.Epsilon, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0 + ValidatorAssertHelper.Epsilon, ValidationIssueType.Warning,
                                              warningMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, 0.1 - ValidatorAssertHelper.Epsilon, ValidationIssueType.Warning,
                                              warningMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0.1);
            ValidatorAssertHelper.AssertValue(validationFunc, 0.1 + ValidatorAssertHelper.Epsilon);

            ValidatorAssertHelper.AssertValue(validationFunc, 5 - ValidatorAssertHelper.Epsilon);
            ValidatorAssertHelper.AssertValue(validationFunc, 5);
            ValidatorAssertHelper.AssertValue(validationFunc, 5 + ValidatorAssertHelper.Epsilon, ValidationIssueType.Warning,
                                              warningMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, 10 - ValidatorAssertHelper.Epsilon, ValidationIssueType.Warning,
                                              warningMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 10, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 10 + ValidatorAssertHelper.Epsilon, ValidationIssueType.Error,
                                              errorMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMax, ValidationIssueType.Error, errorMessage);
        }

        [Test]
        public void ThicknessTopLayer_VariousScenarios_ExpectedValues()
        {
            Func<double, ValidationIssue> validationFunc = NaturalStoneWaveImpactValidator.ThicknessTopLayer;

            const string errorMessage = "ThicknessTopLayer must be in range {0, 1}.";
            const string warningMessage = "ThicknessTopLayer should be in range [0.04, 0.6].";

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMin, ValidationIssueType.Error, errorMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, 0 - ValidatorAssertHelper.Epsilon, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0 + ValidatorAssertHelper.Epsilon, ValidationIssueType.Warning,
                                              warningMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, 0.04 - ValidatorAssertHelper.Epsilon, ValidationIssueType.Warning,
                                              warningMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0.04);
            ValidatorAssertHelper.AssertValue(validationFunc, 0.04 + ValidatorAssertHelper.Epsilon);

            ValidatorAssertHelper.AssertValue(validationFunc, 0.6 - ValidatorAssertHelper.Epsilon);
            ValidatorAssertHelper.AssertValue(validationFunc, 0.6);
            ValidatorAssertHelper.AssertValue(validationFunc, 0.6 + ValidatorAssertHelper.Epsilon, ValidationIssueType.Warning,
                                              warningMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, 1 - ValidatorAssertHelper.Epsilon, ValidationIssueType.Warning,
                                              warningMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 1, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 1 + ValidatorAssertHelper.Epsilon, ValidationIssueType.Error, errorMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMax, ValidationIssueType.Error, errorMessage);
        }

        [Test]
        public void SlopeUpperLevelAus_VariousScenarios_ExpectedValues()
        {
            Func<double, ValidationIssue> validationFunc = NaturalStoneWaveImpactValidator.SlopeUpperLevelAus;

            const string errorMessage = "SlopeUpperLevelAus must be larger than 0.";
            const string warningMessage = "SlopeUpperLevelAus should be in range [0.01, 0.2].";

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMin, ValidationIssueType.Error, errorMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, 0 - ValidatorAssertHelper.Epsilon, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0 + ValidatorAssertHelper.Epsilon, ValidationIssueType.Warning,
                                              warningMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, 0.01 - ValidatorAssertHelper.Epsilon, ValidationIssueType.Warning,
                                              warningMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0.01);
            ValidatorAssertHelper.AssertValue(validationFunc, 0.01 + ValidatorAssertHelper.Epsilon);

            ValidatorAssertHelper.AssertValue(validationFunc, 0.2 - ValidatorAssertHelper.Epsilon);
            ValidatorAssertHelper.AssertValue(validationFunc, 0.2);
            ValidatorAssertHelper.AssertValue(validationFunc, 0.2 + ValidatorAssertHelper.Epsilon, ValidationIssueType.Warning,
                                              warningMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMax, ValidationIssueType.Warning, warningMessage);
        }

        [Test]
        public void SlopeLowerLevelAls_VariousScenarios_ExpectedValues()
        {
            Func<double, ValidationIssue> validationFunc = NaturalStoneWaveImpactValidator.SlopeLowerLevelAls;

            const string errorMessage = "SlopeLowerLevelAls must be larger than 0.";
            const string warningMessage = "SlopeLowerLevelAls should be in range [1, 2].";

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMin, ValidationIssueType.Error, errorMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, 0 - ValidatorAssertHelper.Epsilon, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0 + ValidatorAssertHelper.Epsilon, ValidationIssueType.Warning,
                                              warningMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, 1 - ValidatorAssertHelper.Epsilon, ValidationIssueType.Warning,
                                              warningMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 1);
            ValidatorAssertHelper.AssertValue(validationFunc, 1 + ValidatorAssertHelper.Epsilon);

            ValidatorAssertHelper.AssertValue(validationFunc, 2 - ValidatorAssertHelper.Epsilon);
            ValidatorAssertHelper.AssertValue(validationFunc, 2);
            ValidatorAssertHelper.AssertValue(validationFunc, 2 + ValidatorAssertHelper.Epsilon, ValidationIssueType.Warning,
                                              warningMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMax, ValidationIssueType.Warning, warningMessage);
        }
    }
}