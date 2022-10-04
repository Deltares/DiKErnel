// Copyright (C) Stichting Deltares 2022. All rights reserved.
//
// This file is part of DiKErnel.
//
// DiKErnel is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, version 3.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/lgpl-3.0.html>.
//
// All names, logos, and references to "Deltares" are registered trademarks of
// Stichting Deltares and remain full property of Stichting Deltares at all times.
// All rights reserved.

#include "CalculationInputBuilder.h"

#include <algorithm>
#include <functional>
#include <sstream>

#include "CalculationInput.h"
#include "EventRegistry.h"
#include "InputFactoryHelper.h"
#include "LocationDependentInputFactory.h"
#include "NumericsHelper.h"
#include "OvertoppingAdapter.h"
#include "ProfileDataFactory.h"
#include "ProfileDataFactoryPoint.h"
#include "ProfileDataFactorySegment.h"
#include "ProfileSegmentDefaults.h"
#include "TimeDependentInputFactory.h"
#include "TimeDependentInputFactoryData.h"

namespace DiKErnel::Integration
{
    using namespace Core;
    using namespace DomainLibrary;
    using namespace External;
    using namespace Util;
    using namespace std;

    CalculationInputBuilder::CalculationInputBuilder() = default;

    CalculationInputBuilder::~CalculationInputBuilder() = default;

    void CalculationInputBuilder::AddDikeProfilePointData(
        const double x,
        const CharacteristicPointType characteristicPointType)
    {
        _profilePointDataItems.push_back(make_unique<ProfileDataFactoryPoint>(x, characteristicPointType));
        _profilePointDataItemReferences.emplace_back(*_profilePointDataItems.back());
    }

    void CalculationInputBuilder::AddDikeProfileSegment(
        const double startPointX,
        const double startPointZ,
        const double endPointX,
        const double endPointZ)
    {
        AddDikeProfileSegment(startPointX, startPointZ, endPointX, endPointZ, nullptr);
    }

    void CalculationInputBuilder::AddDikeProfileSegment(
        const double startPointX,
        const double startPointZ,
        const double endPointX,
        const double endPointZ,
        const double roughnessCoefficient)
    {
        AddDikeProfileSegment(startPointX, startPointZ, endPointX, endPointZ, make_unique<double>(roughnessCoefficient));
    }

    void CalculationInputBuilder::AddTimeStep(
        int beginTime,
        int endTime,
        double waterLevel,
        double waveHeightHm0,
        double wavePeriodTm10,
        double waveAngle)
    {
        _timeStepDataItems.push_back(
            make_unique<TimeDependentInputFactoryData>(beginTime, endTime, waterLevel, waveHeightHm0, wavePeriodTm10, waveAngle));
        _timeStepDataItemReferences.emplace_back(*_timeStepDataItems.back());
    }

    void CalculationInputBuilder::AddAsphaltWaveImpactLocation(
        unique_ptr<AsphaltRevetmentWaveImpactLocationConstructionProperties> constructionProperties)
    {
        AddLocation(move(constructionProperties));
    }

    void CalculationInputBuilder::AddGrassOvertoppingLocation(
        unique_ptr<GrassRevetmentOvertoppingLocationConstructionProperties> constructionProperties)
    {
        AddLocation(move(constructionProperties));
        _grassOvertoppingLocationAdded = true;
    }

    void CalculationInputBuilder::AddGrassWaveImpactLocation(
        unique_ptr<GrassRevetmentWaveImpactLocationConstructionProperties> constructionProperties)
    {
        AddLocation(move(constructionProperties));
    }

    void CalculationInputBuilder::AddGrassWaveRunupRayleighLocation(
        unique_ptr<GrassRevetmentWaveRunupRayleighLocationConstructionProperties> constructionProperties)
    {
        AddLocation(move(constructionProperties));
    }

    void CalculationInputBuilder::AddNaturalStoneLocation(
        unique_ptr<NaturalStoneRevetmentLocationConstructionProperties> constructionProperties)
    {
        AddLocation(move(constructionProperties));
    }

    unique_ptr<DataResult<ICalculationInput>> CalculationInputBuilder::Build() const
    {
        if (!CanBuildValidCalculationInput())
        {
            return make_unique<DataResult<ICalculationInput>>(EventRegistry::Flush());
        }

        auto profileData = ProfileDataFactory::Create(_profileSegmentDataItemReferences, _profilePointDataItemReferences);
        auto locations = LocationDependentInputFactory::Create(_locationConstructionPropertiesItemReferences);
        auto timeSteps = TimeDependentInputFactory::Create(_timeStepDataItemReferences);

        return make_unique<DataResult<ICalculationInput>>(make_unique<CalculationInput>(move(profileData), move(locations), move(timeSteps)),
                                                          EventRegistry::Flush());
    }

    void CalculationInputBuilder::AddDikeProfileSegment(
        double startPointX,
        double startPointZ,
        double endPointX,
        double endPointZ,
        unique_ptr<double> roughnessCoefficient)
    {
        _profileSegmentDataItems.push_back(
            make_unique<ProfileDataFactorySegment>(startPointX, startPointZ, endPointX, endPointZ, move(roughnessCoefficient)));
        _profileSegmentDataItemReferences.emplace_back(*_profileSegmentDataItems.back());
    }

    void CalculationInputBuilder::AddLocation(
        unique_ptr<RevetmentLocationConstructionPropertiesBase> constructionProperties)
    {
        _locationConstructionPropertiesItems.push_back(move(constructionProperties));
        _locationConstructionPropertiesItemReferences.emplace_back(*_locationConstructionPropertiesItems.back());
    }

    bool CalculationInputBuilder::CanBuildValidCalculationInput() const
    {
        const auto* outerToe = GetProfilePointDataItemForCharacteristicPointType(CharacteristicPointType::OuterToe);
        const auto* outerCrest = GetProfilePointDataItemForCharacteristicPointType(CharacteristicPointType::OuterCrest);
        const auto* innerToe = GetProfilePointDataItemForCharacteristicPointType(CharacteristicPointType::InnerToe);

        return ValidateProfileSegments()
                && ValidateCharacteristicPoints(outerToe, outerCrest, innerToe)
                && ValidateLocations(*outerToe, *outerCrest, innerToe)
                && ValidateTimeSteps();
    }

    bool CalculationInputBuilder::ValidateProfileSegments() const
    {
        if (_profileSegmentDataItems.empty())
        {
            RegisterValidationError("At least 1 profile segment is required.");
            return false;
        }

        const ProfileDataFactorySegment* previousSegment = nullptr;
        for (const auto& profileSegmentDataItem : _profileSegmentDataItems)
        {
            const ProfileDataFactorySegment* currentSegment = profileSegmentDataItem.get();

            if (previousSegment != nullptr)
            {
                const auto previousSegmentEndPointX = previousSegment->GetEndPointX();
                const auto previousSegmentEndPointZ = previousSegment->GetEndPointZ();

                const auto currentSegmentStartPointX = currentSegment->GetStartPointX();
                const auto currentSegmentStartPointZ = currentSegment->GetStartPointZ();

                if (!NumericsHelper::AreEqual(previousSegmentEndPointX, currentSegmentStartPointX)
                    || !NumericsHelper::AreEqual(previousSegmentEndPointZ, currentSegmentStartPointZ))
                {
                    ostringstream stringStream;
                    stringStream << "The start point of the profile segment (" << currentSegmentStartPointX << ", " << currentSegmentStartPointZ <<
                            ") must be equal to the end point of the previous profile segment (" << previousSegmentEndPointX << ", " <<
                            previousSegmentEndPointZ << ").";

                    RegisterValidationError(stringStream.str());
                    return false;
                }
            }

            previousSegment = currentSegment;
        }

        return true;
    }

    bool CalculationInputBuilder::ValidateCharacteristicPoints(
        const ProfileDataFactoryPoint* outerToe,
        const ProfileDataFactoryPoint* outerCrest,
        const ProfileDataFactoryPoint* innerToe) const
    {
        const auto* innerCrest = GetProfilePointDataItemForCharacteristicPointType(CharacteristicPointType::InnerCrest);

        return ValidateCharacteristicPoint(outerToe, "outer toe")
                && ValidateCharacteristicPoint(outerCrest, "outer crest")
                && ValidateCharacteristicPoint(innerCrest, "inner crest", _grassOvertoppingLocationAdded)
                && ValidateCharacteristicPoint(innerToe, "inner toe", _grassOvertoppingLocationAdded);
    }

    bool CalculationInputBuilder::ValidateCharacteristicPoint(
        const ProfileDataFactoryPoint* characteristicPoint,
        const string& characteristicPointName,
        const bool isRequired) const
    {
        if (characteristicPoint == nullptr)
        {
            if (isRequired)
            {
                RegisterValidationError("The " + characteristicPointName + " is required.");
                return false;
            }

            return true;
        }

        const auto characteristicPointX = characteristicPoint->GetX();

        for (const auto& profileSegment : _profileSegmentDataItems)
        {
            if (NumericsHelper::AreEqual(profileSegment->GetStartPointX(), characteristicPointX)
                || NumericsHelper::AreEqual(profileSegment->GetEndPointX(), characteristicPointX))
            {
                return true;
            }
        }

        RegisterValidationError("The " + characteristicPointName + " must be on a start or end point of a profile segment.");
        return false;
    }

    ProfileDataFactoryPoint* CalculationInputBuilder::GetProfilePointDataItemForCharacteristicPointType(
        const CharacteristicPointType characteristicPointType) const
    {
        const auto result = ranges::find_if(_profilePointDataItemReferences, [characteristicPointType](
                                        const reference_wrapper<ProfileDataFactoryPoint> profilePointDataItem)
                                            {
                                                return profilePointDataItem.get().GetCharacteristicPoint() == characteristicPointType;
                                            });

        return result != _profilePointDataItemReferences.end()
                   ? &result->get()
                   : nullptr;
    }

    bool CalculationInputBuilder::ValidateLocations(
        const ProfileDataFactoryPoint& outerToe,
        const ProfileDataFactoryPoint& outerCrest,
        const ProfileDataFactoryPoint* innerToe) const
    {
        if (_locationConstructionPropertiesItems.empty())
        {
            RegisterValidationError("At least 1 location is required.");
            return false;
        }

        const function validateLocationOnOuterSlope = [this, outerToe, outerCrest](
            const double x)
        {
            return ValidateLocationOnOuterSlope(outerToe, outerCrest, x);
        };

        const function validateLocationOnCrestOrInnerSlope = [this, outerCrest, innerToe](
            const double x)
        {
            return ValidateLocationOnCrestOrInnerSlope(outerCrest, *innerToe, x);
        };

        const function validateOvertoppingLocationSpecificProperties = [this, outerToe, outerCrest](
            const GrassRevetmentOvertoppingLocationConstructionProperties* constructionProperties)
        {
            return ValidateOvertoppingLocationSpecificProperties(constructionProperties, outerToe, outerCrest);
        };

        const function validateAsphaltRevetmentTopLayerType = [](
            const AsphaltRevetmentTopLayerType topLayerType)
        {
            return topLayerType == AsphaltRevetmentTopLayerType::HydraulicAsphaltConcrete;
        };

        const function validateGrassRevetmentTopLayerType = [](
            const GrassRevetmentTopLayerType topLayerType)
        {
            return topLayerType == GrassRevetmentTopLayerType::ClosedSod || topLayerType == GrassRevetmentTopLayerType::OpenSod;
        };

        const function validateNaturalStoneRevetmentTopLayerType = [](
            const NaturalStoneRevetmentTopLayerType topLayerType)
        {
            return topLayerType == NaturalStoneRevetmentTopLayerType::NordicStone;
        };

        return ranges::all_of(_locationConstructionPropertiesItemReferences,
                              [this, &validateLocationOnOuterSlope, &validateLocationOnCrestOrInnerSlope, &validateAsphaltRevetmentTopLayerType,
                                  &validateGrassRevetmentTopLayerType, &validateNaturalStoneRevetmentTopLayerType, &
                                  validateOvertoppingLocationSpecificProperties](
                          const reference_wrapper<RevetmentLocationConstructionPropertiesBase> locationConstructionPropertiesItemReference)
                              {
                                  const auto& locationConstructionPropertiesItem = locationConstructionPropertiesItemReference.get();

                                  return ValidateLocation<AsphaltRevetmentWaveImpactLocationConstructionProperties>(
                                              locationConstructionPropertiesItem, validateLocationOnOuterSlope,
                                              validateAsphaltRevetmentTopLayerType)
                                          && ValidateLocation<GrassRevetmentOvertoppingLocationConstructionProperties>(
                                              locationConstructionPropertiesItem, validateLocationOnCrestOrInnerSlope,
                                              validateGrassRevetmentTopLayerType,
                                              validateOvertoppingLocationSpecificProperties)
                                          && ValidateLocation<GrassRevetmentWaveImpactLocationConstructionProperties>(
                                              locationConstructionPropertiesItem, validateLocationOnOuterSlope, validateGrassRevetmentTopLayerType)
                                          && ValidateLocation<GrassRevetmentWaveRunupRayleighLocationConstructionProperties>(
                                              locationConstructionPropertiesItem, validateLocationOnOuterSlope, validateGrassRevetmentTopLayerType)
                                          && ValidateLocation<NaturalStoneRevetmentLocationConstructionProperties>(
                                              locationConstructionPropertiesItem, validateLocationOnOuterSlope,
                                              validateNaturalStoneRevetmentTopLayerType);
                              });
    }

    template <typename TConstructionProperties, typename TValidateX, typename TValidateTopLayer>
    bool CalculationInputBuilder::ValidateLocation(
        const RevetmentLocationConstructionPropertiesBase& constructionProperties,
        const TValidateX& validateLocationX,
        const TValidateTopLayer& validateTopLayer) const
    {
        if (const auto* location = dynamic_cast<const TConstructionProperties*>(&constructionProperties))
        {
            const auto locationX = location->GetX();
            if (!validateLocationX(locationX))
            {
                return false;
            }

            if (!validateTopLayer(location->GetTopLayerType()))
            {
                stringstream locationXStringStream;
                locationXStringStream << locationX;
                RegisterValidationError("The location with position " + locationXStringStream.str() + " has an invalid top layer type.");
                return false;
            }
        }

        return true;
    }

    template <typename TConstructionProperties, typename TValidateX, typename TValidateTopLayer, typename TValidateLocationSpecificProperties>
    bool CalculationInputBuilder::ValidateLocation(
        const RevetmentLocationConstructionPropertiesBase& constructionProperties,
        const TValidateX& validateLocationX,
        const TValidateTopLayer& validateTopLayer,
        const TValidateLocationSpecificProperties& validateLocationSpecificProperties) const
    {
        if (const auto* location = dynamic_cast<const TConstructionProperties*>(&constructionProperties))
        {
            const auto locationX = location->GetX();
            if (!validateLocationX(locationX))
            {
                return false;
            }

            if (!validateTopLayer(location->GetTopLayerType()))
            {
                stringstream locationXStringStream;
                locationXStringStream << locationX;
                RegisterValidationError("The location on X: " + locationXStringStream.str() + " has an invalid top layer type.");
                return false;
            }

            if (!validateLocationSpecificProperties(location))
            {
                return false;
            }
        }

        return true;
    }

    bool CalculationInputBuilder::ValidateLocationOnOuterSlope(
        const ProfileDataFactoryPoint& outerToe,
        const ProfileDataFactoryPoint& outerCrest,
        const double locationX) const
    {
        if (locationX <= outerToe.GetX() || locationX >= outerCrest.GetX())
        {
            stringstream locationXStringStream;
            locationXStringStream << locationX;

            RegisterValidationError(
                "The location with position " + locationXStringStream.str() + " must be between the outer toe and outer crest.");
            return false;
        }

        return true;
    }

    bool CalculationInputBuilder::ValidateLocationOnCrestOrInnerSlope(
        const ProfileDataFactoryPoint& outerCrest,
        const ProfileDataFactoryPoint& innerToe,
        const double locationX) const
    {
        if (locationX < outerCrest.GetX() || locationX > innerToe.GetX())
        {
            stringstream locationXStringStream;
            locationXStringStream << locationX;

            RegisterValidationError(
                "The location with position " + locationXStringStream.str() + " must be on or between the outer crest and inner toe.");
            return false;
        }

        return true;
    }

    bool CalculationInputBuilder::ValidateTimeSteps() const
    {
        if (_timeStepDataItems.empty())
        {
            RegisterValidationError("At least 1 time step is required.");
            return false;
        }

        const TimeDependentInputFactoryData* previousTimeStep = nullptr;
        for (const auto& timeStepDataItem : _timeStepDataItems)
        {
            const TimeDependentInputFactoryData* currentTimeStep = timeStepDataItem.get();

            const int currentTimeStepBeginTime = currentTimeStep->GetBeginTime();
            if (previousTimeStep != nullptr)
            {
                if (const int previousTimeStepEndTime = previousTimeStep->GetEndTime(); previousTimeStepEndTime != currentTimeStepBeginTime)
                {
                    RegisterValidationError(
                        "The begin time of the time step (" + to_string(currentTimeStepBeginTime) + ") must be equal to the end time of the " +
                        "previous time step (" + to_string(previousTimeStepEndTime) + ").");
                    return false;
                }
            }

            if (const int currentTimeStepEndTime = currentTimeStep->GetEndTime(); currentTimeStepBeginTime >= currentTimeStepEndTime)
            {
                RegisterValidationError(
                    "The begin time of the time step (" + to_string(currentTimeStepBeginTime) + ") must be smaller than the end time of the " +
                    "time step (" + to_string(currentTimeStepEndTime) + ").");
                return false;
            }

            previousTimeStep = currentTimeStep;
        }

        return true;
    }

    bool CalculationInputBuilder::ValidateOvertoppingLocationSpecificProperties(
        const GrassRevetmentOvertoppingLocationConstructionProperties* constructionProperties,
        const ProfileDataFactoryPoint& outerToe,
        const ProfileDataFactoryPoint& outerCrest) const
    {
        vector<double> xValuesProfile;
        vector<double> zValuesProfile;
        vector<double> roughnessCoefficients;

        for (const auto& profileSegment : _profileSegmentDataItemReferences)
        {
            const auto& profileSegmentReference = profileSegment.get();
            if (const auto& startPointX = profileSegmentReference.GetStartPointX(); startPointX >= outerToe.GetX()
                && startPointX < outerCrest.GetX())
            {
                xValuesProfile.push_back(startPointX);
                zValuesProfile.push_back(profileSegmentReference.GetStartPointZ());
                roughnessCoefficients.push_back(InputFactoryHelper::GetValue(profileSegmentReference.GetRoughnessCoefficient(),
                                                                             ProfileSegmentDefaults::GetRoughnessCoefficient()));
            }
        }

        xValuesProfile.push_back(outerCrest.GetX());
        const auto outerCrestZ = FindMatchingZCoordinateOnSegment(outerCrest.GetX());
        zValuesProfile.push_back(outerCrestZ);

        const double dikeHeight = InputFactoryHelper::GetValue(constructionProperties->GetDikeHeight(), outerCrestZ);
        if (const auto messages = Overtopping::OvertoppingAdapter::Validate(xValuesProfile, zValuesProfile, roughnessCoefficients, dikeHeight);
            !messages.empty())
        {
            for (const auto& message : messages)
            {
                RegisterValidationError(*message);
            }

            return false;
        }

        return true;
    }

    double CalculationInputBuilder::FindMatchingZCoordinateOnSegment(
        const double xCoordinate) const
    {
        for (const auto& segment : _profileSegmentDataItemReferences)
        {
            const auto& segmentReference = segment.get();
            if (const auto& segmentStartPointX = segmentReference.GetStartPointX();
                NumericsHelper::AreEqual(xCoordinate, segmentStartPointX))
            {
                return segmentReference.GetStartPointZ();
            }
        }

        return _profileSegmentDataItemReferences.back().get().GetEndPointZ();
    }

    void CalculationInputBuilder::RegisterValidationError(
        const string& message) const
    {
        EventRegistry::Register(make_unique<Event>(message, EventType::Error));
    }
}
