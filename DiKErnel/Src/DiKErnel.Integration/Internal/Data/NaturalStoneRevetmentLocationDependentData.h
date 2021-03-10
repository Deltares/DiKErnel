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

#include <memory>

#include "LocationDependentData.h"
#include "NaturalStoneRevetmentHydraulicLoads.h"

namespace DiKErnel::Integration
{
    class NaturalStoneRevetmentLocationDependentData : public LocationDependentData
    {
        public:
            explicit NaturalStoneRevetmentLocationDependentData(
                double initialDamage,
                double slopeAngle,
                double relativeDensity,
                double thicknessTopLayer,
                std::unique_ptr<NaturalStoneRevetmentHydraulicLoads> hydraulicLoads);

            double Calculate(
                double startDamage,
                const Core::ITimeDependentData& timeDependentData,
                double maximumWaveAngle) override;

            double GetSlopeAngle() const;

            double GetRelativeDensity() const;

            double GetThicknessTopLayer() const;

            NaturalStoneRevetmentHydraulicLoads& GetHydraulicLoads() const;

        private:
            double _slopeAngle;
            double _relativeDensity;
            double _thicknessTopLayer;
            std::unique_ptr<NaturalStoneRevetmentHydraulicLoads> _hydraulicLoads;
    };
}
