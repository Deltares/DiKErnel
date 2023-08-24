﻿// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
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
using System.Collections.Generic;
using DiKErnel.Util;
using DiKErnel.Util.Validation;

namespace DiKErnel.Integration.Helpers
{
    internal static class ValidationHelper
    {
        public static bool RegisterValidationIssues(IReadOnlyList<ValidationIssue> validationIssues)
        {
            var overallValidationSuccessful = true;

            foreach (ValidationIssue validationIssue in validationIssues)
            {
                overallValidationSuccessful &= validationIssue == null || RegisterValidationIssue(validationIssue);
            }

            return overallValidationSuccessful;
        }

        private static bool RegisterValidationIssue(ValidationIssue validationIssue)
        {
            ValidationIssueType validationIssueType = validationIssue.ValidationIssueType;

            EventRegistry.Register(new Event(validationIssue.Message, ConvertValidationIssueType(validationIssueType)));

            return validationIssueType != ValidationIssueType.Error;
        }

        private static EventType ConvertValidationIssueType(ValidationIssueType validationIssueType)
        {
            return validationIssueType switch
            {
                ValidationIssueType.Warning => EventType.Warning,
                ValidationIssueType.Error => EventType.Error,
                _ => throw new NotSupportedException("Unsupported ValidationIssueType.")
            };
        }
    }
}