# Add directories
add_subdirectory(DiKErnel.Core)
add_subdirectory(DiKErnel.DomainLibrary)
add_subdirectory(DiKErnel.FunctionLibrary)
# Only add the GUI in Visual Studio
if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  add_subdirectory(DiKErnel.Gui)
endif()
add_subdirectory(DiKErnel.Integration)
add_subdirectory(DiKErnel.KernelWrapper.Json.Input)
add_subdirectory(DiKErnel.KernelWrapper.Json.Output)
add_subdirectory(DiKErnel.Showcase)
add_subdirectory(DiKErnel.Util)