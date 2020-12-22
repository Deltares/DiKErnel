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

#include "NaturalStoneRevetmentDefaults.h"

namespace DiKErnel::DomainLibrary
{
    const double NaturalStoneRevetmentDefaults::RELATIVE_DENSITY = 1.65;

    const double NaturalStoneRevetmentDefaults::SIMILARITY_PARAMETER_THRESHOLD = 2.9;

    const double NaturalStoneRevetmentDefaults::COEFFICIENT_PLUNGING_AP = 4;

    const double NaturalStoneRevetmentDefaults::COEFFICIENT_PLUNGING_BP = 0.8;

    const double NaturalStoneRevetmentDefaults::COEFFICIENT_PLUNGING_CP = 0;

    const double NaturalStoneRevetmentDefaults::COEFFICIENT_PLUNGING_NP = 0;

    const double NaturalStoneRevetmentDefaults::COEFFICIENT_SURGING_AS = 0;

    const double NaturalStoneRevetmentDefaults::COEFFICIENT_SURGING_BS = 0;

    const double NaturalStoneRevetmentDefaults::COEFFICIENT_SURGING_CS = -0.9;

    const double NaturalStoneRevetmentDefaults::COEFFICIENT_SURGING_NS = 0.6;
}
