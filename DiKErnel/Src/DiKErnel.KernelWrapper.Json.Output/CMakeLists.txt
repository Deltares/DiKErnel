# Set library name
set(LIBNAME DiKErnel.KernelWrapper.Json.Output)

# Set folder names
set(PUBLIC_FOLDER Public)
set(PUBLIC_EXCEPTIONS_FOLDER ${PUBLIC_FOLDER}/Exceptions)
set(INTERNAL_FOLDER Internal)
set(INTERNAL_DATA_FOLDER ${INTERNAL_FOLDER}/Data)
set(INTERNAL_DATA_GENERIC_FOLDER ${INTERNAL_DATA_FOLDER}/Generic)
set(INTERNAL_DATA_REVETMENT_FOLDER ${INTERNAL_DATA_FOLDER}/Revetment)

# Define sources
set(SOURCEFILES_PUBLIC
  ${PUBLIC_FOLDER}/JsonOutputComposer.cpp
  ${PUBLIC_FOLDER}/JsonOutputComposer.h
  ${PUBLIC_FOLDER}/JsonOutputType.h
)

set(SOURCEFILES_PUBLIC_EXCEPTIONS
  ${PUBLIC_EXCEPTIONS_FOLDER}/JsonOutputConversionException.cpp
  ${PUBLIC_EXCEPTIONS_FOLDER}/JsonOutputConversionException.h
)

set(SOURCEFILES_INTERNAL
  ${INTERNAL_FOLDER}/CalculationOutputAdapter.cpp
  ${INTERNAL_FOLDER}/CalculationOutputAdapter.h
  ${INTERNAL_FOLDER}/CalculationOutputAdapterHelper.cpp
  ${INTERNAL_FOLDER}/CalculationOutputAdapterHelper.h
  ${INTERNAL_FOLDER}/JsonOutputDefinitions.h
  ${INTERNAL_FOLDER}/JsonOutputGrassRevetmentWaveImpactDefinitions.h
  ${INTERNAL_FOLDER}/JsonOutputNaturalStoneRevetmentDefinitions.h
  ${INTERNAL_FOLDER}/JsonOutputWriter.cpp
  ${INTERNAL_FOLDER}/JsonOutputWriter.h
)

set(SOURCEFILES_INTERNAL_DATA_GENERIC
  ${INTERNAL_DATA_GENERIC_FOLDER}/IJsonOutputData.h
  ${INTERNAL_DATA_GENERIC_FOLDER}/JsonOutputDamageLocationData.cpp
  ${INTERNAL_DATA_GENERIC_FOLDER}/JsonOutputDamageLocationData.h
  ${INTERNAL_DATA_GENERIC_FOLDER}/JsonOutputData.cpp
  ${INTERNAL_DATA_GENERIC_FOLDER}/JsonOutputData.h
  ${INTERNAL_DATA_GENERIC_FOLDER}/JsonOutputFailureLocationData.cpp
  ${INTERNAL_DATA_GENERIC_FOLDER}/JsonOutputFailureLocationData.h
)

set(SOURCEFILES_INTERNAL_DATA_REVETMENT
  ${INTERNAL_DATA_REVETMENT_FOLDER}/JsonOutputGrassRevetmentWaveImpactPhysicsLocationData.cpp
  ${INTERNAL_DATA_REVETMENT_FOLDER}/JsonOutputGrassRevetmentWaveImpactPhysicsLocationData.h
  ${INTERNAL_DATA_REVETMENT_FOLDER}/JsonOutputNaturalStoneRevetmentPhysicsLocationData.cpp
  ${INTERNAL_DATA_REVETMENT_FOLDER}/JsonOutputNaturalStoneRevetmentPhysicsLocationData.h
)

# Add library
add_library(${LIBNAME} STATIC
  ${SOURCEFILES_PUBLIC}
  ${SOURCEFILES_PUBLIC_EXCEPTIONS}
  ${SOURCEFILES_INTERNAL}
  ${SOURCEFILES_INTERNAL_DATA_GENERIC}
  ${SOURCEFILES_INTERNAL_DATA_REVETMENT}
)

# Configure folder structure
set_target_properties(${LIBNAME} PROPERTIES FOLDER Src)
source_group(${PUBLIC_FOLDER} FILES ${SOURCEFILES_PUBLIC})
source_group(${PUBLIC_EXCEPTIONS_FOLDER} FILES ${SOURCEFILES_PUBLIC_EXCEPTIONS})
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
target_link_libraries(${LIBNAME} nlohmann_json::nlohmann_json DiKErnel.Core DiKErnel.KernelWrapper.Json.Input)

# Expose header files
if(BUILD_WITH_TESTS)
  target_include_directories(${LIBNAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/${INTERNAL_FOLDER}
    ${CMAKE_CURRENT_SOURCE_DIR}/${INTERNAL_DATA_GENERIC_FOLDER}
    ${CMAKE_CURRENT_SOURCE_DIR}/${INTERNAL_DATA_REVETMENT_FOLDER}
    ${CMAKE_CURRENT_SOURCE_DIR}/${PUBLIC_FOLDER}
    ${CMAKE_CURRENT_SOURCE_DIR}/${PUBLIC_EXCEPTIONS_FOLDER}
  )
else()
  target_include_directories(${LIBNAME}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${INTERNAL_FOLDER}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${INTERNAL_DATA_GENERIC_FOLDER}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${INTERNAL_DATA_REVETMENT_FOLDER}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/${PUBLIC_FOLDER}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/${PUBLIC_EXCEPTIONS_FOLDER}
  )
endif()