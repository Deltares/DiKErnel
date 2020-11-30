# Set executable name
set(EXENAME DiKErnel.Test)

# Add sources
set (SOURCES
  ControllerTest.cpp
)

# Add executable
add_executable(${EXENAME} ${SOURCES})

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