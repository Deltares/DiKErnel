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
using DiKErnel.Integration.Data.AsphaltRevetmentWaveImpact;
using DiKErnel.Integration.Data.GrassRevetment;
using DiKErnel.Integration.Data.GrassRevetmentOvertopping;
using DiKErnel.Integration.Data.GrassRevetmentWaveImpact;
using DiKErnel.Integration.Data.GrassRevetmentWaveRunup;
using DiKErnel.Integration.Data.NaturalStoneRevetment;
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

        private readonly List<RevetmentLocationConstructionProperties> locationConstructionPropertiesItems =
            new List<RevetmentLocationConstructionProperties>();

        private bool grassOvertoppingLocationAdded;

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
        public void AddDikeProfileSegment(double startPointX, double startPointZ, double endPointX, double endPointZ)
        {
            AddDikeProfileSegment(startPointX, startPointZ, endPointX, endPointZ, null);
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
                                          double roughnessCoefficient)
        {
            AddDikeProfileSegment(startPointX, startPointZ, endPointX, endPointZ, (double?) roughnessCoefficient);
        }

        /// <summary>
        /// Adds a time step.
        /// </summary>
        /// <param name="beginTime">The begin time.</param>
        /// <param name="endTime">The end time.</param>
        /// <param name="waterLevel">The water level.</param>
        /// <param name="waveHeightHm0">The wave height.</param>
        /// <param name="wavePeriodTm10">The wave period.</param>
        /// <param name="waveAngle">The wave angle.</param>
        public void AddTimeStep(int beginTime, int endTime, double waterLevel, double waveHeightHm0,
                                double wavePeriodTm10, double waveAngle)
        {
            timeDependentInputFactoryDataItems.Add(new TimeDependentInputFactoryData(beginTime, endTime, waterLevel,
                                                                                     waveHeightHm0, wavePeriodTm10,
                                                                                     waveAngle));
        }

        /// <summary>
        /// Adds an asphalt wave impact location.
        /// </summary>
        /// <param name="constructionProperties">The properties to construct the asphalt wave
        /// impact location dependent input.</param>
        public void AddAsphaltWaveImpactLocation(
            AsphaltRevetmentWaveImpactLocationConstructionProperties constructionProperties)
        {
            AddLocation(constructionProperties);
        }

        /// <summary>
        /// Adds a grass overtopping location.
        /// </summary>
        /// <param name="constructionProperties">The properties to construct the grass
        /// overtopping location dependent input.</param>
        public void AddGrassOvertoppingLocation(
            GrassRevetmentOvertoppingLocationConstructionProperties constructionProperties)
        {
            AddLocation(constructionProperties);

            grassOvertoppingLocationAdded = true;
        }

        /// <summary>
        /// Adds a grass wave impact location.
        /// </summary>
        /// <param name="constructionProperties">The properties to construct the grass wave
        /// impact location dependent input.</param>
        public void AddGrassWaveImpactLocation(
            GrassRevetmentWaveImpactLocationConstructionProperties constructionProperties)
        {
            AddLocation(constructionProperties);
        }

        /// <summary>
        /// Adds a grass wave run-up location with Rayleigh protocol.
        /// </summary>
        /// <param name="constructionProperties">The properties to construct the grass wave
        /// run-up Rayleigh location dependent input.</param>
        public void AddGrassWaveRunupRayleighLocation(
            GrassRevetmentWaveRunupRayleighLocationConstructionProperties constructionProperties)
        {
            AddLocation(constructionProperties);
        }

        /// <summary>
        /// Adds a natural stone location.
        /// </summary>
        /// <param name="constructionProperties">The properties to construct the natural
        /// stone location dependent input.</param>
        public void AddNaturalStoneLocation(NaturalStoneRevetmentLocationConstructionProperties constructionProperties)
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

            ProfileData profileData = ProfileDataFactory.Create(profileDataFactorySegments, profileDataFactoryPoints);
            IReadOnlyList<ILocationDependentInput> locationDependentInputItems =
                LocationDependentInputFactory.Create(locationConstructionPropertiesItems);
            IReadOnlyList<ITimeDependentInput> timeDependentInputItems =
                TimeDependentInputFactory.Create(timeDependentInputFactoryDataItems);

            return new DataResult<ICalculationInput>(new CalculationInput(profileData, locationDependentInputItems,
                                                                          timeDependentInputItems),
                                                     EventRegistry.Flush());
        }

        private void AddDikeProfileSegment(double startPointX, double startPointZ, double endPointX, double endPointZ,
                                           double? roughnessCoefficient)
        {
            profileDataFactorySegments.Add(new ProfileDataFactorySegment(startPointX, startPointZ, endPointX, endPointZ,
                                                                         roughnessCoefficient));
        }

        private void AddLocation(RevetmentLocationConstructionProperties constructionProperties)
        {
            locationConstructionPropertiesItems.Add(constructionProperties);
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
                   && ValidateLocations(outerToe, outerCrest, innerToe)
                   && ValidateTimeSteps();
        }

        private bool ValidateProfileSegments()
        {
            if (!profileDataFactorySegments.Any())
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
                   && ValidateCharacteristicPoint(innerCrest, "inner crest", grassOvertoppingLocationAdded)
                   && ValidateCharacteristicPoint(innerToe, "inner toe", grassOvertoppingLocationAdded);
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

        private ProfileDataFactoryPoint GetProfileDataFactoryPointForCharacteristicPointType(
            CharacteristicPointType characteristicPointType)
        {
            return profileDataFactoryPoints.Find(
                profileDataFactoryPoint => profileDataFactoryPoint.CharacteristicPointType == characteristicPointType);
        }

        private bool ValidateLocations(ProfileDataFactoryPoint outerToe, ProfileDataFactoryPoint outerCrest,
                                       ProfileDataFactoryPoint innerToe)
        {
            if (!locationConstructionPropertiesItems.Any())
            {
                RegisterValidationError("At least 1 location is required.");
                return false;
            }

            foreach (RevetmentLocationConstructionProperties locationConstructionProperties in locationConstructionPropertiesItems)
            {
                switch (locationConstructionProperties)
                {
                    case AsphaltRevetmentWaveImpactLocationConstructionProperties asphaltWaveImpactLocationConstructionProperties
                        when !ValidateAsphaltRevetmentWaveImpactLocationConstructionProperties(
                                 asphaltWaveImpactLocationConstructionProperties, outerToe, outerCrest):
                    case GrassRevetmentOvertoppingLocationConstructionProperties grassOvertoppingLocationConstructionProperties
                        when !ValidateGrassRevetmentOvertoppingLocationConstructionProperties(
                                 grassOvertoppingLocationConstructionProperties, outerToe, outerCrest, innerToe):
                    case GrassRevetmentWaveImpactLocationConstructionProperties grassWaveImpactLocationConstructionProperties
                        when !ValidateGrassRevetmentWaveImpactLocationConstructionProperties(
                                 grassWaveImpactLocationConstructionProperties, outerToe, outerCrest):
                    case GrassRevetmentWaveRunupRayleighLocationConstructionProperties rayleighLocationConstructionProperties
                        when !ValidateGrassRevetmentWaveRunupRayleighLocationConstructionProperties(
                                 rayleighLocationConstructionProperties, outerToe, outerCrest):
                    case NaturalStoneRevetmentLocationConstructionProperties naturalStoneLocationConstructionProperties
                        when !ValidateNaturalStoneRevetmentLocationConstructionProperties(
                                 naturalStoneLocationConstructionProperties, outerToe, outerCrest):
                        return false;
                }
            }

            return true;
        }

        private static bool ValidateAsphaltRevetmentWaveImpactLocationConstructionProperties(
            AsphaltRevetmentWaveImpactLocationConstructionProperties constructionProperties,
            ProfileDataFactoryPoint outerToe, ProfileDataFactoryPoint outerCrest)
        {
            return ValidateLocationOnOuterSlope(outerToe, outerCrest, constructionProperties.X)
                   && ValidateAsphaltRevetmentTopLayerType(constructionProperties.TopLayerType,
                                                           constructionProperties.X);
        }

        private bool ValidateGrassRevetmentOvertoppingLocationConstructionProperties(
            GrassRevetmentOvertoppingLocationConstructionProperties constructionProperties,
            ProfileDataFactoryPoint outerToe, ProfileDataFactoryPoint outerCrest, ProfileDataFactoryPoint innerToe)
        {
            return ValidateLocationOnCrestOrInnerSlope(outerCrest, innerToe, constructionProperties.X)
                   && ValidateGrassRevetmentTopLayerType(constructionProperties.TopLayerType, constructionProperties.X)
                   && ValidateOvertoppingLocationSpecificProperties(constructionProperties, outerToe, outerCrest);
        }

        private static bool ValidateGrassRevetmentWaveImpactLocationConstructionProperties(
            GrassRevetmentWaveImpactLocationConstructionProperties constructionProperties,
            ProfileDataFactoryPoint outerToe, ProfileDataFactoryPoint outerCrest)
        {
            return ValidateLocationOnOuterSlope(outerToe, outerCrest, constructionProperties.X)
                   && ValidateGrassRevetmentTopLayerType(constructionProperties.TopLayerType, constructionProperties.X);
        }

        private static bool ValidateGrassRevetmentWaveRunupRayleighLocationConstructionProperties(
            GrassRevetmentWaveRunupRayleighLocationConstructionProperties constructionProperties,
            ProfileDataFactoryPoint outerToe, ProfileDataFactoryPoint outerCrest)
        {
            return ValidateLocationOnOuterSlope(outerToe, outerCrest, constructionProperties.X)
                   && ValidateGrassRevetmentTopLayerType(constructionProperties.TopLayerType, constructionProperties.X);
        }

        private static bool ValidateNaturalStoneRevetmentLocationConstructionProperties(
            NaturalStoneRevetmentLocationConstructionProperties constructionProperties,
            ProfileDataFactoryPoint outerToe, ProfileDataFactoryPoint outerCrest)
        {
            return ValidateLocationOnOuterSlope(outerToe, outerCrest, constructionProperties.X)
                   && ValidateNaturalStoneRevetmentTopLayerType(constructionProperties.TopLayerType,
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

        private static bool ValidateAsphaltRevetmentTopLayerType(AsphaltRevetmentTopLayerType topLayerType,
                                                                 double locationX)
        {
            if (topLayerType != AsphaltRevetmentTopLayerType.HydraulicAsphaltConcrete)
            {
                RegisterValidationError($"The location with position {NumericsHelper.ToString(locationX)} has an " +
                                        "invalid top layer type.");
                return false;
            }

            return true;
        }

        private static bool ValidateGrassRevetmentTopLayerType(GrassRevetmentTopLayerType topLayerType,
                                                               double locationX)
        {
            if (topLayerType != GrassRevetmentTopLayerType.ClosedSod
                && topLayerType != GrassRevetmentTopLayerType.OpenSod)
            {
                RegisterValidationError($"The location with position {NumericsHelper.ToString(locationX)} has an " +
                                        "invalid top layer type.");
                return false;
            }

            return true;
        }

        private static bool ValidateNaturalStoneRevetmentTopLayerType(NaturalStoneRevetmentTopLayerType topLayerType,
                                                                      double locationX)
        {
            if (topLayerType != NaturalStoneRevetmentTopLayerType.NordicStone)
            {
                RegisterValidationError($"The location with position {NumericsHelper.ToString(locationX)} has an " +
                                        "invalid top layer type.");
                return false;
            }

            return true;
        }

        private bool ValidateOvertoppingLocationSpecificProperties(
            GrassRevetmentOvertoppingLocationConstructionProperties constructionProperties,
            ProfileDataFactoryPoint outerToe, ProfileDataFactoryPoint outerCrest)
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

            double outerCrestZ = zValuesProfile[zValuesProfile.Count - 1];
            double dikeHeight = GetOvertoppingDikeHeight(constructionProperties.DikeHeight, outerCrestZ);

            IReadOnlyList<string> messages = OvertoppingAdapter.Validate(xValuesProfile.ToArray(),
                                                                         zValuesProfile.ToArray(),
                                                                         roughnessCoefficients.ToArray(), dikeHeight);
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

        /// <summary>
        /// Gets the location dike height.
        /// </summary>
        /// <param name="locationDikeHeight">The optional dike height of the
        /// location.</param>
        /// <param name="outerCrestZCoordinate">The height of the outer crest.</param>
        /// <returns>The dike height.</returns>
        /// <remarks>In case the dike height of the location is not set, the height of the
        /// outer crest is returned to provide a valid input for the validation from the
        /// overtopping adapter.</remarks>
        private static double GetOvertoppingDikeHeight(double? locationDikeHeight, double outerCrestZCoordinate)
        {
            return locationDikeHeight ?? outerCrestZCoordinate;
        }

        private bool ValidateTimeSteps()
        {
            if (!timeDependentInputFactoryDataItems.Any())
            {
                RegisterValidationError("At least 1 time step is required.");
                return false;
            }

            TimeDependentInputFactoryData previousTimeDependentInput = null;

            foreach (TimeDependentInputFactoryData currentTimeDependentInput in timeDependentInputFactoryDataItems)
            {
                int currentTimeStepBeginTime = currentTimeDependentInput.BeginTime;

                if (previousTimeDependentInput != null)
                {
                    int previousTimeStepEndTime = previousTimeDependentInput.EndTime;
                    if (previousTimeStepEndTime != currentTimeStepBeginTime)
                    {
                        RegisterValidationError($"The begin time of the time step ({currentTimeStepBeginTime}) must " +
                                                "be equal to the end time of the previous time step " +
                                                $"({previousTimeStepEndTime}).");
                        return false;
                    }
                }

                int currentTimeStepEndTime = currentTimeDependentInput.EndTime;

                if (currentTimeStepBeginTime >= currentTimeStepEndTime)
                {
                    RegisterValidationError($"The begin time of the time step ({currentTimeStepBeginTime}) must be " +
                                            $"smaller than the end time of the time step ({currentTimeStepEndTime}).");
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