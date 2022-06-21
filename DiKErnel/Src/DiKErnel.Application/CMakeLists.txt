# Set library name
set(LIBNAME DiKErnel.Application)

# Set folder names
set(PUBLIC_FOLDER Public)

# Configure version header file
set(VERSION_HEADER_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(VERSION_HEADER_FILE ${VERSION_HEADER_DIR}/Version.h)
configure_file(
  ${CMAKE_SOURCE_DIR}/../Deployment/Version.h.in
  ${VERSION_HEADER_FILE}
  @ONLY)

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
  PRIVATE ${VERSION_HEADER_DIR}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/${PUBLIC_FOLDER})