# Set executable name
set(EXENAME DiKErnel.PerformanceConsole)
set(OUTPUTNAME DiKErnel.PerformanceConsole)

# Set application specific version parameters
set(VER_FILEDESCRIPTION_STR "DiKErnel performance console")
set(VER_ORIGINALFILENAME_STR "DiKErnel.PerformanceConsole.exe")
set(VER_PRODUCTNAME_STR "DiKErnel.PerformanceConsole")

# Configure platform specific version resources
CONFIGURE_PLATFORM_SPECIFIC_VERSION_RESOURCE_FILE()

# Define sources
set(SOURCEFILES
  Main.cpp
  ${PLATFORM_SPECIFIC_VERSION_RESOURCE_FILE}
)

# Add executable
add_executable(${EXENAME}
  ${SOURCEFILES}
)

# Configure folder structure
set_target_properties(${EXENAME} PROPERTIES FOLDER Src)
source_group("" FILES ${SOURCEFILES})

# Expose header files
if(BUILD_FOR_RELEASE)
  target_include_directories(${EXENAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/${INTERNAL_FOLDER}
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
  DiKErnel.Integration
  DiKErnel.Util
)