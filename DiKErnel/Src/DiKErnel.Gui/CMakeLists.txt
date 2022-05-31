# Set executable name
set(EXENAME DiKErnel.Gui)
set(OUTPUTNAME DiKErnel-gui)

# Set properties to include Qt
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_PREFIX_PATH $ENV{QT6DIR64})

# Find package Qt
find_package(Qt6 COMPONENTS Qml Quick REQUIRED)
qt_standard_project_setup()

# Set folder names
set(INTERNAL_FOLDER Internal)
set(QML_FOLDER Qml)

# Set application specific version parameters
set(VER_FILEDESCRIPTION_STR "DiKErnel graphical user interface")
set(VER_ORIGINALFILENAME_STR "DiKErnel-gui.exe")
set(VER_PRODUCTNAME_STR "DiKErnel-gui")

# Configure version header file
CONFIGURE_VERSION_HEADER_FILE()

# Configure platform specific version resources
CONFIGURE_PLATFORM_SPECIFIC_VERSION_RESOURCE_FILE()

# Define sources
set(SOURCEFILES
  Main.cpp
  ${VERSION_HEADER_FILE}
  ${PLATFORM_SPECIFIC_VERSION_RESOURCE_FILE}
)

set(INTERNAL_SOURCEFILES
  ${INTERNAL_FOLDER}/DiKErnel.cpp
  ${INTERNAL_FOLDER}/DiKErnel.h
)

set(QMLFILES
  ${QML_FOLDER}/Main.qml
  ${QML_FOLDER}/MainScreen.qml
)

# Add windows executable
qt_add_executable(${EXENAME} WIN32
  ${INTERNAL_SOURCEFILES}
  ${SOURCEFILES}
)

# Add qml module
qt6_add_qml_module(${EXENAME}
  URI "DiKErnel"
  VERSION 1.0
  RESOURCE_PREFIX "/layout"
  QML_FILES ${QMLFILES}
  NO_PLUGIN_OPTIONAL
  NO_GENERATE_PLUGIN_SOURCE
  NO_GENERATE_QMLDIR
  NO_GENERATE_QMLTYPES
  NO_LINT
  NO_CACHEGEN
)

# Add resources
qt_add_resources(${EXENAME} "resources"
  PREFIX "/"
  FILES
    qtquickcontrols2.conf
    Resources/logo.svg
)

# Configure folder structure
set_target_properties(${EXENAME} PROPERTIES FOLDER Src)
source_group("" FILES ${SOURCEFILES})
source_group(${INTERNAL_FOLDER} FILES ${INTERNAL_SOURCEFILES})
source_group(${QML_FOLDER} FILES ${QMLFILES})

# - Configure executable output name
# - Configure Qt variables
#   => Prevent the creation of a console window on Windows.
set_target_properties(${EXENAME} PROPERTIES
  OUTPUT_NAME ${OUTPUTNAME}
  WIN32_EXECUTABLE ON
)

# Expose header files
if (BUILD_WITH_TESTS)
  target_include_directories(${EXENAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/${INTERNAL_FOLDER}
  )
else()
  target_include_directories(${EXENAME}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${INTERNAL_FOLDER}
  )
endif()

# Link dependencies
target_link_libraries(${EXENAME} PRIVATE
  DiKErnel.Core
  DiKErnel.KernelWrapper.Json.Input
  DiKErnel.KernelWrapper.Json.Output
  Qt6::Qml
  Qt6::Quick
)