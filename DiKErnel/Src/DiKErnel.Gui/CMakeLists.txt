# Set executable name
set(EXENAME DiKErnel.Gui)
set(OUTPUTNAME DiKErnel-gui)

# Set properties to include Qt
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_PREFIX_PATH $ENV{QTDIR})

# Find package Qt
find_package(Qt6 COMPONENTS Qml Quick REQUIRED)
qt_standard_project_setup()

# Define sources
set(SOURCEFILES
  Main.cpp
)

# Add executable
qt_add_executable(${EXENAME}
  ${SOURCEFILES}
)

set(QMLFILES
  qml/main.qml
  qml/MainScreen.ui.qml
)

qt6_add_qml_module(${EXENAME}
  URI "main"
  VERSION 1.0
  RESOURCE_PREFIX "/layout"
  QML_FILES ${QMLFILES}
)

qt_add_resources(${EXENAME} "resources"
  PREFIX "/"
  FILES
    qtquickcontrols2.conf
    resources/logo.svg
)

# Configure folder structure
set_target_properties(${EXENAME} PROPERTIES FOLDER Src)
source_group("" FILES ${SOURCEFILES})

# - Configure executable output name
# - Conifgure Qt variables
#   => Prevent the creation of a console window on Windows.
#   => Create an application bundle on macOS.
set_target_properties(${EXENAME} PROPERTIES
  OUTPUT_NAME ${OUTPUTNAME}
  WIN32_EXECUTABLE ON
  MACOSX_BUNDLE ON
)

# Link dependencies
target_link_libraries(${EXENAME} PRIVATE
  Qt6::Qml
  Qt6::Quick
)