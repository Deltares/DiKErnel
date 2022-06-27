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

#include "Validator.h"

#include "EventRegistry.h"

namespace DiKErnel::Core
{
    using namespace std;
    using namespace Util;

    unique_ptr<DataResult<ValidationResultType>> Validator::Validate(
        const ICalculationInput& calculationInput)
    {
        auto validationResult = ValidationResultType::Successful;

        try
        {
            if (!calculationInput.Validate())
            {
                validationResult = ValidationResultType::Failed;
            }

            for (const auto& timeDependentInputItem : calculationInput.GetTimeDependentInputItems())
            {
                if (!timeDependentInputItem.get().Validate())
                {
                    validationResult = ValidationResultType::Failed;
                }
            }

            const auto& profileData = calculationInput.GetProfileData();

            if (!profileData.Validate())
            {
                validationResult = ValidationResultType::Failed;
            }

            for (const auto& locationDependentInputItem : calculationInput.GetLocationDependentInputItems())
            {
                if (!locationDependentInputItem.get().Validate(profileData))
                {
                    validationResult = ValidationResultType::Failed;
                }
            }

            return make_unique<DataResult<ValidationResultType>>(make_unique<ValidationResultType>(validationResult), EventRegistry::Flush());
        }
        catch (const exception& e)
        {
            EventRegistry::Register(make_unique<Event>("An unhandled error occurred while validating the calculation input. See stack trace for "
                                                       "more information:\n" + static_cast<string>(e.what()), EventType::Error));

            return make_unique<DataResult<ValidationResultType>>(EventRegistry::Flush());
        }
    }
}
