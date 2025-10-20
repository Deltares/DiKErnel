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

namespace DiKErnel.TestUtil
{
    public static class Random
    {
        private const string randomChars = "& $ % # @ ! * ? ; : abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ 1234567890";

        private static readonly System.Random instance = new System.Random(21);

        public static int Next()
        {
            return instance.Next();
        }

        public static int Next(int minValue, int maxValue)
        {
            return instance.Next(minValue, maxValue);
        }

        public static double NextDouble()
        {
            return instance.NextDouble();
        }

        public static bool NextBoolean()
        {
            return Convert.ToBoolean(instance.Next(0, 2));
        }

        public static T NextEnumValue<T>()
        {
            var enumValues = (T[]) Enum.GetValues(typeof(T));
            return enumValues[instance.Next(enumValues.Length)];
        }

        public static string NextString()
        {
            var nextString = string.Empty;

            for (var i = 0; i < instance.Next(10, 21); i++)
            {
                nextString += randomChars[instance.Next(0, randomChars.Length)];
            }

            return nextString;
        }
    }
}