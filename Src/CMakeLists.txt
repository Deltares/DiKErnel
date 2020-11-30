# Set library name
set(LIBNAME DiKErnel)

# Define sources
set(COREFILES "")
set(INPUTFILES "")
set(OUTPUTFILES "")

# Add sources
add_subdirectory(Core)
add_subdirectory(Input)
add_subdirectory(Output)

# Add library
add_library(${LIBNAME} STATIC
  ${COREFILES}
  ${INPUTFILES}
  ${OUTPUTFILES}
)

# Create folder structure
source_group(Core FILES ${COREFILES})
source_group(Input FILES ${INPUTFILES})
source_group(Output FILES ${OUTPUTFILES})

# Set include directories
target_include_directories(${LIBNAME} PUBLIC Core)
target_include_directories(${LIBNAME} PUBLIC Input)
target_include_directories(${LIBNAME} PUBLIC Output)