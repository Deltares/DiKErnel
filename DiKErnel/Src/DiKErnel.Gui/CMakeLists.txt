# Set executable name
set(EXENAME DiKErnel.Gui)
set(OUTPUTNAME DiKErnel-gui)

# Set properties to include Qt
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH $ENV{QTDIR})

# Find package Qt
find_package(Qt6 COMPONENTS Widgets REQUIRED)
qt_standard_project_setup()

# Define sources
set(SOURCEFILES
  Main.cpp
  MainWindow.cpp
  MainWindow.h
  MainWindow.ui
)

# Add executable
add_executable(${EXENAME}
  ${SOURCEFILES}
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
target_link_libraries(${EXENAME} Qt6::Widgets)