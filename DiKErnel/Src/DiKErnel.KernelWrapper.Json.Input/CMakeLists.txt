# Set library name
set(LIBNAME DiKErnel.KernelWrapper.Json.Input)

# Define sources
set(SOURCEFILES_PUBLIC "")
set(SOURCEFILES_INTERNAL "")

set(SOURCEFILES_INTERNAL_DATA_GENERIC
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

set(SOURCEFILES_INTERNAL_DATA_REVETMENT
  JsonInputNaturalStoneRevetmentLocationData.cpp
  JsonInputNaturalStoneRevetmentLocationData.h
)

# Add subdirectories
add_subdirectory(Public)
add_subdirectory(Internal)

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