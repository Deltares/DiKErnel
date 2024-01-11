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
                case AsphaltRevetmentWaveImpactLocationDependentOutput asphaltRevetmentWaveImpactLocationDependentOutput:
                {
                    IReadOnlyList<AsphaltRevetmentWaveImpactTimeDependentOutput> asphaltRevetmentWaveImpactTimeDependentOutputItems =
                        locationDependentOutput.TimeDependentOutputItems
                                               .Cast<AsphaltRevetmentWaveImpactTimeDependentOutput>()
                                               .ToList();

                    return new JsonOutputAsphaltRevetmentWaveImpactPhysicsLocationData(
                        asphaltRevetmentWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.IncrementDamage).ToList(),
                        asphaltRevetmentWaveImpactLocationDependentOutput.Z,
                        asphaltRevetmentWaveImpactLocationDependentOutput.OuterSlope,
                        asphaltRevetmentWaveImpactLocationDependentOutput.LogFlexuralStrength,
                        asphaltRevetmentWaveImpactLocationDependentOutput.StiffnessRelation,
                        asphaltRevetmentWaveImpactLocationDependentOutput.ComputationalThickness,
                        asphaltRevetmentWaveImpactLocationDependentOutput.EquivalentElasticModulus,
                        asphaltRevetmentWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.MaximumPeakStress).ToList(),
                        asphaltRevetmentWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.AverageNumberOfWaves).ToList());
                }
                case GrassRevetmentOvertoppingLocationDependentOutput _:
                {
                    IReadOnlyList<GrassRevetmentOvertoppingTimeDependentOutput> grassRevetmentOvertoppingTimeDependentOutputItems =
                        locationDependentOutput.TimeDependentOutputItems
                                               .Cast<GrassRevetmentOvertoppingTimeDependentOutput>()
                                               .ToList();

                    return new JsonOutputGrassRevetmentOvertoppingPhysicsLocationData(
                        grassRevetmentOvertoppingTimeDependentOutputItems
                            .Select(tdo => tdo.IncrementDamage).ToList(),
                        grassRevetmentOvertoppingTimeDependentOutputItems
                            .Select(tdo => tdo.VerticalDistanceWaterLevelElevation).ToList(),
                        grassRevetmentOvertoppingTimeDependentOutputItems
                            .Select(tdo => tdo.RepresentativeWaveRunup2P).ToList(),
                        grassRevetmentOvertoppingTimeDependentOutputItems
                            .Select(tdo => tdo.CumulativeOverload).ToList(),
                        grassRevetmentOvertoppingTimeDependentOutputItems
                            .Select(tdo => tdo.AverageNumberOfWaves).ToList());
                }
                case GrassRevetmentWaveImpactLocationDependentOutput grassRevetmentWaveImpactLocationDependentOutput:
                {
                    IReadOnlyList<GrassRevetmentWaveImpactTimeDependentOutput> grassRevetmentWaveImpactTimeDependentOutputItems =
                        locationDependentOutput.TimeDependentOutputItems
                                               .Cast<GrassRevetmentWaveImpactTimeDependentOutput>()
                                               .ToList();

                    return new JsonOutputGrassRevetmentWaveImpactPhysicsLocationData(
                        grassRevetmentWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.IncrementDamage).ToList(),
                        grassRevetmentWaveImpactLocationDependentOutput.Z,
                        grassRevetmentWaveImpactLocationDependentOutput.MinimumWaveHeight,
                        grassRevetmentWaveImpactLocationDependentOutput.MaximumWaveHeight,
                        grassRevetmentWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.LoadingRevetment).ToList(),
                        grassRevetmentWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.UpperLimitLoading).ToList(),
                        grassRevetmentWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.LowerLimitLoading).ToList(),
                        grassRevetmentWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.WaveAngle).ToList(),
                        grassRevetmentWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.WaveAngleImpact).ToList(),
                        grassRevetmentWaveImpactTimeDependentOutputItems
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