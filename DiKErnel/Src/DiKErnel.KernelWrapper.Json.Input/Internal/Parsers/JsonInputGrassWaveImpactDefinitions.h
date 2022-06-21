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
    class JsonInputGrassWaveImpactDefinitions
    {
        public:
            inline static const std::string TIME_LINE_AGWI = "standtijdlijnGrasGolfklapAgwi";
            inline static const std::string TIME_LINE_BGWI = "standtijdlijnGrasGolfklapBgwi";
            inline static const std::string TIME_LINE_CGWI = "standtijdlijnGrasGolfklapCgwi";

            inline static const std::string MINIMUM_WAVE_HEIGHT = "minimumGolfhoogteGrasGolfklap";
            inline static const std::string MINIMUM_WAVE_HEIGHT_TEMAX = "minimumGolfhoogteGrasGolfklapTemax";

            inline static const std::string MAXIMUM_WAVE_HEIGHT = "maximumGolfhoogteGrasGolfklap";
            inline static const std::string MAXIMUM_WAVE_HEIGHT_TEMIN = "maximumGolfhoogteGrasGolfklapTemin";

            inline static const std::string WAVE_ANGLE_IMPACT = "impactGolfhoekBekledingGrasGolfklap";
            inline static const std::string WAVE_ANGLE_IMPACT_NWA = "impactGolfhoekBekledingGrasGolfklapNwa";
            inline static const std::string WAVE_ANGLE_IMPACT_QWA = "impactGolfhoekBekledingGrasGolfklapQwa";
            inline static const std::string WAVE_ANGLE_IMPACT_RWA = "impactGolfhoekBekledingGrasGolfklapRwa";

            inline static const std::string UPPER_LIMIT_LOADING = "bovengrensBelastingGrasGolfklap";
            inline static const std::string UPPER_LIMIT_LOADING_AUL = "bovengrensBelastingGrasGolfklapAul";

            inline static const std::string LOWER_LIMIT_LOADING = "ondergrensBelastingGrasGolfklap";
            inline static const std::string LOWER_LIMIT_LOADING_ALL = "ondergrensBelastingGrasGolfklapAll";
    };
}
