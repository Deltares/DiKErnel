# Set library name
set(LIBNAME DiKErnel.Core)

# Define sources
set(SOURCEFILES
  CalculationOutput.cpp
  CalculationOutput.h
  Calculator.cpp
  Calculator.h
  ICalculationInput.h
  ILocationDependentInput.h
  ITimeDependentInput.h
  LocationDependentOutput.cpp
  LocationDependentOutput.h
)

# Add library
add_library(${LIBNAME} STATIC ${SOURCEFILES})

# Configure folder structure
set_target_properties(${LIBNAME} PROPERTIES FOLDER Src)
source_group("Sources" FILES ${SOURCEFILES})

# Expose header files
target_include_directories(${LIBNAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})