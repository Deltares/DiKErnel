# Set library name
set(LIBNAME DiKErnel.DomainLibrary)

# Set folder names
set(PUBLIC_FOLDER Public)

# Define sources
set(SOURCEFILES_PUBLIC
  ${PUBLIC_FOLDER}/Constants.h
  ${PUBLIC_FOLDER}/GrassRevetmentWaveImpactClosedSodDefaults.cpp
  ${PUBLIC_FOLDER}/GrassRevetmentWaveImpactClosedSodDefaults.h
  ${PUBLIC_FOLDER}/GrassRevetmentWaveImpactOpenSodDefaults.cpp
  ${PUBLIC_FOLDER}/GrassRevetmentWaveImpactOpenSodDefaults.h
  ${PUBLIC_FOLDER}/IGrassRevetmentWaveImpactDefaults.h
  ${PUBLIC_FOLDER}/INaturalStoneRevetmentDefaults.h
  ${PUBLIC_FOLDER}/NordicStoneRevetmentDefaults.cpp
  ${PUBLIC_FOLDER}/NordicStoneRevetmentDefaults.h
  ${PUBLIC_FOLDER}/RevetmentDefaults.h
)

# Add library
add_library(${LIBNAME} STATIC ${SOURCEFILES_PUBLIC})

# Configure folder structure
set_target_properties(${LIBNAME} PROPERTIES FOLDER Src)
source_group(${PUBLIC_FOLDER} FILES ${SOURCEFILES_PUBLIC})

# Expose header files
target_include_directories(${LIBNAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/${PUBLIC_FOLDER})