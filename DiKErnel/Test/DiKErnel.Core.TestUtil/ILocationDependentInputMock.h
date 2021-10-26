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
            MOCK_METHOD(bool, Validate, (const IProfileData& profileData), (const, override));

            std::unique_ptr<TimeDependentOutput> Calculate(
                double initialDamage,
                const ITimeDependentInput& timeDependentInput,
                const IProfileData& profileData) override;

            MOCK_METHOD(double, GetX, (), (const, override));
            MOCK_METHOD(double, GetInitialDamage, (), (const, override));
            MOCK_METHOD(double, GetFailureNumber, (), (const, override));
            MOCK_METHOD(double, GetZ, (), (const, override));

            void SetIncrementDamage(
                double incrementDamage);

            void SetDamage(
                double damage);

            void SetTimeOfFailure(
                int* timeOfFailure);

            void SetThrowExceptionOnCalculate(
                bool throwExceptionOnCalculate);

        private:
            double _incrementDamage = 0;
            double _damage = 0;
            int* _timeOfFailure = nullptr;
            bool _throwExceptionOnCalculate = false;
    };
}
