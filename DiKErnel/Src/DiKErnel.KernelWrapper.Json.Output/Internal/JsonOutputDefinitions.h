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

namespace DiKErnel::KernelWrapper::Json::Output
{
    class JsonOutputDefinitions
    {
        public:
            inline static const std::string META_DATA = "metaInformatie";

            inline static const std::string OUTPUT_DATA = "uitvoerdata";

            inline static const std::string LOCATIONS = "locaties";

            inline static const std::string FAILURE = "falen";
            inline static const std::string FAILED = "faalgebeurtenis";
            inline static const std::string TIME_OF_FAILURE = "faaltijd";

            inline static const std::string DAMAGE = "schade";
            inline static const std::string DAMAGE_OVER_TIME = "schadegetalPerTijdstap";

            inline static const std::string PHYSICS = "fysica";
            inline static const std::string Z = "hoogte";

            inline static const std::string HYDRAULIC_LOAD = "belastingBekleding";
            inline static const std::string OUTER_SLOPE = "hellingBuitentalud";
            inline static const std::string INCREMENT_DAMAGE = "toenameSchade";

            inline static const std::string UPPER_LIMIT_LOADING = "bovengrensBelasting";
            inline static const std::string LOWER_LIMIT_LOADING = "ondergrensBelasting";
    };
}
