# Set library name
set(LIBNAME DiKErnel.External.Overtopping)

# Set folder names
set(PUBLIC_FOLDER Public)
set(PUBLIC_DATA_FOLDER ${PUBLIC_FOLDER}/Data)
set(OVERTOPPING_FOLDER ${CMAKE_SOURCE_DIR}/../Deployment/Windows/Overtopping)

# Define sources
set(SOURCEFILES_PUBLIC
  ${PUBLIC_FOLDER}/OvertoppingAdapter.cpp
  ${PUBLIC_FOLDER}/OvertoppingAdapter.h
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

# Add dll overtopping
add_library(dllDikesOvertopping SHARED IMPORTED)
set_target_properties(dllDikesOvertopping PROPERTIES 
  IMPORTED_LOCATION ${OVERTOPPING_FOLDER}/dllDikesOvertopping.dll
  IMPORTED_IMPLIB ${OVERTOPPING_FOLDER}/dllDikesOvertopping.lib)

add_library(feedbackDLL SHARED IMPORTED)
set_target_properties(feedbackDLL PROPERTIES 
  IMPORTED_LOCATION ${OVERTOPPING_FOLDER}/feedbackDLL.dll
  IMPORTED_IMPLIB ${OVERTOPPING_FOLDER}/dllDikesOvertopping.lib)

add_library(dllDikesOvertoppingModule INTERFACE IMPORTED)
target_link_libraries(dllDikesOvertoppingModule INTERFACE dllDikesOvertopping feedbackDLL)

# Link dependencies
target_link_libraries(${LIBNAME}
  dllDikesOvertoppingModule)