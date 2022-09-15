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

add_custom_command(TARGET ${EXENAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
    $<TARGET_RUNTIME_DLLS:${EXENAME}>
    ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/
  COMMAND_EXPAND_LISTS)