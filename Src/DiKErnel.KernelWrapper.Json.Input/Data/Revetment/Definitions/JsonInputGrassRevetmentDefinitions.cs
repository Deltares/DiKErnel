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
    internal static class JsonInputGrassRevetmentDefinitions
    {
        public const string TOP_LAYER_TYPE_CLOSED_SOD = "grasGeslotenZode";
        public const string TOP_LAYER_TYPE_OPEN_SOD = "grasOpenZode";

        public const string INCREASED_LOAD_TRANSITION_ALPHA_M = "verhogingBelastingOvergangAlfaM";
        public const string REDUCED_STRENGTH_TRANSITION_ALPHA_S = "verlagingSterkteOvergangAlfaS";

        public const string CRITICAL_CUMULATIVE_OVERLOAD = "kritiekeCumulatieveOverbelasting";
        public const string CRITICAL_FRONT_VELOCITY = "kritiekeFrontsnelheid";

        public const string FIXED_NUMBER_OF_WAVES = "aantalGolvenVast";
    }
}