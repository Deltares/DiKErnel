#include <filesystem>
#include <fstream>

#include "catch2/catch.hpp"

#include "InputComposer.h"
#include "TestDataHelper.h"

namespace DiKErnel::KernelWrapper::Json::Test
{
    TEST_CASE("InputComposerTest")
    {
        SECTION("ReadCalculationData_Always_ReturnsCalculationData")
        {
            // Setup
            const auto filePath = TestUtil::TestDataHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Test") / "calculation.json";

            InputComposer inputComposer;

            std::ifstream ifs(filePath);
            nlohmann::json json = nlohmann::json::parse(ifs);

            // Call
            CalculationData calculationData = inputComposer.ReadCalculationData(json);

            // Assert
            REQUIRE_THAT(calculationData.time, Catch::Equals<int>({ 0, 100, 500, 800, 1200, 2000 }));
        }

        SECTION("ReadHydraulicLoads_Always_ReturnsHydraulicLoads")
        {
            // Setup
            const auto filePath = TestUtil::TestDataHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Test") / "calculation.json";

            InputComposer inputComposer;

            std::ifstream ifs(filePath);
            nlohmann::json json = nlohmann::json::parse(ifs);

            // Call
            HydraulicLoads hydraulicLoads = inputComposer.ReadHydraulicLoads(json);

            // Assert
            REQUIRE(hydraulicLoads.waveAngleMaximum == 78);
        }

        SECTION("ReadLocations_Always_ReturnsCalculationLocations")
        {
            // Setup
            const auto filePath = TestUtil::TestDataHelper::GetTestDataPath("DiKErnel.KernelWrapper.Json.Test") / "calculation.json";

            InputComposer inputComposer;

            std::ifstream ifs(filePath);
            nlohmann::json json = nlohmann::json::parse(ifs);

            // Call
            std::vector<CalculationLocation> calculationLocations = inputComposer.ReadLocations(json);

            // Assert
            REQUIRE(calculationLocations[0].name == "LocatieZwak");
        }
    }
}
