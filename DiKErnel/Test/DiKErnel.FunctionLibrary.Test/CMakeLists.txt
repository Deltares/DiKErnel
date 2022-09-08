# Set executable name
set(EXENAME DiKErnel.FunctionLibrary.Test)

# Set folder names
set(ASPHALT_WAVE_IMPACT_FOLDER AsphaltRevetmentWaveImpact)
set(GRASS_REVETMENT_FOLDER GrassRevetment)
set(GRASS_REVETMENT_OVERTOPPING_FOLDER GrassRevetmentOvertopping)
set(GRASS_REVETMENT_WAVE_IMPACT_FOLDER GrassRevetmentWaveImpact)
set(GRASS_REVETMENT_WAVE_RUNUP_FOLDER GrassRevetmentWaveRunup)
set(NATURAL_STONE_REVETMENT_FOLDER NaturalStoneRevetment)

# Define sources
set(SOURCEFILES_ROOT
  GenericFunctionsTest.cpp
  HydraulicLoadFunctionsTest.cpp
  Main.cpp
  RevetmentFunctionsTest.cpp
)

set(SOURCEFILES_ASPHALT_REVETMENT_WAVE_IMPACT
  ${ASPHALT_WAVE_IMPACT_FOLDER}/AsphaltRevetmentWaveImpactFunctionsInputTest.cpp
  ${ASPHALT_WAVE_IMPACT_FOLDER}/AsphaltRevetmentWaveImpactFunctionsTest.cpp
)

set(SOURCEFILES_GRASS_REVETMENT
  ${GRASS_REVETMENT_FOLDER}/GrassRevetmentCumulativeOverloadInputTest.cpp
  ${GRASS_REVETMENT_FOLDER}/GrassRevetmentFunctionsTest.cpp
)

set(SOURCEFILES_GRASS_REVETMENT_OVERTOPPING
  ${GRASS_REVETMENT_OVERTOPPING_FOLDER}/GrassRevetmentOvertoppingCumulativeOverloadInputTest.cpp
  ${GRASS_REVETMENT_OVERTOPPING_FOLDER}/GrassRevetmentOvertoppingFunctionsTest.cpp
  ${GRASS_REVETMENT_OVERTOPPING_FOLDER}/GrassRevetmentOvertoppingRepresentative2PInputTest.cpp
)

set(SOURCEFILES_GRASS_REVETMENT_WAVE_IMPACT
  ${GRASS_REVETMENT_WAVE_IMPACT_FOLDER}/GrassRevetmentWaveImpactFunctionsTest.cpp
)

set(SOURCEFILES_GRASS_REVETMENT_WAVE_RUNUP
  ${GRASS_REVETMENT_WAVE_RUNUP_FOLDER}/GrassRevetmentWaveRunupFunctionsTest.cpp
  ${GRASS_REVETMENT_WAVE_RUNUP_FOLDER}/GrassRevetmentWaveRunupRayleighCumulativeOverloadInputTest.cpp
  ${GRASS_REVETMENT_WAVE_RUNUP_FOLDER}/GrassRevetmentWaveRunupRayleighFunctionsTest.cpp
  ${GRASS_REVETMENT_WAVE_RUNUP_FOLDER}/GrassRevetmentWaveRunupRepresentative2PInputTest.cpp
)

set(SOURCEFILES_NATURAL_STONE_REVETMENT
  ${NATURAL_STONE_REVETMENT_FOLDER}/NaturalStoneRevetmentFunctionsTest.cpp
  ${NATURAL_STONE_REVETMENT_FOLDER}/NaturalStoneRevetmentHydraulicLoadInputTest.cpp
  ${NATURAL_STONE_REVETMENT_FOLDER}/NaturalStoneRevetmentLimitLoadingInputTest.cpp
  ${NATURAL_STONE_REVETMENT_FOLDER}/NaturalStoneRevetmentOuterSlopeInputTest.cpp
)

# Add executable
add_executable(${EXENAME}
  ${SOURCEFILES_ROOT}
  ${SOURCEFILES_ASPHALT_REVETMENT_WAVE_IMPACT}
  ${SOURCEFILES_GRASS_REVETMENT}
  ${SOURCEFILES_GRASS_REVETMENT_OVERTOPPING}
  ${SOURCEFILES_GRASS_REVETMENT_WAVE_IMPACT}
  ${SOURCEFILES_GRASS_REVETMENT_WAVE_RUNUP}
  ${SOURCEFILES_NATURAL_STONE_REVETMENT}
)

# Configure folder structure
set_target_properties(${EXENAME} PROPERTIES FOLDER Test)
source_group("" FILES ${SOURCEFILES_ROOT})
source_group(${ASPHALT_WAVE_IMPACT_FOLDER} FILES ${SOURCEFILES_ASPHALT_REVETMENT_WAVE_IMPACT})
source_group(${GRASS_REVETMENT_FOLDER} FILES ${SOURCEFILES_GRASS_REVETMENT})
source_group(${GRASS_REVETMENT_OVERTOPPING_FOLDER} FILES ${SOURCEFILES_GRASS_REVETMENT_OVERTOPPING})
source_group(${GRASS_REVETMENT_WAVE_IMPACT_FOLDER} FILES ${SOURCEFILES_GRASS_REVETMENT_WAVE_IMPACT})
source_group(${GRASS_REVETMENT_WAVE_RUNUP_FOLDER} FILES ${SOURCEFILES_GRASS_REVETMENT_WAVE_RUNUP})
source_group(${NATURAL_STONE_REVETMENT_FOLDER} FILES ${SOURCEFILES_NATURAL_STONE_REVETMENT})

# Link dependencies
target_link_libraries(${EXENAME} 
  DiKErnel.FunctionLibrary
  DiKErnel.TestUtil
  gtest
)