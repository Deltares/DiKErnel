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
            switch (locationDependentOutput)
            {
                case AsphaltRevetmentWaveImpactLocationDependentOutput asphaltRevetmentWaveImpactLocationDependentOutput:
                {
                    IEnumerable<AsphaltRevetmentWaveImpactTimeDependentOutput> asphaltRevetmentWaveImpactTimeDependentOutputItems =
                        locationDependentOutput.TimeDependentOutputItems.Cast<AsphaltRevetmentWaveImpactTimeDependentOutput>().ToList();

                    return new JsonOutputAsphaltRevetmentWaveImpactPhysicsLocationData(
                        asphaltRevetmentWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.IncrementDamage).ToList(),
                        asphaltRevetmentWaveImpactLocationDependentOutput.Z,
                        asphaltRevetmentWaveImpactLocationDependentOutput.OuterSlope,
                        asphaltRevetmentWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.LogFailureTension).ToList(),
                        asphaltRevetmentWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.MaximumPeakStress).ToList(),
                        asphaltRevetmentWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.StiffnessRelation).ToList(),
                        asphaltRevetmentWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.ComputationalThickness).ToList(),
                        asphaltRevetmentWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.EquivalentElasticModulus).ToList());
                }
                case GrassRevetmentOvertoppingLocationDependentOutput _:
                {
                    IEnumerable<GrassRevetmentOvertoppingTimeDependentOutput> grassRevetmentOvertoppingTimeDependentOutputItems =
                        locationDependentOutput.TimeDependentOutputItems.Cast<GrassRevetmentOvertoppingTimeDependentOutput>().ToList();

                    return new JsonOutputGrassRevetmentOvertoppingPhysicsLocationData(
                        grassRevetmentOvertoppingTimeDependentOutputItems
                            .Select(tdo => tdo.IncrementDamage).ToList(),
                        grassRevetmentOvertoppingTimeDependentOutputItems
                            .Select(tdo => tdo.VerticalDistanceWaterLevelElevation).ToList(),
                        grassRevetmentOvertoppingTimeDependentOutputItems
                            .Select(tdo => tdo.RepresentativeWaveRunup2P).ToList(),
                        grassRevetmentOvertoppingTimeDependentOutputItems
                            .Select(tdo => tdo.CumulativeOverload).ToList());
                }
                case GrassRevetmentWaveImpactLocationDependentOutput grassRevetmentWaveImpactLocationDependentOutput:
                {
                    IEnumerable<GrassRevetmentWaveImpactTimeDependentOutput> grassRevetmentWaveImpactTimeDependentOutputItems =
                        locationDependentOutput.TimeDependentOutputItems.Cast<GrassRevetmentWaveImpactTimeDependentOutput>().ToList();

                    return new JsonOutputGrassRevetmentWaveImpactPhysicsLocationData(
                        grassRevetmentWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.IncrementDamage).ToList(),
                        grassRevetmentWaveImpactLocationDependentOutput.Z,
                        grassRevetmentWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.LoadingRevetment).ToList(),
                        grassRevetmentWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.UpperLimitLoading).ToList(),
                        grassRevetmentWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.LowerLimitLoading).ToList(),
                        grassRevetmentWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.MinimumWaveHeight).ToList(),
                        grassRevetmentWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.MaximumWaveHeight).ToList(),
                        grassRevetmentWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.WaveAngleImpact).ToList(),
                        grassRevetmentWaveImpactTimeDependentOutputItems
                            .Select(tdo => tdo.WaveHeightImpact).ToList());
                }
                case GrassRevetmentWaveRunupRayleighLocationDependentOutput grassRevetmentWaveRunupRayleighLocationDependentOutput:
                {
                    IEnumerable<GrassRevetmentWaveRunupRayleighTimeDependentOutput>
                        grassRevetmentWaveRunupRayleighTimeDependentOutputItems =
                            locationDependentOutput.TimeDependentOutputItems.Cast<GrassRevetmentWaveRunupRayleighTimeDependentOutput>()
                                                   .ToList();

                    return new JsonOutputGrassRevetmentWaveRunupRayleighPhysicsLocationData(
                        grassRevetmentWaveRunupRayleighTimeDependentOutputItems
                            .Select(tdo => tdo.IncrementDamage).ToList(),
                        grassRevetmentWaveRunupRayleighLocationDependentOutput.Z,
                        grassRevetmentWaveRunupRayleighTimeDependentOutputItems
                            .Select(tdo => tdo.VerticalDistanceWaterLevelElevation).ToList(),
                        grassRevetmentWaveRunupRayleighTimeDependentOutputItems
                            .Select(tdo => tdo.WaveAngleImpact).ToList(),
                        grassRevetmentWaveRunupRayleighTimeDependentOutputItems
                            .Select(tdo => tdo.RepresentativeWaveRunup2P).ToList(),
                        grassRevetmentWaveRunupRayleighTimeDependentOutputItems
                            .Select(tdo => tdo.CumulativeOverload).ToList());
                }
                case NaturalStoneRevetmentLocationDependentOutput naturalStoneRevetmentLocationDependentOutput:
                {
                    IEnumerable<NaturalStoneRevetmentTimeDependentOutput> naturalStoneRevetmentTimeDependentOutputItems =
                        locationDependentOutput.TimeDependentOutputItems.Cast<NaturalStoneRevetmentTimeDependentOutput>().ToList();

                    return new JsonOutputNaturalStoneRevetmentPhysicsLocationData(
                        naturalStoneRevetmentTimeDependentOutputItems
                            .Select(tdo => tdo.IncrementDamage).ToList(),
                        naturalStoneRevetmentLocationDependentOutput.Z,
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
                            .Select(tdo => tdo.WaveAngleImpact).ToList(),
                        naturalStoneRevetmentTimeDependentOutputItems
                            .Select(tdo => tdo.Resistance).ToList(),
                        naturalStoneRevetmentTimeDependentOutputItems
                            .Select(tdo => tdo.ReferenceTimeDegradation).ToList(),
                        naturalStoneRevetmentTimeDependentOutputItems
                            .Select(tdo => tdo.ReferenceDegradation).ToList());
                }
                default:
                    throw new JsonOutputCreationException("Invalid revetment type.");
            }
        }
    }
}