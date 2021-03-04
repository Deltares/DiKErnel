# Set library name
set(LIBNAME DiKErnel.KernelWrapper.Json.Input)

# Define sources
set(SOURCEFILES_PUBLIC
  Public/JsonInputComposer.cpp
  Public/JsonInputComposer.h
)
set(SOURCEFILES_INTERNAL
  Internal/JsonInputDefinitions.h
  Internal/JsonInputParser.cpp
  Internal/JsonInputParser.h
)

set(SOURCEFILES_INTERNAL_DATA_GENERIC
  Internal/Data/Generic/JsonInputCalculationData.cpp
  Internal/Data/Generic/JsonInputCalculationData.h
  Internal/Data/Generic/JsonInputDamageData.cpp
  Internal/Data/Generic/JsonInputDamageData.h
  Internal/Data/Generic/JsonInputData.cpp
  Internal/Data/Generic/JsonInputData.h
  Internal/Data/Generic/JsonInputHydraulicData.cpp
  Internal/Data/Generic/JsonInputHydraulicData.h
  Internal/Data/Generic/JsonInputLocationData.cpp
  Internal/Data/Generic/JsonInputLocationData.h
  Internal/Data/Generic/JsonInputProfileSchematizationData.cpp
  Internal/Data/Generic/JsonInputProfileSchematizationData.h
  Internal/Data/Generic/JsonInputRevetmentLocationData.cpp
  Internal/Data/Generic/JsonInputRevetmentLocationData.h
  Internal/Data/Generic/JsonInputTimeDependentHydraulicData.cpp
  Internal/Data/Generic/JsonInputTimeDependentHydraulicData.h
)

set(SOURCEFILES_INTERNAL_DATA_REVETMENT
  Internal/Data/Revetment/JsonInputNaturalStoneRevetmentLocationData.cpp
  Internal/Data/Revetment/JsonInputNaturalStoneRevetmentLocationData.h
)

# Add library
add_library(${LIBNAME} STATIC
  ${SOURCEFILES_PUBLIC}
  ${SOURCEFILES_INTERNAL}
  ${SOURCEFILES_INTERNAL_DATA_GENERIC}
  ${SOURCEFILES_INTERNAL_DATA_REVETMENT})

# Configure folder structure
set_target_properties(${LIBNAME} PROPERTIES FOLDER Src)
source_group("Public" FILES ${SOURCEFILES_PUBLIC})
source_group("Internal" FILES ${SOURCEFILES_INTERNAL})
source_group("Internal/Data/Generic" FILES ${SOURCEFILES_INTERNAL_DATA_GENERIC})
source_group("Internal/Data/Revetment" FILES ${SOURCEFILES_INTERNAL_DATA_REVETMENT})

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