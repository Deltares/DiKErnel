# Set executable name
set(EXENAME DiKErnel.Overtopping.KernelWrapper.Test)

# Define sources
set(SOURCEFILES
  Main.cpp
  OvertoppingWrapperTest.cpp
)

# Add executable
add_executable(${EXENAME} ${SOURCEFILES})

# Configure folder structure
set_target_properties(${EXENAME} PROPERTIES FOLDER Test)
source_group("" FILES ${SOURCEFILES})

# Link dependencies
target_link_libraries(${EXENAME} PUBLIC  
  DiKErnel.Overtopping.KernelWrapper
  gtest
)