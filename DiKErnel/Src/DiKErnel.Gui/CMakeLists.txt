# Set executable name
set(EXENAME DiKErnel.Gui)
set(OUTPUTNAME DiKErnel-gui)

# Define sources
set(SOURCEFILES
  Main.cpp
)

# Add executable
add_executable(${EXENAME}
  ${SOURCEFILES}
)

# - Configure folder structure
# - Configure executable output name
set_target_properties(${EXENAME} PROPERTIES
  FOLDER Src
  OUTPUT_NAME ${OUTPUTNAME}
)

source_group("" FILES ${SOURCEFILES})