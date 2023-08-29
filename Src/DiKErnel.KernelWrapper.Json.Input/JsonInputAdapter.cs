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
using DiKErnel.Core.Data;
using DiKErnel.Integration;
using DiKErnel.Integration.Data.AsphaltRevetmentWaveImpact;
using DiKErnel.Integration.Data.GrassRevetment;
using DiKErnel.Integration.Data.GrassRevetmentOvertopping;
using DiKErnel.Integration.Data.GrassRevetmentWaveImpact;
using DiKErnel.Integration.Data.GrassRevetmentWaveRunup;
using DiKErnel.Integration.Data.NaturalStoneRevetment;
using DiKErnel.KernelWrapper.Json.Input.Data.Generic;
using DiKErnel.KernelWrapper.Json.Input.Data.Revetment;
using DiKErnel.KernelWrapper.Json.Input.Data.Revetment.JsonInputAsphaltWaveImpact;
using DiKErnel.KernelWrapper.Json.Input.Data.Revetment.JsonInputGrassOvertopping;
using DiKErnel.KernelWrapper.Json.Input.Data.Revetment.JsonInputGrassWaveImpact;
using DiKErnel.KernelWrapper.Json.Input.Data.Revetment.JsonInputGrassWaveRunup;
using DiKErnel.KernelWrapper.Json.Input.Data.Revetment.JsonInputNaturalStone;
using DiKErnel.Util;

namespace DiKErnel.KernelWrapper.Json.Input
{
    internal static class JsonInputAdapter
    {
        public static DataResult<ICalculationInput> AdaptJsonInputData(JsonInputData jsonInputData)
        {
            return null;
        }

        private static void AdaptDikeProfile(JsonInputData jsonInputData, CalculationInputBuilder builder) {}

        private static void AdaptHydraulicData(JsonInputData jsonInputData, CalculationInputBuilder builder) {}

        private static void AdaptLocations(JsonInputData jsonInputData, CalculationInputBuilder builder) {}

        private static T GetCalculationDefinition<T>(
            Dictionary<JsonInputCalculationType, JsonInputCalculationData> calculationDefinitions,
            JsonInputCalculationType calculationType) where T : class
        {
            return null;
        }

        private static AsphaltRevetmentWaveImpactLocationConstructionProperties
            CreateAsphaltWaveImpactConstructionProperties(
                JsonInputAsphaltWaveImpactLocationData location,
                JsonInputAsphaltWaveImpactCalculationData calculationDefinition)
        {
            return null;
        }

        private static AsphaltRevetmentTopLayerType ConvertTopLayerType(
            JsonInputAsphaltRevetmentTopLayerType topLayerType)
        {
            return AsphaltRevetmentTopLayerType.HydraulicAsphaltConcrete;
        }

        private static GrassRevetmentOvertoppingLocationConstructionProperties
            CreateGrassOvertoppingConstructionProperties(
                JsonInputGrassOvertoppingLocationData location,
                JsonInputGrassOvertoppingCalculationData calculationDefinition)
        {
            return null;
        }

        private static GrassRevetmentWaveImpactLocationConstructionProperties
            CreateGrassWaveImpactConstructionProperties(
                JsonInputGrassWaveImpactLocationData location,
                JsonInputGrassWaveImpactCalculationData calculationDefinition)
        {
            return null;
        }

        private static GrassRevetmentWaveRunupLocationConstructionProperties CreateGrassWaveRunupConstructionProperties(
            JsonInputGrassWaveRunupLocationData location, JsonInputGrassWaveRunupCalculationData calculationDefinition)
        {
            return null;
        }

        private static GrassRevetmentWaveRunupRayleighLocationConstructionProperties
            CreateGrassWaveRunupRayleighConstructionProperties(
                JsonInputGrassWaveRunupLocationData location,
                JsonInputGrassWaveRunupCalculationProtocolData calculationProtocol)
        {
            return null;
        }

        private static GrassRevetmentTopLayerType ConvertTopLayerType(JsonInputGrassRevetmentTopLayerType topLayerType)
        {
            return GrassRevetmentTopLayerType.ClosedSod;
        }

        private static NaturalStoneRevetmentLocationConstructionProperties CreateNaturalStoneConstructionProperties(
            JsonInputNaturalStoneLocationData location, JsonInputNaturalStoneCalculationData calculationDefinition)
        {
            return null;
        }

        private static NaturalStoneRevetmentTopLayerType ConvertTopLayerType(
            JsonInputNaturalStoneRevetmentTopLayerType topLayerType)
        {
            return NaturalStoneRevetmentTopLayerType.NordicStone;
        }
    }
}