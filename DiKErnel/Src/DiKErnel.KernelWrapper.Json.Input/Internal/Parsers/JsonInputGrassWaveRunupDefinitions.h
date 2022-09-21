// Copyright (C) Stichting Deltares 2022. All rights reserved.
//
// This file is part of DiKErnel.
//
// DiKErnel is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, version 3.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/lgpl-3.0.html>.
//
// All names, logos, and references to "Deltares" are registered trademarks of
// Stichting Deltares and remain full property of Stichting Deltares at all times.
// All rights reserved.

#pragma once

#include <string>

namespace DiKErnel::KernelWrapper::Json::Input
{
    class JsonInputGrassWaveRunupDefinitions
    {
        public:
            inline static const std::string OUTER_SLOPE = "tanA";

            inline static const std::string INCREASED_LOAD_TRANSITION_ALPHA_M = "verhogingBelastingOvergangAlfaM";
            inline static const std::string REDUCED_STRENGTH_TRANSITION_ALPHA_S = "verlagingSterkteOvergangAlfaS";

            inline static const std::string REPRESENTATIVE_WAVE_RUNUP_2P_GAMMA_B = "bermFactorGammaB";
            inline static const std::string REPRESENTATIVE_WAVE_RUNUP_2P_GAMMA_F = "ruwheidsFactorGammaF";

            inline static const std::string REPRESENTATIVE_WAVE_RUNUP_2P = "representatieveGolfoploop2p";

            inline static const std::string A_BETA = "aBeta";

            inline static const std::string CALCULATION_PROTOCOL_TYPE_RAYLEIGH_DISCRETE = "rayleighDiscreet";
    };
}
