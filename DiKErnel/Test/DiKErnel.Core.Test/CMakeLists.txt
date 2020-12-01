# Set executable name
set(EXENAME DiKErnel.Core.Test)

# Define sources
set(SOURCEFILES
  CalculatorTest.cpp
  ControllerTest.cpp
  Main.cpp
)

# Add executable
add_executable(${EXENAME} ${SOURCEFILES})

# Configure folder structure
set_target_properties(${EXENAME} PROPERTIES FOLDER Test)
source_group("Sources" FILES ${SOURCEFILES})

# Link dependencies
target_link_libraries(${EXENAME} Catch2::Catch2 DiKErnel.Core)