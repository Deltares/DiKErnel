# Set library name
set(LIBNAME DiKErnel.KernelWrapper.Json.Output)

# Set folder names
set(PUBLIC_FOLDER Public)
set(INTERNAL_FOLDER Internal)
set(INTERNAL_DATA_FOLDER ${INTERNAL_FOLDER}/Data)

# Define sources
set(SOURCEFILES_PUBLIC
  ${PUBLIC_FOLDER}/JsonOutputComposer.cpp
  ${PUBLIC_FOLDER}/JsonOutputComposer.h
)
set(SOURCEFILES_INTERNAL
  ${INTERNAL_FOLDER}/CalculationOutputAdapter.cpp
  ${INTERNAL_FOLDER}/CalculationOutputAdapter.h
  ${INTERNAL_FOLDER}/JsonOutputDefinitions.h
  ${INTERNAL_FOLDER}/JsonOutputWriter.cpp
  ${INTERNAL_FOLDER}/JsonOutputWriter.h
)

set(SOURCEFILES_INTERNAL_DATA
  ${INTERNAL_DATA_FOLDER}/JsonOutputData.cpp
  ${INTERNAL_DATA_FOLDER}/JsonOutputData.h
  ${INTERNAL_DATA_FOLDER}/JsonOutputLocationData.cpp
  ${INTERNAL_DATA_FOLDER}/JsonOutputLocationData.h
)

# Add library
add_library(${LIBNAME} STATIC
  ${SOURCEFILES_PUBLIC}
  ${SOURCEFILES_INTERNAL}
  ${SOURCEFILES_INTERNAL_DATA})

# Configure folder structure
set_target_properties(${LIBNAME} PROPERTIES FOLDER Src)
source_group(${PUBLIC_FOLDER} FILES ${SOURCEFILES_PUBLIC})
source_group(${INTERNAL_FOLDER} FILES ${SOURCEFILES_INTERNAL})
source_group(${INTERNAL_DATA_FOLDER} FILES ${SOURCEFILES_INTERNAL_DATA})

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
target_link_libraries(${LIBNAME} nlohmann_json::nlohmann_json DiKErnel.Core)

# Expose header files
if(BUILD_WITH_TESTS)
  target_include_directories(${LIBNAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/${INTERNAL_FOLDER}
    ${CMAKE_CURRENT_SOURCE_DIR}/${INTERNAL_DATA_FOLDER}
    ${CMAKE_CURRENT_SOURCE_DIR}/${PUBLIC_FOLDER}
  )
else()
  target_include_directories(${LIBNAME}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${INTERNAL_FOLDER}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${INTERNAL_DATA_FOLDER}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/${PUBLIC_FOLDER}
  )
endif()