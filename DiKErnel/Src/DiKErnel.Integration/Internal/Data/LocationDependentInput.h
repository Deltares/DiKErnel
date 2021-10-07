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

#include "ILocationDependentInput.h"

namespace DiKErnel::Integration
{
    class LocationDependentInput : public Core::ILocationDependentInput
    {
        public:
            std::unique_ptr<Core::TimeDependentOutput> Calculate(
                double initialDamage,
                const Core::ITimeDependentInput& timeDependentInput,
                const Core::IProfileData& profileData) override;

            std::string GetName() const override;

            double GetX() const override;

            double GetInitialDamage() const override;

            double GetFailureNumber() const override;

            double GetPositionZ() const override;

        protected:
            explicit LocationDependentInput(
                std::string name,
                double x,
                double initialDamage,
                double failureNumber,
                double positionZ);

            virtual std::unique_ptr<Core::TimeDependentOutput> CalculateTimeDependentOutput(
                double initialDamage,
                const Core::ITimeDependentInput& timeDependentInput,
                const Core::IProfileData& profileData) = 0;

        private:
            std::string _name;
            double _x;
            double _initialDamage;
            const double _failureNumber;
            const double _positionZ;
    };
}
