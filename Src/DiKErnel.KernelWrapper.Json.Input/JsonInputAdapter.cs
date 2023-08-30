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
using DiKErnel.KernelWrapper.Json.Input.Exceptions;
using DiKErnel.Util;

namespace DiKErnel.KernelWrapper.Json.Input
{
    internal static class JsonInputAdapter
    {
        public static DataResult<ICalculationInput> AdaptJsonInputData(JsonInputData jsonInputData)
        {
            var builder = new CalculationInputBuilder();

            AdaptDikeProfileData(jsonInputData, builder);
            AdaptHydraulicData(jsonInputData, builder);
            AdaptLocationData(jsonInputData, builder);

            return builder.Build();
        }

        private static void AdaptDikeProfileData(JsonInputData jsonInputData, CalculationInputBuilder builder)
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

        private static void AdaptLocationData(JsonInputData jsonInputData, CalculationInputBuilder builder)
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
            return calculationDataItems.FirstOrDefault(cd => cd.CalculationMethodType == calculationType) as T;
        }

        private static AsphaltRevetmentWaveImpactLocationConstructionProperties
            CreateAsphaltWaveImpactConstructionProperties(
                JsonInputAsphaltWaveImpactLocationData locationData,
                JsonInputAsphaltWaveImpactCalculationData calculationData)
        {
            JsonInputAsphaltWaveImpactTopLayerData topLayerDefinition =
                calculationData?.TopLayerDefinitionData?
                    .FirstOrDefault(tldd => tldd.TopLayerType == locationData.TopLayerType);

            return new AsphaltRevetmentWaveImpactLocationConstructionProperties(
                locationData.X, ConvertTopLayerType(locationData.TopLayerType), locationData.FailureTension,
                locationData.SoilElasticity, locationData.UpperLayer.ThicknessLayer,
                locationData.UpperLayer.ElasticModulusLayer)
            {
                InitialDamage = locationData.InitialDamage,
                ThicknessSubLayer = locationData.SubLayerData?.ThicknessLayer,
                ElasticModulusSubLayer = locationData.SubLayerData?.ElasticModulusLayer,
                FailureNumber = calculationData?.FailureNumber,
                DensityOfWater = calculationData?.DensityOfWater,
                AverageNumberOfWavesCtm = calculationData?.FactorCtm,
                FatigueAlpha = topLayerDefinition?.Fatigue?.FatigueAlpha,
                FatigueBeta = topLayerDefinition?.Fatigue?.FatigueBeta,
                StiffnessRelationNu = topLayerDefinition?.StiffnessRelationNu,
                ImpactNumberC = calculationData?.ImpactNumberC,
                WidthFactors = calculationData?.WidthFactors?
                    .Select(widthFactor => (widthFactor[0], widthFactor[1])).ToList(),
                DepthFactors = calculationData?.DepthFactors?
                    .Select(depthFactor => (depthFactor[0], depthFactor[1])).ToList(),
                ImpactFactors = calculationData?.ImpactFactors?
                    .Select(impactFactor => (impactFactor[0], impactFactor[1])).ToList()
            };
        }

        private static AsphaltRevetmentTopLayerType ConvertTopLayerType(
            JsonInputAsphaltRevetmentTopLayerType topLayerType)
        {
            return topLayerType switch
            {
                JsonInputAsphaltRevetmentTopLayerType.HydraulicAsphaltConcrete =>
                    AsphaltRevetmentTopLayerType.HydraulicAsphaltConcrete,
                _ => throw new JsonInputConversionException("Cannot convert top layer type.")
            };
        }

        private static GrassRevetmentOvertoppingLocationConstructionProperties
            CreateGrassOvertoppingConstructionProperties(
                JsonInputGrassOvertoppingLocationData locationData,
                JsonInputGrassOvertoppingCalculationData calculationData)
        {
            JsonInputGrassCumulativeOverloadTopLayerData topLayerDefinition =
                calculationData?.TopLayerDefinitionData?
                    .FirstOrDefault(tldd => tldd.TopLayerType == locationData.TopLayerType);

            return new GrassRevetmentOvertoppingLocationConstructionProperties(
                locationData.X, ConvertTopLayerType(locationData.TopLayerType))
            {
                InitialDamage = locationData.InitialDamage,
                IncreasedLoadTransitionAlphaM = locationData.IncreasedLoadTransitionAlphaM,
                ReducedStrengthTransitionAlphaS = locationData.ReducedStrengthTransitionAlphaS,
                FailureNumber = calculationData?.FailureNumber,
                CriticalCumulativeOverload = topLayerDefinition?.CriticalCumulativeOverload,
                CriticalFrontVelocity = topLayerDefinition?.CriticalFrontVelocity,
                DikeHeight = calculationData?.DikeHeight,
                AccelerationAlphaAForCrest = calculationData?.AccelerationAlphaAData?.AccelerationAlphaAForCrest,
                AccelerationAlphaAForInnerSlope =
                    calculationData?.AccelerationAlphaAData?.AccelerationAlphaAForInnerSlope,
                FixedNumberOfWaves = calculationData?.FixedNumberOfWaves,
                FrontVelocityCwo = calculationData?.FrontVelocity,
                AverageNumberOfWavesCtm = calculationData?.FactorCtm
            };
        }

        private static GrassRevetmentWaveImpactLocationConstructionProperties
            CreateGrassWaveImpactConstructionProperties(
                JsonInputGrassWaveImpactLocationData locationData,
                JsonInputGrassWaveImpactCalculationData calculationData)
        {
            JsonInputGrassWaveImpactTopLayerData topLayerDefinition =
                calculationData?.TopLayerDefinitionData?
                    .FirstOrDefault(tldd => tldd.TopLayerType == locationData.TopLayerType);

            return new GrassRevetmentWaveImpactLocationConstructionProperties(
                locationData.X, ConvertTopLayerType(locationData.TopLayerType))
            {
                InitialDamage = locationData.InitialDamage,
                FailureNumber = calculationData?.FailureNumber,
                TimeLineAgwi = topLayerDefinition?.TimeLine?.TimeLineA,
                TimeLineBgwi = topLayerDefinition?.TimeLine?.TimeLineB,
                TimeLineCgwi = topLayerDefinition?.TimeLine?.TimeLineC,
                MinimumWaveHeightTemax = calculationData?.Temax,
                MaximumWaveHeightTemin = calculationData?.Temin,
                WaveAngleImpactNwa = calculationData?.WaveAngleData?.WaveAngleImpactN,
                WaveAngleImpactQwa = calculationData?.WaveAngleData?.WaveAngleImpactQ,
                WaveAngleImpactRwa = calculationData?.WaveAngleData?.WaveAngleImpactR,
                UpperLimitLoadingAul = calculationData?.LoadingAreaData?.UpperLimit?.LimitLoading,
                LowerLimitLoadingAll = calculationData?.LoadingAreaData?.LowerLimit?.LimitLoading
            };
        }

        private static GrassRevetmentWaveRunupLocationConstructionProperties CreateGrassWaveRunupConstructionProperties(
            JsonInputGrassWaveRunupLocationData locationData, JsonInputGrassWaveRunupCalculationData calculationData)
        {
            GrassRevetmentWaveRunupLocationConstructionProperties constructionProperties =
                calculationData?.CalculationProtocolData?.CalculationProtocolType switch
                {
                    JsonInputGrassWaveRunupCalculationProtocolType.RayleighDiscrete =>
                        CreateGrassWaveRunupRayleighConstructionProperties(
                            locationData, calculationData.CalculationProtocolData),
                    _ => throw new JsonInputConversionException("Cannot convert calculation protocol type.")
                };

            JsonInputGrassCumulativeOverloadTopLayerData topLayerDefinition =
                calculationData.TopLayerDefinitionData?
                    .FirstOrDefault(tldd => tldd.TopLayerType == locationData.TopLayerType);

            constructionProperties.InitialDamage = locationData.InitialDamage;
            constructionProperties.FailureNumber = calculationData.FailureNumber;
            constructionProperties.IncreasedLoadTransitionAlphaM = locationData.IncreasedLoadTransitionAlphaM;
            constructionProperties.ReducedStrengthTransitionAlphaS = locationData.ReducedStrengthTransitionAlphaS;
            constructionProperties.RepresentativeWaveRunup2PGammab = locationData.RepresentativeWaveRunup2PGammaB;
            constructionProperties.RepresentativeWaveRunup2PGammaf = locationData.RepresentativeWaveRunup2PGammaF;
            constructionProperties.AverageNumberOfWavesCtm = calculationData.FactorCtm;
            constructionProperties.RepresentativeWaveRunup2PAru =
                calculationData.JsonInputGrassWaveRunupCalculationRepresentativeWaveRunupData?.RepresentativeWaveRunup2Pa;
            constructionProperties.RepresentativeWaveRunup2PBru =
                calculationData.JsonInputGrassWaveRunupCalculationRepresentativeWaveRunupData?.RepresentativeWaveRunup2Pb;
            constructionProperties.RepresentativeWaveRunup2PCru =
                calculationData.JsonInputGrassWaveRunupCalculationRepresentativeWaveRunupData?.RepresentativeWaveRunup2Pc;
            constructionProperties.WaveAngleImpactAbeta =
                calculationData.JsonInputGrassWaveRunupCalculationImpactAngleData?.WaveAngleImpactABeta;
            constructionProperties.WaveAngleImpactBetamax =
                calculationData.JsonInputGrassWaveRunupCalculationImpactAngleData?.WaveAngleImpactBetaMax;
            constructionProperties.CriticalCumulativeOverload = topLayerDefinition?.CriticalCumulativeOverload;
            constructionProperties.CriticalFrontVelocity = topLayerDefinition?.CriticalFrontVelocity;

            return constructionProperties;
        }

        private static GrassRevetmentWaveRunupRayleighLocationConstructionProperties
            CreateGrassWaveRunupRayleighConstructionProperties(
                JsonInputGrassWaveRunupLocationData locationData,
                JsonInputGrassWaveRunupCalculationProtocolData calculationProtocolData)
        {
            return new GrassRevetmentWaveRunupRayleighLocationConstructionProperties(
                locationData.X, locationData.OuterSlope, ConvertTopLayerType(locationData.TopLayerType))
            {
                FixedNumberOfWaves = calculationProtocolData.FixedNumberOfWaves,
                FrontVelocityCu = calculationProtocolData.FrontVelocity
            };
        }

        private static GrassRevetmentTopLayerType ConvertTopLayerType(JsonInputGrassRevetmentTopLayerType topLayerType)
        {
            return topLayerType switch
            {
                JsonInputGrassRevetmentTopLayerType.OpenSod => GrassRevetmentTopLayerType.OpenSod,
                JsonInputGrassRevetmentTopLayerType.ClosedSod => GrassRevetmentTopLayerType.ClosedSod,
                _ => throw new JsonInputConversionException("Cannot convert top layer type.")
            };
        }

        private static NaturalStoneRevetmentLocationConstructionProperties CreateNaturalStoneConstructionProperties(
            JsonInputNaturalStoneLocationData locationData, JsonInputNaturalStoneCalculationData calculationData)
        {
            JsonInputNaturalStoneTopLayerData topLayerDefinition =
                calculationData?.TopLayerDefinitionData?
                    .FirstOrDefault(tldd => tldd.TopLayerType == locationData.TopLayerType);

            return new NaturalStoneRevetmentLocationConstructionProperties(
                locationData.X, ConvertTopLayerType(locationData.TopLayerType), locationData.ThicknessTopLayer,
                locationData.RelativeDensity)
            {
                InitialDamage = locationData.InitialDamage,
                FailureNumber = calculationData?.FailureNumber,
                HydraulicLoadAp =
                    topLayerDefinition?.Stability?.JsonInputNaturalStoneTopLayerNorseStoneStabilityCoefficientsData?.A,
                HydraulicLoadBp =
                    topLayerDefinition?.Stability?.JsonInputNaturalStoneTopLayerNorseStoneStabilityCoefficientsData?.B,
                HydraulicLoadCp =
                    topLayerDefinition?.Stability?.JsonInputNaturalStoneTopLayerNorseStoneStabilityCoefficientsData?.C,
                HydraulicLoadNp =
                    topLayerDefinition?.Stability?.JsonInputNaturalStoneTopLayerNorseStoneStabilityCoefficientsData?.N,
                HydraulicLoadAs = topLayerDefinition?.Stability?.JsonInputNaturalStoneTopLayerNorseStoneSurgingData?.A,
                HydraulicLoadBs = topLayerDefinition?.Stability?.JsonInputNaturalStoneTopLayerNorseStoneSurgingData?.B,
                HydraulicLoadCs = topLayerDefinition?.Stability?.JsonInputNaturalStoneTopLayerNorseStoneSurgingData?.C,
                HydraulicLoadNs = topLayerDefinition?.Stability?.JsonInputNaturalStoneTopLayerNorseStoneSurgingData?.N,
                HydraulicLoadXib = topLayerDefinition?.Stability?.StabilityXib,
                SlopeUpperLevelAus = calculationData?.Slope?.SlopeUpperLevel,
                SlopeLowerLevelAls = calculationData?.Slope?.SlopeLowerLevel,
                UpperLimitLoadingAul = calculationData?.LoadingArea?.UpperLimitLoading?.A,
                UpperLimitLoadingBul = calculationData?.LoadingArea?.UpperLimitLoading?.B,
                UpperLimitLoadingCul = calculationData?.LoadingArea?.UpperLimitLoading?.C,
                LowerLimitLoadingAll = calculationData?.LoadingArea?.LowerLimitLoading?.A,
                LowerLimitLoadingBll = calculationData?.LoadingArea?.LowerLimitLoading?.B,
                LowerLimitLoadingCll = calculationData?.LoadingArea?.LowerLimitLoading?.C,
                DistanceMaximumWaveElevationAsmax =
                    calculationData?.DistanceMaximumWaveElevation?.DistanceMaximumWaveElevationA,
                DistanceMaximumWaveElevationBsmax =
                    calculationData?.DistanceMaximumWaveElevation?.DistanceMaximumWaveElevationB,
                NormativeWidthOfWaveImpactAwi =
                    calculationData?.NormativeWidthOfWaveImpact?.NormativeWidthOfWaveImpactA,
                NormativeWidthOfWaveImpactBwi =
                    calculationData?.NormativeWidthOfWaveImpact?.NormativeWidthOfWaveImpactB,
                WaveAngleImpactBetamax = calculationData?.WaveAngleImpact?.WaveAngleImpactBetaMax
            };
        }

        private static NaturalStoneRevetmentTopLayerType ConvertTopLayerType(
            JsonInputNaturalStoneRevetmentTopLayerType topLayerType)
        {
            return topLayerType switch
            {
                JsonInputNaturalStoneRevetmentTopLayerType.NordicStone => NaturalStoneRevetmentTopLayerType.NordicStone,
                _ => throw new JsonInputConversionException("Cannot convert top layer type.")
            };
        }
    }
}