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
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using DiKErnel.Integration.Data.Grass;
using DiKErnel.SpecFlow.Test.Steps.Definitions;
using TechTalk.SpecFlow;

namespace DiKErnel.SpecFlow.Test.Steps
{
    internal static class ScenarioContextExtensions
    {
        private static readonly CultureInfo Culture = CultureInfo.InvariantCulture;

        public static double GetDouble(this ScenarioContext context, string id)
        {
            return double.Parse(context.GetString(id), Culture);
        }

        public static double? GetNullableDouble(this ScenarioContext context, string id)
        {
            return context.ContainsKey(id)
                       ? (double?) context.GetDouble(id)
                       : null;
        }

        public static double[] GetDoubleCollection(this ScenarioContext context, string id)
        {
            var values = (IReadOnlyList<string>) context[id];

            return values.Where(s => !Equals(s, GeneralDefinitions.NotApplicable))
                         .Select(s => double.Parse(s, Culture))
                         .ToArray();
        }

        public static int? GetNullableInt(this ScenarioContext context, string id)
        {
            return context.ContainsKey(id)
                       ? (int?) int.Parse(context.GetString(id), Culture)
                       : null;
        }

        public static GrassTopLayerType GetGrassTopLayerType(this ScenarioContext context)
        {
            switch (context.GetString(GeneralDefinitions.TopLayerType))
            {
                case GrassDefinitions.OpenSod:
                    return GrassTopLayerType.OpenSod;
                case GrassDefinitions.ClosedSod:
                    return GrassTopLayerType.ClosedSod;
                default:
                    throw new NotSupportedException();
            }
        }

        private static string GetString(this ScenarioContext context, string id)
        {
            return (string) context[id];
        }
    }
}