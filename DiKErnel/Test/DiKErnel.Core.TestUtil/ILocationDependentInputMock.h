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

#include <gmock/gmock.h>

#include "ILocationDependentInput.h"

namespace DiKErnel::Core::TestUtil
{
    class ILocationDependentInputMock : public ILocationDependentInput
    {
        public:
            std::unique_ptr<TimeDependentOutput> Calculate(
                double initialDamage,
                const ITimeDependentInput& timeDependentInput) override
            {
                return std::make_unique<TimeDependentOutput>(_damage, nullptr);
            };

            MOCK_METHOD(std::string, GetName, (), (const, override));
            MOCK_METHOD(double, GetInitialDamage, (), (const, override));
            MOCK_METHOD(double, GetFailureNumber, (), (const, override));
            MOCK_METHOD(double, GetTanA, (), (const, override));
            MOCK_METHOD(double, GetPositionZ, (), (const, override));

            void SetDamage(
                const double damage)
            {
                _damage = damage;
            }

        private:
            double _damage;
    };
}
