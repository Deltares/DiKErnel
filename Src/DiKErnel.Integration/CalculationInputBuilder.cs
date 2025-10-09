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
using DiKErnel.DomainLibrary.Defaults;
using DiKErnel.External.Overtopping;
using DiKErnel.Integration.Data;
using DiKErnel.Integration.Data.AsphaltWaveImpact;
using DiKErnel.Integration.Data.Grass;
using DiKErnel.Integration.Data.GrassWaveImpact;
using DiKErnel.Integration.Data.GrassWaveOvertopping;
using DiKErnel.Integration.Data.GrassWaveRunup;
using DiKErnel.Integration.Data.NaturalStoneWaveImpact;
using DiKErnel.Integration.Factories;
using DiKErnel.Util;
using DiKErnel.Util.Helpers;

namespace DiKErnel.Integration
{
    /// <summary>
    /// Builder to configure and create calculation input.
    /// </summary>
    public class CalculationInputBuilder
    {
        private readonly List<ProfileDataFactoryPoint> profileDataFactoryPoints =
            new List<ProfileDataFactoryPoint>();

        private readonly List<ProfileDataFactorySegment> profileDataFactorySegments =
            new List<ProfileDataFactorySegment>();

        private readonly List<TimeDependentInputFactoryData> timeDependentInputFactoryDataItems =
            new List<TimeDependentInputFactoryData>();

        private readonly List<LocationConstructionProperties> locationConstructionPropertiesItems =
            new List<LocationConstructionProperties>();

        private readonly double dikeOrientation;

        private Foreshore foreshore;

        private bool crestOrInnerSlopeLocationAdded;
        private bool foreshoreDependentLocationAdded;

        /// <summary>
        /// Creates a new instance.
        /// </summary>
        /// <param name="dikeOrientation">The dike orientation.</param>
        public CalculationInputBuilder(double dikeOrientation)
        {
            this.dikeOrientation = dikeOrientation;
        }

        /// <summary>
        /// Adds a dike profile point.
        /// </summary>
        /// <param name="x">The x coordinate.</param>
        /// <param name="characteristicPointType">The characteristic point type.</param>
        public void AddDikeProfilePoint(double x, CharacteristicPointType characteristicPointType)
        {
            profileDataFactoryPoints.Add(new ProfileDataFactoryPoint(x, characteristicPointType));
        }

        /// <summary>
        /// Adds a dike profile segment.
        /// </summary>
        /// <param name="startPointX">The x coordinate for the start profile point.</param>
        /// <param name="startPointZ">The z coordinate for the start profile point.</param>
        /// <param name="endPointX">The x coordinate for the end profile point.</param>
        /// <param name="endPointZ">The z coordinate for the end profile point.</param>
        /// <param name="roughnessCoefficient">The roughness coefficient.</param>
        public void AddDikeProfileSegment(double startPointX, double startPointZ, double endPointX, double endPointZ,
                                          double? roughnessCoefficient = null)
        {
            profileDataFactorySegments.Add(new ProfileDataFactorySegment(startPointX, startPointZ, endPointX, endPointZ,
                                                                         roughnessCoefficient));
        }

        /// <summary>
        /// Adds a foreshore.
        /// </summary>
        /// <param name="slope">The slope of the foreshore.</param>
        /// <param name="bottomZ">The z coordinate at the bottom of the foreshore.</param>
        public void AddForeshore(double slope, double bottomZ)
        {
            foreshore = new Foreshore(slope, bottomZ);
        }

        /// <summary>
        /// Adds a time step.
        /// </summary>
        /// <param name="beginTime">The begin time.</param>
        /// <param name="endTime">The end time.</param>
        /// <param name="waterLevel">The water level.</param>
        /// <param name="waveHeightHm0">The wave height.</param>
        /// <param name="wavePeriodTm10">The wave period.</param>
        /// <param name="waveDirection">The wave direction.</param>
        public void AddTimeStep(double beginTime, double endTime, double waterLevel, double waveHeightHm0,
                                double wavePeriodTm10, double waveDirection)
        {
            timeDependentInputFactoryDataItems.Add(new TimeDependentInputFactoryData(beginTime, endTime, waterLevel,
                                                                                     waveHeightHm0, wavePeriodTm10,
                                                                                     waveDirection));
        }

        /// <summary>
        /// Adds an asphalt wave impact location.
        /// </summary>
        /// <param name="constructionProperties">The properties to construct the asphalt wave
        /// impact location dependent input.</param>
        public void AddAsphaltWaveImpactLocation(AsphaltWaveImpactLocationConstructionProperties constructionProperties)
        {
            AddLocation(constructionProperties);
        }

        /// <summary>
        /// Adds a grass wave overtopping Rayleigh discrete location.
        /// </summary>
        /// <param name="constructionProperties">The properties to construct the grass
        /// wave overtopping Rayleigh discrete location dependent input.</param>
        public void AddGrassWaveOvertoppingRayleighDiscreteLocation(
            GrassWaveOvertoppingRayleighDiscreteLocationConstructionProperties constructionProperties)
        {
            AddLocation(constructionProperties);

            crestOrInnerSlopeLocationAdded = true;
        }

        /// <summary>
        /// Adds a grass wave overtopping Rayleigh analytical location.
        /// </summary>
        /// <param name="constructionProperties">The properties to construct the grass
        /// wave overtopping Rayleigh analytical location dependent input.</param>
        public void AddGrassWaveOvertoppingRayleighAnalyticalLocation(
            GrassWaveOvertoppingRayleighLocationConstructionProperties constructionProperties)
        {
            AddLocation(constructionProperties);

            crestOrInnerSlopeLocationAdded = true;
        }

        /// <summary>
        /// Adds a grass wave impact location.
        /// </summary>
        /// <param name="constructionProperties">The properties to construct the grass wave
        /// impact location dependent input.</param>
        public void AddGrassWaveImpactLocation(GrassWaveImpactLocationConstructionProperties constructionProperties)
        {
            AddLocation(constructionProperties);
        }

        /// <summary>
        /// Adds a grass wave run-up Rayleigh discrete location.
        /// </summary>
        /// <param name="constructionProperties">The properties to construct the grass wave
        /// run-up Rayleigh discrete location dependent input.</param>
        public void AddGrassWaveRunupRayleighDiscreteLocation(
            GrassWaveRunupRayleighDiscreteLocationConstructionProperties constructionProperties)
        {
            AddLocation(constructionProperties);
        }

        /// <summary>
        /// Adds a grass wave run-up Battjes-Groenendijk analytical location.
        /// </summary>
        /// <param name="constructionProperties">The properties to construct the grass wave
        /// run-up Battjes-Groenendijk analytical location dependent input.</param>
        public void AddGrassWaveRunupBattjesGroenendijkAnalyticalLocation(
            GrassWaveRunupBattjesGroenendijkAnalyticalLocationConstructionProperties constructionProperties)
        {
            AddLocation(constructionProperties);

            foreshoreDependentLocationAdded = true;
        }

        /// <summary>
        /// Adds a natural stone wave impact location.
        /// </summary>
        /// <param name="constructionProperties">The properties to construct the natural
        /// stone wave impact location dependent input.</param>
        public void AddNaturalStoneWaveImpactLocation(
            NaturalStoneWaveImpactLocationConstructionProperties constructionProperties)
        {
            AddLocation(constructionProperties);
        }

        /// <summary>
        /// Builds the calculation input.
        /// </summary>
        /// <returns>The result with the created calculation input.</returns>
        public DataResult<ICalculationInput> Build()
        {
            if (!CanBuildValidCalculationInput())
            {
                return new DataResult<ICalculationInput>(EventRegistry.Flush());
            }

            ProfileData profileData = ProfileDataFactory.Create(dikeOrientation, profileDataFactorySegments,
                                                                profileDataFactoryPoints,
                                                                foreshore ?? new Foreshore(double.NaN, double.NaN));
            IReadOnlyList<ILocationDependentInput> locationDependentInputItems =
                LocationDependentInputFactory.Create(locationConstructionPropertiesItems);
            IReadOnlyList<ITimeDependentInput> timeDependentInputItems =
                TimeDependentInputFactory.Create(timeDependentInputFactoryDataItems);

            return new DataResult<ICalculationInput>(new CalculationInput(profileData, locationDependentInputItems,
                                                                          timeDependentInputItems),
                                                     EventRegistry.Flush());
        }

        private void AddLocation(LocationConstructionProperties locationConstructionProperties)
        {
            locationConstructionPropertiesItems.Add(locationConstructionProperties);
        }

        private bool CanBuildValidCalculationInput()
        {
            ProfileDataFactoryPoint outerToe =
                GetProfileDataFactoryPointForCharacteristicPointType(CharacteristicPointType.OuterToe);
            ProfileDataFactoryPoint outerCrest =
                GetProfileDataFactoryPointForCharacteristicPointType(CharacteristicPointType.OuterCrest);
            ProfileDataFactoryPoint innerToe =
                GetProfileDataFactoryPointForCharacteristicPointType(CharacteristicPointType.InnerToe);

            return ValidateProfileSegments()
                   && ValidateCharacteristicPoints(outerToe, outerCrest, innerToe)
                   && ValidateForeshore(foreshoreDependentLocationAdded)
                   && ValidateLocations(outerToe, outerCrest, innerToe)
                   && ValidateTimeSteps();
        }

        private bool ValidateProfileSegments()
        {
            if (profileDataFactorySegments.Count == 0)
            {
                RegisterValidationError("At least 1 profile segment is required.");
                return false;
            }

            ProfileDataFactorySegment previousSegment = null;

            foreach (ProfileDataFactorySegment currentSegment in profileDataFactorySegments)
            {
                if (previousSegment != null)
                {
                    double previousSegmentEndPointX = previousSegment.EndPointX;
                    double previousSegmentEndPointZ = previousSegment.EndPointZ;
                    double currentSegmentStartPointX = currentSegment.StartPointX;
                    double currentSegmentStartPointZ = currentSegment.StartPointZ;

                    if (!NumericsHelper.AreEqual(previousSegmentEndPointX, currentSegmentStartPointX)
                        || !NumericsHelper.AreEqual(previousSegmentEndPointZ, currentSegmentStartPointZ))
                    {
                        RegisterValidationError(
                            "The start point of the profile segment " +
                            $"({NumericsHelper.ToString(currentSegmentStartPointX)}, " +
                            $"{NumericsHelper.ToString(currentSegmentStartPointZ)}) must be equal to the end point " +
                            $"of the previous profile segment ({NumericsHelper.ToString(previousSegmentEndPointX)}, " +
                            $"{NumericsHelper.ToString(previousSegmentEndPointZ)}).");

                        return false;
                    }
                }

                previousSegment = currentSegment;
            }

            return true;
        }

        private bool ValidateCharacteristicPoints(ProfileDataFactoryPoint outerToe, ProfileDataFactoryPoint outerCrest,
                                                  ProfileDataFactoryPoint innerToe)
        {
            ProfileDataFactoryPoint crestOuterBerm =
                GetProfileDataFactoryPointForCharacteristicPointType(CharacteristicPointType.CrestOuterBerm);
            ProfileDataFactoryPoint notchOuterBerm =
                GetProfileDataFactoryPointForCharacteristicPointType(CharacteristicPointType.NotchOuterBerm);
            ProfileDataFactoryPoint innerCrest =
                GetProfileDataFactoryPointForCharacteristicPointType(CharacteristicPointType.InnerCrest);

            return ValidateCharacteristicPoint(outerToe, "outer toe", true)
                   && ValidateCharacteristicPoint(crestOuterBerm, "crest outer berm", false)
                   && ValidateCharacteristicPoint(notchOuterBerm, "notch outer berm", false)
                   && ValidateCharacteristicPoint(outerCrest, "outer crest", true)
                   && ValidateCharacteristicPoint(innerCrest, "inner crest", crestOrInnerSlopeLocationAdded)
                   && ValidateCharacteristicPoint(innerToe, "inner toe", crestOrInnerSlopeLocationAdded);
        }

        private bool ValidateCharacteristicPoint(ProfileDataFactoryPoint characteristicPoint,
                                                 string characteristicPointName, bool isRequired)
        {
            if (characteristicPoint == null)
            {
                if (!isRequired)
                {
                    return true;
                }

                RegisterValidationError($"The {characteristicPointName} is required.");
                return false;
            }

            if (profileDataFactorySegments.Exists(profileSegment => NumericsHelper.AreEqual(profileSegment.StartPointX,
                                                                                            characteristicPoint.X)))
            {
                return true;
            }

            if (NumericsHelper.AreEqual(profileDataFactorySegments[profileDataFactorySegments.Count - 1].EndPointX,
                                        characteristicPoint.X))
            {
                return true;
            }

            RegisterValidationError($"The {characteristicPointName} must be on a start or end point of a profile " +
                                    "segment.");
            return false;
        }

        private bool ValidateForeshore(bool isRequired)
        {
            if (isRequired && foreshore == null)
            {
                RegisterValidationError("Foreshore is required.");
                return false;
            }

            return true;
        }

        private ProfileDataFactoryPoint GetProfileDataFactoryPointForCharacteristicPointType(
            CharacteristicPointType characteristicPointType)
        {
            return profileDataFactoryPoints.Find(profileDataFactoryPoint =>
                                                     profileDataFactoryPoint.CharacteristicPointType == characteristicPointType);
        }

        private bool ValidateLocations(ProfileDataFactoryPoint outerToe, ProfileDataFactoryPoint outerCrest,
                                       ProfileDataFactoryPoint innerToe)
        {
            if (locationConstructionPropertiesItems.Count == 0)
            {
                RegisterValidationError("At least 1 location is required.");
                return false;
            }

            foreach (LocationConstructionProperties locationConstructionProperties in locationConstructionPropertiesItems)
            {
                switch (locationConstructionProperties)
                {
                    case AsphaltWaveImpactLocationConstructionProperties asphaltWaveImpactLocationConstructionProperties
                        when !ValidateAsphaltWaveImpactLocationConstructionProperties(
                                 asphaltWaveImpactLocationConstructionProperties, outerToe, outerCrest):
                    case GrassWaveOvertoppingRayleighLocationConstructionProperties
                        grassWaveOvertoppingRayleighLocationConstructionProperties
                        when !ValidateGrassWaveOvertoppingRayleighLocationConstructionProperties(
                                 grassWaveOvertoppingRayleighLocationConstructionProperties, outerToe, outerCrest,
                                 innerToe):
                    case GrassWaveImpactLocationConstructionProperties grassWaveImpactLocationConstructionProperties
                        when !ValidateGrassWaveImpactLocationConstructionProperties(
                                 grassWaveImpactLocationConstructionProperties, outerToe, outerCrest):
                    case GrassWaveRunupLocationConstructionProperties grassWaveRunupLocationConstructionProperties
                        when !ValidateGrassWaveRunupLocationConstructionProperties(
                                 grassWaveRunupLocationConstructionProperties, outerToe, outerCrest):
                    case NaturalStoneWaveImpactLocationConstructionProperties naturalStoneWaveImpactLocationConstructionProperties
                        when !ValidateNaturalStoneWaveImpactLocationConstructionProperties(
                                 naturalStoneWaveImpactLocationConstructionProperties, outerToe, outerCrest):
                        return false;
                }
            }

            return true;
        }

        private static bool ValidateAsphaltWaveImpactLocationConstructionProperties(
            AsphaltWaveImpactLocationConstructionProperties constructionProperties, ProfileDataFactoryPoint outerToe,
            ProfileDataFactoryPoint outerCrest)
        {
            return ValidateLocationOnOuterSlope(outerToe, outerCrest, constructionProperties.X)
                   && ValidateAsphaltWaveImpactTopLayerType(constructionProperties.TopLayerType,
                                                            constructionProperties.X);
        }

        private bool ValidateGrassWaveOvertoppingRayleighLocationConstructionProperties(
            GrassWaveOvertoppingRayleighLocationConstructionProperties constructionProperties,
            ProfileDataFactoryPoint outerToe, ProfileDataFactoryPoint outerCrest, ProfileDataFactoryPoint innerToe)
        {
            return ValidateLocationOnCrestOrInnerSlope(outerCrest, innerToe, constructionProperties.X)
                   && ValidateGrassTopLayerType(constructionProperties.TopLayerType, constructionProperties.X)
                   && ValidateOvertoppingAdapterProperties(outerToe, outerCrest, constructionProperties.DikeHeight);
        }

        private static bool ValidateGrassWaveImpactLocationConstructionProperties(
            GrassWaveImpactLocationConstructionProperties constructionProperties, ProfileDataFactoryPoint outerToe,
            ProfileDataFactoryPoint outerCrest)
        {
            return ValidateLocationOnOuterSlope(outerToe, outerCrest, constructionProperties.X)
                   && ValidateGrassTopLayerType(constructionProperties.TopLayerType, constructionProperties.X);
        }

        private bool ValidateGrassWaveRunupLocationConstructionProperties(
            GrassWaveRunupLocationConstructionProperties constructionProperties,
            ProfileDataFactoryPoint outerToe, ProfileDataFactoryPoint outerCrest)
        {
            return ValidateLocationOnOuterSlope(outerToe, outerCrest, constructionProperties.X)
                   && ValidateGrassTopLayerType(constructionProperties.TopLayerType, constructionProperties.X)
                   && ValidateOvertoppingAdapterProperties(outerToe, outerCrest);
        }

        private static bool ValidateNaturalStoneWaveImpactLocationConstructionProperties(
            NaturalStoneWaveImpactLocationConstructionProperties constructionProperties,
            ProfileDataFactoryPoint outerToe, ProfileDataFactoryPoint outerCrest)
        {
            return ValidateLocationOnOuterSlope(outerToe, outerCrest, constructionProperties.X)
                   && ValidateNaturalStoneWaveImpactTopLayerType(constructionProperties.TopLayerType,
                                                                 constructionProperties.X);
        }

        private static bool ValidateLocationOnOuterSlope(ProfileDataFactoryPoint outerToe,
                                                         ProfileDataFactoryPoint outerCrest, double locationX)
        {
            if (locationX <= outerToe.X || locationX >= outerCrest.X)
            {
                RegisterValidationError($"The location with position {NumericsHelper.ToString(locationX)} must be " +
                                        "between the outer toe and outer crest.");
                return false;
            }

            return true;
        }

        private static bool ValidateLocationOnCrestOrInnerSlope(ProfileDataFactoryPoint outerCrest,
                                                                ProfileDataFactoryPoint innerToe, double locationX)
        {
            if (locationX < outerCrest.X || locationX > innerToe.X)
            {
                RegisterValidationError($"The location with position {NumericsHelper.ToString(locationX)} must be on " +
                                        "or between the outer crest and inner toe.");
                return false;
            }

            return true;
        }

        private static bool ValidateAsphaltWaveImpactTopLayerType(AsphaltWaveImpactTopLayerType topLayerType,
                                                                  double locationX)
        {
            if (topLayerType != AsphaltWaveImpactTopLayerType.HydraulicAsphaltConcrete)
            {
                RegisterValidationError($"The location with position {NumericsHelper.ToString(locationX)} has an " +
                                        "invalid top layer type.");
                return false;
            }

            return true;
        }

        private static bool ValidateGrassTopLayerType(GrassTopLayerType topLayerType, double locationX)
        {
            if (topLayerType != GrassTopLayerType.ClosedSod
                && topLayerType != GrassTopLayerType.OpenSod)
            {
                RegisterValidationError($"The location with position {NumericsHelper.ToString(locationX)} has an " +
                                        "invalid top layer type.");
                return false;
            }

            return true;
        }

        private static bool ValidateNaturalStoneWaveImpactTopLayerType(NaturalStoneWaveImpactTopLayerType topLayerType,
                                                                       double locationX)
        {
            if (topLayerType != NaturalStoneWaveImpactTopLayerType.NordicStone)
            {
                RegisterValidationError($"The location with position {NumericsHelper.ToString(locationX)} has an " +
                                        "invalid top layer type.");
                return false;
            }

            return true;
        }

        private bool ValidateOvertoppingAdapterProperties(
            ProfileDataFactoryPoint outerToe, ProfileDataFactoryPoint outerCrest, double? dikeHeight = null)
        {
            var xValuesProfile = new List<double>();
            var zValuesProfile = new List<double>();
            var roughnessCoefficients = new List<double>();

            foreach (ProfileDataFactorySegment profileDataFactorySegment in profileDataFactorySegments)
            {
                double startPointX = profileDataFactorySegment.StartPointX;

                if (startPointX >= outerToe.X && startPointX < outerCrest.X)
                {
                    xValuesProfile.Add(startPointX);
                    zValuesProfile.Add(profileDataFactorySegment.StartPointZ);
                    roughnessCoefficients.Add(profileDataFactorySegment.RoughnessCoefficient
                                              ?? ProfileSegmentDefaults.RoughnessCoefficient);

                    double endPointX = profileDataFactorySegment.EndPointX;

                    if (NumericsHelper.AreEqual(endPointX, outerCrest.X))
                    {
                        xValuesProfile.Add(endPointX);
                        zValuesProfile.Add(profileDataFactorySegment.EndPointZ);
                    }
                }
            }

            dikeHeight ??= zValuesProfile[zValuesProfile.Count - 1];

            IReadOnlyList<string> messages = OvertoppingAdapter.Validate(xValuesProfile.ToArray(),
                                                                         zValuesProfile.ToArray(),
                                                                         roughnessCoefficients.ToArray(),
                                                                         dikeHeight.Value, dikeOrientation);
            if (messages.Any())
            {
                foreach (string message in messages)
                {
                    RegisterValidationError(message);
                }

                return false;
            }

            return true;
        }

        private bool ValidateTimeSteps()
        {
            if (timeDependentInputFactoryDataItems.Count == 0)
            {
                RegisterValidationError("At least 1 time step is required.");
                return false;
            }

            TimeDependentInputFactoryData previousTimeDependentInput = null;

            foreach (TimeDependentInputFactoryData currentTimeDependentInput in timeDependentInputFactoryDataItems)
            {
                double currentTimeStepBeginTime = currentTimeDependentInput.BeginTime;

                if (previousTimeDependentInput != null)
                {
                    double previousTimeStepEndTime = previousTimeDependentInput.EndTime;

                    if (!NumericsHelper.AreEqual(previousTimeStepEndTime, currentTimeStepBeginTime))
                    {
                        RegisterValidationError(
                            $"The begin time of the time step ({NumericsHelper.ToString(currentTimeStepBeginTime)}) must " +
                            "be equal to the end time of the previous time step " +
                            $"({NumericsHelper.ToString(previousTimeStepEndTime)}).");
                        return false;
                    }
                }

                double currentTimeStepEndTime = currentTimeDependentInput.EndTime;

                if (currentTimeStepBeginTime >= currentTimeStepEndTime)
                {
                    RegisterValidationError(
                        $"The begin time of the time step ({NumericsHelper.ToString(currentTimeStepBeginTime)}) must be " +
                        $"smaller than the end time of the time step ({NumericsHelper.ToString(currentTimeStepEndTime)}).");
                    return false;
                }

                previousTimeDependentInput = currentTimeDependentInput;
            }

            return true;
        }

        private static void RegisterValidationError(string message)
        {
            EventRegistry.Register(new Event(message, EventType.Error));
        }
    }
}