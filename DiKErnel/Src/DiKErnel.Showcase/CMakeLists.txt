# Set executable name
set(EXENAME DiKErnel.Showcase)

# Define sources
set(SOURCEFILES
  Main.cpp
)

# Add executable
add_executable(${EXENAME} ${SOURCEFILES})

# Configure folder structure
set_target_properties(${EXENAME} PROPERTIES FOLDER Src)
source_group("Sources" FILES ${SOURCEFILES})