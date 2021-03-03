# Set library name
set(LIBNAME DiKErnel.KernelWrapper.Json.Input)

# Define sources
set(SOURCEFILES
  JsonInputAdapter.cpp
  JsonInputAdapter.h
  JsonInputComposer.cpp
  JsonInputComposer.h
)

set(SOURCEFILES_PARSER
  JsonInputDefinitions.h
  JsonInputParser.cpp
  JsonInputParser.h
)

set(SOURCEFILES_PARSER_DATA_BASE
  JsonInputCalculationData.cpp
  JsonInputCalculationData.h
  JsonInputDamageData.cpp
  JsonInputDamageData.h
  JsonInputData.cpp
  JsonInputData.h
  JsonInputHydraulicData.cpp
  JsonInputHydraulicData.h
  JsonInputLocationData.cpp
  JsonInputLocationData.h
  JsonInputProfileSchematizationData.cpp
  JsonInputProfileSchematizationData.h
  JsonInputRevetmentLocationData.cpp
  JsonInputRevetmentLocationData.h
  JsonInputTimeDependentHydraulicData.cpp
  JsonInputTimeDependentHydraulicData.h
)

set(SOURCEFILES_PARSER_DATA_REVETMENT
  JsonInputNaturalStoneRevetmentLocationData.cpp
  JsonInputNaturalStoneRevetmentLocationData.h
)

# Add library
add_library(${LIBNAME} STATIC ${SOURCEFILES} ${SOURCEFILES_PARSER} ${SOURCEFILES_PARSER_DATA_BASE} ${SOURCEFILES_PARSER_DATA_REVETMENT})

# Configure folder structure
set_target_properties(${LIBNAME} PROPERTIES FOLDER Src)
source_group("Sources" FILES ${SOURCEFILES})
source_group("Sources/Parser" FILES ${SOURCEFILES_PARSER})
source_group("Sources/Parser/Data/Base" FILES ${SOURCEFILES_PARSER_DATA_BASE})
source_group("Sources/Parser/Data/Revetment" FILES ${SOURCEFILES_PARSER_DATA_REVETMENT})

# Fetch third party libraries
include(FetchContent)

FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.9.1
)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
  FetchContent_Populate(json)
  add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# Link dependencies
target_link_libraries(${LIBNAME} nlohmann_json::nlohmann_json)

# Expose header files
target_include_directories(${LIBNAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})