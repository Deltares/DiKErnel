// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
//
// This file is part of DiKErnel.
//
// DiKErnel is free software: you can redistribute it and/or modify it under the terms of the
// GNU Lesser General Public License as published by the Free Software Foundation, either
// version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with this
// program. If not, see <http://www.gnu.org/licenses/>.
//
// All names, logos, and references to "Deltares" are registered trademarks of Stichting
// Deltares and remain full property of Stichting Deltares at all times. All rights reserved.

using System.Collections.Generic;
using System.Linq;
using DiKErnel.Core.Data;
using DiKErnel.Core.Extensions;
using DiKErnel.Integration.Data.AsphaltRevetmentWaveImpact;
using DiKErnel.Integration.Data.GrassRevetmentOvertopping;
using DiKErnel.Integration.Data.GrassRevetmentWaveImpact;
using DiKErnel.Integration.Data.GrassRevetmentWaveRunup;
using DiKErnel.Integration.Data.NaturalStoneRevetment;
using DiKErnel.KernelWrapper.Json.Output.Data.Generic;
using DiKErnel.KernelWrapper.Json.Output.Data.Revetment;
using DiKErnel.KernelWrapper.Json.Output.Exceptions;

namespace DiKErnel.KernelWrapper.Json.Output
{
    internal static class CalculationOutputAdapter
    {
        public static JsonOutputData AdaptCalculationOutput(
            CalculationOutput calculationOutput, JsonOutputType outputType,
            IReadOnlyDictionary<string, object> metaDataItems)
        {
            return new JsonOutputData(
                GetJsonOutputLocations(calculationOutput.LocationDependentOutputItems, outputType), metaDataItems);
        }

        private static JsonOutputLocationsObject GetJsonOutputLocations(
            IReadOnlyList<LocationDependentOutput> locationDependentOutputItems, JsonOutputType outputType)
        {
            return new JsonOutputLocationsObject(
                locationDependentOutputItems
                    .Select(locationDependentOutput => CreateLocationData(locationDependentOutput, outputType))
                    .ToList());
        }

        private static JsonOutputLocationData CreateLocationData(
            LocationDependentOutput locationDependentOutput, JsonOutputType outputType)
        {
            return new JsonOutputLocationData(
                CreateFailureData(locationDependentOutput),
                outputType == JsonOutputType.Damage || outputType == JsonOutputType.Physics
                    ? CreateDamageData(locationDependentOutput)
                    : null,
                outputType == JsonOutputType.Physics
                    ? CreatePhysicsData(locationDependentOutput)
                    : null);
        }

        private static JsonOutputFailureLocationData CreateFailureData(
            LocationDependentOutput locationDependentOutput)
        {
            return new JsonOutputFailureLocationData(locationDependentOutput.GetTimeOfFailure());
        }

        private static JsonOutputDamageLocationData CreateDamageData(
            LocationDependentOutput locationDependentOutput)
        {
            return new JsonOutputDamageLocationData(locationDependentOutput.GetDamages());
        }

        private static JsonOutputPhysicsLocationData CreatePhysicsData(
            LocationDependentOutput locationDependentOutput)
        {
            return locationDependentOutput switch
            {
                AsphaltRevetmentWaveImpactLocationDependentOutput asphaltRevetmentWaveImpactLocationDependentOutput =>
                    new JsonOutputAsphaltRevetmentWaveImpactPhysicsLocationData(),
                GrassRevetmentOvertoppingLocationDependentOutput grassRevetmentOvertoppingLocationDependentOutput =>
                    new JsonOutputGrassRevetmentOvertoppingPhysicsLocationData(),
                GrassRevetmentWaveImpactLocationDependentOutput grassRevetmentWaveImpactLocationDependentOutput =>
                    new JsonOutputGrassRevetmentWaveImpactPhysicsLocationData(),
                GrassRevetmentWaveRunupRayleighLocationDependentOutput grassRevetmentWaveRunupRayleighLocationDependentOutput =>
                    new JsonOutputGrassRevetmentWaveRunupRayleighPhysicsLocationData(),
                NaturalStoneRevetmentLocationDependentOutput naturalStoneRevetmentLocationDependentOutput =>
                    new JsonOutputNaturalStoneRevetmentPhysicsLocationData(),
                _ => throw new JsonOutputCreationException("Invalid revetment type.")
            };
        }
    }
}