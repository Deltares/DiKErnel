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

namespace DiKErnel.Core
{
    /// <summary>
    /// Class containing settings to be used by <see cref="Calculator"/>.
    /// </summary>
    public class CalculatorSettings
    {
        /// <summary>
        /// Gets or sets the progress handler.
        /// </summary>
        /// <remarks>The progress of the calculations is reported back as a rounded percentage in the range from 0 to 100.</remarks>
        public IProgress<int> ProgressHandler { get; set; }

        /// <summary>
        /// Gets or sets the log handler.
        /// </summary>
        public ILogHandler LogHandler { get; set; }

        /// <summary>
        /// Gets or sets the delegate that handles if a calculation should cancel.
        /// </summary>
        public Func<bool> ShouldCancel { get; set; }
    }
}