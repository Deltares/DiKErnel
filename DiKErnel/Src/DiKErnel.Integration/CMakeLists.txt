# Set library name
set(LIBNAME DiKErnel.Integration)

# Set folder names
set(PUBLIC_FOLDER Public)
set(PUBLIC_DATA_FOLDER ${PUBLIC_FOLDER}/Data)
set(PUBLIC_EXCEPTIONS_FOLDER ${PUBLIC_FOLDER}/Exceptions)
set(INTERNAL_DATA_FOLDER Internal/Data)
set(INTERNAL_EXCEPTIONS_FOLDER Internal/Exceptions)

# Define sources
set(SOURCEFILES_PUBLIC
  ${PUBLIC_FOLDER}/RevetmentCalculationInputBuilder.cpp
  ${PUBLIC_FOLDER}/RevetmentCalculationInputBuilder.h
)

set(SOURCEFILES_PUBLIC_DATA
  ${PUBLIC_DATA_FOLDER}/NaturalStoneRevetmentLocationConstructionProperties.cpp
  ${PUBLIC_DATA_FOLDER}/NaturalStoneRevetmentLocationConstructionProperties.h
)

set(SOURCEFILES_PUBLIC_EXCEPTIONS
  ${PUBLIC_EXCEPTIONS_FOLDER}/RevetmentCalculationInputBuilderException.cpp
  ${PUBLIC_EXCEPTIONS_FOLDER}/RevetmentCalculationInputBuilderException.h  
)

set(SOURCEFILES_INTERNAL_DATA
  ${INTERNAL_DATA_FOLDER}/CalculationInput.cpp
  ${INTERNAL_DATA_FOLDER}/CalculationInput.h
  ${INTERNAL_DATA_FOLDER}/LocationDependentData.cpp
  ${INTERNAL_DATA_FOLDER}/LocationDependentData.h
  ${INTERNAL_DATA_FOLDER}/NaturalStoneRevetmentLocationDependentData.cpp
  ${INTERNAL_DATA_FOLDER}/NaturalStoneRevetmentLocationDependentData.h
  ${INTERNAL_DATA_FOLDER}/TimeDependentData.cpp
  ${INTERNAL_DATA_FOLDER}/TimeDependentData.h
)

set(SOURCEFILES_INTERNAL_EXCEPTIONS
  ${INTERNAL_EXCEPTIONS_FOLDER}/InvalidCalculationDataException.cpp
  ${INTERNAL_EXCEPTIONS_FOLDER}/InvalidCalculationDataException.h
)

# Add library
add_library(${LIBNAME} STATIC
  ${SOURCEFILES_PUBLIC}
  ${SOURCEFILES_PUBLIC_DATA}
  ${SOURCEFILES_PUBLIC_EXCEPTIONS}
  ${SOURCEFILES_INTERNAL_DATA}
  ${SOURCEFILES_INTERNAL_EXCEPTIONS}
)

# Configure folder structure
set_target_properties(${LIBNAME} PROPERTIES FOLDER Src)
source_group(${PUBLIC_FOLDER} FILES ${SOURCEFILES_PUBLIC})
source_group(${PUBLIC_DATA_FOLDER} FILES ${SOURCEFILES_PUBLIC_DATA})
source_group(${PUBLIC_EXCEPTIONS_FOLDER} FILES ${SOURCEFILES_PUBLIC_EXCEPTIONS})
source_group(${INTERNAL_DATA_FOLDER} FILES ${SOURCEFILES_INTERNAL_DATA})
source_group(${INTERNAL_EXCEPTIONS_FOLDER} FILES ${SOURCEFILES_INTERNAL_EXCEPTIONS})

# Expose header files
if (BUILD_WITH_TESTS)
  target_include_directories(${LIBNAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/${PUBLIC_FOLDER}
    ${CMAKE_CURRENT_SOURCE_DIR}/${PUBLIC_DATA_FOLDER}
    ${CMAKE_CURRENT_SOURCE_DIR}/${PUBLIC_EXCEPTIONS_FOLDER}
    ${CMAKE_CURRENT_SOURCE_DIR}/${INTERNAL_DATA_FOLDER}
    ${CMAKE_CURRENT_SOURCE_DIR}/${INTERNAL_EXCEPTIONS_FOLDER}
  )
else()
  target_include_directories(${LIBNAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/${PUBLIC_FOLDER}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/${PUBLIC_DATA_FOLDER}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/${PUBLIC_EXCEPTIONS_FOLDER}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${INTERNAL_DATA_FOLDER}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${INTERNAL_EXCEPTIONS_FOLDER}
  )
endif()

# Link dependencies
target_link_libraries(${LIBNAME} DiKErnel.Core DiKErnel.FunctionLibrary)