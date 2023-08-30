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
            var builder = new CalculationInputBuilder();

            AdaptDikeProfile(jsonInputData, builder);
            AdaptHydraulicData(jsonInputData, builder);
            AdaptLocations(jsonInputData, builder);

            return builder.Build();
        }

        private static void AdaptDikeProfile(JsonInputData jsonInputData, CalculationInputBuilder builder)
        {
            JsonInputDikeProfileData dikeProfileData = jsonInputData.DikeProfileData;

            IReadOnlyList<double> xLocations = dikeProfileData.XLocations;
            IReadOnlyList<double> zLocations = dikeProfileData.ZLocations;
            IReadOnlyList<double> roughnessCoefficients = dikeProfileData.RoughnessCoefficients;

            for (var i = 0; i < xLocations.Count - 1; i++)
            {
                double startPointX = xLocations[i];
                double startPointZ = zLocations[i];
                double endPointX = xLocations[i + 1];
                double endPointZ = zLocations[i + 1];

                if (roughnessCoefficients != null)
                {
                    builder.AddDikeProfileSegment(startPointX, startPointZ, endPointX, endPointZ,
                                                  roughnessCoefficients[i]);
                }
                else
                {
                    builder.AddDikeProfileSegment(startPointX, startPointZ, endPointX, endPointZ);
                }
            }

            if (dikeProfileData.OuterToe.HasValue)
            {
                builder.AddDikeProfilePoint(dikeProfileData.OuterToe.Value, CharacteristicPointType.OuterToe);
            }

            if (dikeProfileData.CrestOuterBerm.HasValue)
            {
                builder.AddDikeProfilePoint(dikeProfileData.CrestOuterBerm.Value,
                                            CharacteristicPointType.CrestOuterBerm);
            }

            if (dikeProfileData.NotchOuterBerm.HasValue)
            {
                builder.AddDikeProfilePoint(dikeProfileData.NotchOuterBerm.Value,
                                            CharacteristicPointType.NotchOuterBerm);
            }

            if (dikeProfileData.OuterCrest.HasValue)
            {
                builder.AddDikeProfilePoint(dikeProfileData.OuterCrest.Value, CharacteristicPointType.OuterCrest);
            }

            if (dikeProfileData.InnerCrest.HasValue)
            {
                builder.AddDikeProfilePoint(dikeProfileData.InnerCrest.Value, CharacteristicPointType.InnerCrest);
            }

            if (dikeProfileData.InnerToe.HasValue)
            {
                builder.AddDikeProfilePoint(dikeProfileData.InnerToe.Value, CharacteristicPointType.InnerToe);
            }
        }

        private static void AdaptHydraulicData(JsonInputData jsonInputData, CalculationInputBuilder builder)
        {
            JsonInputHydraulicData hydraulicData = jsonInputData.HydraulicData;

            IReadOnlyList<double> waterLevels = hydraulicData.WaterLevels;
            IReadOnlyList<double> waveHeightsHm0 = hydraulicData.WaveHeightsHm0;
            IReadOnlyList<double> wavePeriodsTm10 = hydraulicData.WavePeriodsTm10;
            IReadOnlyList<double> waveAngles = hydraulicData.WaveAngles;

            IReadOnlyList<int> times = jsonInputData.Times;

            for (var i = 0; i < times.Count - 1; i++)
            {
                builder.AddTimeStep(times[i], times[i + 1], waterLevels[i], waveHeightsHm0[i], wavePeriodsTm10[i],
                                    waveAngles[i]);
            }
        }

        private static void AdaptLocations(JsonInputData jsonInputData, CalculationInputBuilder builder)
        {
            IReadOnlyList<JsonInputLocationData> locationDataItems = jsonInputData.LocationData;
            IReadOnlyList<JsonInputCalculationData> calculationDataItems = jsonInputData.CalculationDefinitionData;

            foreach (JsonInputLocationData locationData in locationDataItems)
            {
                switch (locationData)
                {
                    case JsonInputAsphaltWaveImpactLocationData asphaltWaveImpactLocationData:
                    {
                        builder.AddAsphaltWaveImpactLocation(
                            CreateAsphaltWaveImpactConstructionProperties(
                                asphaltWaveImpactLocationData,
                                GetCalculationDefinition<JsonInputAsphaltWaveImpactCalculationData>(
                                    calculationDataItems, JsonInputCalculationType.AsphaltWaveImpact)));
                        break;
                    }
                    case JsonInputGrassOvertoppingLocationData grassOvertoppingLocationData:
                    {
                        builder.AddGrassOvertoppingLocation(
                            CreateGrassOvertoppingConstructionProperties(
                                grassOvertoppingLocationData,
                                GetCalculationDefinition<JsonInputGrassOvertoppingCalculationData>(
                                    calculationDataItems, JsonInputCalculationType.GrassOvertopping)));
                        break;
                    }
                    case JsonInputGrassWaveImpactLocationData grassWaveImpactLocationData:
                    {
                        builder.AddGrassWaveImpactLocation(
                            CreateGrassWaveImpactConstructionProperties(
                                grassWaveImpactLocationData,
                                GetCalculationDefinition<JsonInputGrassWaveImpactCalculationData>(
                                    calculationDataItems, JsonInputCalculationType.GrassWaveImpact)));
                        break;
                    }
                    case JsonInputGrassWaveRunupLocationData grassWaveRunupLocationData:
                    {
                        GrassRevetmentWaveRunupLocationConstructionProperties constructionProperties =
                            CreateGrassWaveRunupConstructionProperties(
                                grassWaveRunupLocationData,
                                GetCalculationDefinition<JsonInputGrassWaveRunupCalculationData>(
                                    calculationDataItems, JsonInputCalculationType.GrassWaveRunup));

                        if (constructionProperties is
                            GrassRevetmentWaveRunupRayleighLocationConstructionProperties rayleighConstructionProperties)
                        {
                            builder.AddGrassWaveRunupRayleighLocation(rayleighConstructionProperties);
                        }

                        break;
                    }
                    case JsonInputNaturalStoneLocationData naturalStoneLocationData:
                    {
                        builder.AddNaturalStoneLocation(
                            CreateNaturalStoneConstructionProperties(
                                naturalStoneLocationData,
                                GetCalculationDefinition<JsonInputNaturalStoneCalculationData>(
                                    calculationDataItems, JsonInputCalculationType.NaturalStone)));
                        break;
                    }
                }
            }
        }

        private static T GetCalculationDefinition<T>(IReadOnlyList<JsonInputCalculationData> calculationDataItems,
                                                     JsonInputCalculationType calculationType)
            where T : class
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