# Set library name
set(LIBNAME DiKErnel.Integration)

# Define sources
set(SOURCEFILES
  CalculationInput.cpp
  CalculationInput.h
  LocationDependentData.cpp
  LocationDependentData.h
  NaturalStoneRevetmentLocationConstructionProperties.cpp
  NaturalStoneRevetmentLocationConstructionProperties.h
  NaturalStoneRevetmentLocationDependentData.cpp
  NaturalStoneRevetmentLocationDependentData.h
  RevetmentCalculationInputBuilder.cpp
  RevetmentCalculationInputBuilder.h
  RevetmentCalculationInputBuilderException.cpp
  RevetmentCalculationInputBuilderException.h
  TimeDependentData.cpp
  TimeDependentData.h
)

# Add library
add_library(${LIBNAME} STATIC ${SOURCEFILES})

# Configure folder structure
set_target_properties(${LIBNAME} PROPERTIES FOLDER Src)
source_group("Sources" FILES ${SOURCEFILES})

# Expose header files
target_include_directories(${LIBNAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Link dependencies
target_link_libraries(${LIBNAME} DiKErnel.Core DiKErnel.FunctionLibrary)