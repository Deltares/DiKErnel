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

namespace DiKErnel.KernelWrapper.Json.Output.Data.Definitions
{
    internal class JsonOutputDefinitions
    {
        public const string META_DATA = "metaInformatie";

        public const string OUTPUT_DATA = "uitvoerdata";

        public const string LOCATIONS = "locaties";

        public const string FAILURE = "falen";
        public const string FAILED = "faalgebeurtenis";
        public const string TIME_OF_FAILURE = "faaltijd";

        public const string DAMAGE = "schade";
        public const string DAMAGE_OVER_TIME = "schadegetalPerTijdstap";

        public const string PHYSICS = "fysica";

        public const string Z = "hoogteLocatie";

        public const string HYDRAULIC_LOAD = "belastingBekleding";
        public const string OUTER_SLOPE = "hellingBuitentalud";
        public const string INCREMENT_DAMAGE = "toenameSchade";

        public const string UPPER_LIMIT_LOADING = "bovengrensBelasting";
        public const string LOWER_LIMIT_LOADING = "ondergrensBelasting";

        public const string WAVE_ANGLE_IMPACT = "impactGolfhoek";
    }
}