# Set library name
set(LIBNAME DiKErnel.KernelWrapper.Json.Input)

# Set folder names
set(PUBLIC_FOLDER Public)
set(INTERNAL_FOLDER Internal)
set(INTERNAL_DATA_GENERIC_FOLDER ${INTERNAL_FOLDER}/Data/Generic)
set(INTERNAL_DATA_REVETMENT_FOLDER ${INTERNAL_FOLDER}/Data/Revetment)

# Define sources
set(SOURCEFILES_PUBLIC
  ${PUBLIC_FOLDER}/JsonInputComposer.cpp
  ${PUBLIC_FOLDER}/JsonInputComposer.h
)
set(SOURCEFILES_INTERNAL
  ${INTERNAL_FOLDER}/JsonInputAdapter.cpp
  ${INTERNAL_FOLDER}/JsonInputAdapter.h
  ${INTERNAL_FOLDER}/JsonInputDefinitions.h
  ${INTERNAL_FOLDER}/JsonInputParser.cpp
  ${INTERNAL_FOLDER}/JsonInputParser.h
)

set(SOURCEFILES_INTERNAL_DATA_GENERIC
  ${INTERNAL_DATA_GENERIC_FOLDER}/JsonInputCalculationData.cpp
  ${INTERNAL_DATA_GENERIC_FOLDER}/JsonInputCalculationData.h
  ${INTERNAL_DATA_GENERIC_FOLDER}/JsonInputDamageData.cpp
  ${INTERNAL_DATA_GENERIC_FOLDER}/JsonInputDamageData.h
  ${INTERNAL_DATA_GENERIC_FOLDER}/JsonInputData.cpp
  ${INTERNAL_DATA_GENERIC_FOLDER}/JsonInputData.h
  ${INTERNAL_DATA_GENERIC_FOLDER}/JsonInputHydraulicData.cpp
  ${INTERNAL_DATA_GENERIC_FOLDER}/JsonInputHydraulicData.h
  ${INTERNAL_DATA_GENERIC_FOLDER}/JsonInputLocationData.cpp
  ${INTERNAL_DATA_GENERIC_FOLDER}/JsonInputLocationData.h
  ${INTERNAL_DATA_GENERIC_FOLDER}/JsonInputProfileSchematizationData.cpp
  ${INTERNAL_DATA_GENERIC_FOLDER}/JsonInputProfileSchematizationData.h
  ${INTERNAL_DATA_GENERIC_FOLDER}/JsonInputRevetmentLocationData.cpp
  ${INTERNAL_DATA_GENERIC_FOLDER}/JsonInputRevetmentLocationData.h
  ${INTERNAL_DATA_GENERIC_FOLDER}/JsonInputTimeDependentHydraulicData.cpp
  ${INTERNAL_DATA_GENERIC_FOLDER}/JsonInputTimeDependentHydraulicData.h
)

set(SOURCEFILES_INTERNAL_DATA_REVETMENT
  ${INTERNAL_DATA_REVETMENT_FOLDER}/JsonInputNaturalStoneRevetmentLocationData.cpp
  ${INTERNAL_DATA_REVETMENT_FOLDER}/JsonInputNaturalStoneRevetmentLocationData.h
)

# Add library
add_library(${LIBNAME} STATIC
  ${SOURCEFILES_PUBLIC}
  ${SOURCEFILES_INTERNAL}
  ${SOURCEFILES_INTERNAL_DATA_GENERIC}
  ${SOURCEFILES_INTERNAL_DATA_REVETMENT})

# Configure folder structure
set_target_properties(${LIBNAME} PROPERTIES FOLDER Src)
source_group(${PUBLIC_FOLDER} FILES ${SOURCEFILES_PUBLIC})
source_group(${INTERNAL_FOLDER} FILES ${SOURCEFILES_INTERNAL})
source_group(${INTERNAL_DATA_GENERIC_FOLDER} FILES ${SOURCEFILES_INTERNAL_DATA_GENERIC})
source_group(${INTERNAL_DATA_REVETMENT_FOLDER} FILES ${SOURCEFILES_INTERNAL_DATA_REVETMENT})

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
target_link_libraries(${LIBNAME} nlohmann_json::nlohmann_json DiKErnel.Core DiKErnel.Integration)

# Expose header files
if(BUILD_WITH_TESTS)
  target_include_directories(${LIBNAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/${INTERNAL_FOLDER}
    ${CMAKE_CURRENT_SOURCE_DIR}/${INTERNAL_DATA_GENERIC_FOLDER}
    ${CMAKE_CURRENT_SOURCE_DIR}/${INTERNAL_DATA_REVETMENT_FOLDER}
    ${CMAKE_CURRENT_SOURCE_DIR}/${PUBLIC_FOLDER}
  )
else()
  target_include_directories(${LIBNAME}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${INTERNAL_FOLDER}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${INTERNAL_DATA_GENERIC_FOLDER}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${INTERNAL_DATA_REVETMENT_FOLDER}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/${PUBLIC_FOLDER}
  )
endif()