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

namespace DiKErnel.TestUtil
{
    public static class RandomExtensions
    {
        private static readonly string randomChars = "$%#@! abcdefghijklmnopqrstuvwxyz 1234567890 ?;: ABCDEFGHIJKLMNOPQRSTUVWXYZ";

        public static bool NextBoolean(this Random random)
        {
            if (random == null)
            {
                throw new ArgumentNullException(nameof(random));
            }

            return Convert.ToBoolean(random.Next(0, 2));
        }

        public static TEnum NextEnumValue<TEnum>(this Random random)
        {
            if (random == null)
            {
                throw new ArgumentNullException(nameof(random));
            }

            var enumValues = (TEnum[]) Enum.GetValues(typeof(TEnum));
            return enumValues[random.Next(enumValues.Length)];
        }

        public static string NextString(this Random random)
        {
            if (random == null)
            {
                throw new ArgumentNullException(nameof(random));
            }

            var nextString = string.Empty;

            for (var i = 0; i < random.Next(10, 21); i++)
            {
                nextString += randomChars[random.Next(0, randomChars.Length)];
            }

            return nextString;
        }
    }
}