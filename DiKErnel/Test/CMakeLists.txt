# Add directories
add_subdirectory(DiKErnel.Core.Test)
add_subdirectory(DiKErnel.DomainLibrary.Test)
add_subdirectory(DiKErnel.FunctionLibrary.Test)
add_subdirectory(DiKErnel.KernelWrapper.Json.Test)
add_subdirectory(DiKErnel.TestUtil)

# Fetch third party libraries
Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v2.13.3
)

FetchContent_MakeAvailable(Catch2)