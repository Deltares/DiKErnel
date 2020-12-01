# Set library name
set(LIBNAME DiKErnel.Core)

# Define sources
set(SOURCEFILES
  Calculator.cpp
  Calculator.h
  Controller.cpp
  Controller.h
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