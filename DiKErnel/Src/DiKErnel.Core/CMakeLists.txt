# Set library name
set(LIBNAME DiKErnel.Core)

# Set folder names
set(PUBLIC_FOLDER Public)
set(PUBLIC_DATA_FOLDER ${PUBLIC_FOLDER}/Data)
set(PUBLIC_EXCEPTIONS_FOLDER ${PUBLIC_FOLDER}/Exceptions)

# Define sources
set(SOURCEFILES_PUBLIC
  ${PUBLIC_FOLDER}/CalculationMode.h
  ${PUBLIC_FOLDER}/Calculator.cpp
  ${PUBLIC_FOLDER}/Calculator.h
  ${PUBLIC_FOLDER}/Validator.cpp
  ${PUBLIC_FOLDER}/Validator.h
)

set(SOURCEFILES_PUBLIC_DATA
  ${PUBLIC_DATA_FOLDER}/CalculationOutput.cpp
  ${PUBLIC_DATA_FOLDER}/CalculationOutput.h
  ${PUBLIC_DATA_FOLDER}/CharacteristicPoint.cpp
  ${PUBLIC_DATA_FOLDER}/CharacteristicPoint.h
  ${PUBLIC_DATA_FOLDER}/CharacteristicPointType.h
  ${PUBLIC_DATA_FOLDER}/ICalculationInput.h
  ${PUBLIC_DATA_FOLDER}/ILocationDependentInput.h
  ${PUBLIC_DATA_FOLDER}/IProfileData.h
  ${PUBLIC_DATA_FOLDER}/ITimeDependentInput.h
  ${PUBLIC_DATA_FOLDER}/LocationDependentOutput.cpp
  ${PUBLIC_DATA_FOLDER}/LocationDependentOutput.h
  ${PUBLIC_DATA_FOLDER}/ProfilePoint.cpp
  ${PUBLIC_DATA_FOLDER}/ProfilePoint.h
  ${PUBLIC_DATA_FOLDER}/ProfileSegment.cpp
  ${PUBLIC_DATA_FOLDER}/ProfileSegment.h
  ${PUBLIC_DATA_FOLDER}/TimeDependentOutputConstructionProperties.h
  ${PUBLIC_DATA_FOLDER}/TimeDependentOutput.cpp
  ${PUBLIC_DATA_FOLDER}/TimeDependentOutput.h
  ${PUBLIC_DATA_FOLDER}/ValidationResultType.h
)

set(SOURCEFILES_PUBLIC_EXCEPTIONS
  ${PUBLIC_EXCEPTIONS_FOLDER}/InvalidTimeDependentOutputException.cpp
  ${PUBLIC_EXCEPTIONS_FOLDER}/InvalidTimeDependentOutputException.h
)

# Add library
add_library(${LIBNAME} STATIC
  ${SOURCEFILES_PUBLIC}
  ${SOURCEFILES_PUBLIC_DATA}
  ${SOURCEFILES_PUBLIC_EXCEPTIONS}
)

# Configure folder structure
set_target_properties(${LIBNAME} PROPERTIES FOLDER Src)
source_group(${PUBLIC_FOLDER} FILES ${SOURCEFILES_PUBLIC})
source_group(${PUBLIC_DATA_FOLDER} FILES ${SOURCEFILES_PUBLIC_DATA})
source_group(${PUBLIC_EXCEPTIONS_FOLDER} FILES ${SOURCEFILES_PUBLIC_EXCEPTIONS})

# Expose header files
target_include_directories(${LIBNAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/${PUBLIC_FOLDER}
  ${CMAKE_CURRENT_SOURCE_DIR}/${PUBLIC_DATA_FOLDER}
  ${CMAKE_CURRENT_SOURCE_DIR}/${PUBLIC_EXCEPTIONS_FOLDER}
)

# Link dependencies
target_link_libraries(${LIBNAME} DiKErnel.Util)