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

#include "LocationDependentInputFactory.h"

#include "AsphaltRevetmentWaveImpactLocationConstructionProperties.h"
#include "AsphaltRevetmentWaveImpactLocationDependentInputFactory.h"
#include "GrassRevetmentOvertoppingLocationConstructionProperties.h"
#include "GrassRevetmentOvertoppingLocationDependentInputFactory.h"
#include "GrassRevetmentWaveImpactLocationConstructionProperties.h"
#include "GrassRevetmentWaveImpactLocationDependentInputFactory.h"
#include "GrassRevetmentWaveRunupRayleighLocationConstructionProperties.h"
#include "GrassRevetmentWaveRunupRayleighLocationDependentInputFactory.h"
#include "InputFactoryException.h"
#include "NaturalStoneRevetmentLocationConstructionProperties.h"
#include "NaturalStoneRevetmentLocationDependentInputFactory.h"
#include "RevetmentLocationConstructionPropertiesBase.h"

namespace DiKErnel::Integration
{
    using namespace Core;
    using namespace std;

    vector<unique_ptr<ILocationDependentInput>> LocationDependentInputFactory::Create(
        const vector<reference_wrapper<RevetmentLocationConstructionPropertiesBase>>& locationConstructionPropertiesItems)
    {
        auto locationDependentInputItems = vector<unique_ptr<ILocationDependentInput>>();

        for (const auto& locationConstructionPropertiesReference : locationConstructionPropertiesItems)
        {
            const auto& locationConstructionProperties = locationConstructionPropertiesReference.get();

            if (const auto* asphaltWaveImpactLocationConstructionProperties = dynamic_cast<const
                    AsphaltRevetmentWaveImpactLocationConstructionProperties*>(&locationConstructionProperties);
                asphaltWaveImpactLocationConstructionProperties != nullptr)
            {
                locationDependentInputItems.push_back(
                    AsphaltRevetmentWaveImpactLocationDependentInputFactory::CreateLocationDependentInput(
                        *asphaltWaveImpactLocationConstructionProperties));
                continue;
            }

            if (const auto* grassOvertoppingLocationConstructionProperties = dynamic_cast<const
                    GrassRevetmentOvertoppingLocationConstructionProperties*>(&locationConstructionProperties);
                grassOvertoppingLocationConstructionProperties != nullptr)
            {
                locationDependentInputItems.push_back(
                    GrassRevetmentOvertoppingLocationDependentInputFactory::CreateLocationDependentInput(
                        *grassOvertoppingLocationConstructionProperties));
                continue;
            }

            if (const auto* grassWaveImpactLocationConstructionProperties = dynamic_cast<const
                    GrassRevetmentWaveImpactLocationConstructionProperties*>(&locationConstructionProperties);
                grassWaveImpactLocationConstructionProperties != nullptr)
            {
                locationDependentInputItems.push_back(
                    GrassRevetmentWaveImpactLocationDependentInputFactory::CreateLocationDependentInput(
                        *grassWaveImpactLocationConstructionProperties));
                continue;
            }

            if (const auto* grassWaveRunupRayleighLocationConstructionProperties = dynamic_cast<const
                    GrassRevetmentWaveRunupRayleighLocationConstructionProperties*>(&locationConstructionProperties);
                grassWaveRunupRayleighLocationConstructionProperties != nullptr)
            {
                locationDependentInputItems.push_back(
                    GrassRevetmentWaveRunupRayleighLocationDependentInputFactory::CreateLocationDependentInput(
                        *grassWaveRunupRayleighLocationConstructionProperties));
                continue;
            }

            if (const auto* naturalStoneLocationConstructionProperties = dynamic_cast<const NaturalStoneRevetmentLocationConstructionProperties*>(
                &locationConstructionProperties); naturalStoneLocationConstructionProperties != nullptr)
            {
                locationDependentInputItems.push_back(
                    NaturalStoneRevetmentLocationDependentInputFactory::CreateLocationDependentInput(*naturalStoneLocationConstructionProperties));
                continue;
            }

            throw InputFactoryException("Couldn't create location dependent input for the given construction properties.");
        }

        return locationDependentInputItems;
    }
}
