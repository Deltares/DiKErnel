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
source_group("" FILES ${SOURCEFILES})

# Link dependencies
target_link_libraries(${EXENAME}
  DiKErnel.Core
  DiKErnel.KernelWrapper.Json.Input
  DiKErnel.KernelWrapper.Json.Output
)