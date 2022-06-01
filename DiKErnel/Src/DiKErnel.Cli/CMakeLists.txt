# Set executable name
set(EXENAME DiKErnel.Cli)
set(OUTPUTNAME DiKErnel-cli)

# Set folder names
set(INTERNAL_FOLDER Internal)

# Set application specific version parameters
set(VER_FILEDESCRIPTION_STR "DiKErnel command line interface")
set(VER_ORIGINALFILENAME_STR "DiKErnel-cli.exe")
set(VER_PRODUCTNAME_STR "DiKErnel-cli")

# Configure platform specific version resources
CONFIGURE_PLATFORM_SPECIFIC_VERSION_RESOURCE_FILE()

# Define sources
set(SOURCEFILES
  Main.cpp
  ${PLATFORM_SPECIFIC_VERSION_RESOURCE_FILE}
)

set(INTERNAL_SOURCEFILES
  ${INTERNAL_FOLDER}/CommandLineArgumentParser.cpp
  ${INTERNAL_FOLDER}/CommandLineArgumentParser.h
)

# Add executable
add_executable(${EXENAME}
  ${SOURCEFILES}
  ${INTERNAL_SOURCEFILES}
)

# Configure folder structure
set_target_properties(${EXENAME} PROPERTIES FOLDER Src)
source_group("" FILES ${SOURCEFILES})
source_group(${INTERNAL_FOLDER} FILES ${INTERNAL_SOURCEFILES})

# Expose header files
if(BUILD_FOR_RELEASE)
  target_include_directories(${EXENAME}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${INTERNAL_FOLDER}
  )
else()
  target_include_directories(${EXENAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/${INTERNAL_FOLDER}
  )
endif()

# Configure executable output name
set_target_properties(${EXENAME} PROPERTIES
  OUTPUT_NAME ${OUTPUTNAME}
)

# Link dependencies
target_link_libraries(${EXENAME}
  DiKErnel.Core
  DiKErnel.KernelWrapper.Json.Input
  DiKErnel.KernelWrapper.Json.Output
)