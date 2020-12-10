# Set library name
set(LIBNAME DiKErnel.DomainLibrary)

# Define sources
set(SOURCEFILES
  Constants.cpp
  Constants.h
  HydraulicLoadsDefaults.cpp
  HydraulicLoadsDefaults.h
  NaturalStoneRevetmentDefaults.cpp
  NaturalStoneRevetmentDefaults.h
)

# Add library
add_library(${LIBNAME} STATIC ${SOURCEFILES})

# Configure folder structure
set_target_properties(${LIBNAME} PROPERTIES FOLDER Src)
source_group("Sources" FILES ${SOURCEFILES})

# Expose header files
target_include_directories(${LIBNAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})