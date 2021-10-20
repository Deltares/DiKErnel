# Set executable name
set(EXENAME DiKErnel.DomainLibrary.Constants.Test)

# Define sources
set(SOURCEFILES_ROOT
  ConstantsTest.cpp
  Main.cpp
)

# Add executable
add_executable(${EXENAME} ${SOURCEFILES_ROOT})

# Configure folder structure
set_target_properties(${EXENAME} PROPERTIES FOLDER Test)
source_group("" FILES ${SOURCEFILES_ROOT})

# Link dependencies
target_link_libraries(${EXENAME} gtest DiKErnel.DomainLibrary.Constants)