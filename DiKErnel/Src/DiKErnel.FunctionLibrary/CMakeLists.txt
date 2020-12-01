# Set library name
set(LIBNAME DiKErnel.FunctionLibrary)

# Define sources
set(SOURCEFILES
  Dummy.cpp
  Dummy.h
)

# Add library
add_library(${LIBNAME} STATIC ${SOURCEFILES})

# Configure folder structure
set_target_properties(${LIBNAME} PROPERTIES FOLDER Src)
source_group("Sources" FILES ${SOURCEFILES})

# Include directories
target_include_directories(${LIBNAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})