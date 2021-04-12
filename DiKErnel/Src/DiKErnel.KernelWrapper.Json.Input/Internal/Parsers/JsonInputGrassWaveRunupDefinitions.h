// Copyright (C) Stichting Deltares 2020. All rights reserved.
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
            inline static const std::string CRITICAL_CUMULATIVE_OVERLOAD = "KritiekeCumulatieveOverbelasting";
            inline static const std::string CRITICAL_FRONT_VELOCITY = "KritiekeFrontsnelheidGrasGolfoploop";
            inline static const std::string INCREASED_LOAD_TRANSITION_ALPHA_M = "VerhogingBelastingOvergangAlfaM";
            inline static const std::string REDUCED_STRENGTH_TRANSITION_ALPHA_S = "VerlagingSterkteOvergangAlfaS";

            inline static const std::string AVERAGE_NUMBER_WAVE_TIMESTEP = "GemiddeldAantalGolvenPerTijdstap";
            inline static const std::string AVERAGE_NUMBER_WAVE_TIMESTEP_CTM = "GemiddeldAantalGolvenPerTijdstapCtm";

            inline static const std::string REPRESENTATIVE_WAVE_RUNUP_2P = "RepresentatieveGolfoploop2p";
            inline static const std::string REPRESENTATIVE_WAVE_RUNUP_2P_ARU = "RepresentatieveGolfoploop2pAru";
            inline static const std::string REPRESENTATIVE_WAVE_RUNUP_2P_BRU = "RepresentatieveGolfoploop2pBru";
            inline static const std::string REPRESENTATIVE_WAVE_RUNUP_2P_CRU = "RepresentatieveGolfoploop2pCru";

            inline static const std::string WAVE_ANGLE_IMPACT = "ImpactGolfhoekGolfoploop";
            inline static const std::string WAVE_ANGLE_IMPACT_ABETA = "ImpactGolfhoekGolfoploopAbeta";
            inline static const std::string WAVE_ANGLE_IMPACT_BETAMAX = "ImpactGolfhoekGolfoploopBetamax";

            inline static const std::string CALCULATION_PROTOCOL = "Rekenprotocol";
            inline static const std::string CALCULATION_PROTOCOL_TYPE = "Rekenprotocolsoort";

            inline static const std::string CUMULATIVE_OVERLOAD_TIMESTEP_RDNF = "AantalGolvenVastRD";

            inline static const std::string FRONTVELOCITY = "FrontsnelheidGolfOploopRD";
            inline static const std::string FRONTVELOCITYCU = "FrontsnelheidGolfOploopRDCu";

            inline static const std::string REPRESENTATIVE_WAVE_RUNUP_2P_GAMMA_B = "BermfactorGammab";
            inline static const std::string REPRESENTATIVE_WAVE_RUNUP_2P_GAMMA_F = "RuwheidsfactorGammaf";
    };
}
