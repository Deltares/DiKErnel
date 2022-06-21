# Set CMake variables
cmake_minimum_required(VERSION 3.18)

# Define project
project(DiKErnel)

# Define options
option(BUILD_FOR_RELEASE "Build for release" FALSE)

# Set compiler flags
set(CMAKE_CXX_STANDARD 17)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  message("Building with code coverage")
  set(CMAKE_CXX_FLAGS "-g -Og -fprofile-arcs -ftest-coverage -fno-elide-constructors -fno-inline -static-libgcc -static-libstdc++")
  set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)
else()
  message("Building without code coverage")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif()

# Set global properties
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Set generic version parameters
set(VER_COMPANYNAME_STR "Deltares")
set(VER_LEGALCOPYRIGHT_STR "Copyright \\xA9 Deltares 2022")
set(VER_PRODUCTVERSION 22,1,1)
if(NOT DEFINED VER_BUILDNUMBER)
  set(VER_BUILDNUMBER 0)
endif()
if(BUILD_FOR_RELEASE)
  set(VER_PRODUCTVERSION_STR "22.1.1 (ALPHA)")
else()
  set(VER_PRODUCTVERSION_STR "22.1.1.${VER_BUILDNUMBER} (ALPHA)")
endif()
set(VER_FILEVERSION 22,1,1,${VER_BUILDNUMBER})
set(VER_FILEVERSION_STR "22.1.1.${VER_BUILDNUMBER}")

# Macro for configuring a platform specific version resource file
macro(CONFIGURE_PLATFORM_SPECIFIC_VERSION_RESOURCE_FILE)
  if(WIN32)
    set(PLATFORM_SPECIFIC_VERSION_RESOURCE_FILE ${CMAKE_CURRENT_BINARY_DIR}/version.rc)
    configure_file(
      ${CMAKE_SOURCE_DIR}/../Deployment/Windows/version.rc.in
      ${PLATFORM_SPECIFIC_VERSION_RESOURCE_FILE}
      @ONLY)
  endif()
endmacro()

# Macro for configuring a version header file
macro(CONFIGURE_VERSION_HEADER_FILE)
  set(VERSION_HEADER_DIR ${CMAKE_CURRENT_BINARY_DIR})
  set(VERSION_HEADER_FILE ${VERSION_HEADER_DIR}/Version.h)
  configure_file(
    ${CMAKE_SOURCE_DIR}/../Deployment/Version.h.in
    ${VERSION_HEADER_FILE}
    @ONLY)
endmacro()

# Macro for embedding a textual resource
macro(EMBED_TEXTUAL_RESOURCE RESOURCE_FILE_PATH HEADER_FILE_NAME RESOURCE_NAME)
  set(EMBEDDED_RESOURCES_DIR ${CMAKE_CURRENT_BINARY_DIR})
  set(RESOURCE_NAME ${RESOURCE_NAME})
  file(READ ${RESOURCE_FILE_PATH} TEXTUAL_CONTENT)
  configure_file(
    ${CMAKE_SOURCE_DIR}/../Deployment/EmbeddedResources/Textual.h.in
    ${EMBEDDED_RESOURCES_DIR}/${HEADER_FILE_NAME}
    @ONLY)
endmacro()

# Add directories
add_subdirectory(Src)

# Set startup project in Visual Studio
if(CMAKE_GENERATOR MATCHES "Visual Studio")
  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT DiKErnel.Gui)
endif()

if(NOT BUILD_FOR_RELEASE)
  add_subdirectory(Test)
endif()