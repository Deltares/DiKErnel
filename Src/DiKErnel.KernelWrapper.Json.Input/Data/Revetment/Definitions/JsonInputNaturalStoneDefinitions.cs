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

namespace DiKErnel.KernelWrapper.Json.Input.Data.Revetment.Definitions
{
    public class JsonInputNaturalStoneDefinitions
    {
        public const string TOP_LAYER_TYPE_NORDIC_STONE = "noorseSteen";

        public const string RELATIVE_DENSITY = "relatieveDichtheid";
        public const string THICKNESS_TOP_LAYER = "dikteToplaag";

        public const string STABILITY = "stabiliteit";
        public const string STABILITY_PLUNGING = "plunging";
        public const string STABILITY_SURGING = "surging";

        public const string N_COEFFICIENT = "n";
        public const string XIB_COEFFICIENT = "xib";

        public const string SLOPE = "hellingvlak";
        public const string SLOPE_UPPER_LEVEL = "bovenzijde";
        public const string SLOPE_LOWER_LEVEL = "onderzijde";

        public const string DISTANCE_MAXIMUM_WAVE_ELEVATION = "afstandMaximaleStijghoogte";

        public const string NORMATIVE_WIDTH_OF_WAVE_IMPACT = "maatgevendeBreedteGolfklap";
    }
}