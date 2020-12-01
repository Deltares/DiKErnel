# Set executable name
set(EXENAME DiKErnel.Core.Test)

# Define sources
set(SOURCEFILES
  CalculatorTest.cpp
  ControllerTest.cpp
  InputComposerTest.cpp
  OutputComposerTest.cpp
)

# Add executable
add_executable(${EXENAME} ${SOURCEFILES})

# Configure folder structure
set_target_properties(${EXENAME} PROPERTIES FOLDER Test)
source_group("Sources" FILES ${SOURCEFILES})