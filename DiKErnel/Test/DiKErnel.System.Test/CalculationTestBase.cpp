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

#include "CalculationTestBase.h"

#include "AssertHelper.h"

namespace DiKErnel::System::Test
{
    using namespace Core;
    using namespace std;
    using namespace TestUtil;

    void CalculationTestBase::AssertOutput(
        const Calculator& calculator,
        const vector<reference_wrapper<ILocationDependentInput>>& locationDependentInputItems,
        const vector<reference_wrapper<ITimeDependentInput>>& timeDependentInputItems,
        const double expectedDamage,
        const int* expectedTimeOfFailure)
    {
        const auto calculatorResult = calculator.GetResult();
        ASSERT_TRUE(calculatorResult->GetSuccessful());
        ASSERT_EQ(0, calculatorResult->GetEvents().size());

        const auto* calculationOutput = calculatorResult->GetData();
        const auto& locationDependentOutput = calculationOutput->GetLocationDependentOutputItems().at(0).get();
        const auto& locationDependentInput = locationDependentInputItems.at(0).get();

        const auto actualDamage = locationDependentOutput.GetDamages(locationDependentInput.GetInitialDamage()).back();
        AssertHelper::AssertAreEqualWithAcceptablePrecision(expectedDamage, actualDamage);

        const auto actualTimeOfFailure = locationDependentOutput.GetTimeOfFailure(
            locationDependentInput.GetInitialDamage(), locationDependentInput.GetFailureNumber(),
            timeDependentInputItems);

        if (expectedTimeOfFailure == nullptr)
        {
            ASSERT_EQ(numeric_limits<double>::infinity(), actualTimeOfFailure);
        }
        else
        {
            ASSERT_EQ(*expectedTimeOfFailure, actualTimeOfFailure);
        }
    }
}
