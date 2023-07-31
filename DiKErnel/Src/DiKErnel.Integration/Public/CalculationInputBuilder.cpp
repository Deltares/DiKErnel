
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
        const auto* crestOuterBerm = GetProfilePointDataItemForCharacteristicPointType(CharacteristicPointType::CrestOuterBerm);
        const auto* notchOuterBerm = GetProfilePointDataItemForCharacteristicPointType(CharacteristicPointType::NotchOuterBerm);
        const auto* innerCrest = GetProfilePointDataItemForCharacteristicPointType(CharacteristicPointType::InnerCrest);

        return ValidateCharacteristicPoint(outerToe, "outer toe")
                && ValidateCharacteristicPoint(crestOuterBerm, "crest outer berm", false)
                && ValidateCharacteristicPoint(notchOuterBerm, "notch outer berm", false)
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
            if (const auto* asphaltWaveImpactLocationConstructionProperties = dynamic_cast<
                    const AsphaltRevetmentWaveImpactLocationConstructionProperties*>(locationReference);
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

    void CalculationInputBuilder::RegisterValidationError(
        const string& message) const
    {
        EventRegistry::Register(make_unique<Event>(message, EventType::Error));
    }
}
