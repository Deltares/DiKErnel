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

namespace DiKErnel.Integration
{
    /// <summary>
    /// Builder to configure and create calculation input.
    /// </summary>
    public class CalculationInputBuilder
    {
        /// <summary>
        /// Adds a dike profile point.
        /// </summary>
        /// <param name="x">The x coordinate.</param>
        /// <param name="characteristicPointType">The characteristic point type.</param>
        public void AddDikeProfilePointData(
            double x,
            Core::CharacteristicPointType characteristicPointType)
        {
            
        }

        /// <summary>
        /// Adds a new dike profile segment.
        /// </summary>
        /// <param name="startPointX">The x coordinate for the start profile point.</param>
        /// <param name="startPointZ">The z coordinate for the start profile point.</param>
        /// <param name="endPointX">The x coordinate for the end profile point.</param>
        /// <param name="endPointZ">The z coordinate for the end profile point.</param>
        public void AddDikeProfileSegment(
            double startPointX,
            double startPointZ,
            double endPointX,
            double endPointZ)
        {
            
        }

        /// <summary>
        /// Adds a new dike profile segment.
        /// </summary>
        /// <param name="startPointX">The x coordinate for the start profile point.</param>
        /// <param name="startPointZ">The z coordinate for the start profile point.</param>
        /// <param name="endPointX">The x coordinate for the end profile point.</param>
        /// <param name="endPointZ">The z coordinate for the end profile point.</param>
        /// <param name="roughnessCoefficient">The roughness coefficient.</param>
        public void AddDikeProfileSegment(
            double startPointX,
            double startPointZ,
            double endPointX,
            double endPointZ,
            double roughnessCoefficient)
        {
            
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
        public void AddTimeStep(
            int beginTime,
            int endTime,
            double waterLevel,
            double waveHeightHm0,
            double wavePeriodTm10,
            double waveAngle)
        {
            
        }

        /// <summary>
        /// Adds an asphalt wave impact location.
        /// </summary>
        /// <param name="constructionProperties">The properties to construct the asphalt wave
        /// impact location dependent input.</param>
        public void AddAsphaltWaveImpactLocation(
            std::unique_ptr<AsphaltRevetmentWaveImpactLocationConstructionProperties> constructionProperties)
        {
            
        }

        /// <summary>
        /// Adds a grass overtopping location.
        /// </summary>
        /// <param name="constructionProperties">The properties to construct the grass
        /// overtopping location dependent input.</param>
        public void AddGrassOvertoppingLocation(
            std::unique_ptr<GrassRevetmentOvertoppingLocationConstructionProperties> constructionProperties)
        {
            
        }

        /// <summary>
        /// Adds a grass wave impact location.
        /// </summary>
        /// <param name="constructionProperties">The properties to construct the grass wave
        /// impact location dependent input.</param>
        public void AddGrassWaveImpactLocation(
            std::unique_ptr<GrassRevetmentWaveImpactLocationConstructionProperties> constructionProperties)
        {
            
        }

        /// <summary>
        /// Adds a grass wave run-up location with Rayleigh protocol.
        /// </summary>
        /// <param name="constructionProperties">The properties to construct the grass wave
        /// run-up Rayleigh location dependent input.</param>
        public void AddGrassWaveRunupRayleighLocation(
            std::unique_ptr<GrassRevetmentWaveRunupRayleighLocationConstructionProperties> constructionProperties)
        {
            
        }


        /// <summary>
        /// Adds a natural stone location.
        /// </summary>
        /// <param name="constructionProperties">The properties to construct the natural
        /// stone location dependent input.</param>
        public void AddNaturalStoneLocation(
            std::unique_ptr<NaturalStoneRevetmentLocationConstructionProperties> constructionProperties)
        {
            
        }

        /// <summary>
        /// Builds the calculation input.
        /// </summary>
        /// <returns>The result with the created calculation input.</returns>
        public std::unique_ptr<Util::DataResult<Core::ICalculationInput>> Build()
        {
            
        }

        private void AddDikeProfileSegment(
            double startPointX,
            double startPointZ,
            double endPointX,
            double endPointZ,
            std::unique_ptr<double> roughnessCoefficient)
        {
            
        }

        private void AddLocation(
            std::unique_ptr<RevetmentLocationConstructionPropertiesBase> constructionProperties)
        {
            
        }

        private bool CanBuildValidCalculationInput()
        {
            
        }

        private bool ValidateProfileSegments()
        {
            
        }

            private bool ValidateCharacteristicPoints(
                const ProfileDataFactoryPoint* outerToe,
                const ProfileDataFactoryPoint* outerCrest,
                const ProfileDataFactoryPoint* innerToe)
                {
                    
                }

            private bool ValidateCharacteristicPoint(
                const ProfileDataFactoryPoint* characteristicPoint,
                const std::string& characteristicPointName,
                bool isRequired = true)
                {
                    
                }

                private ProfileDataFactoryPoint* GetProfilePointDataItemForCharacteristicPointType(
                    Core::CharacteristicPointType characteristicPointType)
                {
                    
                }

            private bool ValidateLocations(
                const ProfileDataFactoryPoint& outerToe,
                const ProfileDataFactoryPoint& outerCrest,
                const ProfileDataFactoryPoint* innerToe)
                {
                    
                }

            private bool ValidateAsphaltRevetmentWaveImpactLocationConstructionProperties(
                const AsphaltRevetmentWaveImpactLocationConstructionProperties& constructionProperties,
                const ProfileDataFactoryPoint& outerToe,
                const ProfileDataFactoryPoint& outerCrest)
                {
                    
                }

            private bool ValidateGrassRevetmentOvertoppingLocationConstructionProperties(
                const GrassRevetmentOvertoppingLocationConstructionProperties& constructionProperties,
                const ProfileDataFactoryPoint& outerToe,
                const ProfileDataFactoryPoint& outerCrest,
                const ProfileDataFactoryPoint& innerToe)
                {
                    
                }

            private bool ValidateGrassRevetmentWaveImpactLocationConstructionProperties(
                const GrassRevetmentWaveImpactLocationConstructionProperties& constructionProperties,
                const ProfileDataFactoryPoint& outerToe,
                const ProfileDataFactoryPoint& outerCrest)
                {
                    
                }

            private bool ValidateGrassRevetmentWaveRunupRayleighLocationConstructionProperties(
                const GrassRevetmentWaveRunupRayleighLocationConstructionProperties& constructionProperties,
                const ProfileDataFactoryPoint& outerToe,
                const ProfileDataFactoryPoint& outerCrest)
                {
                    
                }

            private bool ValidateNaturalStoneRevetmentLocationConstructionProperties(
                const NaturalStoneRevetmentLocationConstructionProperties& constructionProperties,
                const ProfileDataFactoryPoint& outerToe,
                const ProfileDataFactoryPoint& outerCrest)
                {
                    
                }

            private bool ValidateLocationOnOuterSlope(
                const ProfileDataFactoryPoint& outerToe,
                const ProfileDataFactoryPoint& outerCrest,
                double locationX)
                {
                    
                }

            private bool ValidateLocationOnCrestOrInnerSlope(
                const ProfileDataFactoryPoint& outerCrest,
                const ProfileDataFactoryPoint& innerToe,
                double locationX)
                {
                    
                }

                private bool ValidateAsphaltRevetmentTopLayerType(
                    AsphaltRevetmentTopLayerType topLayerType,
                    double locationX)
                {
                    
                }

                private bool ValidateGrassRevetmentTopLayerType(
                    GrassRevetmentTopLayerType topLayerType,
                    double locationX)
                {
                    
                }

                private bool ValidateNaturalStoneRevetmentTopLayerType(
                    NaturalStoneRevetmentTopLayerType topLayerType,
                    double locationX)
                {
                    
                }

            private bool ValidateOvertoppingLocationSpecificProperties(
                const GrassRevetmentOvertoppingLocationConstructionProperties& constructionProperties,
                const ProfileDataFactoryPoint& outerToe,
                const ProfileDataFactoryPoint& outerCrest)
                {
                    
                }

            /*!
             * \brief Gets the location dike height.
             * \param locationDikeHeight
             *        The optional dike height of the location.
             * \param outerCrestZCoordinate
             *        The height of the outer crest.
             * \return The dike height.
             * \remarks In case the dike height of the location is not set, the height of the outer
             *          crest is returned to provide a valid input for the validation from the
             *          overtopping adapter.
             */
            private static double GetOvertoppingDikeHeight(
                const double* locationDikeHeight,
                double outerCrestZCoordinate)
                {
                    
                }

                private bool ValidateTimeSteps()
                {
                    
                }

            private void RegisterValidationError(
                const std::string& message)
                {
                    
                }

            private std::vector<std::unique_ptr<ProfileDataFactoryPoint>> _profilePointDataItems;
            private std::vector<std::reference_wrapper<ProfileDataFactoryPoint>> _profilePointDataItemReferences;
            private std::vector<std::unique_ptr<ProfileDataFactorySegment>> _profileSegmentDataItems;
            private std::vector<std::reference_wrapper<ProfileDataFactorySegment>> _profileSegmentDataItemReferences;
            private std::vector<std::unique_ptr<TimeDependentInputFactoryData>> _timeStepDataItems;
            private std::vector<std::reference_wrapper<TimeDependentInputFactoryData>> _timeStepDataItemReferences;
            private std::vector<std::unique_ptr<RevetmentLocationConstructionPropertiesBase>> _locationConstructionPropertiesItems;
            private std::vector<std::reference_wrapper<RevetmentLocationConstructionPropertiesBase>> _locationConstructionPropertiesItemReferences;
            private bool _grassOvertoppingLocationAdded = false;

    }
}