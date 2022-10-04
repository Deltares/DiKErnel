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
set(INTERNAL_FOLDER Internal)
set(INTERNAL_DATA_FOLDER ${INTERNAL_FOLDER}/Data)

set(OVERTOPPING_FOLDER ${CMAKE_SOURCE_DIR}/../Deployment/Windows/Overtopping/${OVERTOPPING_PLATFORM})

# Define sources
set(SOURCEFILES_PUBLIC
  ${PUBLIC_FOLDER}/OvertoppingAdapter.cpp
  ${PUBLIC_FOLDER}/OvertoppingAdapter.h
)

set(SOURCEFILES_INTERNAL_DATA
  ${INTERNAL_DATA_FOLDER}/Geometry.h
  ${INTERNAL_DATA_FOLDER}/Load.h
  ${INTERNAL_DATA_FOLDER}/ModelFactors.h
  ${INTERNAL_DATA_FOLDER}/Result.h
)

# Add library
add_library(${LIBNAME} STATIC
  ${SOURCEFILES_PUBLIC}
  ${SOURCEFILES_INTERNAL_DATA}
)

# Configure folder structure
set_target_properties(${LIBNAME} PROPERTIES FOLDER Src)
source_group(${PUBLIC_FOLDER} FILES ${SOURCEFILES_PUBLIC})
source_group(${INTERNAL_DATA_FOLDER} FILES ${SOURCEFILES_INTERNAL_DATA})

# Expose header files
if(BUILD_FOR_RELEASE)
  target_include_directories(${LIBNAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/${PUBLIC_FOLDER}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${INTERNAL_DATA_FOLDER}
  )
else()
  target_include_directories(${LIBNAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/${PUBLIC_FOLDER}
    ${CMAKE_CURRENT_SOURCE_DIR}/${INTERNAL_DATA_FOLDER}
  )
endif()

# Import dll overtopping
add_library(dllDikesOvertopping SHARED IMPORTED)
set_target_properties(dllDikesOvertopping PROPERTIES 
  IMPORTED_LOCATION ${OVERTOPPING_FOLDER}/dllDikesOvertopping.dll
  IMPORTED_IMPLIB ${OVERTOPPING_FOLDER}/dllDikesOvertopping.lib)

# Install overtopping files
set(OVERTOPPING_FILES
  ${OVERTOPPING_FOLDER}/dllDikesOvertopping.dll
  ${OVERTOPPING_FOLDER}/feedbackDLL.dll
  ${OVERTOPPING_FOLDER}/libifcoremd.dll
  ${OVERTOPPING_FOLDER}/libiomp5md.dll
  ${OVERTOPPING_FOLDER}/libmmd.dll
)

install(FILES ${OVERTOPPING_FILES} DESTINATION ./$<CONFIG>)

# Link dependencies
target_link_libraries(${LIBNAME}
  dllDikesOvertopping)