// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
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
using DiKErnel.Integration.Data.AsphaltRevetmentWaveImpact;
using DiKErnel.Integration.Data.GrassOvertopping;
using DiKErnel.Integration.Data.GrassWaveImpact;
using DiKErnel.Integration.Data.GrassWaveRunup;
using DiKErnel.Integration.Data.NaturalStoneWaveImpact;

namespace DiKErnel.Integration.Factories
{
    internal static class LocationDependentInputFactory
    {
        public static IReadOnlyList<ILocationDependentInput> Create(
            IReadOnlyList<RevetmentLocationConstructionProperties> locationConstructionPropertiesItems)
        {
            var locationDependentInputItems = new List<ILocationDependentInput>();

            foreach (RevetmentLocationConstructionProperties locationConstructionProperties in locationConstructionPropertiesItems)
            {
                switch (locationConstructionProperties)
                {
                    case AsphaltRevetmentWaveImpactLocationConstructionProperties asphaltWaveImpactLocationConstructionProperties:
                        locationDependentInputItems.Add(
                            AsphaltRevetmentWaveImpactLocationDependentInputFactory.CreateLocationDependentInput(
                                asphaltWaveImpactLocationConstructionProperties));
                        break;
                    case GrassRevetmentOvertoppingLocationConstructionProperties grassOvertoppingLocationConstructionProperties:
                        locationDependentInputItems.Add(
                            GrassRevetmentOvertoppingLocationDependentInputFactory.CreateLocationDependentInput(
                                grassOvertoppingLocationConstructionProperties));
                        break;
                    case GrassRevetmentWaveImpactLocationConstructionProperties grassWaveImpactLocationConstructionProperties:
                        locationDependentInputItems.Add(
                            GrassRevetmentWaveImpactLocationDependentInputFactory.CreateLocationDependentInput(
                                grassWaveImpactLocationConstructionProperties));
                        break;
                    case GrassRevetmentWaveRunupRayleighLocationConstructionProperties grassWaveRunupRayleighLocationConstructionProperties:
                        locationDependentInputItems.Add(
                            GrassRevetmentWaveRunupRayleighLocationDependentInputFactory.CreateLocationDependentInput(
                                grassWaveRunupRayleighLocationConstructionProperties));
                        break;
                    case NaturalStoneRevetmentLocationConstructionProperties naturalStoneLocationConstructionProperties:
                        locationDependentInputItems.Add(
                            NaturalStoneRevetmentLocationDependentInputFactory.CreateLocationDependentInput(
                                naturalStoneLocationConstructionProperties));
                        break;
                }
            }

            return locationDependentInputItems;
        }
    }
}