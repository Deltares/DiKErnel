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

add_custom_command(TARGET ${EXENAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_SOURCE_DIR}/../External/
  ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/
)

# Link dependencies
target_link_libraries(${EXENAME} PUBLIC  
  DiKErnel.Overtopping.KernelWrapper
  gtest
)