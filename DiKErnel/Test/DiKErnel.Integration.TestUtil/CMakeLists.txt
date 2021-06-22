# Set library name
set(LIBNAME DiKErnel.Integration.TestUtil)

# Define sources
set(SOURCEFILES
  AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper.cpp
  AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper.h
  GrassRevetmentWaveImpactLocationDependentInputAssertHelper.cpp
  GrassRevetmentWaveImpactLocationDependentInputAssertHelper.h
  GrassRevetmentWaveRunupLocationConstructionPropertiesMock.cpp
  GrassRevetmentWaveRunupLocationConstructionPropertiesMock.h
  GrassRevetmentWaveRunupLocationDependentInputAssertHelper.cpp
  GrassRevetmentWaveRunupLocationDependentInputAssertHelper.h
  GrassRevetmentWaveRunupRayleighLocationDependentInputAssertHelper.cpp
  GrassRevetmentWaveRunupRayleighLocationDependentInputAssertHelper.h
  LocationDependentInputAssertHelper.cpp
  LocationDependentInputAssertHelper.h
  LocationDependentInputMock.cpp
  LocationDependentInputMock.h
  NaturalStoneRevetmentLocationDependentInputAssertHelper.cpp
  NaturalStoneRevetmentLocationDependentInputAssertHelper.h
  RevetmentLocationConstructionPropertiesMock.cpp
  RevetmentLocationConstructionPropertiesMock.h
  TimeDependentInputAssertHelper.cpp
  TimeDependentInputAssertHelper.h
)

# Add library
add_library(${LIBNAME} ${SOURCEFILES})

# Configure folder structure
set_target_properties(${LIBNAME} PROPERTIES FOLDER Test)
source_group("" FILES ${SOURCEFILES})

# Expose header files
target_include_directories(${LIBNAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Link dependencies
target_link_libraries(${LIBNAME} gmock DiKErnel.Core DiKErnel.Integration)