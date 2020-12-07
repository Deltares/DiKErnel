#include <filesystem>
#include <iostream>

#include "catch2/catch.hpp"

#include "InputComposer.h"
#include "TestDataHelper.h"

namespace DiKErnel::KernelWrapper::Json::Test
{
    TEST_CASE("InputComposerTest")
    {
        // SECTION("GetDomainParametersFromJson_Always_ReturnsTimes")
        // {
        //     // Setup
        //     const auto filePath = TestUtil::TestDataHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Test") / "calculation.json";
        //
        //     const InputComposer inputComposer;
        //
        //     // Call
        //     const auto times = inputComposer.GetDomainParametersFromJson(filePath.string());
        //
        //     // Assert
        //     REQUIRE_THAT(times, Catch::Equals<int>({0, 100, 500, 800, 1200, 2000 }));
        // }
    }
}
