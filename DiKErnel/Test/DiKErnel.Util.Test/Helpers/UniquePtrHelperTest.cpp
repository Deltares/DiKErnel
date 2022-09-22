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

#include <gtest/gtest.h>

#include "UniquePtrHelper.h"

#include "Helpers/Base.h"
#include "Helpers/Derived1.h"
#include "Helpers/Derived2.h"

namespace DiKErnel::Util::Test
{
    using namespace std;
    using namespace TestUtil;

    TEST(UniquePtrHelperTest, DynamicCast_DerivedTypeNotSameAsObject_ReturnsNullPtrAndBaseIntact)
    {
        // Setup
        unique_ptr<Base> base = make_unique<Derived1>();

        // Call
        const auto derived = UniquePtrHelper::DynamicCast<Derived2, Base>(base);

        // Assert
        ASSERT_EQ(nullptr, derived);
        ASSERT_NE(nullptr, base);
    }

    TEST(UniquePtrHelperTest, DynamicCast_DerivedTypeSameAsObject_ReturnsDerviedObjectAndBaseNullPtr)
    {
        // Setup
        unique_ptr<Base> base = make_unique<Derived1>();

        // Call
        const auto derived = UniquePtrHelper::DynamicCast<Derived1, Base>(base);

        // Assert
        ASSERT_NE(nullptr, derived);
        ASSERT_EQ(nullptr, base);
    }

    TEST(UniquePtrHelperTest, CreatePointerOfValue_ValueNotNullPtr_ReturnsUniquePtrWithValue)
    {
        // Setup
        constexpr auto value = 4;

        // Call
        const auto uniquePtr = UniquePtrHelper::CreatePtrOfValue(&value);

        // Assert
        ASSERT_EQ(value, *uniquePtr);
    }

    TEST(UniquePtrHelperTest, CreatePointerOfValue_ValueNullPtr_ReturnsNullPtr)
    {
        // Call
        const auto uniquePtr = UniquePtrHelper::CreatePtrOfValue<double*>(nullptr);

        // Assert
        ASSERT_EQ(nullptr, uniquePtr);
    }
}
