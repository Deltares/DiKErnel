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

# Define sources
set(SOURCEFILES
  Main.cpp
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
# - Conifgure Qt variables
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
  Qt6::Qml
  Qt6::Quick
)