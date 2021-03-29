# Set executable name
set(EXENAME DiKErnel.Integration.Test)

# Set folder names
set(DATA_FOLDER Data)
set(EXCEPTIONS_FOLDER Exceptions)

# Define sources
set(SOURCEFILES_MAIN
  Main.cpp
  RevetmentCalculationInputBuilderTest.cpp
)

set(SOURCEFILES_DATA
  ${DATA_FOLDER}/GrassRevetmentWaveImpactLocationConstructionPropertiesTest.cpp
  ${DATA_FOLDER}/NaturalStoneRevetmentLocationConstructionPropertiesTest.cpp
)

set(SOURCEFILES_EXCEPTIONS
  ${EXCEPTIONS_FOLDER}/RevetmentCalculationInputBuilderExceptionTest.cpp
)

# Add executable
add_executable(${EXENAME}
  ${SOURCEFILES_MAIN}
  ${SOURCEFILES_DATA}
  ${SOURCEFILES_EXCEPTIONS}
)

# Configure folder structure
set_target_properties(${EXENAME} PROPERTIES FOLDER Test)
source_group("" FILES ${SOURCEFILES_MAIN})
source_group(${DATA_FOLDER} FILES ${SOURCEFILES_DATA})
source_group(${EXCEPTIONS_FOLDER} FILES ${SOURCEFILES_EXCEPTIONS})

# Link dependencies
target_link_libraries(${EXENAME} PUBLIC gtest DiKErnel.Integration DiKErnel.Integration.TestUtil DiKErnel.TestUtil)