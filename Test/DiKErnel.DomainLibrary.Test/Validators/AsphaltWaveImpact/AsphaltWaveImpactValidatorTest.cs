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
using DiKErnel.DomainLibrary.Validators.AsphaltWaveImpact;
using DiKErnel.Util.TestUtil;
using DiKErnel.Util.Validation;
using NUnit.Framework;

namespace DiKErnel.DomainLibrary.Test.Validators.AsphaltWaveImpact
{
    [TestFixture]
    internal sealed class AsphaltWaveImpactValidatorTest
    {
        [Test]
        public void FatigueAlpha_VariousScenarios_ExpectedValues()
        {
            Func<double, ValidationIssue> validationFunc = AsphaltWaveImpactValidator.FatigueAlpha;

            const string errorMessage = "FatigueAlpha must be larger than 0.";

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMin, ValidationIssueType.Error, errorMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, 0 - ValidatorAssertHelper.Epsilon, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0 + ValidatorAssertHelper.Epsilon);

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMax);
        }

        [Test]
        public void FatigueBeta_VariousScenarios_ExpectedValues()
        {
            Func<double, ValidationIssue> validationFunc = AsphaltWaveImpactValidator.FatigueBeta;

            const string errorMessage = "FatigueBeta must be larger than 0.";

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMin, ValidationIssueType.Error, errorMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, 0 - ValidatorAssertHelper.Epsilon, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0 + ValidatorAssertHelper.Epsilon);

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMax);
        }

        [Test]
        public void FlexuralStrength_VariousScenarios_ExpectedValues()
        {
            Func<double, ValidationIssue> validationFunc = AsphaltWaveImpactValidator.FlexuralStrength;

            const string errorMessage = "FlexuralStrength must be larger than 0.";

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMin, ValidationIssueType.Error, errorMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, 0 - ValidatorAssertHelper.Epsilon, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0 + ValidatorAssertHelper.Epsilon);

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMax);
        }

        [Test]
        public void ImpactNumberC_VariousScenarios_ExpectedValues()
        {
            Func<double, ValidationIssue> validationFunc = AsphaltWaveImpactValidator.ImpactNumberC;

            const string errorMessage = "ImpactNumberC must be larger than 0.";

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMin, ValidationIssueType.Error, errorMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, 0 - ValidatorAssertHelper.Epsilon, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0 + ValidatorAssertHelper.Epsilon);

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMax);
        }

        [Test]
        public void DensityOfWater_VariousScenarios_ExpectedValues()
        {
            Func<double, ValidationIssue> validationFunc = AsphaltWaveImpactValidator.DensityOfWater;

            const string errorMessage = "DensityOfWater must be in range [950, 1050].";

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMin, ValidationIssueType.Error, errorMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, 950 - ValidatorAssertHelper.Epsilon, ValidationIssueType.Error,
                                              errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 950);
            ValidatorAssertHelper.AssertValue(validationFunc, 950 + ValidatorAssertHelper.Epsilon);

            ValidatorAssertHelper.AssertValue(validationFunc, 1050 - ValidatorAssertHelper.Epsilon);
            ValidatorAssertHelper.AssertValue(validationFunc, 1050);
            ValidatorAssertHelper.AssertValue(validationFunc, 1050 + ValidatorAssertHelper.Epsilon, ValidationIssueType.Error,
                                              errorMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMax, ValidationIssueType.Error, errorMessage);
        }

        [Test]
        public void SoilElasticity_VariousScenarios_ExpectedValues()
        {
            Func<double, ValidationIssue> validationFunc = AsphaltWaveImpactValidator.SoilElasticity;

            const string errorMessage = "SoilElasticity must be larger than 0.";

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMin, ValidationIssueType.Error, errorMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, 0 - ValidatorAssertHelper.Epsilon, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0 + ValidatorAssertHelper.Epsilon);

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMax);
        }

        [Test]
        public void StiffnessRelationNu_VariousScenarios_ExpectedValues()
        {
            Func<double, ValidationIssue> validationFunc = AsphaltWaveImpactValidator.StiffnessRelationNu;

            const string errorMessage = "StiffnessRelationNu must be larger than 0.";

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMin, ValidationIssueType.Error, errorMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, 0 - ValidatorAssertHelper.Epsilon, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0 + ValidatorAssertHelper.Epsilon);

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMax);
        }

        [Test]
        public void Thickness_VariousScenarios_ExpectedValues()
        {
            Func<double, ValidationIssue> validationFunc = AsphaltWaveImpactValidator.Thickness;

            const string errorMessage = "Thickness must be larger than 0.";

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMin, ValidationIssueType.Error, errorMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, 0 - ValidatorAssertHelper.Epsilon, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0 + ValidatorAssertHelper.Epsilon);

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMax);
        }

        [Test]
        public void ElasticModulus_VariousScenarios_ExpectedValues()
        {
            Func<double, ValidationIssue> validationFunc = AsphaltWaveImpactValidator.ElasticModulus;

            const string errorMessage = "ElasticModulus must be larger than 0.";

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMin, ValidationIssueType.Error, errorMessage);

            ValidatorAssertHelper.AssertValue(validationFunc, 0 - ValidatorAssertHelper.Epsilon, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0, ValidationIssueType.Error, errorMessage);
            ValidatorAssertHelper.AssertValue(validationFunc, 0 + ValidatorAssertHelper.Epsilon);

            ValidatorAssertHelper.AssertValue(validationFunc, ValidatorAssertHelper.DoubleMax);
        }
    }
}