# Set library name
set(LIBNAME DiKErnel.KernelWrapper.Json.Input)

# Set folder names
set(PUBLIC_FOLDER Public)
set(PUBLIC_DATA_FOLDER ${PUBLIC_FOLDER}/Data)
set(PUBLIC_EXCEPTIONS_FOLDER ${PUBLIC_FOLDER}/Exceptions)
set(INTERNAL_FOLDER Internal)
set(INTERNAL_DATA_GENERIC_FOLDER ${INTERNAL_FOLDER}/Data/Generic)
set(INTERNAL_DATA_REVETMENT_FOLDER ${INTERNAL_FOLDER}/Data/Revetment)
set(INTERNAL_PARSERS_FOLDER ${INTERNAL_FOLDER}/Parsers)

# Define sources
set(SOURCEFILES_PUBLIC
  ${PUBLIC_FOLDER}/JsonInputComposer.cpp
  ${PUBLIC_FOLDER}/JsonInputComposer.h
  ${PUBLIC_FOLDER}/JsonInputComposerResult.cpp
  ${PUBLIC_FOLDER}/JsonInputComposerResult.h
)

set(SOURCEFILES_PUBLIC_DATA
  ${PUBLIC_DATA_FOLDER}/JsonInputProcessType.h
)

set(SOURCEFILES_PUBLIC_EXCEPTIONS
  ${PUBLIC_EXCEPTIONS_FOLDER}/JsonInputConversionException.cpp
  ${PUBLIC_EXCEPTIONS_FOLDER}/JsonInputConversionException.h
)

set(SOURCEFILES_INTERNAL
  ${INTERNAL_FOLDER}/JsonInputAdapter.cpp
  ${INTERNAL_FOLDER}/JsonInputAdapter.h
)

set(SOURCEFILES_INTERNAL_DATA_GENERIC
  ${INTERNAL_DATA_GENERIC_FOLDER}/JsonInputCalculationData.cpp
  ${INTERNAL_DATA_GENERIC_FOLDER}/JsonInputCalculationData.h
  ${INTERNAL_DATA_GENERIC_FOLDER}/JsonInputCalculationDefinitionData.cpp
  ${INTERNAL_DATA_GENERIC_FOLDER}/JsonInputCalculationDefinitionData.h
  ${INTERNAL_DATA_GENERIC_FOLDER}/JsonInputCalculationType.h
  ${INTERNAL_DATA_GENERIC_FOLDER}/JsonInputCharacteristicPointType.h
  ${INTERNAL_DATA_GENERIC_FOLDER}/JsonInputDamageData.cpp
  ${INTERNAL_DATA_GENERIC_FOLDER}/JsonInputDamageData.h
  ${INTERNAL_DATA_GENERIC_FOLDER}/JsonInputData.cpp
  ${INTERNAL_DATA_GENERIC_FOLDER}/JsonInputData.h
  ${INTERNAL_DATA_GENERIC_FOLDER}/JsonInputDikeProfileData.cpp
  ${INTERNAL_DATA_GENERIC_FOLDER}/JsonInputDikeProfileData.h
  ${INTERNAL_DATA_GENERIC_FOLDER}/JsonInputDikeProfilePoint.cpp
  ${INTERNAL_DATA_GENERIC_FOLDER}/JsonInputDikeProfilePoint.h
  ${INTERNAL_DATA_GENERIC_FOLDER}/JsonInputHydraulicData.cpp
  ${INTERNAL_DATA_GENERIC_FOLDER}/JsonInputHydraulicData.h
  ${INTERNAL_DATA_GENERIC_FOLDER}/JsonInputLocationData.cpp
  ${INTERNAL_DATA_GENERIC_FOLDER}/JsonInputLocationData.h
  ${INTERNAL_DATA_GENERIC_FOLDER}/JsonInputProcessData.cpp
  ${INTERNAL_DATA_GENERIC_FOLDER}/JsonInputProcessData.h
  ${INTERNAL_DATA_GENERIC_FOLDER}/JsonInputTimeDependentHydraulicData.cpp
  ${INTERNAL_DATA_GENERIC_FOLDER}/JsonInputTimeDependentHydraulicData.h
)

set(SOURCEFILES_INTERNAL_DATA_REVETMENT
  ${INTERNAL_DATA_REVETMENT_FOLDER}/JsonInputAsphaltRevetmentTopLayerType.h
  ${INTERNAL_DATA_REVETMENT_FOLDER}/JsonInputAsphaltWaveImpactCalculationDefinitionData.cpp
  ${INTERNAL_DATA_REVETMENT_FOLDER}/JsonInputAsphaltWaveImpactCalculationDefinitionData.h
  ${INTERNAL_DATA_REVETMENT_FOLDER}/JsonInputAsphaltWaveImpactLocationData.cpp
  ${INTERNAL_DATA_REVETMENT_FOLDER}/JsonInputAsphaltWaveImpactLocationData.h
  ${INTERNAL_DATA_REVETMENT_FOLDER}/JsonInputAsphaltWaveImpactTopLayerDefinitionData.cpp
  ${INTERNAL_DATA_REVETMENT_FOLDER}/JsonInputAsphaltWaveImpactTopLayerDefinitionData.h
  ${INTERNAL_DATA_REVETMENT_FOLDER}/JsonInputGrassRevetmentTopLayerType.h
  ${INTERNAL_DATA_REVETMENT_FOLDER}/JsonInputGrassRevetmentWaveRunupCalculationProtocolType.h
  ${INTERNAL_DATA_REVETMENT_FOLDER}/JsonInputGrassRevetmentWaveRunupLocationData.cpp
  ${INTERNAL_DATA_REVETMENT_FOLDER}/JsonInputGrassRevetmentWaveRunupLocationData.h
  ${INTERNAL_DATA_REVETMENT_FOLDER}/JsonInputGrassRevetmentWaveRunupRayleighLocationData.cpp
  ${INTERNAL_DATA_REVETMENT_FOLDER}/JsonInputGrassRevetmentWaveRunupRayleighLocationData.h
  ${INTERNAL_DATA_REVETMENT_FOLDER}/JsonInputGrassWaveImpactCalculationDefinitionData.cpp
  ${INTERNAL_DATA_REVETMENT_FOLDER}/JsonInputGrassWaveImpactCalculationDefinitionData.h
  ${INTERNAL_DATA_REVETMENT_FOLDER}/JsonInputGrassWaveImpactLocationData.cpp
  ${INTERNAL_DATA_REVETMENT_FOLDER}/JsonInputGrassWaveImpactLocationData.h
  ${INTERNAL_DATA_REVETMENT_FOLDER}/JsonInputGrassWaveRunupRayleighLocationData.cpp
  ${INTERNAL_DATA_REVETMENT_FOLDER}/JsonInputGrassWaveRunupRayleighLocationData.h
  ${INTERNAL_DATA_REVETMENT_FOLDER}/JsonInputNaturalStoneCalculationDefinitionData.cpp
  ${INTERNAL_DATA_REVETMENT_FOLDER}/JsonInputNaturalStoneCalculationDefinitionData.h
  ${INTERNAL_DATA_REVETMENT_FOLDER}/JsonInputNaturalStoneLocationData.cpp
  ${INTERNAL_DATA_REVETMENT_FOLDER}/JsonInputNaturalStoneLocationData.h
  ${INTERNAL_DATA_REVETMENT_FOLDER}/JsonInputNaturalStoneRevetmentTopLayerType.h
  ${INTERNAL_DATA_REVETMENT_FOLDER}/JsonInputNaturalStoneTopLayerDefinitionData.cpp
  ${INTERNAL_DATA_REVETMENT_FOLDER}/JsonInputNaturalStoneTopLayerDefinitionData.h
)

set(SOURCEFILES_INTERNAL_PARSERS
  ${INTERNAL_PARSERS_FOLDER}/JsonInputAsphaltWaveImpactCalculationDefinitionParser.cpp
  ${INTERNAL_PARSERS_FOLDER}/JsonInputAsphaltWaveImpactCalculationDefinitionParser.h
  ${INTERNAL_PARSERS_FOLDER}/JsonInputAsphaltWaveImpactDefinitions.h
  ${INTERNAL_PARSERS_FOLDER}/JsonInputAsphaltWaveImpactParser.cpp
  ${INTERNAL_PARSERS_FOLDER}/JsonInputAsphaltWaveImpactParser.h
  ${INTERNAL_PARSERS_FOLDER}/JsonInputCalculationDefinitionParser.cpp
  ${INTERNAL_PARSERS_FOLDER}/JsonInputCalculationDefinitionParser.h
  ${INTERNAL_PARSERS_FOLDER}/JsonInputDefinitions.h
  ${INTERNAL_PARSERS_FOLDER}/JsonInputGrassRevetmentDefinitions.h
  ${INTERNAL_PARSERS_FOLDER}/JsonInputGrassWaveImpactDefinitions.h
  ${INTERNAL_PARSERS_FOLDER}/JsonInputGrassWaveImpactCalculationDefinitionParser.cpp
  ${INTERNAL_PARSERS_FOLDER}/JsonInputGrassWaveImpactCalculationDefinitionParser.h
  ${INTERNAL_PARSERS_FOLDER}/JsonInputGrassWaveImpactParser.cpp
  ${INTERNAL_PARSERS_FOLDER}/JsonInputGrassWaveImpactParser.h
  ${INTERNAL_PARSERS_FOLDER}/JsonInputGrassWaveRunupDefinitions.h
  ${INTERNAL_PARSERS_FOLDER}/JsonInputGrassWaveRunupParser.cpp
  ${INTERNAL_PARSERS_FOLDER}/JsonInputGrassWaveRunupParser.h
  ${INTERNAL_PARSERS_FOLDER}/JsonInputGrassWaveRunupRayleighDefinitions.h
  ${INTERNAL_PARSERS_FOLDER}/JsonInputLocationParser.cpp
  ${INTERNAL_PARSERS_FOLDER}/JsonInputLocationParser.h
  ${INTERNAL_PARSERS_FOLDER}/JsonInputNaturalStoneCalculationDefinitionParser.cpp
  ${INTERNAL_PARSERS_FOLDER}/JsonInputNaturalStoneCalculationDefinitionParser.h
  ${INTERNAL_PARSERS_FOLDER}/JsonInputNaturalStoneDefinitions.h
  ${INTERNAL_PARSERS_FOLDER}/JsonInputNaturalStoneParser.cpp
  ${INTERNAL_PARSERS_FOLDER}/JsonInputNaturalStoneParser.h
  ${INTERNAL_PARSERS_FOLDER}/JsonInputParser.cpp
  ${INTERNAL_PARSERS_FOLDER}/JsonInputParser.h
  ${INTERNAL_PARSERS_FOLDER}/JsonInputParserHelper.cpp
  ${INTERNAL_PARSERS_FOLDER}/JsonInputParserHelper.h
)

# Add library
add_library(${LIBNAME} STATIC
  ${SOURCEFILES_PUBLIC}
  ${SOURCEFILES_PUBLIC_DATA}
  ${SOURCEFILES_PUBLIC_EXCEPTIONS}
  ${SOURCEFILES_INTERNAL}
  ${SOURCEFILES_INTERNAL_DATA_GENERIC}
  ${SOURCEFILES_INTERNAL_DATA_REVETMENT}
  ${SOURCEFILES_INTERNAL_PARSERS})

# Configure folder structure
set_target_properties(${LIBNAME} PROPERTIES FOLDER Src)
source_group(${PUBLIC_FOLDER} FILES ${SOURCEFILES_PUBLIC})
source_group(${PUBLIC_DATA_FOLDER} FILES ${SOURCEFILES_PUBLIC_DATA})
source_group(${PUBLIC_EXCEPTIONS_FOLDER} FILES ${SOURCEFILES_PUBLIC_EXCEPTIONS})
source_group(${INTERNAL_FOLDER} FILES ${SOURCEFILES_INTERNAL})
source_group(${INTERNAL_DATA_GENERIC_FOLDER} FILES ${SOURCEFILES_INTERNAL_DATA_GENERIC})
source_group(${INTERNAL_DATA_REVETMENT_FOLDER} FILES ${SOURCEFILES_INTERNAL_DATA_REVETMENT})
source_group(${INTERNAL_PARSERS_FOLDER} FILES ${SOURCEFILES_INTERNAL_PARSERS})

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

# Expose header files
if(BUILD_FOR_RELEASE)
  target_include_directories(${LIBNAME}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${INTERNAL_FOLDER}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${INTERNAL_DATA_GENERIC_FOLDER}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${INTERNAL_DATA_REVETMENT_FOLDER}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${INTERNAL_PARSERS_FOLDER}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/${PUBLIC_FOLDER}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/${PUBLIC_DATA_FOLDER}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/${PUBLIC_EXCEPTIONS_FOLDER}
  )
else()
  target_include_directories(${LIBNAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/${INTERNAL_FOLDER}
    ${CMAKE_CURRENT_SOURCE_DIR}/${INTERNAL_DATA_GENERIC_FOLDER}
    ${CMAKE_CURRENT_SOURCE_DIR}/${INTERNAL_DATA_REVETMENT_FOLDER}
    ${CMAKE_CURRENT_SOURCE_DIR}/${INTERNAL_PARSERS_FOLDER}
    ${CMAKE_CURRENT_SOURCE_DIR}/${PUBLIC_FOLDER}
    ${CMAKE_CURRENT_SOURCE_DIR}/${PUBLIC_DATA_FOLDER}
    ${CMAKE_CURRENT_SOURCE_DIR}/${PUBLIC_EXCEPTIONS_FOLDER}
  )
endif()

# Link dependencies
target_link_libraries(${LIBNAME}
  DiKErnel.Core
  DiKErnel.Integration
  DiKErnel.Util
  nlohmann_json::nlohmann_json
)