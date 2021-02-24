# Set library name
set(LIBNAME DiKErnel.KernelWrapper.Json.Input)

# Define sources
set(SOURCEFILES
  JsonInputAdapter.cpp
  JsonInputAdapter.h
  JsonInputCalculationData.cpp
  JsonInputCalculationData.h
  JsonInputComposer.cpp
  JsonInputComposer.h
  JsonInputData.cpp
  JsonInputData.h
  JsonInputHydraulicData.cpp
  JsonInputHydraulicData.h
  JsonInputLocationData.cpp
  JsonInputLocationData.h
  JsonInputParser.cpp
  JsonInputParser.h
  NaturalStoneRevetmentJsonInputLocationData.cpp
  NaturalStoneRevetmentJsonInputLocationData.h
)

# Add library
add_library(${LIBNAME} STATIC ${SOURCEFILES})

# Configure folder structure
set_target_properties(${LIBNAME} PROPERTIES FOLDER Src)
source_group("Sources" FILES ${SOURCEFILES})

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