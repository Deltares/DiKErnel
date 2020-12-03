# Set library name
set(LIBNAME DiKErnel.KernelWrapper.Json)

# Define sources
set(SOURCEFILES
  InputComposer.cpp
  InputComposer.h
  OutputComposer.cpp
  OutputComposer.h
)

# Add library
add_library(${LIBNAME} STATIC ${SOURCEFILES})

# Configure folder structure
set_target_properties(${LIBNAME} PROPERTIES FOLDER Src)
source_group("Sources" FILES ${SOURCEFILES})

# Expose header files
target_include_directories(${LIBNAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})