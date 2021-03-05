# Set library name
set(LIBNAME DiKErnel.Core.TestUtil)

# Define sources
set(SOURCEFILES
  ICalculationInputMock.cpp
  ICalculationInputMock.h
  ILocationDependentDataMock.cpp
  ILocationDependentDataMock.h
  ITimeDependentDataMock.cpp
  ITimeDependentDataMock.h
)

# Add library
add_library(${LIBNAME} ${SOURCEFILES})

# Configure folder structure
set_target_properties(${LIBNAME} PROPERTIES FOLDER Test)
source_group("Sources" FILES ${SOURCEFILES})

# Expose header files
target_include_directories(${LIBNAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Link dependencies
target_link_libraries(${LIBNAME} gmock DiKErnel.Core)