# Add directories
add_subdirectory(DiKErnel.Acceptance.Test)
add_subdirectory(DiKErnel.Core.Test)
add_subdirectory(DiKErnel.Core.TestUtil)
add_subdirectory(DiKErnel.DomainLibrary.Test)
add_subdirectory(DiKErnel.FunctionLibrary.Test)
add_subdirectory(DiKErnel.Integration.Test)
add_subdirectory(DiKErnel.Integration.TestUtil)
add_subdirectory(DiKErnel.KernelWrapper.Json.Input.Test)
add_subdirectory(DiKErnel.KernelWrapper.Json.Integration.Test)
add_subdirectory(DiKErnel.KernelWrapper.Json.Output.Test)
add_subdirectory(DiKErnel.TestUtil)
add_subdirectory(DiKErnel.Util.Test)
add_subdirectory(DiKErnel.Util.TestUtil)

# Fetch third party libraries
Include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.10.0
)

FetchContent_MakeAvailable(googletest)