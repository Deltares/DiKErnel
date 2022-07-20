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

#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "AsphaltRevetmentWaveImpactLocationDependentOutput.h"
#include "AsphaltRevetmentWaveImpactTimeDependentOutput.h"
#include "EventAssertHelper.h"
#include "FileAssert.h"
#include "GrassRevetmentWaveImpactLocationDependentOutput.h"
#include "GrassRevetmentWaveImpactTimeDependentOutput.h"
#include "GrassRevetmentWaveRunupRayleighLocationDependentOutput.h"
#include "GrassRevetmentWaveRunupRayleighTimeDependentOutput.h"
#include "JsonOutputComposer.h"
#include "LocationDependentOutputMock.h"
#include "NaturalStoneRevetmentLocationDependentOutput.h"
#include "NaturalStoneRevetmentTimeDependentOutput.h"
#include "TestDataPathHelper.h"
#include "TimeDependentOutputMock.h"

namespace DiKErnel::KernelWrapper::Json::Output::Test
{
    using namespace Core;
    using namespace Core::TestUtil;
    using namespace DiKErnel::TestUtil;
    using namespace Integration;
    using namespace std;
    using namespace testing;
    using namespace Util;
    using namespace Util::TestUtil;

    struct JsonOutputComposerTest : Test
    {
        const string _actualOutputFilePath = (filesystem::temp_directory_path() / "actualOutput.json").string();

        ~JsonOutputComposerTest() override
        {
            remove(_actualOutputFilePath.c_str());
        }

        void PerformTest(
            const string& filename,
            const JsonOutputType outputType,
            const bool withMetaData) const
        {
            // Setup
            const auto expectedOutputFilePath = (TestDataPathHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Output.Test")
                / "JsonOutputComposerTest" / filename).string();

            auto location1TimeDependentOutputItems = vector<unique_ptr<TimeDependentOutput>>();
            location1TimeDependentOutputItems.push_back(make_unique<TimeDependentOutputMock>(0, 0.15, nullptr));
            location1TimeDependentOutputItems.push_back(make_unique<TimeDependentOutputMock>(0, 0.253, make_unique<int>(60)));

            auto location2TimeDependentOutputItems = vector<unique_ptr<TimeDependentOutput>>();
            location2TimeDependentOutputItems.push_back(make_unique<TimeDependentOutputMock>(0, 0.28, nullptr));
            location2TimeDependentOutputItems.push_back(make_unique<TimeDependentOutputMock>(0, 0.512, nullptr));

            vector<unique_ptr<LocationDependentOutput>> locations;
            locations.push_back(make_unique<LocationDependentOutputMock>(1.1, move(location1TimeDependentOutputItems)));
            locations.push_back(make_unique<LocationDependentOutputMock>(2.2, move(location2TimeDependentOutputItems)));

            const CalculationOutput calculationOutput(move(locations));

            auto metaDataItems = vector<pair<string, variant<double, string>>>();

            if (withMetaData)
            {
                metaDataItems.emplace_back("Test 1", 1.23);
                metaDataItems.emplace_back("Test 2", "4.56");
            }

            // Call
            const auto& result = JsonOutputComposer::WriteCalculationOutputToJson(_actualOutputFilePath, calculationOutput, outputType,
                                                                                  metaDataItems);

            // Assert
            FileAssert::AssertFileContents(expectedOutputFilePath, _actualOutputFilePath);
            ASSERT_TRUE(result->GetSuccessful());
            ASSERT_EQ(0, result->GetEvents().size());
        }

        void PerformPhysicsTest(
            const string& filename,
            const CalculationOutput& calculationOutput,
            const bool withMetaData) const
        {
            // Setup
            auto metaDataItems = vector<pair<string, variant<double, string>>>();

            if (withMetaData)
            {
                metaDataItems.emplace_back(pair("Test 1", 1.23));
                metaDataItems.emplace_back(pair("Test 2", "4.56"));
            }

            // Call
            const auto& result = JsonOutputComposer::WriteCalculationOutputToJson(_actualOutputFilePath, calculationOutput, JsonOutputType::Physics,
                                                                                  metaDataItems);

            // Assert
            const auto expectedOutputFilePath = (TestDataPathHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Output.Test")
                / "JsonOutputComposerTest" / filename).string();
            FileAssert::AssertFileContents(expectedOutputFilePath, _actualOutputFilePath);
            ASSERT_TRUE(result->GetSuccessful());
            ASSERT_EQ(0, result->GetEvents().size());
        }

        [[nodiscard]]
        unique_ptr<CalculationOutput> CreateCalculationOutputWithRevetmentSpecificTimeDependentOutputWithAllDataSet() const
        {
            AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties asphaltWaveImpactTimeDependentOutputConstructionProperties;
            asphaltWaveImpactTimeDependentOutputConstructionProperties._incrementDamage = make_unique<double>(0.1);
            asphaltWaveImpactTimeDependentOutputConstructionProperties._damage = make_unique<double>(0.2);
            asphaltWaveImpactTimeDependentOutputConstructionProperties._timeOfFailure = make_unique<int>(3);
            asphaltWaveImpactTimeDependentOutputConstructionProperties._logFailureTension = make_unique<double>(0.4);
            asphaltWaveImpactTimeDependentOutputConstructionProperties._maximumPeakStress = make_unique<double>(0.5);
            asphaltWaveImpactTimeDependentOutputConstructionProperties._stiffnessRelation = make_unique<double>(0.6);
            asphaltWaveImpactTimeDependentOutputConstructionProperties._computationalThickness = make_unique<double>(0.7);
            asphaltWaveImpactTimeDependentOutputConstructionProperties._equivalentElasticModulus = make_unique<double>(0.8);
            auto asphaltWaveImpactTimeDependentOutput = make_unique<AsphaltRevetmentWaveImpactTimeDependentOutput>(
                asphaltWaveImpactTimeDependentOutputConstructionProperties);

            GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties grassWaveImpactTimeDependentOutputConstructionProperties;
            grassWaveImpactTimeDependentOutputConstructionProperties._incrementDamage = make_unique<double>(0.9);
            grassWaveImpactTimeDependentOutputConstructionProperties._damage = make_unique<double>(1.0);
            grassWaveImpactTimeDependentOutputConstructionProperties._timeOfFailure = make_unique<int>(11);
            grassWaveImpactTimeDependentOutputConstructionProperties._loadingRevetment = make_unique<bool>(true);
            grassWaveImpactTimeDependentOutputConstructionProperties._upperLimitLoading = make_unique<double>(1.2);
            grassWaveImpactTimeDependentOutputConstructionProperties._lowerLimitLoading = make_unique<double>(1.3);
            grassWaveImpactTimeDependentOutputConstructionProperties._minimumWaveHeight = make_unique<double>(1.4);
            grassWaveImpactTimeDependentOutputConstructionProperties._maximumWaveHeight = make_unique<double>(1.5);
            grassWaveImpactTimeDependentOutputConstructionProperties._waveAngleImpact = make_unique<double>(1.6);
            grassWaveImpactTimeDependentOutputConstructionProperties._waveHeightImpact = make_unique<double>(1.7);
            auto grassWaveImpactTimeDependentOutput = make_unique<GrassRevetmentWaveImpactTimeDependentOutput>(
                grassWaveImpactTimeDependentOutputConstructionProperties);

            GrassRevetmentWaveRunupRayleighTimeDependentOutputConstructionProperties
                    grassWaveRunupRayleighTimeDependentOutputConstructionProperties;
            grassWaveRunupRayleighTimeDependentOutputConstructionProperties._incrementDamage = make_unique<double>(1.8);
            grassWaveRunupRayleighTimeDependentOutputConstructionProperties._damage = make_unique<double>(1.9);
            grassWaveRunupRayleighTimeDependentOutputConstructionProperties._timeOfFailure = make_unique<int>(20);
            grassWaveRunupRayleighTimeDependentOutputConstructionProperties._verticalDistanceWaterLevelElevation = make_unique<double>(2.1);
            grassWaveRunupRayleighTimeDependentOutputConstructionProperties._waveAngleImpact = make_unique<double>(2.2);
            grassWaveRunupRayleighTimeDependentOutputConstructionProperties._representativeWaveRunup2P = make_unique<double>(2.3);
            grassWaveRunupRayleighTimeDependentOutputConstructionProperties._cumulativeOverload = make_unique<double>(2.4);
            auto grassWaveRunupRayleighTimeDependentOutput = make_unique<GrassRevetmentWaveRunupRayleighTimeDependentOutput>(
                grassWaveRunupRayleighTimeDependentOutputConstructionProperties);

            NaturalStoneRevetmentTimeDependentOutputConstructionProperties naturalStoneTimeDependentOutputConstructionProperties;
            naturalStoneTimeDependentOutputConstructionProperties._incrementDamage = make_unique<double>(2.5);
            naturalStoneTimeDependentOutputConstructionProperties._damage = make_unique<double>(2.6);
            naturalStoneTimeDependentOutputConstructionProperties._timeOfFailure = make_unique<int>(27);
            naturalStoneTimeDependentOutputConstructionProperties._outerSlope = make_unique<double>(2.8);
            naturalStoneTimeDependentOutputConstructionProperties._slopeUpperLevel = make_unique<double>(2.9);
            naturalStoneTimeDependentOutputConstructionProperties._slopeUpperPosition = make_unique<double>(3.0);
            naturalStoneTimeDependentOutputConstructionProperties._slopeLowerLevel = make_unique<double>(3.1);
            naturalStoneTimeDependentOutputConstructionProperties._slopeLowerPosition = make_unique<double>(3.2);
            naturalStoneTimeDependentOutputConstructionProperties._loadingRevetment = make_unique<bool>(true);
            naturalStoneTimeDependentOutputConstructionProperties._surfSimilarityParameter = make_unique<double>(3.3);
            naturalStoneTimeDependentOutputConstructionProperties._waveSteepnessDeepWater = make_unique<double>(3.4);
            naturalStoneTimeDependentOutputConstructionProperties._upperLimitLoading = make_unique<double>(3.5);
            naturalStoneTimeDependentOutputConstructionProperties._lowerLimitLoading = make_unique<double>(3.6);
            naturalStoneTimeDependentOutputConstructionProperties._depthMaximumWaveLoad = make_unique<double>(3.7);
            naturalStoneTimeDependentOutputConstructionProperties._distanceMaximumWaveElevation = make_unique<double>(3.8);
            naturalStoneTimeDependentOutputConstructionProperties._normativeWidthOfWaveImpact = make_unique<double>(3.9);
            naturalStoneTimeDependentOutputConstructionProperties._hydraulicLoad = make_unique<double>(4.0);
            naturalStoneTimeDependentOutputConstructionProperties._waveAngleImpact = make_unique<double>(4.1);
            naturalStoneTimeDependentOutputConstructionProperties._resistance = make_unique<double>(4.2);
            naturalStoneTimeDependentOutputConstructionProperties._referenceTimeDegradation = make_unique<double>(4.3);
            naturalStoneTimeDependentOutputConstructionProperties._referenceDegradation = make_unique<double>(4.4);
            auto naturalStoneTimeDependentOutput = make_unique<NaturalStoneRevetmentTimeDependentOutput>(
                naturalStoneTimeDependentOutputConstructionProperties);

            vector<unique_ptr<TimeDependentOutput>> asphaltWaveImpactTimeDependentOutputs;
            asphaltWaveImpactTimeDependentOutputs.push_back(move(asphaltWaveImpactTimeDependentOutput));
            vector<unique_ptr<TimeDependentOutput>> grassWaveImpactTimeDependentOutputs;
            grassWaveImpactTimeDependentOutputs.push_back(move(grassWaveImpactTimeDependentOutput));
            vector<unique_ptr<TimeDependentOutput>> grassWaveRunupRayleighTimeDependentOutputs;
            grassWaveRunupRayleighTimeDependentOutputs.push_back(move(grassWaveRunupRayleighTimeDependentOutput));
            vector<unique_ptr<TimeDependentOutput>> naturalStoneTimeDependentOutputs;
            naturalStoneTimeDependentOutputs.push_back(move(naturalStoneTimeDependentOutput));

            vector<unique_ptr<LocationDependentOutput>> locations;
            locations.push_back(
                make_unique<AsphaltRevetmentWaveImpactLocationDependentOutput>(4.5, move(asphaltWaveImpactTimeDependentOutputs), 4.6));
            locations.push_back(make_unique<GrassRevetmentWaveImpactLocationDependentOutput>(4.7, move(grassWaveImpactTimeDependentOutputs)));
            locations.push_back(
                make_unique<GrassRevetmentWaveRunupRayleighLocationDependentOutput>(4.8, move(grassWaveRunupRayleighTimeDependentOutputs)));
            locations.push_back(make_unique<NaturalStoneRevetmentLocationDependentOutput>(4.9, move(naturalStoneTimeDependentOutputs)));

            return make_unique<CalculationOutput>(move(locations));
        }

        [[nodiscard]]
        unique_ptr<CalculationOutput> CreateCalculationOutputWithRevetmentSpecificTimeDependentOutputWithOnlyMandatoryDataSet() const
        {
            AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties asphaltWaveImpactTimeDependentOutputConstructionProperties;
            asphaltWaveImpactTimeDependentOutputConstructionProperties._incrementDamage = make_unique<double>(0.1);
            asphaltWaveImpactTimeDependentOutputConstructionProperties._damage = make_unique<double>(0.2);
            asphaltWaveImpactTimeDependentOutputConstructionProperties._timeOfFailure = nullptr;
            asphaltWaveImpactTimeDependentOutputConstructionProperties._logFailureTension = make_unique<double>(0.3);
            asphaltWaveImpactTimeDependentOutputConstructionProperties._maximumPeakStress = make_unique<double>(0.4);
            asphaltWaveImpactTimeDependentOutputConstructionProperties._stiffnessRelation = make_unique<double>(0.5);
            asphaltWaveImpactTimeDependentOutputConstructionProperties._computationalThickness = make_unique<double>(0.6);
            asphaltWaveImpactTimeDependentOutputConstructionProperties._equivalentElasticModulus = make_unique<double>(0.7);
            auto asphaltWaveImpactTimeDependentOutput = make_unique<AsphaltRevetmentWaveImpactTimeDependentOutput>(
                asphaltWaveImpactTimeDependentOutputConstructionProperties);

            GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties grassRevetmentWaveImpactTimeDependentOutputConstructionProperties;
            grassRevetmentWaveImpactTimeDependentOutputConstructionProperties._incrementDamage = make_unique<double>(0.8);
            grassRevetmentWaveImpactTimeDependentOutputConstructionProperties._damage = make_unique<double>(0.9);
            grassRevetmentWaveImpactTimeDependentOutputConstructionProperties._loadingRevetment = make_unique<bool>(true);
            grassRevetmentWaveImpactTimeDependentOutputConstructionProperties._upperLimitLoading = make_unique<double>(1.0);
            grassRevetmentWaveImpactTimeDependentOutputConstructionProperties._lowerLimitLoading = make_unique<double>(1.1);
            auto grassWaveImpactTimeDependentOutput = make_unique<GrassRevetmentWaveImpactTimeDependentOutput>(
                grassRevetmentWaveImpactTimeDependentOutputConstructionProperties);

            GrassRevetmentWaveRunupRayleighTimeDependentOutputConstructionProperties
                    grassWaveRunupRayleighTimeDependentOutputConstructionProperties;
            grassWaveRunupRayleighTimeDependentOutputConstructionProperties._incrementDamage = make_unique<double>(1.2);
            grassWaveRunupRayleighTimeDependentOutputConstructionProperties._damage = make_unique<double>(1.3);
            grassWaveRunupRayleighTimeDependentOutputConstructionProperties._verticalDistanceWaterLevelElevation = make_unique<double>(1.4);
            auto grassWaveRunupRayleighTimeDependentOutput = make_unique<GrassRevetmentWaveRunupRayleighTimeDependentOutput>(
                grassWaveRunupRayleighTimeDependentOutputConstructionProperties);

            NaturalStoneRevetmentTimeDependentOutputConstructionProperties naturalStoneTimeDependentOutputConstructionProperties;
            naturalStoneTimeDependentOutputConstructionProperties._incrementDamage = make_unique<double>(1.5);
            naturalStoneTimeDependentOutputConstructionProperties._damage = make_unique<double>(1.6);
            naturalStoneTimeDependentOutputConstructionProperties._outerSlope = make_unique<double>(1.7);
            naturalStoneTimeDependentOutputConstructionProperties._slopeUpperLevel = make_unique<double>(1.8);
            naturalStoneTimeDependentOutputConstructionProperties._slopeUpperPosition = make_unique<double>(1.9);
            naturalStoneTimeDependentOutputConstructionProperties._slopeLowerLevel = make_unique<double>(2.0);
            naturalStoneTimeDependentOutputConstructionProperties._slopeLowerPosition = make_unique<double>(2.1);
            naturalStoneTimeDependentOutputConstructionProperties._loadingRevetment = make_unique<bool>(true);
            naturalStoneTimeDependentOutputConstructionProperties._surfSimilarityParameter = make_unique<double>(2.2);
            naturalStoneTimeDependentOutputConstructionProperties._waveSteepnessDeepWater = make_unique<double>(2.3);
            naturalStoneTimeDependentOutputConstructionProperties._upperLimitLoading = make_unique<double>(2.4);
            naturalStoneTimeDependentOutputConstructionProperties._lowerLimitLoading = make_unique<double>(2.5);
            naturalStoneTimeDependentOutputConstructionProperties._depthMaximumWaveLoad = make_unique<double>(2.6);
            naturalStoneTimeDependentOutputConstructionProperties._distanceMaximumWaveElevation = make_unique<double>(2.7);
            naturalStoneTimeDependentOutputConstructionProperties._normativeWidthOfWaveImpact = make_unique<double>(2.8);
            auto naturalStoneTimeDependentOutput = make_unique<NaturalStoneRevetmentTimeDependentOutput>(
                naturalStoneTimeDependentOutputConstructionProperties);

            vector<unique_ptr<TimeDependentOutput>> asphaltWaveImpactTimeDependentOutputs;
            asphaltWaveImpactTimeDependentOutputs.push_back(move(asphaltWaveImpactTimeDependentOutput));
            vector<unique_ptr<TimeDependentOutput>> grassWaveImpactTimeDependentOutputs;
            grassWaveImpactTimeDependentOutputs.push_back(move(grassWaveImpactTimeDependentOutput));
            vector<unique_ptr<TimeDependentOutput>> grassWaveRunupRayleighTimeDependentOutputs;
            grassWaveRunupRayleighTimeDependentOutputs.push_back(move(grassWaveRunupRayleighTimeDependentOutput));
            vector<unique_ptr<TimeDependentOutput>> naturalStoneTimeDependentOutputs;
            naturalStoneTimeDependentOutputs.push_back(move(naturalStoneTimeDependentOutput));

            vector<unique_ptr<LocationDependentOutput>> locations;
            locations.push_back(
                make_unique<AsphaltRevetmentWaveImpactLocationDependentOutput>(2.9, move(asphaltWaveImpactTimeDependentOutputs), 3.0));
            locations.push_back(make_unique<GrassRevetmentWaveImpactLocationDependentOutput>(3.1, move(grassWaveImpactTimeDependentOutputs)));
            locations.push_back(
                make_unique<GrassRevetmentWaveRunupRayleighLocationDependentOutput>(3.2, move(grassWaveRunupRayleighTimeDependentOutputs)));
            locations.push_back(make_unique<NaturalStoneRevetmentLocationDependentOutput>(3.3, move(naturalStoneTimeDependentOutputs)));

            return make_unique<CalculationOutput>(move(locations));
        }
    };

    TEST_F(JsonOutputComposerTest, WriteCalculationOutputToJson_InvalidJsonOutputType_ReturnsResultWithSuccessfulFalseAndWithExpectedEvent)
    {
        /// Setup
        const CalculationOutput calculationOutput((vector<unique_ptr<LocationDependentOutput>>()));

        // Call
        const auto& result = JsonOutputComposer::WriteCalculationOutputToJson("", calculationOutput, static_cast<JsonOutputType>(99));

        // Assert
        ASSERT_FALSE(result->GetSuccessful());

        const auto& events = result->GetEvents();
        ASSERT_EQ(1, events.size());

        EventAssertHelper::AssertEvent(
            EventType::Error,
            "An unhandled error occurred while composing Json output from the calculation data. See stack trace for more information:\n"
            "Invalid JsonOutputType.",
            events.at(0).get());
    }

    TEST_F(JsonOutputComposerTest,
           WriteCalculationOutputToJson_JsonOutputTypeFailureWithoutMetaData_ReturnsResultWithSuccessfulTrueAndNoEventsAndWritesExpectedValues)
    {
        PerformTest("ExpectedFailureOutputWithoutMetaData.json", JsonOutputType::Failure, false);
    }

    TEST_F(JsonOutputComposerTest,
           WriteCalculationOutputToJson_JsonOutputTypeFailureWithMetaData_ReturnsResultWithSuccessfulTrueAndNoEventsAndWritesExpectedValues)
    {
        PerformTest("ExpectedFailureOutputWithMetaData.json", JsonOutputType::Failure, true);
    }

    TEST_F(JsonOutputComposerTest,
           WriteCalculationOutputToJson_JsonOutputTypeDamageWithoutMetaData_ReturnsResultWithSuccessfulTrueAndNoEventsAndWritesExpectedValues)
    {
        PerformTest("ExpectedDamageOutputWithoutMetaData.json", JsonOutputType::Damage, false);
    }

    TEST_F(JsonOutputComposerTest,
           WriteCalculationOutputToJson_JsonOutputTypeDamageWithMetaData_ReturnsResultWithSuccessfulTrueAndNoEventsAndWritesExpectedValues)
    {
        PerformTest("ExpectedDamageOutputWithMetaData.json", JsonOutputType::Damage, true);
    }

    TEST_F(JsonOutputComposerTest,
           WriteCalculationOutputToJson_JsonOutputTypePhysicsAndTimeDependentOutputNotSupported_ReturnsResultWithSuccessfulFalseAndWithExpectedEvent)
    {
        // Setup
        auto locationTimeDependentOutputItems = vector<unique_ptr<TimeDependentOutput>>();
        locationTimeDependentOutputItems.push_back(make_unique<TimeDependentOutputMock>(0, 0.15, nullptr));

        vector<unique_ptr<LocationDependentOutput>> locations;
        locations.push_back(make_unique<LocationDependentOutputMock>(1.1, move(locationTimeDependentOutputItems)));

        const CalculationOutput calculationOutput(move(locations));

        // Call
        const auto& result = JsonOutputComposer::WriteCalculationOutputToJson("", calculationOutput, JsonOutputType::Physics);

        // Assert
        ASSERT_FALSE(result->GetSuccessful());

        const auto& events = result->GetEvents();
        ASSERT_EQ(1, events.size());

        EventAssertHelper::AssertEvent(
            EventType::Error,
            "An unhandled error occurred while composing Json output from the calculation data. See stack trace for more information:\n"
            "Invalid revetment type.",
            events.at(0).get());
    }

    TEST_F(JsonOutputComposerTest,
           WriteCalculationOutputToJson_JsonOutputTypePhysicsWithAllDataAndMetaDataAndTimeDependentOutputSupported_ReturnsResultWithSuccessfulTrueAndNoEventsAndWritesExpectedValues)
    {
        PerformPhysicsTest("ExpectedPhysicsOutputWithAllDataAndMetaData.json",
                           *CreateCalculationOutputWithRevetmentSpecificTimeDependentOutputWithAllDataSet(), true);
    }

    TEST_F(JsonOutputComposerTest,
           WriteCalculationOutputToJson_JsonOutputTypePhysicsWithAllDataAndWithoutMetaDataAndTimeDependentOutputSupported_ReturnsResultWithSuccessfulTrueAndNoEventsAndWritesExpectedValues)
    {
        PerformPhysicsTest("ExpectedPhysicsOutputWithAllDataAndWithoutMetaData.json",
                           *CreateCalculationOutputWithRevetmentSpecificTimeDependentOutputWithAllDataSet(), false);
    }

    TEST_F(JsonOutputComposerTest,
           WriteCalculationOutputToJson_JsonOutputTypePhysicsWithOnlyMandatoryDataAndMetaDataAndTimeDependentOutputSupported_ReturnsResultWithSuccessfulTrueAndNoEventsAndWritesExpectedValues)
    {
        PerformPhysicsTest("ExpectedPhysicsOutputWithOnlyMandatoryDataAndMetaData.json",
                           *CreateCalculationOutputWithRevetmentSpecificTimeDependentOutputWithOnlyMandatoryDataSet(), true);
    }

    TEST_F(JsonOutputComposerTest,
           WriteCalculationOutputToJson_JsonOutputTypePhysicsWithOnlyMandatoryDataAndWithoutMetaDataAndTimeDependentOutputSupported_ReturnsResultWithSuccessfulTrueAndNoEventsAndWritesExpectedValues)
    {
        PerformPhysicsTest("ExpectedPhysicsOutputWithOnlyMandatoryDataAndWithoutMetaData.json",
                           *CreateCalculationOutputWithRevetmentSpecificTimeDependentOutputWithOnlyMandatoryDataSet(), false);
    }
}
