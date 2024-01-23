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
using DiKErnel.Core.Extensions;
using DiKErnel.Integration.Data.AsphaltWaveImpact;
using DiKErnel.Integration.Data.GrassOvertopping;
using DiKErnel.Integration.Data.GrassWaveImpact;
using DiKErnel.Integration.Data.GrassWaveRunup;
using DiKErnel.Integration.Data.NaturalStoneWaveImpact;
using DiKErnel.KernelWrapper.Json.Output.Data.Generic;
using DiKErnel.KernelWrapper.Json.Output.Data.Revetment;
using DiKErnel.KernelWrapper.Json.Output.Exceptions;

namespace DiKErnel.KernelWrapper.Json.Output
{
    internal static class CalculationOutputAdapter
    {
        public static JsonOutputData AdaptCalculationOutput(
            CalculationOutput calculationOutput, JsonOutputType outputType)
        {
            return new JsonOutputData(CreateLocations(calculationOutput.LocationDependentOutputItems, outputType));
        }

        private static JsonOutputLocationsObject CreateLocations(
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
            var locationData = new JsonOutputLocationData(CreateFailureLocationData(locationDependentOutput));

            if (outputType != JsonOutputType.Failure)
            {
                locationData.DamageData = CreateDamageLocationData(locationDependentOutput);
            }

            if (outputType == JsonOutputType.Physics)
            {
                locationData.PhysicsData = CreatePhysicsLocationData(locationDependentOutput);
            }

            return locationData;
        }

        private static JsonOutputFailureLocationData CreateFailureLocationData(
            LocationDependentOutput locationDependentOutput)
        {
            return new JsonOutputFailureLocationData(locationDependentOutput.GetTimeOfFailure());
        }

        private static JsonOutputDamageLocationData CreateDamageLocationData(
            LocationDependentOutput locationDependentOutput)
        {
            return new JsonOutputDamageLocationData(locationDependentOutput.GetDamages());
        }

        private static JsonOutputPhysicsLocationData CreatePhysicsLocationData(
            LocationDependentOutput locationDependentOutput)
        {
            switch (locationDependentOutput)
            {
                case AsphaltWaveImpactLocationDependentOutput asphaltWaveImpactLocationDependentOutput:
                {
                    IReadOnlyList<AsphaltWaveImpactTimeDependentOutput> asphaltWaveImpactTimeDependentOutputItems =
                        locationDependentOutput.TimeDependentOutputItems
                                               .Cast<AsphaltWaveImpactTimeDependentOutput>()
                                               .ToList();

                    return new JsonOutputAsphaltRevetmentWaveImpactPhysicsLocationData(
                        asphaltWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.IncrementDamage).ToList(),
                        asphaltWaveImpactLocationDependentOutput.Z,
                        asphaltWaveImpactLocationDependentOutput.OuterSlope,
                        asphaltWaveImpactLocationDependentOutput.LogFlexuralStrength,
                        asphaltWaveImpactLocationDependentOutput.StiffnessRelation,
                        asphaltWaveImpactLocationDependentOutput.ComputationalThickness,
                        asphaltWaveImpactLocationDependentOutput.EquivalentElasticModulus,
                        asphaltWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.MaximumPeakStress).ToList(),
                        asphaltWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.AverageNumberOfWaves).ToList());
                }
                case GrassOvertoppingRayleighDiscreteLocationDependentOutput _:
                {
                    IReadOnlyList<GrassOvertoppingRayleighDiscreteTimeDependentOutput>
                        grassOvertoppingRayleighDiscreteTimeDependentOutputItems =
                            locationDependentOutput.TimeDependentOutputItems
                                                   .Cast<GrassOvertoppingRayleighDiscreteTimeDependentOutput>()
                                                   .ToList();

                    return new JsonOutputGrassRevetmentOvertoppingPhysicsLocationData(
                        grassOvertoppingRayleighDiscreteTimeDependentOutputItems
                            .Select(tdo => tdo.IncrementDamage).ToList(),
                        grassOvertoppingRayleighDiscreteTimeDependentOutputItems
                            .Select(tdo => tdo.VerticalDistanceWaterLevelElevation).ToList(),
                        grassOvertoppingRayleighDiscreteTimeDependentOutputItems
                            .Select(tdo => tdo.RepresentativeWaveRunup2P).ToList(),
                        grassOvertoppingRayleighDiscreteTimeDependentOutputItems
                            .Select(tdo => tdo.CumulativeOverload).ToList(),
                        grassOvertoppingRayleighDiscreteTimeDependentOutputItems
                            .Select(tdo => tdo.AverageNumberOfWaves).ToList());
                }
                case GrassWaveImpactLocationDependentOutput grassWaveImpactLocationDependentOutput:
                {
                    IReadOnlyList<GrassWaveImpactTimeDependentOutput> grassWaveImpactTimeDependentOutputItems =
                        locationDependentOutput.TimeDependentOutputItems
                                               .Cast<GrassWaveImpactTimeDependentOutput>()
                                               .ToList();

                    return new JsonOutputGrassRevetmentWaveImpactPhysicsLocationData(
                        grassWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.IncrementDamage).ToList(),
                        grassWaveImpactLocationDependentOutput.Z,
                        grassWaveImpactLocationDependentOutput.MinimumWaveHeight,
                        grassWaveImpactLocationDependentOutput.MaximumWaveHeight,
                        grassWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.LoadingRevetment).ToList(),
                        grassWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.UpperLimitLoading).ToList(),
                        grassWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.LowerLimitLoading).ToList(),
                        grassWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.WaveAngle).ToList(),
                        grassWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.WaveAngleImpact).ToList(),
                        grassWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.WaveHeightImpact).ToList());
                }
                case GrassRevetmentWaveRunupRayleighLocationDependentOutput grassRevetmentWaveRunupRayleighLocationDependentOutput:
                {
                    IReadOnlyList<GrassRevetmentWaveRunupRayleighTimeDependentOutput>
                        grassRevetmentWaveRunupRayleighTimeDependentOutputItems =
                            locationDependentOutput.TimeDependentOutputItems
                                                   .Cast<GrassRevetmentWaveRunupRayleighTimeDependentOutput>()
                                                   .ToList();

                    return new JsonOutputGrassRevetmentWaveRunupRayleighPhysicsLocationData(
                        grassRevetmentWaveRunupRayleighTimeDependentOutputItems
                            .Select(tdo => tdo.IncrementDamage).ToList(),
                        grassRevetmentWaveRunupRayleighLocationDependentOutput.Z,
                        grassRevetmentWaveRunupRayleighTimeDependentOutputItems
                            .Select(tdo => tdo.VerticalDistanceWaterLevelElevation).ToList(),
                        grassRevetmentWaveRunupRayleighTimeDependentOutputItems
                            .Select(tdo => tdo.RepresentativeWaveRunup2P).ToList(),
                        grassRevetmentWaveRunupRayleighTimeDependentOutputItems
                            .Select(tdo => tdo.CumulativeOverload).ToList(),
                        grassRevetmentWaveRunupRayleighTimeDependentOutputItems
                            .Select(tdo => tdo.AverageNumberOfWaves).ToList());
                }
                case NaturalStoneRevetmentLocationDependentOutput naturalStoneRevetmentLocationDependentOutput:
                {
                    IReadOnlyList<NaturalStoneRevetmentTimeDependentOutput> naturalStoneRevetmentTimeDependentOutputItems =
                        locationDependentOutput.TimeDependentOutputItems
                                               .Cast<NaturalStoneRevetmentTimeDependentOutput>()
                                               .ToList();

                    return new JsonOutputNaturalStoneRevetmentPhysicsLocationData(
                        naturalStoneRevetmentTimeDependentOutputItems
                            .Select(tdo => tdo.IncrementDamage).ToList(),
                        naturalStoneRevetmentLocationDependentOutput.Z,
                        naturalStoneRevetmentLocationDependentOutput.Resistance,
                        naturalStoneRevetmentTimeDependentOutputItems
                            .Select(tdo => tdo.OuterSlope).ToList(),
                        naturalStoneRevetmentTimeDependentOutputItems
                            .Select(tdo => tdo.SlopeUpperLevel).ToList(),
                        naturalStoneRevetmentTimeDependentOutputItems
                            .Select(tdo => tdo.SlopeUpperPosition).ToList(),
                        naturalStoneRevetmentTimeDependentOutputItems
                            .Select(tdo => tdo.SlopeLowerLevel).ToList(),
                        naturalStoneRevetmentTimeDependentOutputItems
                            .Select(tdo => tdo.SlopeLowerPosition).ToList(),
                        naturalStoneRevetmentTimeDependentOutputItems
                            .Select(tdo => tdo.LoadingRevetment).ToList(),
                        naturalStoneRevetmentTimeDependentOutputItems
                            .Select(tdo => tdo.SurfSimilarityParameter).ToList(),
                        naturalStoneRevetmentTimeDependentOutputItems
                            .Select(tdo => tdo.WaveSteepnessDeepWater).ToList(),
                        naturalStoneRevetmentTimeDependentOutputItems
                            .Select(tdo => tdo.UpperLimitLoading).ToList(),
                        naturalStoneRevetmentTimeDependentOutputItems
                            .Select(tdo => tdo.LowerLimitLoading).ToList(),
                        naturalStoneRevetmentTimeDependentOutputItems
                            .Select(tdo => tdo.DepthMaximumWaveLoad).ToList(),
                        naturalStoneRevetmentTimeDependentOutputItems
                            .Select(tdo => tdo.DistanceMaximumWaveElevation).ToList(),
                        naturalStoneRevetmentTimeDependentOutputItems
                            .Select(tdo => tdo.NormativeWidthOfWaveImpact).ToList(),
                        naturalStoneRevetmentTimeDependentOutputItems
                            .Select(tdo => tdo.HydraulicLoad).ToList(),
                        naturalStoneRevetmentTimeDependentOutputItems
                            .Select(tdo => tdo.WaveAngle).ToList(),
                        naturalStoneRevetmentTimeDependentOutputItems
                            .Select(tdo => tdo.WaveAngleImpact).ToList(),
                        naturalStoneRevetmentTimeDependentOutputItems
                            .Select(tdo => tdo.ReferenceTimeDegradation).ToList(),
                        naturalStoneRevetmentTimeDependentOutputItems
                            .Select(tdo => tdo.ReferenceDegradation).ToList());
                }
                default:
                    throw new JsonOutputConversionException("Invalid revetment type.");
            }
        }
    }
}