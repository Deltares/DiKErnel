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
using DiKErnel.Integration.Data.GrassWaveImpact;
using DiKErnel.Integration.Data.GrassWaveOvertopping;
using DiKErnel.Integration.Data.GrassWaveRunup;
using DiKErnel.Integration.Data.NaturalStoneWaveImpact;
using DiKErnel.KernelWrapper.Json.Input.Data.Generic;
using DiKErnel.KernelWrapper.Json.Input.Data.Revetment.JsonInputAsphaltWaveImpact;
using DiKErnel.KernelWrapper.Json.Input.Data.Revetment.JsonInputGrass;
using DiKErnel.KernelWrapper.Json.Input.Data.Revetment.JsonInputGrassWaveImpact;
using DiKErnel.KernelWrapper.Json.Input.Data.Revetment.JsonInputGrassWaveOvertopping;
using DiKErnel.KernelWrapper.Json.Input.Data.Revetment.JsonInputGrassWaveRunup;
using DiKErnel.KernelWrapper.Json.Input.Data.Revetment.JsonInputNaturalStoneWaveImpact;
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
            IReadOnlyList<JsonInputCalculationData> calculationDataItems = jsonInputData.CalculationData;

            foreach (JsonInputLocationData locationData in locationDataItems)
            {
                switch (locationData.CalculationMethodType)
                {
                    case JsonInputCalculationType.AsphaltWaveImpact:
                    {
                        builder.AddAsphaltWaveImpactLocation(
                            CreateAsphaltWaveImpactLocationConstructionProperties(
                                (JsonInputAsphaltWaveImpactLocationData) locationData,
                                GetCalculationDefinition<JsonInputAsphaltWaveImpactCalculationData>(
                                    calculationDataItems, JsonInputCalculationType.AsphaltWaveImpact)));
                        break;
                    }
                    case JsonInputCalculationType.GrassWaveOvertopping:
                    {
                        builder.AddGrassWaveOvertoppingRayleighDiscreteLocation(
                            CreateGrassWaveOvertoppingRayleighDiscreteLocationConstructionProperties(
                                (JsonInputGrassCumulativeOverloadLocationData) locationData,
                                GetCalculationDefinition<JsonInputGrassWaveOvertoppingRayleighDiscreteCalculationData>(
                                    calculationDataItems, JsonInputCalculationType.GrassWaveOvertopping)));
                        break;
                    }
                    case JsonInputCalculationType.GrassWaveImpact:
                    {
                        builder.AddGrassWaveImpactLocation(
                            CreateGrassWaveImpactLocationConstructionProperties(
                                (JsonInputGrassWaveImpactLocationData) locationData,
                                GetCalculationDefinition<JsonInputGrassWaveImpactCalculationData>(
                                    calculationDataItems, JsonInputCalculationType.GrassWaveImpact)));
                        break;
                    }
                    case JsonInputCalculationType.GrassWaveRunup:
                    {
                        GrassCumulativeOverloadLocationConstructionProperties constructionProperties =
                            CreateGrassWaveRunupLocationConstructionProperties(
                                (JsonInputGrassCumulativeOverloadLocationData) locationData,
                                GetCalculationDefinition<JsonInputGrassWaveRunupCalculationData>(
                                    calculationDataItems, JsonInputCalculationType.GrassWaveRunup));

                        if (constructionProperties is
                            GrassWaveRunupRayleighDiscreteLocationConstructionProperties
                            grassWaveRunupRayleighDiscreteLocationConstructionProperties)
                        {
                            builder.AddGrassWaveRunupRayleighDiscreteLocation(
                                grassWaveRunupRayleighDiscreteLocationConstructionProperties);
                        }

                        break;
                    }
                    case JsonInputCalculationType.NaturalStoneWaveImpact:
                    {
                        builder.AddNaturalStoneWaveImpactLocation(
                            CreateNaturalStoneWaveImpactLocationConstructionProperties(
                                (JsonInputNaturalStoneWaveImpactLocationData) locationData,
                                GetCalculationDefinition<JsonInputNaturalStoneWaveImpactCalculationData>(
                                    calculationDataItems, JsonInputCalculationType.NaturalStoneWaveImpact)));
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

        private static AsphaltWaveImpactLocationConstructionProperties CreateAsphaltWaveImpactLocationConstructionProperties(
            JsonInputAsphaltWaveImpactLocationData locationData,
            JsonInputAsphaltWaveImpactCalculationData calculationData)
        {
            JsonInputAsphaltWaveImpactLayerData upperLayerData = locationData.UpperLayerData;
            JsonInputAsphaltWaveImpactLayerData subLayerData = locationData.SubLayerData;
            JsonInputAsphaltWaveImpactTopLayerData topLayerData =
                calculationData?.TopLayerData?.FirstOrDefault(tld => tld.TopLayerType == locationData.TopLayerType);
            JsonInputAsphaltWaveImpactFatigueData fatigueData = locationData.FatigueData;

            return new AsphaltWaveImpactLocationConstructionProperties(
                locationData.X, ConvertAsphaltWaveImpactTopLayerType(locationData.TopLayerType),
                locationData.FlexuralStrength, locationData.SoilElasticity, upperLayerData.ThicknessLayer,
                upperLayerData.ElasticModulusLayer)
            {
                InitialDamage = locationData.InitialDamage,
                ThicknessSubLayer = subLayerData?.ThicknessLayer,
                ElasticModulusSubLayer = subLayerData?.ElasticModulusLayer,
                FailureNumber = calculationData?.FailureNumber,
                DensityOfWater = calculationData?.DensityOfWater,
                AverageNumberOfWavesCtm = calculationData?.FactorCtm,
                FatigueAlpha = fatigueData?.Alpha,
                FatigueBeta = fatigueData?.Beta,
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

        private static AsphaltWaveImpactTopLayerType ConvertAsphaltWaveImpactTopLayerType(
            JsonInputAsphaltWaveImpactTopLayerType topLayerType)
        {
            return topLayerType switch
            {
                JsonInputAsphaltWaveImpactTopLayerType.HydraulicAsphaltConcrete =>
                    AsphaltWaveImpactTopLayerType.HydraulicAsphaltConcrete,
                _ => throw new JsonInputConversionException("Cannot convert top layer type.")
            };
        }

        private static GrassWaveOvertoppingRayleighDiscreteLocationConstructionProperties
            CreateGrassWaveOvertoppingRayleighDiscreteLocationConstructionProperties(
                JsonInputGrassCumulativeOverloadLocationData locationData,
                JsonInputGrassWaveOvertoppingRayleighDiscreteCalculationData calculationData)
        {
            JsonInputGrassCumulativeOverloadTopLayerData topLayerData =
                calculationData?.TopLayerData?.FirstOrDefault(tld => tld.TopLayerType == locationData.TopLayerType);
            JsonInputGrassWaveOvertoppingRayleighDiscreteAccelerationAlphaAData accelerationAlphaAData =
                calculationData?.AccelerationAlphaAData;

            return new GrassWaveOvertoppingRayleighDiscreteLocationConstructionProperties(
                locationData.X, ConvertGrassTopLayerType(locationData.TopLayerType))
            {
                InitialDamage = locationData.InitialDamage,
                IncreasedLoadTransitionAlphaM = locationData.IncreasedLoadTransitionAlphaM,
                ReducedStrengthTransitionAlphaS = locationData.ReducedStrengthTransitionAlphaS,
                FailureNumber = calculationData?.FailureNumber,
                CriticalCumulativeOverload = topLayerData?.CriticalCumulativeOverload,
                CriticalFrontVelocity = topLayerData?.CriticalFrontVelocity,
                DikeHeight = calculationData?.DikeHeight,
                AccelerationAlphaAForCrest = accelerationAlphaAData?.AForCrest,
                AccelerationAlphaAForInnerSlope = accelerationAlphaAData?.AForInnerSlope,
                FixedNumberOfWaves = calculationData?.FixedNumberOfWaves,
                FrontVelocityCwo = calculationData?.FrontVelocity,
                AverageNumberOfWavesCtm = calculationData?.FactorCtm
            };
        }

        private static GrassWaveImpactLocationConstructionProperties CreateGrassWaveImpactLocationConstructionProperties(
            JsonInputGrassWaveImpactLocationData locationData,
            JsonInputGrassWaveImpactCalculationData calculationData)
        {
            JsonInputGrassWaveImpactTimeLineData timeLineData =
                calculationData?.TopLayerData?
                    .FirstOrDefault(tld => tld.TopLayerType == locationData.TopLayerType)?.TimeLineData;
            JsonInputGrassWaveImpactWaveAngleData waveAngleData = calculationData?.WaveAngleData;
            JsonInputGrassWaveImpactLoadingAreaData loadingAreaData = calculationData?.LoadingAreaData;

            return new GrassWaveImpactLocationConstructionProperties(
                locationData.X, ConvertGrassTopLayerType(locationData.TopLayerType))
            {
                InitialDamage = locationData.InitialDamage,
                FailureNumber = calculationData?.FailureNumber,
                TimeLineAgwi = timeLineData?.A,
                TimeLineBgwi = timeLineData?.B,
                TimeLineCgwi = timeLineData?.C,
                MinimumWaveHeightTemax = calculationData?.Temax,
                MaximumWaveHeightTemin = calculationData?.Temin,
                WaveAngleImpactNwa = waveAngleData?.N,
                WaveAngleImpactQwa = waveAngleData?.Q,
                WaveAngleImpactRwa = waveAngleData?.R,
                UpperLimitLoadingAul = loadingAreaData?.UpperLimitData?.LimitLoading,
                LowerLimitLoadingAll = loadingAreaData?.LowerLimitData?.LimitLoading
            };
        }

        private static GrassCumulativeOverloadLocationConstructionProperties CreateGrassWaveRunupLocationConstructionProperties(
            JsonInputGrassCumulativeOverloadLocationData locationData,
            JsonInputGrassWaveRunupCalculationData calculationData)
        {
            GrassCumulativeOverloadLocationConstructionProperties constructionProperties;

            switch (calculationData?.ProtocolData?.ProtocolType)
            {
                case JsonInputGrassWaveRunupProtocolType.RayleighDiscrete:
                    constructionProperties = CreateGrassWaveRunupRayleighDiscreteLocationConstructionProperties(
                        locationData, calculationData.ProtocolData);
                    break;
                default:
                    throw new JsonInputConversionException("Cannot convert protocol type.");
            }

            JsonInputGrassCumulativeOverloadTopLayerData topLayerData =
                calculationData.TopLayerData?.FirstOrDefault(tld => tld.TopLayerType == locationData.TopLayerType);

            constructionProperties.InitialDamage = locationData.InitialDamage;
            constructionProperties.FailureNumber = calculationData.FailureNumber;
            constructionProperties.IncreasedLoadTransitionAlphaM = locationData.IncreasedLoadTransitionAlphaM;
            constructionProperties.ReducedStrengthTransitionAlphaS = locationData.ReducedStrengthTransitionAlphaS;
            constructionProperties.AverageNumberOfWavesCtm = calculationData.FactorCtm;
            constructionProperties.CriticalCumulativeOverload = topLayerData?.CriticalCumulativeOverload;
            constructionProperties.CriticalFrontVelocity = topLayerData?.CriticalFrontVelocity;

            return constructionProperties;
        }

        private static GrassWaveRunupRayleighDiscreteLocationConstructionProperties
            CreateGrassWaveRunupRayleighDiscreteLocationConstructionProperties(
                JsonInputGrassCumulativeOverloadLocationData locationData,
                JsonInputGrassWaveRunupProtocolData protocolData)
        {
            return new GrassWaveRunupRayleighDiscreteLocationConstructionProperties(
                locationData.X, ConvertGrassTopLayerType(locationData.TopLayerType))
            {
                FixedNumberOfWaves = protocolData.FixedNumberOfWaves,
                FrontVelocityCu = protocolData.FrontVelocity
            };
        }

        private static GrassTopLayerType ConvertGrassTopLayerType(JsonInputGrassTopLayerType topLayerType)
        {
            return topLayerType switch
            {
                JsonInputGrassTopLayerType.OpenSod => GrassTopLayerType.OpenSod,
                JsonInputGrassTopLayerType.ClosedSod => GrassTopLayerType.ClosedSod,
                _ => throw new JsonInputConversionException("Cannot convert top layer type.")
            };
        }

        private static NaturalStoneWaveImpactLocationConstructionProperties
            CreateNaturalStoneWaveImpactLocationConstructionProperties(
                JsonInputNaturalStoneWaveImpactLocationData locationData,
                JsonInputNaturalStoneWaveImpactCalculationData calculationData)
        {
            JsonInputNaturalStoneWaveImpactStabilityData stabilityData =
                calculationData?.TopLayerData?
                    .FirstOrDefault(tld => tld.TopLayerType == locationData.TopLayerType)?.StabilityData;
            JsonInputNaturalStoneWaveImpactStabilityCoefficientsData plungingData =
                stabilityData?.PlungingData;
            JsonInputNaturalStoneWaveImpactStabilityCoefficientsData surgingData =
                stabilityData?.SurgingData;
            JsonInputNaturalStoneWaveImpactSlopeData slopeData = calculationData?.SlopeData;
            JsonInputNaturalStoneWaveImpactLoadingAreaData loadingAreaData = calculationData?.LoadingAreaData;
            JsonInputNaturalStoneWaveImpactLimitData upperLimitData = loadingAreaData?.UpperLimitData;
            JsonInputNaturalStoneWaveImpactLimitData lowerLimitData = loadingAreaData?.LowerLimitData;
            JsonInputNaturalStoneWaveImpactMaximumWaveElevationData maximumWaveElevationData =
                calculationData?.MaximumWaveElevationData;
            JsonInputNaturalStoneWaveImpactNormativeWidthData normativeWidthData = calculationData?.NormativeWidthData;

            return new NaturalStoneWaveImpactLocationConstructionProperties(
                locationData.X, ConvertNaturalStoneWaveImpactTopLayerType(locationData.TopLayerType),
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
                SlopeUpperLevelAus = slopeData?.UpperLevel,
                SlopeLowerLevelAls = slopeData?.LowerLevel,
                UpperLimitLoadingAul = upperLimitData?.A,
                UpperLimitLoadingBul = upperLimitData?.B,
                UpperLimitLoadingCul = upperLimitData?.C,
                LowerLimitLoadingAll = lowerLimitData?.A,
                LowerLimitLoadingBll = lowerLimitData?.B,
                LowerLimitLoadingCll = lowerLimitData?.C,
                DistanceMaximumWaveElevationAsmax = maximumWaveElevationData?.A,
                DistanceMaximumWaveElevationBsmax = maximumWaveElevationData?.B,
                NormativeWidthOfWaveImpactAwi = normativeWidthData?.A,
                NormativeWidthOfWaveImpactBwi = normativeWidthData?.B,
                WaveAngleImpactBetamax = calculationData?.WaveAngleData?.BetaMax
            };
        }

        private static NaturalStoneWaveImpactTopLayerType ConvertNaturalStoneWaveImpactTopLayerType(
            JsonInputNaturalStoneWaveImpactTopLayerType topLayerType)
        {
            return topLayerType switch
            {
                JsonInputNaturalStoneWaveImpactTopLayerType.NordicStone => NaturalStoneWaveImpactTopLayerType.NordicStone,
                _ => throw new JsonInputConversionException("Cannot convert top layer type.")
            };
        }
    }
}