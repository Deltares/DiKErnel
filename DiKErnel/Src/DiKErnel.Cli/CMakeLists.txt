# Set executable name
set(EXENAME DiKErnel.Cli)
set(OUTPUTNAME DiKErnel-cli)

# Define sources
set(SOURCEFILES
  Main.cpp
)

# Add executable
add_executable(${EXENAME} ${SOURCEFILES})

# Configure folder structure
set_target_properties(${EXENAME} PROPERTIES FOLDER Src)
source_group("" FILES ${SOURCEFILES})

# Configure executable output name
set_target_properties(${EXENAME} PROPERTIES
  OUTPUT_NAME ${OUTPUTNAME}
)

# Link dependencies
target_link_libraries(${EXENAME}
  DiKErnel.Core
  DiKErnel.KernelWrapper.Json.Input
  DiKErnel.KernelWrapper.Json.Output
)