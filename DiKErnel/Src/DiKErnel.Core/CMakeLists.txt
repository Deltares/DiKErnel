# Set library name
set(LIBNAME DiKErnel.Core)

# Define sources
set(SOURCEFILES
  CalculationInput.cpp
  CalculationInput.h
  CalculationOutput.cpp
  CalculationOutput.h
  Calculator.cpp
  Calculator.h
  DeprecatedCalculator.cpp
  DeprecatedCalculator.h
  ILocationCalculationInput.cpp
  ILocationCalculationInput.h
)

# Add library
add_library(${LIBNAME} STATIC ${SOURCEFILES})

# Configure folder structure
set_target_properties(${LIBNAME} PROPERTIES FOLDER Src)
source_group("Sources" FILES ${SOURCEFILES})

# Expose header files
target_include_directories(${LIBNAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Link dependencies
target_link_libraries(${LIBNAME} DiKErnel.KernelWrapper.Json)