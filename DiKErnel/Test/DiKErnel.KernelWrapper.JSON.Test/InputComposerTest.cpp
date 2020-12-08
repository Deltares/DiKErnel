#include <filesystem>
#include <iostream>

#include "catch2/catch.hpp"

#include "InputComposer.h"
#include "TestDataHelper.h"

namespace DiKErnel::KernelWrapper::Json::Test
{
    TEST_CASE("InputComposerTest")
    {
        SECTION("GetDomainParametersFromJson_Always_ReturnsTimes")
        {
            // Setup
            const auto filePath = TestUtil::TestDataHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Test") / "calculation.json";
        
            const InputComposer inputComposer;
        
            // Call
            inputComposer.GetDomainParametersFromJson(filePath.string());
        
            // Assert
            REQUIRE(filePath == "filepath");
        }
    }
}
