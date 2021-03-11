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
    /*!
     * \brief Helper class for assertions.
    */
    class AssertHelper
    {
        public:
            /*!
             * \brief Asserts whether the given collections of doubles are equal.
             * \param expectedCollection
             *        The expected collection.
             * \param actualCollection
             *        The actual collection.
             */
            static void AssertAreEqual(
                const std::vector<double>& expectedCollection,
                const std::vector<double>& actualCollection);

            /*!
             * \brief Function pointer to use as action.
             */
            typedef void (*Action)();

            /*!
             * \brief Asserts whether an exception is thrown with an expected message.
             * \tparam TException
             *         The type of the exception.
             * \param action
             *        The action to perform.
             * \param expectedMessage
             *        The expected message in the exception.
             */
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
                    ASSERT_TRUE(expectedMessage == exception.what());
                }
                catch (...)
                {
                    FAIL() << "Expected " << typeid(TException).name();
                }
            }

            /*!
             * \brief Asserts whether an exception is thrown with an expected message and an
             *        expected inner exception.
             * \tparam TException
             *         The type of the exception.
             * \tparam TInnerException
             *         The type of the inner exception.
             * \param action
             *        The action to perform.
             * \param expectedMessage
             *        The expected message in the exception.
             * \param expectedInnerExceptionMessage
             *        The expected message in the inner exception.
             */
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
                    ASSERT_TRUE(expectedMessage == exception.what());
                    AssertInnerException<TException, TInnerException>(exception, expectedInnerExceptionMessage);
                }
                catch (...)
                {
                    FAIL() << "Expected " << typeid(TException).name();
                }
            }

            /*!
             * \brief Asserts whether TActual is of type TExpected.
             * \tparam TExpected
             *         The expected type.
             * \tparam TActual
             *         The actual type.
             * \param actual
             *        The object to assert.
             */
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
                    ASSERT_TRUE(expectedInnerExceptionMessage == exception.what());
                }
                catch (...)
                {
                    FAIL() << "Expected " << typeid(TInnerException).name();
                }
            }
    };
}
