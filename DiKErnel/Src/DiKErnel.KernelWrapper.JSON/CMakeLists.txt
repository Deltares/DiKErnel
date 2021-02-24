# Set library name
set(LIBNAME DiKErnel.KernelWrapper.Json)

# Define sources
set(SOURCEFILES
  BoundaryConditionsPerTimeStep.cpp
  BoundaryConditionsPerTimeStep.h
  CalculationData.cpp
  CalculationData.h
  CalculationLocation.cpp
  CalculationLocation.h
  CalculationLocationOutput.cpp
  CalculationLocationOutput.h
  DamageVariables.cpp
  DamageVariables.h
  HydraulicLoads.cpp
  HydraulicLoads.h
  InputComposer.cpp
  InputComposer.h
  InputData.cpp
  InputData.h
  JsonDefinitions.cpp
  JsonDefinitions.h
  OutputComposer.cpp
  OutputComposer.h
  OutputData.cpp
  OutputData.h
  ProfileSchematization.cpp
  ProfileSchematization.h
  Revetment.cpp
  Revetment.h
  RevetmentOutput.cpp
  RevetmentOutput.h
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
target_link_libraries(${LIBNAME} nlohmann_json::nlohmann_json DiKErnel.DomainLibrary)

# Expose header files
target_include_directories(${LIBNAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})