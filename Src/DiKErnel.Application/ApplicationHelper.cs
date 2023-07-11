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
using System.Globalization;
using System.Reflection;

namespace DiKErnel.Application
{
    /// <summary>
    /// Class containing helper methods for applications.
    /// </summary>
    public class ApplicationHelper
    {
        private const string isoFormat = "yyyy-MM-ddTHH:mm:ssK";

        /// <summary>
        /// Gets the application version as a string.
        /// </summary>
        /// <returns>The version of the application as a string.</returns>
        public static string GetApplicationVersionString()
        {
            return Assembly.GetExecutingAssembly().GetName().Version.ToString();
        }

        /// <summary>
        /// Gets the operating system name.
        /// </summary>
        /// <returns>The operating system name.</returns>
        public static string GetOperatingSystemName()
        {
            return Environment.OSVersion.ToString();
        }

        /// <summary>
        /// Gets the current date and time as a formatted string.
        /// </summary>
        /// <returns>The current date and time as a formatted string.</returns>
        public static string GetFormattedDateTimeString()
        {
            return DateTime.UtcNow.ToString(isoFormat, CultureInfo.InvariantCulture);
        }
    }
}