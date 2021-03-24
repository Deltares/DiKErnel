# Set library name
set(LIBNAME DiKErnel.FunctionLibrary)

# Define sources
set(SOURCEFILES
  NaturalStoneRevetment.cpp
  NaturalStoneRevetment.h
  NaturalStoneRevetmentDeprecated.cpp
  NaturalStoneRevetmentDeprecated.h
)

# Add library
add_library(${LIBNAME} STATIC ${SOURCEFILES})

# Configure folder structure
set_target_properties(${LIBNAME} PROPERTIES FOLDER Src)
source_group("Sources" FILES ${SOURCEFILES})

# Expose header files
target_include_directories(${LIBNAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Link dependencies
target_link_libraries(${LIBNAME} DiKErnel.DomainLibrary)