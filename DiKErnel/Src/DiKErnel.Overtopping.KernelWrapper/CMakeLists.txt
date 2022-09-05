# Set library name
set(LIBNAME DiKErnel.Overtopping.KernelWrapper)

# Set folder names
set(PUBLIC_FOLDER Public)

# Define sources
set(SOURCEFILES_PUBLIC
  ${PUBLIC_FOLDER}/Overtopping.cpp
  ${PUBLIC_FOLDER}/Overtopping.h
)

# Add library
add_library(${LIBNAME} STATIC
  ${SOURCEFILES_PUBLIC}
)

# Configure folder structure
set_target_properties(${LIBNAME} PROPERTIES FOLDER Src)
source_group(${PUBLIC_FOLDER} FILES ${SOURCEFILES_PUBLIC})

# Expose header files
target_include_directories(${LIBNAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/${PUBLIC_FOLDER}
)

# Link dependencies
target_link_libraries(${LIBNAME}
   ${CMAKE_SOURCE_DIR}/../External/dllDikesOvertopping.lib
)