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

using System;
using System.Collections.Generic;
using System.Linq;
using DiKErnel.Core.Data;
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
        private readonly List<ProfileDataFactoryPoint> profilePointDataItems = new List<ProfileDataFactoryPoint>();
        private readonly List<TimeDependentInputFactoryData> timeStepDataItems = new List<TimeDependentInputFactoryData>();
        private readonly List<ProfileDataFactorySegment> profileSegmentDataItems = new List<ProfileDataFactorySegment>();

        private readonly List<RevetmentLocationConstructionPropertiesBase> locationConstructionPropertiesItems =
            new List<RevetmentLocationConstructionPropertiesBase>();

        private bool grassOvertoppingLocationAdded;

        /// <summary>
        /// Adds a dike profile point.
        /// </summary>
        /// <param name="x">The x coordinate.</param>
        /// <param name="characteristicPointType">The characteristic point type.</param>
        public void AddDikeProfilePointData(double x, CharacteristicPointType characteristicPointType)
        {
            profilePointDataItems.Add(new ProfileDataFactoryPoint(x, characteristicPointType));
        }

        /// <summary>
        /// Adds a new dike profile segment.
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
        /// Adds a new dike profile segment.
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
            timeStepDataItems.Add(new TimeDependentInputFactoryData(beginTime, endTime, waterLevel, waveHeightHm0,
                                                                    wavePeriodTm10, waveAngle));
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

            ProfileData profileData = ProfileDataFactory.Create(profileSegmentDataItems, profilePointDataItems);
            IReadOnlyList<ILocationDependentInput> locations =
                LocationDependentInputFactory.Create(locationConstructionPropertiesItems);
            IReadOnlyList<ITimeDependentInput> timeSteps = TimeDependentInputFactory.Create(timeStepDataItems);

            return new DataResult<ICalculationInput>(new CalculationInput(profileData, locations, timeSteps),
                                                     EventRegistry.Flush());
        }

        private void AddDikeProfileSegment(double startPointX, double startPointZ, double endPointX, double endPointZ,
                                           double? roughnessCoefficient)
        {
            profileSegmentDataItems.Add(new ProfileDataFactorySegment(startPointX, startPointZ, endPointX, endPointZ,
                                                                      roughnessCoefficient));
        }

        private void AddLocation(RevetmentLocationConstructionPropertiesBase constructionProperties)
        {
            locationConstructionPropertiesItems.Add(constructionProperties);
        }

        private bool CanBuildValidCalculationInput()
        {
            ProfileDataFactoryPoint outerToe = GetProfilePointDataItemForCharacteristicPointType(CharacteristicPointType.OuterToe);
            ProfileDataFactoryPoint outerCrest = GetProfilePointDataItemForCharacteristicPointType(CharacteristicPointType.OuterCrest);
            ProfileDataFactoryPoint innerToe = GetProfilePointDataItemForCharacteristicPointType(CharacteristicPointType.InnerToe);

            return ValidateProfileSegments()
                   && ValidateCharacteristicPoints(outerToe, outerCrest, innerToe)
                   && ValidateLocations(outerToe, outerCrest, innerToe)
                   && ValidateTimeSteps();
        }

        private bool ValidateProfileSegments()
        {
            if (profileSegmentDataItems.Count == 0)
            {
                RegisterValidationError("At least 1 profile segment is required.");
                return false;
            }

            ProfileDataFactorySegment previousSegment = null;

            foreach (ProfileDataFactorySegment profileSegmentDataItem in profileSegmentDataItems)
            {
                if (previousSegment != null)
                {
                    double previousSegmentEndPointX = previousSegment.EndPointX;
                    double previousSegmentEndPointZ = previousSegment.EndPointZ;
                    double currentSegmentStartPointX = profileSegmentDataItem.StartPointX;
                    double currentSegmentStartPointZ = profileSegmentDataItem.StartPointZ;

                    if (!NumericsHelper.AreEqual(previousSegmentEndPointX, currentSegmentStartPointX)
                        || !NumericsHelper.AreEqual(previousSegmentEndPointZ, currentSegmentStartPointZ))
                    {
                        RegisterValidationError(
                            $"The start point of the profile segment ({NumericsHelper.ToString(currentSegmentStartPointX)}, " +
                            $"{NumericsHelper.ToString(currentSegmentStartPointZ)}) must be equal to the end point of " +
                            $"the previous profile segment ({NumericsHelper.ToString(previousSegmentEndPointX)}, " +
                            $"{NumericsHelper.ToString(previousSegmentEndPointZ)}).");

                        return false;
                    }
                }

                previousSegment = profileSegmentDataItem;
            }

            return true;
        }

        private bool ValidateCharacteristicPoints(ProfileDataFactoryPoint outerToe, ProfileDataFactoryPoint outerCrest,
                                                  ProfileDataFactoryPoint innerToe)
        {
            ProfileDataFactoryPoint crestOuterBerm =
                GetProfilePointDataItemForCharacteristicPointType(CharacteristicPointType.CrestOuterBerm);
            ProfileDataFactoryPoint notchOuterBerm =
                GetProfilePointDataItemForCharacteristicPointType(CharacteristicPointType.NotchOuterBerm);
            ProfileDataFactoryPoint innerCrest =
                GetProfilePointDataItemForCharacteristicPointType(CharacteristicPointType.InnerCrest);

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

                RegisterValidationError("The " + characteristicPointName + " is required.");
                return false;
            }

            double characteristicPointX = characteristicPoint.X;

            if (profileSegmentDataItems.Any(profileSegment => NumericsHelper.AreEqual(profileSegment.StartPointX, characteristicPointX)))
            {
                return true;
            }

            if (NumericsHelper.AreEqual(profileSegmentDataItems.Last().EndPointX, characteristicPointX))
            {
                return true;
            }

            RegisterValidationError("The " + characteristicPointName + " must be on a start or end point of a profile segment.");
            return false;
        }

        private ProfileDataFactoryPoint GetProfilePointDataItemForCharacteristicPointType(
            CharacteristicPointType characteristicPointType)
        {
            throw new NotImplementedException();
        }

        private bool ValidateLocations(ProfileDataFactoryPoint outerToe, ProfileDataFactoryPoint outerCrest,
                                       ProfileDataFactoryPoint innerToe)
        {
            throw new NotImplementedException();
        }

        private bool ValidateAsphaltRevetmentWaveImpactLocationConstructionProperties(
            AsphaltRevetmentWaveImpactLocationConstructionProperties constructionProperties,
            ProfileDataFactoryPoint outerToe, ProfileDataFactoryPoint outerCrest)
        {
            throw new NotImplementedException();
        }

        private bool ValidateGrassRevetmentOvertoppingLocationConstructionProperties(
            GrassRevetmentOvertoppingLocationConstructionProperties constructionProperties,
            ProfileDataFactoryPoint outerToe, ProfileDataFactoryPoint outerCrest, ProfileDataFactoryPoint innerToe)
        {
            throw new NotImplementedException();
        }

        private bool ValidateGrassRevetmentWaveImpactLocationConstructionProperties(
            GrassRevetmentWaveImpactLocationConstructionProperties constructionProperties,
            ProfileDataFactoryPoint outerToe, ProfileDataFactoryPoint outerCrest)
        {
            throw new NotImplementedException();
        }

        private bool ValidateGrassRevetmentWaveRunupRayleighLocationConstructionProperties(
            GrassRevetmentWaveRunupRayleighLocationConstructionProperties constructionProperties,
            ProfileDataFactoryPoint outerToe, ProfileDataFactoryPoint outerCrest)
        {
            throw new NotImplementedException();
        }

        private bool ValidateNaturalStoneRevetmentLocationConstructionProperties(
            NaturalStoneRevetmentLocationConstructionProperties constructionProperties,
            ProfileDataFactoryPoint outerToe, ProfileDataFactoryPoint outerCrest)
        {
            throw new NotImplementedException();
        }

        private bool ValidateLocationOnOuterSlope(ProfileDataFactoryPoint outerToe, ProfileDataFactoryPoint outerCrest,
                                                  double locationX)
        {
            throw new NotImplementedException();
        }

        private bool ValidateLocationOnCrestOrInnerSlope(ProfileDataFactoryPoint outerCrest,
                                                         ProfileDataFactoryPoint innerToe,
                                                         double locationX)
        {
            throw new NotImplementedException();
        }

        private bool ValidateAsphaltRevetmentTopLayerType(
            AsphaltRevetmentTopLayerType topLayerType,
            double locationX)
        {
            throw new NotImplementedException();
        }

        private bool ValidateGrassRevetmentTopLayerType(
            GrassRevetmentTopLayerType topLayerType,
            double locationX)
        {
            throw new NotImplementedException();
        }

        private bool ValidateNaturalStoneRevetmentTopLayerType(
            NaturalStoneRevetmentTopLayerType topLayerType,
            double locationX)
        {
            throw new NotImplementedException();
        }

        private bool ValidateOvertoppingLocationSpecificProperties(
            GrassRevetmentOvertoppingLocationConstructionProperties constructionProperties,
            ProfileDataFactoryPoint outerToe,
            ProfileDataFactoryPoint outerCrest)
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Gets the location dike height.
        /// </summary>
        /// <param name="locationDikeHeight">The optional dike height of the location.</param>
        /// <param name="outerCrestZCoordinate">The height of the outer crest.</param>
        /// <returns>The dike height.</returns>
        /// <remarks>In case the dike height of the location is not set, the height of the
        /// outer crest is returned to provide a valid input for the validation from the
        /// overtopping adapter.</remarks>
        private static double GetOvertoppingDikeHeight(double? locationDikeHeight, double outerCrestZCoordinate)
        {
            throw new NotImplementedException();
        }

        private bool ValidateTimeSteps()
        {
            throw new NotImplementedException();
        }

        private void RegisterValidationError(string message) {}
    }
}