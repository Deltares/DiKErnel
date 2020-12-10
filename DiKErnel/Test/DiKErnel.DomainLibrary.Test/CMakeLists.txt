# Set executable name
set(EXENAME DiKErnel.DomainLibrary.Test)

# Define sources
set(SOURCEFILES
  ConstantsTest.cpp
  HydraulicLoadsDefaultsTest.cpp
  Main.cpp
  NaturalStoneRevetmentDefaultsTest.cpp
)

# Add executable
add_executable(${EXENAME} ${SOURCEFILES})

# Configure folder structure
set_target_properties(${EXENAME} PROPERTIES FOLDER Test)
source_group("Sources" FILES ${SOURCEFILES})

# Link dependencies
target_link_libraries(${EXENAME} Catch2::Catch2 DiKErnel.DomainLibrary)