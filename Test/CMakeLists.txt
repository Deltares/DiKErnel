# Set executable name
set(EXENAME DiKErnel.Test)

# Define sources
set(CORETESTFILES "")
set(INPUTTESTFILES "")
set(OUTPUTTESTFILES "")

# Add sources
add_subdirectory(Core)
add_subdirectory(Input)
add_subdirectory(Output)

# Add executable
add_executable(${EXENAME}
  ${CORETESTFILES}
  ${INPUTTESTFILES}
  ${OUTPUTTESTFILES}
)

# Create folder structure
source_group(Core FILES ${CORETESTFILES})
source_group(Input FILES ${INPUTTESTFILES})
source_group(Output FILES ${OUTPUTTESTFILES})

# Set include directories
target_include_directories(${EXENAME} PUBLIC Core)
target_include_directories(${EXENAME} PUBLIC Input)
target_include_directories(${EXENAME} PUBLIC Output)

# Fetch third party libraries
Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v2.13.3
)

FetchContent_MakeAvailable(Catch2)

# Link dependencies
target_link_libraries(${EXENAME}
  Catch2::Catch2
  DiKErnel
)