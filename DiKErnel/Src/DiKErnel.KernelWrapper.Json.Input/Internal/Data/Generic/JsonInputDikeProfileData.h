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

#include <memory>
#include <vector>

#include "JsonInputDikeProfilePoint.h"

namespace DiKErnel::KernelWrapper::Json::Input
{
    class JsonInputDikeProfileData
    {
        public:
            explicit JsonInputDikeProfileData(
                std::vector<double> xLocations,
                std::vector<double> zLocations,
                std::vector<std::pair<JsonInputCharacteristicPointType, double>> characteristicPoints);

            explicit JsonInputDikeProfileData(
                std::vector<std::unique_ptr<JsonInputDikeProfilePoint>> dikeProfilePoints);

            [[nodiscard]]
            const std::vector<double>& GetXLocations() const;

            [[nodiscard]]
            const std::vector<double>& GetZLocations() const;

            [[nodiscard]]
            const std::vector<std::pair<JsonInputCharacteristicPointType, double>>& GetCharacteristicPoints() const;

            [[nodiscard]]
            const std::vector<std::reference_wrapper<JsonInputDikeProfilePoint>>& GetDikeProfilePoints() const;

        private:
            std::vector<double> _xLocations;
            std::vector<double> _zLocations;
            std::vector<std::pair<JsonInputCharacteristicPointType, double>> _characteristicPoints;

            std::vector<std::unique_ptr<JsonInputDikeProfilePoint>> _dikeProfilePoints;
            std::vector<std::reference_wrapper<JsonInputDikeProfilePoint>> _dikeProfilePointReferences;
    };
}
