# Set library name
set(LIBNAME DiKErnel.Integration)

# Define sources
set(SOURCEFILES
  NaturalStoneRevetmentLocationDependentData.cpp
  NaturalStoneRevetmentLocationDependentData.h
  RevetmentCalculationInputBuilder.cpp
  RevetmentCalculationInputBuilder.h
)

# Add library
add_library(${LIBNAME} STATIC ${SOURCEFILES})

# Configure folder structure
set_target_properties(${LIBNAME} PROPERTIES FOLDER Src)
source_group("Sources" FILES ${SOURCEFILES})

# Expose header files
target_include_directories(${LIBNAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Link dependencies
target_link_libraries(${LIBNAME} DiKErnel.Core DiKErnel.FunctionLibrary)