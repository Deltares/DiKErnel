// Copyright (C) Stichting Deltares and State of the Netherlands 2025. All rights reserved.
//
// This file is part of DiKErnel.
//
// This program is free software; you can redistribute it and/or modify it under the terms of
// the GNU Lesser General Public License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with this
// program; if not, see <https://www.gnu.org/licenses/>.
//
// All names, logos, and references to "Deltares" are registered trademarks of Stichting
// Deltares and remain full property of Stichting Deltares at all times. All rights reserved.

using System.Collections.Generic;
using DiKErnel.Core.Data;
using DiKErnel.Integration.Data;
using DiKErnel.Integration.Data.AsphaltWaveImpact;
using DiKErnel.Integration.Data.GrassWaveImpact;
using DiKErnel.Integration.Data.GrassWaveOvertopping;
using DiKErnel.Integration.Data.GrassWaveRunup;
using DiKErnel.Integration.Data.NaturalStoneWaveImpact;

namespace DiKErnel.Integration.Factories
{
    internal static class LocationDependentInputFactory
    {
        public static IReadOnlyList<ILocationDependentInput> Create(
            IReadOnlyList<LocationConstructionProperties> locationConstructionPropertiesItems)
        {
            var locationDependentInputItems = new List<ILocationDependentInput>();

            foreach (LocationConstructionProperties locationConstructionProperties in locationConstructionPropertiesItems)
            {
                switch (locationConstructionProperties)
                {
                    case AsphaltWaveImpactLocationConstructionProperties asphaltWaveImpactLocationConstructionProperties:
                        locationDependentInputItems.Add(
                            AsphaltWaveImpactLocationDependentInputFactory.CreateLocationDependentInput(
                                asphaltWaveImpactLocationConstructionProperties));
                        break;
                    case GrassWaveOvertoppingRayleighDiscreteLocationConstructionProperties
                        grassWaveOvertoppingRayleighDiscreteLocationConstructionProperties:
                        locationDependentInputItems.Add(
                            GrassWaveOvertoppingRayleighDiscreteLocationDependentInputFactory.CreateLocationDependentInput(
                                grassWaveOvertoppingRayleighDiscreteLocationConstructionProperties));
                        break;
                    case GrassWaveOvertoppingRayleighLocationConstructionProperties
                        grassWaveOvertoppingRayleighAnalyticalLocationConstructionProperties:
                        locationDependentInputItems.Add(
                            GrassWaveOvertoppingRayleighAnalyticalLocationDependentInputFactory.CreateLocationDependentInput(
                                grassWaveOvertoppingRayleighAnalyticalLocationConstructionProperties));
                        break;
                    case GrassWaveImpactLocationConstructionProperties grassWaveImpactLocationConstructionProperties:
                        locationDependentInputItems.Add(
                            GrassWaveImpactLocationDependentInputFactory.CreateLocationDependentInput(
                                grassWaveImpactLocationConstructionProperties));
                        break;
                    case GrassWaveRunupRayleighDiscreteLocationConstructionProperties
                        grassWaveRunupRayleighDiscreteLocationConstructionProperties:
                        locationDependentInputItems.Add(
                            GrassWaveRunupRayleighDiscreteLocationDependentInputFactory.CreateLocationDependentInput(
                                grassWaveRunupRayleighDiscreteLocationConstructionProperties));
                        break;
                    case GrassWaveRunupBattjesGroenendijkAnalyticalLocationConstructionProperties
                        grassWaveRunupBattjesGroenendijkAnalyticalLocationConstructionProperties:
                        locationDependentInputItems.Add(
                            GrassWaveRunupBattjesGroenendijkAnalyticalLocationDependentInputFactory.CreateLocationDependentInput(
                                grassWaveRunupBattjesGroenendijkAnalyticalLocationConstructionProperties));
                        break;
                    case NaturalStoneWaveImpactLocationConstructionProperties naturalStoneWaveImpactLocationConstructionProperties:
                        locationDependentInputItems.Add(
                            NaturalStoneWaveImpactLocationDependentInputFactory.CreateLocationDependentInput(
                                naturalStoneWaveImpactLocationConstructionProperties));
                        break;
                }
            }

            return locationDependentInputItems;
        }
    }
}