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
    class JsonInputGrassWaveImpactDefinitions
    {
        public:
            inline static const std::string TIME_LINE_AGWI = "StandtijdlijnGrasGolfklapAgwi";
            inline static const std::string TIME_LINE_BGWI = "StandtijdlijnGrasGolfklapBgwi";
            inline static const std::string TIME_LINE_CGWI = "StandtijdlijnGrasGolfklapCgwi";

            inline static const std::string MINIMUM_WAVE_HEIGHT = "MinimumGolfhoogteGrasGolfklap";
            inline static const std::string MINIMUM_WAVE_HEIGHT_TEMAX = "MinimumGolfhoogteGrasGolfklapTemax";

            inline static const std::string MAXIMUM_WAVE_HEIGHT = "MaximumGolfhoogteGrasGolfklap";
            inline static const std::string MAXIMUM_WAVE_HEIGHT_TEMIN = "MaximumGolfhoogteGrasGolfklapTemin";

            inline static const std::string WAVE_ANGLE_IMPACT = "ImpactGolfhoekBekledingGrasGolfklap";
            inline static const std::string WAVE_ANGLE_IMPACT_NWA = "ImpactGolfhoekBekledingGrasGolfklapNwa";
            inline static const std::string WAVE_ANGLE_IMPACT_QWA = "ImpactGolfhoekBekledingGrasGolfklapQwa";
            inline static const std::string WAVE_ANGLE_IMPACT_RWA = "ImpactGolfhoekBekledingGrasGolfklapRwa";

            inline static const std::string UPPER_LIMIT_LOADING = "BovengrensBelastingGrasGolfklap";
            inline static const std::string UPPER_LIMIT_LOADING_AUL = "BovengrensBelastingGrasGolfklapAul";

            inline static const std::string LOWER_LIMIT_LOADING = "OndergrensBelastingGrasGolfklap";
            inline static const std::string LOWER_LIMIT_LOADING_ALL = "OndergrensBelastingGrasGolfklapAll";

            inline static const std::string TOP_LAYER_TYPE_CLOSED_SOD = "GrasGeslotenZode";
            inline static const std::string TOP_LAYER_TYPE_OPEN_SOD = "GrasOpenZode";
    };
}
