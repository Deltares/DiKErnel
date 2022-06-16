# Set library name
set(LIBNAME DiKErnel.Application)

# Set folder names
set(PUBLIC_FOLDER Public)

# Configure version header file
CONFIGURE_VERSION_HEADER_FILE()

# Define sources
set(SOURCEFILES_PUBLIC
  ${PUBLIC_FOLDER}/ApplicationHelper.h
  ${PUBLIC_FOLDER}/ApplicationHelper.cpp
  ${VERSION_HEADER_FILE}
)

# Add library
add_library(${LIBNAME} STATIC ${SOURCEFILES_PUBLIC})

# Configure folder structure
set_target_properties(${LIBNAME} PROPERTIES FOLDER Src)
source_group(${PUBLIC_FOLDER} FILES ${SOURCEFILES_PUBLIC})

# Expose header files
target_include_directories(${LIBNAME}
  PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/${PUBLIC_FOLDER})