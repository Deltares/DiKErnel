# Set library name
set(LIBNAME DiKErnel.Core)

# Set folder names
set(PUBLIC_FOLDER Public)

# Define sources
set(SOURCEFILES_PUBLIC
  ${PUBLIC_FOLDER}/CalculationOutput.cpp
  ${PUBLIC_FOLDER}/CalculationOutput.h
  ${PUBLIC_FOLDER}/Calculator.cpp
  ${PUBLIC_FOLDER}/Calculator.h
  ${PUBLIC_FOLDER}/CalculationState.h
  ${PUBLIC_FOLDER}/CharacteristicPoint.cpp
  ${PUBLIC_FOLDER}/CharacteristicPoint.h
  ${PUBLIC_FOLDER}/CharacteristicPointType.h
  ${PUBLIC_FOLDER}/ICalculationInput.h
  ${PUBLIC_FOLDER}/ILocationDependentInput.h
  ${PUBLIC_FOLDER}/IProfileData.h
  ${PUBLIC_FOLDER}/ITimeDependentInput.h
  ${PUBLIC_FOLDER}/LocationDependentOutput.cpp
  ${PUBLIC_FOLDER}/LocationDependentOutput.h
  ${PUBLIC_FOLDER}/ProfilePoint.cpp
  ${PUBLIC_FOLDER}/ProfilePoint.h
  ${PUBLIC_FOLDER}/TimeDependentOutput.cpp
  ${PUBLIC_FOLDER}/TimeDependentOutput.h
  ${PUBLIC_FOLDER}/ValidationResultType.h
  ${PUBLIC_FOLDER}/Validator.cpp
  ${PUBLIC_FOLDER}/Validator.h
)

# Add library
add_library(${LIBNAME} STATIC ${SOURCEFILES_PUBLIC})

# Configure folder structure
set_target_properties(${LIBNAME} PROPERTIES FOLDER Src)
source_group(${PUBLIC_FOLDER} FILES ${SOURCEFILES_PUBLIC})

# Expose header files
target_include_directories(${LIBNAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/${PUBLIC_FOLDER})

# Link dependencies
target_link_libraries(${LIBNAME} DiKErnel.Util)