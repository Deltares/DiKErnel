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
using System.Linq;
using DiKErnel.Core.Data;
using DiKErnel.Integration;
using DiKErnel.Integration.Data.AsphaltWaveImpact;
using DiKErnel.Integration.Data.Grass;
using DiKErnel.Integration.Data.GrassOvertopping;
using DiKErnel.Integration.Data.GrassWaveImpact;
using DiKErnel.Integration.Data.GrassWaveRunup;
using DiKErnel.Integration.Data.NaturalStoneWaveImpact;
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
            var builder = new CalculationInputBuilder(jsonInputData.DikeProfileData.DikeOrientation);

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
            IReadOnlyList<double> waveDirections = hydraulicData.WaveDirections;

            IReadOnlyList<double> times = jsonInputData.Times;

            for (var i = 0; i < times.Count - 1; i++)
            {
                builder.AddTimeStep(times[i], times[i + 1], waterLevels[i], waveHeightsHm0[i], wavePeriodsTm10[i],
                                    waveDirections[i]);
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
            return calculationDataItems?.FirstOrDefault(cd => cd.CalculationMethodType == calculationType) as T;
        }

        private static AsphaltWaveImpactLocationConstructionProperties CreateAsphaltWaveImpactConstructionProperties(
            JsonInputAsphaltWaveImpactLocationData locationData,
            JsonInputAsphaltWaveImpactCalculationData calculationData)
        {
            JsonInputAsphaltWaveImpactLocationLayerData upperLayerData = locationData.UpperLayer;
            JsonInputAsphaltWaveImpactLocationLayerData subLayerData = locationData.SubLayerData;
            JsonInputAsphaltWaveImpactTopLayerData topLayerData =
                calculationData?.TopLayerDefinitionData?
                    .FirstOrDefault(tldd => tldd.TopLayerType == locationData.TopLayerType);
            JsonInputAsphaltWaveImpactLocationFatigueData fatigueData = locationData.Fatigue;

            return new AsphaltWaveImpactLocationConstructionProperties(
                locationData.X, ConvertAsphaltRevetmentTopLayerType(locationData.TopLayerType),
                locationData.FlexuralStrength, locationData.SoilElasticity, upperLayerData.ThicknessLayer,
                upperLayerData.ElasticModulusLayer)
            {
                InitialDamage = locationData.InitialDamage,
                ThicknessSubLayer = subLayerData?.ThicknessLayer,
                ElasticModulusSubLayer = subLayerData?.ElasticModulusLayer,
                FailureNumber = calculationData?.FailureNumber,
                DensityOfWater = calculationData?.DensityOfWater,
                AverageNumberOfWavesCtm = calculationData?.FactorCtm,
                FatigueAlpha = fatigueData?.FatigueAlpha,
                FatigueBeta = fatigueData?.FatigueBeta,
                StiffnessRelationNu = topLayerData?.StiffnessRelationNu,
                ImpactNumberC = calculationData?.ImpactNumberC,
                WidthFactors = calculationData?.WidthFactors?
                    .Select(widthFactor => (widthFactor[0], widthFactor[1])).ToList(),
                DepthFactors = calculationData?.DepthFactors?
                    .Select(depthFactor => (depthFactor[0], depthFactor[1])).ToList(),
                ImpactFactors = calculationData?.ImpactFactors?
                    .Select(impactFactor => (impactFactor[0], impactFactor[1])).ToList()
            };
        }

        private static AsphaltTopLayerType ConvertAsphaltRevetmentTopLayerType(
            JsonInputAsphaltRevetmentTopLayerType topLayerType)
        {
            return topLayerType switch
            {
                JsonInputAsphaltRevetmentTopLayerType.HydraulicAsphaltConcrete =>
                    AsphaltTopLayerType.HydraulicAsphaltConcrete,
                _ => throw new JsonInputConversionException("Cannot convert top layer type.")
            };
        }

        private static GrassOvertoppingLocationConstructionProperties CreateGrassOvertoppingConstructionProperties(
            JsonInputGrassOvertoppingLocationData locationData,
            JsonInputGrassOvertoppingCalculationData calculationData)
        {
            JsonInputGrassCumulativeOverloadTopLayerData topLayerData =
                calculationData?.TopLayerDefinitionData?
                    .FirstOrDefault(tldd => tldd.TopLayerType == locationData.TopLayerType);
            JsonInputGrassOvertoppingCalculationAccelerationAlphaAData accelerationAlphaAData =
                calculationData?.AccelerationAlphaAData;

            return new GrassOvertoppingLocationConstructionProperties(
                locationData.X, ConvertGrassRevetmentTopLayerType(locationData.TopLayerType))
            {
                InitialDamage = locationData.InitialDamage,
                IncreasedLoadTransitionAlphaM = locationData.IncreasedLoadTransitionAlphaM,
                ReducedStrengthTransitionAlphaS = locationData.ReducedStrengthTransitionAlphaS,
                FailureNumber = calculationData?.FailureNumber,
                CriticalCumulativeOverload = topLayerData?.CriticalCumulativeOverload,
                CriticalFrontVelocity = topLayerData?.CriticalFrontVelocity,
                DikeHeight = calculationData?.DikeHeight,
                AccelerationAlphaAForCrest = accelerationAlphaAData?.AccelerationAlphaAForCrest,
                AccelerationAlphaAForInnerSlope = accelerationAlphaAData?.AccelerationAlphaAForInnerSlope,
                FixedNumberOfWaves = calculationData?.FixedNumberOfWaves,
                FrontVelocityCwo = calculationData?.FrontVelocity,
                AverageNumberOfWavesCtm = calculationData?.FactorCtm
            };
        }

        private static GrassWaveImpactLocationConstructionProperties CreateGrassWaveImpactConstructionProperties(
                JsonInputGrassWaveImpactLocationData locationData,
                JsonInputGrassWaveImpactCalculationData calculationData)
        {
            JsonInputGrassWaveImpactTopLayerTimeLineData timeLineData =
                calculationData?.TopLayerDefinitionData?
                    .FirstOrDefault(tldd => tldd.TopLayerType == locationData.TopLayerType)?.TimeLine;
            JsonInputGrassWaveImpactCalculationImpactWaveAngleData impactWaveAngleData = calculationData?.WaveAngleData;
            JsonInputGrassWaveImpactCalculationLoadingAreaData loadingAreaData = calculationData?.LoadingAreaData;

            return new GrassWaveImpactLocationConstructionProperties(
                locationData.X, ConvertGrassRevetmentTopLayerType(locationData.TopLayerType))
            {
                InitialDamage = locationData.InitialDamage,
                FailureNumber = calculationData?.FailureNumber,
                TimeLineAgwi = timeLineData?.TimeLineA,
                TimeLineBgwi = timeLineData?.TimeLineB,
                TimeLineCgwi = timeLineData?.TimeLineC,
                MinimumWaveHeightTemax = calculationData?.Temax,
                MaximumWaveHeightTemin = calculationData?.Temin,
                WaveAngleImpactNwa = impactWaveAngleData?.WaveAngleImpactN,
                WaveAngleImpactQwa = impactWaveAngleData?.WaveAngleImpactQ,
                WaveAngleImpactRwa = impactWaveAngleData?.WaveAngleImpactR,
                UpperLimitLoadingAul = loadingAreaData?.UpperLimit?.LimitLoading,
                LowerLimitLoadingAll = loadingAreaData?.LowerLimit?.LimitLoading
            };
        }

        private static GrassRevetmentWaveRunupLocationConstructionProperties CreateGrassWaveRunupConstructionProperties(
            JsonInputGrassWaveRunupLocationData locationData, JsonInputGrassWaveRunupCalculationData calculationData)
        {
            GrassRevetmentWaveRunupLocationConstructionProperties constructionProperties;

            switch (calculationData?.CalculationProtocolData?.CalculationProtocolType)
            {
                case JsonInputGrassWaveRunupCalculationProtocolType.RayleighDiscrete:
                    constructionProperties = CreateGrassWaveRunupRayleighConstructionProperties(
                        locationData, calculationData.CalculationProtocolData);
                    break;
                default:
                    throw new JsonInputConversionException("Cannot convert calculation protocol type.");
            }

            JsonInputGrassCumulativeOverloadTopLayerData topLayerData =
                calculationData.TopLayerDefinitionData?
                    .FirstOrDefault(tldd => tldd.TopLayerType == locationData.TopLayerType);

            constructionProperties.InitialDamage = locationData.InitialDamage;
            constructionProperties.FailureNumber = calculationData.FailureNumber;
            constructionProperties.IncreasedLoadTransitionAlphaM = locationData.IncreasedLoadTransitionAlphaM;
            constructionProperties.ReducedStrengthTransitionAlphaS = locationData.ReducedStrengthTransitionAlphaS;
            constructionProperties.AverageNumberOfWavesCtm = calculationData.FactorCtm;
            constructionProperties.CriticalCumulativeOverload = topLayerData?.CriticalCumulativeOverload;
            constructionProperties.CriticalFrontVelocity = topLayerData?.CriticalFrontVelocity;

            return constructionProperties;
        }

        private static GrassRevetmentWaveRunupRayleighLocationConstructionProperties
            CreateGrassWaveRunupRayleighConstructionProperties(
                JsonInputGrassWaveRunupLocationData locationData,
                JsonInputGrassWaveRunupCalculationProtocolData calculationProtocolData)
        {
            return new GrassRevetmentWaveRunupRayleighLocationConstructionProperties(
                locationData.X, ConvertGrassRevetmentTopLayerType(locationData.TopLayerType))
            {
                FixedNumberOfWaves = calculationProtocolData.FixedNumberOfWaves,
                FrontVelocityCu = calculationProtocolData.FrontVelocity
            };
        }

        private static GrassTopLayerType ConvertGrassRevetmentTopLayerType(
            JsonInputGrassRevetmentTopLayerType topLayerType)
        {
            return topLayerType switch
            {
                JsonInputGrassRevetmentTopLayerType.OpenSod => GrassTopLayerType.OpenSod,
                JsonInputGrassRevetmentTopLayerType.ClosedSod => GrassTopLayerType.ClosedSod,
                _ => throw new JsonInputConversionException("Cannot convert top layer type.")
            };
        }

        private static NaturalStoneRevetmentLocationConstructionProperties CreateNaturalStoneConstructionProperties(
            JsonInputNaturalStoneLocationData locationData, JsonInputNaturalStoneCalculationData calculationData)
        {
            JsonInputNaturalStoneTopLayerStabilityData stabilityData =
                calculationData?.TopLayerDefinitionData?
                    .FirstOrDefault(tldd => tldd.TopLayerType == locationData.TopLayerType)?.Stability;
            JsonInputNaturalStoneTopLayerStabilityCoefficientsData plungingData =
                stabilityData?.JsonInputNaturalStoneTopLayerPlungingData;
            JsonInputNaturalStoneTopLayerStabilityCoefficientsData surgingData =
                stabilityData?.JsonInputNaturalStoneTopLayerSurgingData;
            JsonInputNaturalStoneCalculationSlopeData slopeData = calculationData?.Slope;
            JsonInputNaturalStoneCalculationLoadingAreaData loadingAreaData = calculationData?.LoadingArea;
            JsonInputNaturalStoneCalculationLimitData upperLimitLoadingData = loadingAreaData?.UpperLimitLoading;
            JsonInputNaturalStoneCalculationLimitData lowerLimitLoadingData = loadingAreaData?.LowerLimitLoading;
            JsonInputNaturalStoneCalculationMaximumWaveElevationData maximumWaveElevationData =
                calculationData?.DistanceMaximumWaveElevation;
            JsonInputNaturalStoneCalculationNormativeWidthWaveImpactData normativeWidthWaveImpactData =
                calculationData?.NormativeWidthOfWaveImpact;

            return new NaturalStoneRevetmentLocationConstructionProperties(
                locationData.X, ConvertNaturalStoneRevetmentTopLayerType(locationData.TopLayerType),
                locationData.ThicknessTopLayer, locationData.RelativeDensity)
            {
                InitialDamage = locationData.InitialDamage,
                FailureNumber = calculationData?.FailureNumber,
                HydraulicLoadAp = plungingData?.A,
                HydraulicLoadBp = plungingData?.B,
                HydraulicLoadCp = plungingData?.C,
                HydraulicLoadNp = plungingData?.N,
                HydraulicLoadAs = surgingData?.A,
                HydraulicLoadBs = surgingData?.B,
                HydraulicLoadCs = surgingData?.C,
                HydraulicLoadNs = surgingData?.N,
                HydraulicLoadXib = stabilityData?.StabilityXib,
                SlopeUpperLevelAus = slopeData?.SlopeUpperLevel,
                SlopeLowerLevelAls = slopeData?.SlopeLowerLevel,
                UpperLimitLoadingAul = upperLimitLoadingData?.A,
                UpperLimitLoadingBul = upperLimitLoadingData?.B,
                UpperLimitLoadingCul = upperLimitLoadingData?.C,
                LowerLimitLoadingAll = lowerLimitLoadingData?.A,
                LowerLimitLoadingBll = lowerLimitLoadingData?.B,
                LowerLimitLoadingCll = lowerLimitLoadingData?.C,
                DistanceMaximumWaveElevationAsmax = maximumWaveElevationData?.DistanceMaximumWaveElevationA,
                DistanceMaximumWaveElevationBsmax = maximumWaveElevationData?.DistanceMaximumWaveElevationB,
                NormativeWidthOfWaveImpactAwi = normativeWidthWaveImpactData?.NormativeWidthOfWaveImpactA,
                NormativeWidthOfWaveImpactBwi = normativeWidthWaveImpactData?.NormativeWidthOfWaveImpactB,
                WaveAngleImpactBetamax = calculationData?.WaveAngleImpact?.WaveAngleImpactBetaMax
            };
        }

        private static NaturalStoneTopLayerType ConvertNaturalStoneRevetmentTopLayerType(
            JsonInputNaturalStoneRevetmentTopLayerType topLayerType)
        {
            return topLayerType switch
            {
                JsonInputNaturalStoneRevetmentTopLayerType.NordicStone => NaturalStoneTopLayerType.NordicStone,
                _ => throw new JsonInputConversionException("Cannot convert top layer type.")
            };
        }
    }
}