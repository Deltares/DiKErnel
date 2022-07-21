# Set executable name
set(EXENAME DiKErnel.Util.Test)

# Set folder names
set(VALIDATION_FOLDER Validation)

# Define sources
set(SOURCEFILES_ROOT
  DataResultTest.cpp
  EventRegistryTest.cpp
  EventTest.cpp
  Main.cpp
  SimpleResultTest.cpp
)

set(SOURCEFILES_VALIDATION
  ${VALIDATION_FOLDER}/ValidationIssueTest.cpp
)

# Add executable
add_executable(${EXENAME}
  ${SOURCEFILES_ROOT}
  ${SOURCEFILES_VALIDATION}
)

# Configure folder structure
set_target_properties(${EXENAME} PROPERTIES FOLDER Test)
source_group("" FILES ${SOURCEFILES_ROOT})
source_group(${VALIDATION_FOLDER} FILES ${SOURCEFILES_VALIDATION})

# Link dependencies
target_link_libraries(${EXENAME} PUBLIC
  DiKErnel.Util
  DiKErnel.Util.TestUtil
  gtest
)