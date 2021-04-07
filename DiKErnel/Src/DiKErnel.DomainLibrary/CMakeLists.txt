# Set library name
set(LIBNAME DiKErnel.DomainLibrary)

# Set folder names
set(PUBLIC_FOLDER Public)

# Define sources
set(SOURCEFILES_PUBLIC
  ${PUBLIC_FOLDER}/Constants.h
  ${PUBLIC_FOLDER}/GrassRevetmentWaveImpactClosedSodDefaults.h
  ${PUBLIC_FOLDER}/GrassRevetmentWaveImpactOpenSodDefaults.h
  ${PUBLIC_FOLDER}/NordicStoneRevetmentDefaults.h
  ${PUBLIC_FOLDER}/RevetmentDefaults.h
)

# Add library
add_library(${LIBNAME} INTERFACE)

# Set target sources
target_sources(${LIBNAME} INTERFACE ${SOURCEFILES_PUBLIC})

# Expose header files
target_include_directories(${LIBNAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/${PUBLIC_FOLDER})