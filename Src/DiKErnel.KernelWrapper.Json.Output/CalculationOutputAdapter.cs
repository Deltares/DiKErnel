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
using DiKErnel.Integration.Data.GrassWaveImpact;
using DiKErnel.Integration.Data.GrassWaveOvertopping;
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

                    return new JsonOutputAsphaltWaveImpactPhysicsLocationData(
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
                case GrassWaveOvertoppingRayleighDiscreteLocationDependentOutput _:
                {
                    IReadOnlyList<GrassWaveOvertoppingRayleighDiscreteTimeDependentOutput>
                        grassWaveOvertoppingRayleighDiscreteTimeDependentOutputItems =
                            locationDependentOutput.TimeDependentOutputItems
                                                   .Cast<GrassWaveOvertoppingRayleighDiscreteTimeDependentOutput>()
                                                   .ToList();

                    return new JsonOutputGrassOvertoppingRayleighDiscretePhysicsLocationData(
                        grassWaveOvertoppingRayleighDiscreteTimeDependentOutputItems
                            .Select(tdo => tdo.IncrementDamage).ToList(),
                        grassWaveOvertoppingRayleighDiscreteTimeDependentOutputItems
                            .Select(tdo => tdo.VerticalDistanceWaterLevelElevation).ToList(),
                        grassWaveOvertoppingRayleighDiscreteTimeDependentOutputItems
                            .Select(tdo => tdo.RepresentativeWaveRunup2P).ToList(),
                        grassWaveOvertoppingRayleighDiscreteTimeDependentOutputItems
                            .Select(tdo => tdo.CumulativeOverload).ToList(),
                        grassWaveOvertoppingRayleighDiscreteTimeDependentOutputItems
                            .Select(tdo => tdo.AverageNumberOfWaves).ToList());
                }
                case GrassWaveImpactLocationDependentOutput grassWaveImpactLocationDependentOutput:
                {
                    IReadOnlyList<GrassWaveImpactTimeDependentOutput> grassWaveImpactTimeDependentOutputItems =
                        locationDependentOutput.TimeDependentOutputItems
                                               .Cast<GrassWaveImpactTimeDependentOutput>()
                                               .ToList();

                    return new JsonOutputGrassWaveImpactPhysicsLocationData(
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
                case GrassWaveRunupRayleighDiscreteLocationDependentOutput grassWaveRunupRayleighDiscreteLocationDependentOutput:
                {
                    IReadOnlyList<GrassWaveRunupRayleighDiscreteTimeDependentOutput>
                        grassWaveRunupRayleighDiscreteTimeDependentOutputItems =
                            locationDependentOutput.TimeDependentOutputItems
                                                   .Cast<GrassWaveRunupRayleighDiscreteTimeDependentOutput>()
                                                   .ToList();

                    return new JsonOutputGrassWaveRunupRayleighDiscretePhysicsLocationData(
                        grassWaveRunupRayleighDiscreteTimeDependentOutputItems
                            .Select(tdo => tdo.IncrementDamage).ToList(),
                        grassWaveRunupRayleighDiscreteLocationDependentOutput.Z,
                        grassWaveRunupRayleighDiscreteTimeDependentOutputItems
                            .Select(tdo => tdo.VerticalDistanceWaterLevelElevation).ToList(),
                        grassWaveRunupRayleighDiscreteTimeDependentOutputItems
                            .Select(tdo => tdo.RepresentativeWaveRunup2P).ToList(),
                        grassWaveRunupRayleighDiscreteTimeDependentOutputItems
                            .Select(tdo => tdo.CumulativeOverload).ToList(),
                        grassWaveRunupRayleighDiscreteTimeDependentOutputItems
                            .Select(tdo => tdo.AverageNumberOfWaves).ToList());
                }
                case NaturalStoneWaveImpactLocationDependentOutput naturalStoneWaveImpactLocationDependentOutput:
                {
                    IReadOnlyList<NaturalStoneWaveImpactTimeDependentOutput> naturalStoneWaveImpactTimeDependentOutputItems =
                        locationDependentOutput.TimeDependentOutputItems
                                               .Cast<NaturalStoneWaveImpactTimeDependentOutput>()
                                               .ToList();

                    return new JsonOutputNaturalStoneWaveImpactPhysicsLocationData(
                        naturalStoneWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.IncrementDamage).ToList(),
                        naturalStoneWaveImpactLocationDependentOutput.Z,
                        naturalStoneWaveImpactLocationDependentOutput.Resistance,
                        naturalStoneWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.OuterSlope).ToList(),
                        naturalStoneWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.SlopeUpperLevel).ToList(),
                        naturalStoneWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.SlopeUpperPosition).ToList(),
                        naturalStoneWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.SlopeLowerLevel).ToList(),
                        naturalStoneWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.SlopeLowerPosition).ToList(),
                        naturalStoneWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.LoadingRevetment).ToList(),
                        naturalStoneWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.SurfSimilarityParameter).ToList(),
                        naturalStoneWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.WaveSteepnessDeepWater).ToList(),
                        naturalStoneWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.UpperLimitLoading).ToList(),
                        naturalStoneWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.LowerLimitLoading).ToList(),
                        naturalStoneWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.DepthMaximumWaveLoad).ToList(),
                        naturalStoneWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.DistanceMaximumWaveElevation).ToList(),
                        naturalStoneWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.NormativeWidthOfWaveImpact).ToList(),
                        naturalStoneWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.HydraulicLoad).ToList(),
                        naturalStoneWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.WaveAngle).ToList(),
                        naturalStoneWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.WaveAngleImpact).ToList(),
                        naturalStoneWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.ReferenceTimeDegradation).ToList(),
                        naturalStoneWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.ReferenceDegradation).ToList());
                }
                default:
                    throw new JsonOutputConversionException("Invalid revetment type.");
            }
        }
    }
}