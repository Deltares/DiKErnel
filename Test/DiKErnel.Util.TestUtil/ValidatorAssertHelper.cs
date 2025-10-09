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
using DiKErnel.Util.Validation;
using NUnit.Framework;

namespace DiKErnel.Util.TestUtil
{
    public static class ValidatorAssertHelper
    {
        public const double Epsilon = 1e-6;

        public const double DoubleMin = double.MinValue;

        public const double DoubleMax = double.MaxValue;

        public const int IntegerMin = int.MinValue;

        public const int IntegerMax = int.MaxValue;

        public static void AssertValue<T>(Func<T, ValidationIssue> validationFunc, T value)
        {
            // Call
            ValidationIssue validationIssue = validationFunc(value);

            // Assert
            Assert.That(validationIssue, Is.Null);
        }

        public static void AssertValue<T>(Func<T, ValidationIssue> validationFunc, T value,
                                          ValidationIssueType validationIssueType, string message)
        {
            // Call
            ValidationIssue validationIssue = validationFunc(value);

            // Assert
            Assert.That(validationIssue, Is.Not.Null);
            Assert.That(validationIssue.ValidationIssueType, Is.EqualTo(validationIssueType));
            Assert.That(validationIssue.Message, Is.EqualTo(message));
        }
    }
}