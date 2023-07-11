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

namespace DiKErnel.Util.Validation
{
    /// <summary>
    /// Class that represents a validation issue.
    /// </summary>
    public class ValidationIssue
    {
        private readonly ValidationIssueType validationIssueType;
        private readonly string message;

        /// <summary>
        /// Creates a new instance.
        /// </summary>
        /// <param name="validationIssueType">The validation issue type.</param>
        /// <param name="message">The message.</param>
        public ValidationIssue(ValidationIssueType validationIssueType, string message)
        {
            this.validationIssueType = validationIssueType;
            this.message = message;
        }

        /// <summary>
        /// Gets the validation issue type.
        /// </summary>
        /// <returns>The validation issue type.</returns>
        public ValidationIssueType GetValidationIssueType()
        {
            return validationIssueType;
        }

        /// <summary>
        /// Gets the message.
        /// </summary>
        /// <returns>The message.</returns>
        public string GetMessage()
        {
            return message;
        }
    }
}