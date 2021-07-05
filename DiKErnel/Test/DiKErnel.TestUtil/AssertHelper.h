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

#include <gtest/gtest.h>

namespace DiKErnel::TestUtil
{
    class AssertHelper
    {
        public:
            static void AssertAreAlmostEqual(
                const std::vector<double>& expectedCollection,
                const std::vector<double>& actualCollection);

            static void AssertAreAlmostEqual(
                double expected,
                double actual);

            typedef void (*Action)();

            template <typename TException>
            static void AssertThrowsWithMessage(
                const Action action,
                const std::string& expectedMessage)
            {
                try
                {
                    action();
                    FAIL() << "Expected " << typeid(TException).name();
                }
                catch (TException& exception)
                {
                    ASSERT_EQ(expectedMessage, exception.what());
                }
                catch (...)
                {
                    FAIL() << "Expected " << typeid(TException).name();
                }
            }

            template <typename TException, typename TInnerException>
            static void AssertThrowsWithMessageAndInnerException(
                const Action action,
                const std::string& expectedMessage,
                const std::string& expectedInnerExceptionMessage)
            {
                try
                {
                    action();
                    FAIL() << "Expected " << typeid(TException).name();
                }
                catch (TException& exception)
                {
                    ASSERT_EQ(expectedMessage, exception.what());
                    AssertInnerException<TException, TInnerException>(exception, expectedInnerExceptionMessage);
                }
                catch (...)
                {
                    FAIL() << "Expected " << typeid(TException).name();
                }
            }

            template <typename TExpected, typename TActual>
            static void AssertIsInstanceOf(
                const TActual* actual)
            {
                ASSERT_TRUE(dynamic_cast<const TExpected*>(actual) != nullptr);
            }

        private:
            template <typename TException, typename TInnerException>
            static void AssertInnerException(
                TException& actualException,
                const std::string& expectedInnerExceptionMessage)
            {
                try
                {
                    std::rethrow_if_nested(actualException);
                    FAIL() << "Expected " << typeid(TInnerException).name();
                }
                catch (TInnerException& exception)
                {
                    ASSERT_EQ(expectedInnerExceptionMessage, exception.what());
                }
                catch (...)
                {
                    FAIL() << "Expected " << typeid(TInnerException).name();
                }
            }
    };
}
