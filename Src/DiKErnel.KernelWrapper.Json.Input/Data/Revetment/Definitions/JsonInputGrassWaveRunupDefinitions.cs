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
    public class JsonInputGrassWaveRunupDefinitions
    {
        public const string OUTER_SLOPE = "tanA";

        public const string REPRESENTATIVE_WAVE_RUNUP_2P_GAMMA_B = "bermFactorGammaB";
        public const string REPRESENTATIVE_WAVE_RUNUP_2P_GAMMA_F = "ruwheidsFactorGammaF";

        public const string REPRESENTATIVE_WAVE_RUNUP_2P = "representatieveGolfoploop2p";

        public const string A_BETA = "aBeta";

        public const string CALCULATION_PROTOCOL = "rekenprotocol";
        public const string CALCULATION_PROTOCOL_TYPE = "typeRekenprotocol";
        public const string CALCULATION_PROTOCOL_TYPE_RAYLEIGH_DISCRETE = "rayleighDiscreet";
        public const string FRONT_VELOCITY = "frontsnelheid";
    }
}