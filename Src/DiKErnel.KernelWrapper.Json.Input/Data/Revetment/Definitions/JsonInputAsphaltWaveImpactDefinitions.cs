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
    public class JsonInputAsphaltWaveImpactDefinitions
    {
        public const string TOP_LAYER_TYPE_HYDRAULIC_ASPHALT_CONCRETE = "waterbouwAsfaltBeton";

        public const string FAILURE_TENSION = "breuksterkteAsfalt";
        public const string DENSITY_OF_WATER = "soortelijkeDichtheidWater";
        public const string SOIL_ELASTICITY = "veerconstanteOndergrond";

        public const string UPPER_LAYER = "toplaag";
        public const string SUB_LAYER = "onderlaag";

        public const string THICKNESS = "dikte";
        public const string ELASTIC_MODULUS = "stijfheidsmodulus";

        public const string FATIGUE = "vermoeiingAsfalt";
        public const string ALPHA = "alfa";
        public const string BETA = "beta";

        public const string IMPACT_NUMBER_C = "stootgetalC";
        public const string STIFFNESS_RELATION_NU = "stijfheidsverhoudingNu";

        public const string WIDTH_FACTORS = "breedteFactoren";
        public const string DEPTH_FACTORS = "diepteFactoren";
        public const string IMPACT_FACTORS = "stootFactoren";
    }
}