# Set library name
set(LIBNAME DiKErnel.Overtopping.KernelWrapper)

# Set folder names
set(PUBLIC_FOLDER Public)
set(PUBLIC_DATA_FOLDER ${PUBLIC_FOLDER}/Data)

# Define sources
set(SOURCEFILES_PUBLIC
  ${PUBLIC_FOLDER}/Overtopping.cpp
  ${PUBLIC_FOLDER}/Overtopping.h
)

set(SOURCEFILES_PUBLIC_DATA
  ${PUBLIC_DATA_FOLDER}/Geometry.h
  ${PUBLIC_DATA_FOLDER}/Input.h
  ${PUBLIC_DATA_FOLDER}/Load.h
  ${PUBLIC_DATA_FOLDER}/Result.h
)

# Add library
add_library(${LIBNAME} STATIC
  ${SOURCEFILES_PUBLIC}
  ${SOURCEFILES_PUBLIC_DATA}
)

# Configure folder structure
set_target_properties(${LIBNAME} PROPERTIES FOLDER Src)
source_group(${PUBLIC_FOLDER} FILES ${SOURCEFILES_PUBLIC})
source_group(${PUBLIC_DATA_FOLDER} FILES ${SOURCEFILES_PUBLIC_DATA})

# Expose header files
target_include_directories(${LIBNAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/${PUBLIC_FOLDER}
  ${CMAKE_CURRENT_SOURCE_DIR}/${PUBLIC_DATA_FOLDER}
)

# Link dependencies
target_link_libraries(${LIBNAME}
   ${CMAKE_SOURCE_DIR}/../External/dllDikesOvertopping.lib
)