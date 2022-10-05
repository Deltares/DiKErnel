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

#include <functional>

#include "CalculationInput.h"
#include "EventRegistry.h"
#include "InputHelper.h"
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
    using namespace External::Overtopping;
    using namespace std;
    using namespace Util;

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
            const ProfileDataFactorySegment& currentSegment = *profileSegmentDataItem;

            if (previousSegment != nullptr)
            {
                const auto previousSegmentEndPointX = previousSegment->GetEndPointX();
                const auto previousSegmentEndPointZ = previousSegment->GetEndPointZ();

                const auto currentSegmentStartPointX = currentSegment.GetStartPointX();
                const auto currentSegmentStartPointZ = currentSegment.GetStartPointZ();

                if (!NumericsHelper::AreEqual(previousSegmentEndPointX, currentSegmentStartPointX)
                    || !NumericsHelper::AreEqual(previousSegmentEndPointZ, currentSegmentStartPointZ))
                {
                    RegisterValidationError(
                        "The start point of the profile segment (" + NumericsHelper::ToString(currentSegmentStartPointX) + ", " +
                        NumericsHelper::ToString(currentSegmentStartPointZ) + ") must be equal to the end point of the previous profile segment (" +
                        NumericsHelper::ToString(previousSegmentEndPointX) + ", " + NumericsHelper::ToString(previousSegmentEndPointZ) + ").");
                    return false;
                }
            }

            previousSegment = &currentSegment;
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
            if (NumericsHelper::AreEqual(profileSegment->GetStartPointX(), characteristicPointX))
            {
                return true;
            }
        }

        if (NumericsHelper::AreEqual(_profileSegmentDataItems.back()->GetEndPointX(), characteristicPointX))
        {
            return true;
        }

        RegisterValidationError("The " + characteristicPointName + " must be on a start or end point of a profile segment.");
        return false;
    }

    ProfileDataFactoryPoint* CalculationInputBuilder::GetProfilePointDataItemForCharacteristicPointType(
        const CharacteristicPointType characteristicPointType) const
    {
        for (const auto& profilePoint : _profilePointDataItems)
        {
            if (profilePoint->GetCharacteristicPoint() == characteristicPointType)
            {
                return profilePoint.get();
            }
        }

        return nullptr;
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

        for (const auto& location : _locationConstructionPropertiesItems)
        {
            const auto* locationReference = location.get();
            if (const auto* asphaltWaveImpactLocationConstructionProperties = dynamic_cast<const
                    AsphaltRevetmentWaveImpactLocationConstructionProperties*>(locationReference);
                asphaltWaveImpactLocationConstructionProperties != nullptr
                && !ValidateAsphaltRevetmentWaveImpactLocationConstructionProperties(
                    *asphaltWaveImpactLocationConstructionProperties, outerToe, outerCrest))
            {
                return false;
            }

            if (const auto* grassOvertoppingLocationConstructionProperties = dynamic_cast<const
                    GrassRevetmentOvertoppingLocationConstructionProperties*>(locationReference);
                grassOvertoppingLocationConstructionProperties != nullptr
                && !ValidateGrassRevetmentOvertoppingLocationConstructionProperties(
                    *grassOvertoppingLocationConstructionProperties, outerToe, outerCrest, *innerToe))
            {
                return false;
            }

            if (const auto* grassWaveImpactLocationConstructionProperties = dynamic_cast<const
                    GrassRevetmentWaveImpactLocationConstructionProperties*>(locationReference);
                grassWaveImpactLocationConstructionProperties != nullptr
                && !ValidateGrassRevetmentWaveImpactLocationConstructionProperties(
                    *grassWaveImpactLocationConstructionProperties, outerToe, outerCrest))
            {
                return false;
            }

            if (const auto* grassWaveRunupRayleighLocationConstructionProperties = dynamic_cast<const
                    GrassRevetmentWaveRunupRayleighLocationConstructionProperties*>(locationReference);
                grassWaveRunupRayleighLocationConstructionProperties != nullptr
                && !ValidateGrassRevetmentWaveRunupRayleighLocationConstructionProperties(
                    *grassWaveRunupRayleighLocationConstructionProperties, outerToe, outerCrest))
            {
                return false;
            }

            if (const auto* naturalStoneLocationConstructionProperties = dynamic_cast<const NaturalStoneRevetmentLocationConstructionProperties*>(
                    locationReference); naturalStoneLocationConstructionProperties != nullptr
                && !ValidateNaturalStoneRevetmentLocationConstructionProperties(*naturalStoneLocationConstructionProperties, outerToe, outerCrest))
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
            RegisterValidationError(
                "The location with position " + NumericsHelper::ToString(locationX) + " must be between the outer toe and outer crest.");
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
            RegisterValidationError(
                "The location with position " + NumericsHelper::ToString(locationX) + " must be on or between the outer crest and inner toe.");
            return false;
        }

        return true;
    }

    bool CalculationInputBuilder::ValidateAsphaltRevetmentWaveImpactLocationConstructionProperties(
        const AsphaltRevetmentWaveImpactLocationConstructionProperties& constructionProperties,
        const ProfileDataFactoryPoint& outerToe,
        const ProfileDataFactoryPoint& outerCrest) const
    {
        const auto locationX = constructionProperties.GetX();
        return ValidateLocationOnOuterSlope(outerToe, outerCrest, locationX)
                && ValidateAsphaltRevetmentTopLayerType(constructionProperties.GetTopLayerType(), locationX);
    }

    bool CalculationInputBuilder::ValidateGrassRevetmentOvertoppingLocationConstructionProperties(
        const GrassRevetmentOvertoppingLocationConstructionProperties& constructionProperties,
        const ProfileDataFactoryPoint& outerToe,
        const ProfileDataFactoryPoint& outerCrest,
        const ProfileDataFactoryPoint& innerToe) const
    {
        const auto locationX = constructionProperties.GetX();
        return ValidateLocationOnCrestOrInnerSlope(outerCrest, innerToe, locationX)
                && ValidateGrassRevetmentTopLayerType(constructionProperties.GetTopLayerType(), locationX)
                && ValidateOvertoppingLocationSpecificProperties(constructionProperties, outerToe, outerCrest);
    }

    bool CalculationInputBuilder::ValidateGrassRevetmentWaveImpactLocationConstructionProperties(
        const GrassRevetmentWaveImpactLocationConstructionProperties& constructionProperties,
        const ProfileDataFactoryPoint& outerToe,
        const ProfileDataFactoryPoint& outerCrest) const
    {
        const auto locationX = constructionProperties.GetX();
        return ValidateLocationOnOuterSlope(outerToe, outerCrest, locationX)
                && ValidateGrassRevetmentTopLayerType(constructionProperties.GetTopLayerType(), locationX);
    }

    bool CalculationInputBuilder::ValidateGrassRevetmentWaveRunupRayleighLocationConstructionProperties(
        const GrassRevetmentWaveRunupRayleighLocationConstructionProperties& constructionProperties,
        const ProfileDataFactoryPoint& outerToe,
        const ProfileDataFactoryPoint& outerCrest) const
    {
        const auto locationX = constructionProperties.GetX();
        return ValidateLocationOnOuterSlope(outerToe, outerCrest, locationX)
                && ValidateGrassRevetmentTopLayerType(constructionProperties.GetTopLayerType(), locationX);
    }

    bool CalculationInputBuilder::ValidateNaturalStoneRevetmentLocationConstructionProperties(
        const NaturalStoneRevetmentLocationConstructionProperties& constructionProperties,
        const ProfileDataFactoryPoint& outerToe,
        const ProfileDataFactoryPoint& outerCrest) const
    {
        const auto locationX = constructionProperties.GetX();
        return ValidateLocationOnOuterSlope(outerToe, outerCrest, locationX)
                && ValidateNaturalStoneRevetmentTopLayerType(constructionProperties.GetTopLayerType(), locationX);
    }

    bool CalculationInputBuilder::ValidateGrassRevetmentTopLayerType(
        const GrassRevetmentTopLayerType topLayerType,
        const double locationX) const
    {
        if (topLayerType != GrassRevetmentTopLayerType::ClosedSod && topLayerType != GrassRevetmentTopLayerType::OpenSod)
        {
            RegisterValidationError(
                "The location with position " + NumericsHelper::ToString(locationX) + " has an invalid top layer type.");
            return false;
        }

        return true;
    }

    bool CalculationInputBuilder::ValidateAsphaltRevetmentTopLayerType(
        const AsphaltRevetmentTopLayerType topLayerType,
        const double locationX) const
    {
        if (topLayerType != AsphaltRevetmentTopLayerType::HydraulicAsphaltConcrete)
        {
            RegisterValidationError(
                "The location with position " + NumericsHelper::ToString(locationX) + " has an invalid top layer type.");
            return false;
        }

        return true;
    }

    bool CalculationInputBuilder::ValidateNaturalStoneRevetmentTopLayerType(
        const NaturalStoneRevetmentTopLayerType topLayerType,
        const double locationX) const
    {
        if (topLayerType != NaturalStoneRevetmentTopLayerType::NordicStone)
        {
            RegisterValidationError(
                "The location with position " + NumericsHelper::ToString(locationX) + " has an invalid top layer type.");
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
            const TimeDependentInputFactoryData& currentTimeStep = *timeStepDataItem;

            const int currentTimeStepBeginTime = currentTimeStep.GetBeginTime();
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

            if (const int currentTimeStepEndTime = currentTimeStep.GetEndTime(); currentTimeStepBeginTime >= currentTimeStepEndTime)
            {
                RegisterValidationError(
                    "The begin time of the time step (" + to_string(currentTimeStepBeginTime) + ") must be smaller than the end time of the " +
                    "time step (" + to_string(currentTimeStepEndTime) + ").");
                return false;
            }

            previousTimeStep = &currentTimeStep;
        }

        return true;
    }

    bool CalculationInputBuilder::ValidateOvertoppingLocationSpecificProperties(
        const GrassRevetmentOvertoppingLocationConstructionProperties& constructionProperties,
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
                roughnessCoefficients.push_back(InputHelper::GetValue(profileSegmentReference.GetRoughnessCoefficient(),
                                                                      ProfileSegmentDefaults::GetRoughnessCoefficient()));

                if (const auto& endPointX = profileSegmentReference.GetEndPointX(); NumericsHelper::AreEqual(endPointX, outerCrest.GetX()))
                {
                    xValuesProfile.push_back(endPointX);
                    zValuesProfile.push_back(profileSegmentReference.GetEndPointZ());
                }
            }
        }

        const double outerCrestZ = zValuesProfile.back();
        const double dikeHeight = GetOvertoppingDikeHeight(constructionProperties.GetDikeHeight(), outerCrestZ);
        if (const auto messages = OvertoppingAdapter::Validate(xValuesProfile, zValuesProfile, roughnessCoefficients, dikeHeight);
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

    double CalculationInputBuilder::GetOvertoppingDikeHeight(
        const double* locationDikeHeight,
        const double outerCrestZCoordinate)
    {
        if (locationDikeHeight != nullptr)
        {
            return *locationDikeHeight;
        }

        return outerCrestZCoordinate;
    }

    void CalculationInputBuilder::RegisterValidationError(
        const string& message) const
    {
        EventRegistry::Register(make_unique<Event>(message, EventType::Error));
    }
}
