# Set library name
set(LIBNAME DiKErnel.IO)

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