# Set executable name
set(EXENAME DiKErnel.DomainLibrary.Test)

# Set folder names
set(GRASS_REVETMENT_WAVE_IMPACT_FOLDER GrassRevetmentWaveImpact)
set(GRASS_REVETMENT_WAVE_RUNUP_FOLDER GrassRevetmentWaveRunup)
set(NATURAL_STONE_REVETMENT_FOLDER NaturalStoneRevetment)

# Define sources
set(SOURCEFILES_ROOT
  ConstantsTest.cpp
  Main.cpp
  RevetmentDefaultsTest.cpp
)

set(SOURCEFILES_GRASS_REVETMENT_WAVE_IMPACT
  ${GRASS_REVETMENT_WAVE_IMPACT_FOLDER}/GrassRevetmentWaveImpactClosedSodDefaultsTest.cpp
  ${GRASS_REVETMENT_WAVE_IMPACT_FOLDER}/GrassRevetmentWaveImpactOpenSodDefaultsTest.cpp
)

set(SOURCEFILES_GRASS_REVETMENT_WAVE_RUNUP
  ${GRASS_REVETMENT_WAVE_RUNUP_FOLDER}/GrassRevetmentWaveRunupClosedSodDefaultsTest.cpp
  ${GRASS_REVETMENT_WAVE_RUNUP_FOLDER}/GrassRevetmentWaveRunupOpenSodDefaultsTest.cpp
  ${GRASS_REVETMENT_WAVE_RUNUP_FOLDER}/GrassRevetmentWaveRunupRayleighClosedSodDefaultsTest.cpp
  ${GRASS_REVETMENT_WAVE_RUNUP_FOLDER}/GrassRevetmentWaveRunupRayleighOpenSodDefaultsTest.cpp
)

set(SOURCEFILES_NATURAL_STONE_REVETMENT
  ${NATURAL_STONE_REVETMENT_FOLDER}/NordicStoneRevetmentDefaultsTest.cpp
)

# Add executable
add_executable(${EXENAME}
  ${SOURCEFILES_ROOT}
  ${SOURCEFILES_GRASS_REVETMENT_WAVE_IMPACT}
  ${SOURCEFILES_GRASS_REVETMENT_WAVE_RUNUP}
  ${SOURCEFILES_NATURAL_STONE_REVETMENT}
)

# Configure folder structure
set_target_properties(${EXENAME} PROPERTIES FOLDER Test)
source_group("" FILES ${SOURCEFILES_ROOT})
source_group(${GRASS_REVETMENT_WAVE_IMPACT_FOLDER} FILES ${SOURCEFILES_GRASS_REVETMENT_WAVE_IMPACT})
source_group(${GRASS_REVETMENT_WAVE_RUNUP_FOLDER} FILES ${SOURCEFILES_GRASS_REVETMENT_WAVE_RUNUP})
source_group(${NATURAL_STONE_REVETMENT_FOLDER} FILES ${SOURCEFILES_NATURAL_STONE_REVETMENT})

# Link dependencies
target_link_libraries(${EXENAME} gtest DiKErnel.DomainLibrary DiKErnel.TestUtil)