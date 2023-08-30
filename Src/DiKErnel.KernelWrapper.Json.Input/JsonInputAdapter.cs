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
            return calculationDataItems.FirstOrDefault(cd => cd.CalculationMethodType == calculationType) as T;
        }

        private static AsphaltRevetmentWaveImpactLocationConstructionProperties
            CreateAsphaltWaveImpactConstructionProperties(
                JsonInputAsphaltWaveImpactLocationData location,
                JsonInputAsphaltWaveImpactCalculationData calculationDefinition)
        {
            var constructionProperties = new AsphaltRevetmentWaveImpactLocationConstructionProperties(
                location.X, ConvertTopLayerType(location.TopLayerType), location.FailureTension,
                location.SoilElasticity, location.UpperLayer.ThicknessLayer, location.UpperLayer.ElasticModulusLayer)
            {
                InitialDamage = location.InitialDamage,
                ThicknessSubLayer = location.SubLayerData?.ThicknessLayer,
                ElasticModulusSubLayer = location.SubLayerData?.ElasticModulusLayer
            };

            if (calculationDefinition != null)
            {
                constructionProperties.FailureNumber = calculationDefinition.FailureNumber;
                constructionProperties.DensityOfWater = calculationDefinition.DensityOfWater;
                constructionProperties.AverageNumberOfWavesCtm = calculationDefinition.FactorCtm;

                JsonInputAsphaltWaveImpactTopLayerData topLayerDefinition =
                    calculationDefinition.TopLayerDefinitionData
                                         .FirstOrDefault(tldd => tldd.TopLayerType == location.TopLayerType);

                if (topLayerDefinition != null)
                {
                    constructionProperties.FatigueAlpha = topLayerDefinition.Fatigue?.FatigueAlpha;
                    constructionProperties.FatigueBeta = topLayerDefinition.Fatigue?.FatigueBeta;
                    constructionProperties.StiffnessRelationNu = topLayerDefinition.StiffnessRelationNu;
                }

                constructionProperties.ImpactNumberC = calculationDefinition.ImpactNumberC;

                constructionProperties.WidthFactors =
                    calculationDefinition.WidthFactors
                                         .Select(widthFactor => (widthFactor[0], widthFactor[1])).ToList();

                constructionProperties.DepthFactors =
                    calculationDefinition.DepthFactors
                                         .Select(depthFactor => (depthFactor[0], depthFactor[1])).ToList();

                constructionProperties.ImpactFactors =
                    calculationDefinition.ImpactFactors
                                         .Select(impactFactor => (impactFactor[0], impactFactor[1])).ToList();
            }

            return constructionProperties;
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
                JsonInputGrassOvertoppingLocationData location,
                JsonInputGrassOvertoppingCalculationData calculationDefinition)
        {
            JsonInputGrassRevetmentTopLayerType jsonInputTopLayerType = location.TopLayerType;
            var constructionProperties = new GrassRevetmentOvertoppingLocationConstructionProperties(
                location.X, ConvertTopLayerType(jsonInputTopLayerType))
            {
                InitialDamage = location.InitialDamage,
                IncreasedLoadTransitionAlphaM = location.IncreasedLoadTransitionAlphaM,
                ReducedStrengthTransitionAlphaS = location.ReducedStrengthTransitionAlphaS
            };

            if (calculationDefinition != null)
            {
                constructionProperties.FailureNumber = calculationDefinition.FailureNumber;

                JsonInputGrassCumulativeOverloadTopLayerData topLayerDefinition =
                    calculationDefinition.TopLayerDefinitionData
                                         .FirstOrDefault(tldd => tldd.TopLayerType == location.TopLayerType);

                if (topLayerDefinition != null)
                {
                    constructionProperties.CriticalCumulativeOverload = topLayerDefinition.CriticalCumulativeOverload;
                    constructionProperties.CriticalFrontVelocity = topLayerDefinition.CriticalFrontVelocity;
                }

                constructionProperties.DikeHeight = calculationDefinition.DikeHeight;
                constructionProperties.AccelerationAlphaAForCrest =
                    calculationDefinition.AccelerationAlphaAData?.AccelerationAlphaAForCrest;
                constructionProperties.AccelerationAlphaAForInnerSlope =
                    calculationDefinition.AccelerationAlphaAData?.AccelerationAlphaAForInnerSlope;
                constructionProperties.FixedNumberOfWaves = calculationDefinition.FixedNumberOfWaves;
                constructionProperties.FrontVelocityCwo = calculationDefinition.FrontVelocity;
                constructionProperties.AverageNumberOfWavesCtm = calculationDefinition.FactorCtm;
            }

            return constructionProperties;
        }

        private static GrassRevetmentWaveImpactLocationConstructionProperties
            CreateGrassWaveImpactConstructionProperties(
                JsonInputGrassWaveImpactLocationData location,
                JsonInputGrassWaveImpactCalculationData calculationDefinition)
        {
            var constructionProperties = new GrassRevetmentWaveImpactLocationConstructionProperties(
                location.X, ConvertTopLayerType(location.TopLayerType))
            {
                InitialDamage = location.InitialDamage
            };

            if (calculationDefinition != null)
            {
                constructionProperties.FailureNumber = calculationDefinition.FailureNumber;

                JsonInputGrassWaveImpactTopLayerData topLayerDefinition =
                    calculationDefinition.TopLayerDefinitionData
                                         .FirstOrDefault(tldd => tldd.TopLayerType == location.TopLayerType);

                if (topLayerDefinition != null)
                {
                    constructionProperties.TimeLineAgwi = topLayerDefinition.TimeLine?.TimeLineA;
                    constructionProperties.TimeLineBgwi = topLayerDefinition.TimeLine?.TimeLineB;
                    constructionProperties.TimeLineCgwi = topLayerDefinition.TimeLine?.TimeLineC;
                }

                constructionProperties.MinimumWaveHeightTemax = calculationDefinition.Temax;
                constructionProperties.MaximumWaveHeightTemin = calculationDefinition.Temin;

                constructionProperties.WaveAngleImpactNwa = calculationDefinition.WaveAngleData?.WaveAngleImpactN;
                constructionProperties.WaveAngleImpactQwa = calculationDefinition.WaveAngleData?.WaveAngleImpactQ;
                constructionProperties.WaveAngleImpactRwa = calculationDefinition.WaveAngleData?.WaveAngleImpactR;

                constructionProperties.UpperLimitLoadingAul =
                    calculationDefinition.LoadingAreaData?.UpperLimit?.LimitLoading;
                constructionProperties.LowerLimitLoadingAll =
                    calculationDefinition.LoadingAreaData?.LowerLimit?.LimitLoading;
            }

            return constructionProperties;
        }

        private static GrassRevetmentWaveRunupLocationConstructionProperties CreateGrassWaveRunupConstructionProperties(
            JsonInputGrassWaveRunupLocationData location, JsonInputGrassWaveRunupCalculationData calculationDefinition)
        {
            if (calculationDefinition?.CalculationProtocolData == null)
            {
                throw new JsonInputConversionException("Cannot convert calculation protocol type.");
            }

            GrassRevetmentWaveRunupLocationConstructionProperties constructionProperties;

            if (calculationDefinition.CalculationProtocolData.CalculationProtocolType ==
                JsonInputGrassWaveRunupCalculationProtocolType.RayleighDiscrete)
            {
                constructionProperties =
                    CreateGrassWaveRunupRayleighConstructionProperties(
                        location, calculationDefinition.CalculationProtocolData);
            }
            else
            {
                throw new JsonInputConversionException("Cannot convert calculation protocol type.");
            }

            constructionProperties.InitialDamage = location.InitialDamage;
            constructionProperties.FailureNumber = calculationDefinition.FailureNumber;

            constructionProperties.IncreasedLoadTransitionAlphaM = location.IncreasedLoadTransitionAlphaM;
            constructionProperties.ReducedStrengthTransitionAlphaS = location.ReducedStrengthTransitionAlphaS;
            constructionProperties.RepresentativeWaveRunup2PGammab = location.RepresentativeWaveRunup2PGammaB;
            constructionProperties.RepresentativeWaveRunup2PGammaf = location.RepresentativeWaveRunup2PGammaF;

            constructionProperties.AverageNumberOfWavesCtm = calculationDefinition.FactorCtm;
            constructionProperties.RepresentativeWaveRunup2PAru =
                calculationDefinition.JsonInputGrassWaveRunupCalculationRepresentativeWaveRunupData?.RepresentativeWaveRunup2Pa;
            constructionProperties.RepresentativeWaveRunup2PBru =
                calculationDefinition.JsonInputGrassWaveRunupCalculationRepresentativeWaveRunupData?.RepresentativeWaveRunup2Pb;
            constructionProperties.RepresentativeWaveRunup2PCru =
                calculationDefinition.JsonInputGrassWaveRunupCalculationRepresentativeWaveRunupData?.RepresentativeWaveRunup2Pc;
            constructionProperties.WaveAngleImpactAbeta =
                calculationDefinition.JsonInputGrassWaveRunupCalculationImpactAngleData?.WaveAngleImpactABeta;
            constructionProperties.WaveAngleImpactBetamax =
                calculationDefinition.JsonInputGrassWaveRunupCalculationImpactAngleData?.WaveAngleImpactBetaMax;

            JsonInputGrassCumulativeOverloadTopLayerData topLayerDefinition =
                calculationDefinition.TopLayerDefinitionData
                                     .FirstOrDefault(tldd => tldd.TopLayerType == location.TopLayerType);

            if (topLayerDefinition != null)
            {
                constructionProperties.CriticalCumulativeOverload = topLayerDefinition.CriticalCumulativeOverload;
                constructionProperties.CriticalFrontVelocity = topLayerDefinition.CriticalFrontVelocity;
            }

            return constructionProperties;
        }

        private static GrassRevetmentWaveRunupRayleighLocationConstructionProperties
            CreateGrassWaveRunupRayleighConstructionProperties(
                JsonInputGrassWaveRunupLocationData location,
                JsonInputGrassWaveRunupCalculationProtocolData calculationProtocol)
        {
            return new GrassRevetmentWaveRunupRayleighLocationConstructionProperties(
                location.X, location.OuterSlope, ConvertTopLayerType(location.TopLayerType))
            {
                FixedNumberOfWaves = calculationProtocol.FixedNumberOfWaves,
                FrontVelocityCu = calculationProtocol.FrontVelocity
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
            JsonInputNaturalStoneLocationData location, JsonInputNaturalStoneCalculationData calculationDefinition)
        {
            var constructionProperties = new NaturalStoneRevetmentLocationConstructionProperties(
                location.X, ConvertTopLayerType(location.TopLayerType), location.ThicknessTopLayer,
                location.RelativeDensity)
            {
                InitialDamage = location.InitialDamage
            };

            if (calculationDefinition != null)
            {
                constructionProperties.FailureNumber = calculationDefinition.FailureNumber;

                JsonInputNaturalStoneTopLayerData topLayerDefinition =
                    calculationDefinition.TopLayerDefinitionData
                                         .FirstOrDefault(tldd => tldd.TopLayerType == location.TopLayerType);

                if (topLayerDefinition != null)
                {
                    constructionProperties.HydraulicLoadAp =
                        topLayerDefinition.Stability?.JsonInputNaturalStoneTopLayerNorseStoneStabilityCoefficientsData?.A;
                    constructionProperties.HydraulicLoadBp =
                        topLayerDefinition.Stability?.JsonInputNaturalStoneTopLayerNorseStoneStabilityCoefficientsData?.B;
                    constructionProperties.HydraulicLoadCp =
                        topLayerDefinition.Stability?.JsonInputNaturalStoneTopLayerNorseStoneStabilityCoefficientsData?.C;
                    constructionProperties.HydraulicLoadNp =
                        topLayerDefinition.Stability?.JsonInputNaturalStoneTopLayerNorseStoneStabilityCoefficientsData?.N;
                    constructionProperties.HydraulicLoadAs =
                        topLayerDefinition.Stability?.JsonInputNaturalStoneTopLayerNorseStoneSurgingData?.A;
                    constructionProperties.HydraulicLoadBs =
                        topLayerDefinition.Stability?.JsonInputNaturalStoneTopLayerNorseStoneSurgingData?.B;
                    constructionProperties.HydraulicLoadCs =
                        topLayerDefinition.Stability?.JsonInputNaturalStoneTopLayerNorseStoneSurgingData?.C;
                    constructionProperties.HydraulicLoadNs =
                        topLayerDefinition.Stability?.JsonInputNaturalStoneTopLayerNorseStoneSurgingData?.N;
                    constructionProperties.HydraulicLoadXib = topLayerDefinition.Stability?.StabilityXib;
                }

                constructionProperties.SlopeUpperLevelAus = calculationDefinition.Slope?.SlopeUpperLevel;
                constructionProperties.SlopeLowerLevelAls = calculationDefinition.Slope?.SlopeLowerLevel;

                constructionProperties.UpperLimitLoadingAul = calculationDefinition.LoadingArea?.UpperLimitLoading?.A;
                constructionProperties.UpperLimitLoadingBul = calculationDefinition.LoadingArea?.UpperLimitLoading?.B;
                constructionProperties.UpperLimitLoadingCul = calculationDefinition.LoadingArea?.UpperLimitLoading?.C;

                constructionProperties.LowerLimitLoadingAll = calculationDefinition.LoadingArea?.LowerLimitLoading?.A;
                constructionProperties.LowerLimitLoadingBll = calculationDefinition.LoadingArea?.LowerLimitLoading?.B;
                constructionProperties.LowerLimitLoadingCll = calculationDefinition.LoadingArea?.LowerLimitLoading?.C;

                constructionProperties.DistanceMaximumWaveElevationAsmax =
                    calculationDefinition.DistanceMaximumWaveElevation?.DistanceMaximumWaveElevationA;
                constructionProperties.DistanceMaximumWaveElevationBsmax =
                    calculationDefinition.DistanceMaximumWaveElevation?.DistanceMaximumWaveElevationB;

                constructionProperties.NormativeWidthOfWaveImpactAwi =
                    calculationDefinition.NormativeWidthOfWaveImpact?.NormativeWidthOfWaveImpactA;
                constructionProperties.NormativeWidthOfWaveImpactBwi =
                    calculationDefinition.NormativeWidthOfWaveImpact?.NormativeWidthOfWaveImpactB;

                constructionProperties.WaveAngleImpactBetamax =
                    calculationDefinition.WaveAngleImpact?.WaveAngleImpactBetaMax;
            }

            return constructionProperties;
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