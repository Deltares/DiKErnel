# Set executable name
set(EXENAME DiKErnel.KernelWrapper.Json.Input.Test)

# Set folder names
set(EXCEPTIONS_FOLDER Exceptions)

# Define sources
set(SOURCEFILES_ROOT
  JsonInputComposerTest.cpp
  Main.cpp
)

set(SOURCEFILES_EXCEPTIONS 
  ${EXCEPTIONS_FOLDER}/JsonInputConversionExceptionTest.cpp
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
target_link_libraries(${EXENAME} PUBLIC gtest DiKErnel.Integration DiKErnel.Integration.TestUtil DiKErnel.KernelWrapper.Json.Input DiKErnel.TestUtil)