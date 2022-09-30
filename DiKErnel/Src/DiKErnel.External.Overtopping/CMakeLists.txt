# Set library name
set(LIBNAME DiKErnel.External.Overtopping)

# Set overtopping platform folder
if(CMAKE_GENERATOR_PLATFORM STREQUAL "Win32")
  set(OVERTOPPING_PLATFORM "x86")
else()
  set(OVERTOPPING_PLATFORM "x64")
endif()

# Set folder names
set(PUBLIC_FOLDER Public)
set(PUBLIC_DATA_FOLDER ${PUBLIC_FOLDER}/Data)
set(OVERTOPPING_FOLDER ${CMAKE_SOURCE_DIR}/../Deployment/Windows/Overtopping/${OVERTOPPING_PLATFORM})

# Define sources
set(SOURCEFILES_PUBLIC
  ${PUBLIC_FOLDER}/OvertoppingAdapter.cpp
  ${PUBLIC_FOLDER}/OvertoppingAdapter.h
)

set(SOURCEFILES_PUBLIC_DATA
  ${PUBLIC_DATA_FOLDER}/Geometry.h
  ${PUBLIC_DATA_FOLDER}/Load.h
  ${PUBLIC_DATA_FOLDER}/ModelFactors.h
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

# Import dll overtopping
add_library(dllDikesOvertopping SHARED IMPORTED)
set_target_properties(dllDikesOvertopping PROPERTIES 
  IMPORTED_LOCATION ${OVERTOPPING_FOLDER}/dllDikesOvertopping.dll
  IMPORTED_IMPLIB ${OVERTOPPING_FOLDER}/dllDikesOvertopping.lib)

# Install overtopping files
set(OVERTOPPING_FILES
  ${OVERTOPPING_FOLDER}/dllDikesOvertopping.dll
  ${OVERTOPPING_FOLDER}/dllDikesOvertopping.lib
  ${OVERTOPPING_FOLDER}/feedbackDLL.dll
  ${OVERTOPPING_FOLDER}/libifcoremd.dll
  ${OVERTOPPING_FOLDER}/libiomp5md.dll
  ${OVERTOPPING_FOLDER}/libmmd.dll
)

install(FILES ${OVERTOPPING_FILES} DESTINATION ./$<CONFIG>)

# Link dependencies
target_link_libraries(${LIBNAME}
  dllDikesOvertopping)