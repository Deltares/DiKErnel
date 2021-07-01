# Set executable name
set(EXENAME DiKErnel.KernelWrapper.Json.Output.Test)

# Set folder names
set(EXCEPTIONS_FOLDER Exceptions)

# Define sources
set(SOURCEFILES_ROOT 
  JsonOutputComposerTest.cpp
  Main.cpp
)

set(SOURCEFILES_EXCEPTIONS 
  ${EXCEPTIONS_FOLDER}/JsonOutputConversionException.cpp
)

# Add executable
add_executable(${EXENAME} 
  ${SOURCEFILES_ROOT}
  ${SOURCEFILES_EXCEPTIONS}
)

# Configure folder structure
set_target_properties(${EXENAME} PROPERTIES FOLDER Test)
source_group("" FILES ${SOURCEFILES_ROOT})
source_group(${EXCEPTIONS_FOLDER} FILES ${SOURCEFILES_EXCEPTIONS})

# Link dependencies
target_link_libraries(${EXENAME} PUBLIC gmock gtest DiKErnel.Core DiKErnel.Core.TestUtil DiKErnel.KernelWrapper.Json.Output DiKErnel.TestUtil)