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

namespace DiKErnel.KernelWrapper.Json.Input.Data.Generic.Definitions
{
    internal static class JsonInputDefinitions
    {
        public const string HYDRAULIC_LOADS = "hydraulischeBelastingen";
        public const string LOCATIONS = "locaties";

        public const string TIME = "tijdstippen";
        public const string WATER_LEVELS = "waterstanden";
        public const string WAVE_HEIGHTS_HM0 = "golfhoogtenHm0";
        public const string WAVE_PERIODS_TM10 = "golfperiodenTm10";
        public const string WAVE_ANGLES = "golfhoeken";

        public const string DIKE_PROFILE = "dijkprofiel";
        public const string DIKE_PROFILE_POINTS_X = "posities";
        public const string DIKE_PROFILE_POINTS_Z = "hoogten";
        public const string DIKE_PROFILE_ROUGHNESS_COEFFICIENTS = "ruwheidscoefficienten";

        public const string CHARACTERISTIC_POINT_TYPE_OUTER_TOE = "teenBuitenzijde";
        public const string CHARACTERISTIC_POINT_TYPE_OUTER_CREST = "kruinBuitenzijde";
        public const string CHARACTERISTIC_POINT_TYPE_CREST_OUTER_BERM = "kruinBermBuitenzijde";
        public const string CHARACTERISTIC_POINT_TYPE_NOTCH_OUTER_BERM = "insteekBermBuitenzijde";
        public const string CHARACTERISTIC_POINT_TYPE_INNER_CREST = "kruinBinnenzijde";
        public const string CHARACTERISTIC_POINT_TYPE_INNER_TOE = "teenBinnenzijde";

        public const string X = "positie";
        public const string INITIAL_DAMAGE = "beginschade";
        public const string FAILURE_NUMBER = "faalgetal";

        public const string CALCULATION_METHODS = "rekenmethoden";
        public const string CALCULATION_METHOD_TYPE = "rekenmethode";

        public const string CALCULATION_METHOD_TYPE_ASPHALT_WAVE_IMPACT = "asfaltGolfklap";
        public const string CALCULATION_METHOD_TYPE_GRASS_OVERTOPPING = "grasGolfoverslag";
        public const string CALCULATION_METHOD_TYPE_GRASS_WAVE_IMPACT = "grasGolfklap";
        public const string CALCULATION_METHOD_TYPE_GRASS_WAVE_RUNUP = "grasGolfoploop";
        public const string CALCULATION_METHOD_TYPE_NATURAL_STONE = "natuursteen";

        public const string TOP_LAYERS = "toplagen";
        public const string TYPE_TOP_LAYER = "typeToplaag";

        public const string A_COEFFICIENT = "a";
        public const string B_COEFFICIENT = "b";
        public const string C_COEFFICIENT = "c";

        public const string LOADING_AREA = "belastingzone";
        public const string UPPER_LIMIT = "bovengrens";
        public const string LOWER_LIMIT = "ondergrens";

        public const string WAVE_ANGLE_IMPACT = "impactGolfhoek";
        public const string BETA_MAX = "betaMax";

        public const string FACTOR_CTM = "factorCtm";
    }
}