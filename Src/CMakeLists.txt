###########
# Project #
###########
set(LIBNAME DiKErnel)

###########
# Targets #
###########

set(COREFILES "")
add_subdirectory(Core)

set(INPUTFILES "")
add_subdirectory(Input)

set(OUTPUTFILES "")
add_subdirectory(Output)

# Add library
add_library(${LIBNAME} STATIC ${COREFILES} ${INPUTFILES} ${OUTPUTFILES})

# Add folder
source_group(Core FILES ${COREFILES})
source_group(Input FILES ${INPUTFILES})
source_group(Output FILES ${OUTPUTFILES})

# Make sure the compiler can find include files

target_include_directories(${LIBNAME} PUBLIC Core)
target_include_directories(${LIBNAME} PUBLIC Input)
target_include_directories(${LIBNAME} PUBLIC Output)