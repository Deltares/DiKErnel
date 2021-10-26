# Set library name
set(LIBNAME DiKErnel.Util.TestUtil)

# Define sources
set(SOURCEFILES
  EventAssertHelper.cpp
  EventAssertHelper.h
  EventRegistryTestHelper.cpp
  EventRegistryTestHelper.h
)

# Add library
add_library(${LIBNAME} ${SOURCEFILES})

# Configure folder structure
set_target_properties(${LIBNAME} PROPERTIES FOLDER Test)
source_group("" FILES ${SOURCEFILES})

# Expose header files
target_include_directories(${LIBNAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Link dependencies
target_link_libraries(${LIBNAME}
  DiKErnel.Util
  gmock
)