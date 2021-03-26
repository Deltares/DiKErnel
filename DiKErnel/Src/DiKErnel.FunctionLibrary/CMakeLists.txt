# Set library name
set(LIBNAME DiKErnel.FunctionLibrary)

# Set folder names
set(PUBLIC_FOLDER Public)

# Define sources
set(SOURCEFILES_PUBLIC
  ${PUBLIC_FOLDER}/Generic.cpp
  ${PUBLIC_FOLDER}/Generic.h
  ${PUBLIC_FOLDER}/NaturalStoneRevetment.cpp
  ${PUBLIC_FOLDER}/NaturalStoneRevetment.h
  ${PUBLIC_FOLDER}/NaturalStoneRevetmentDeprecated.cpp
  ${PUBLIC_FOLDER}/NaturalStoneRevetmentDeprecated.h
  ${PUBLIC_FOLDER}/Revetment.cpp
  ${PUBLIC_FOLDER}/Revetment.h
)

# Add library
add_library(${LIBNAME} STATIC ${SOURCEFILES_PUBLIC})

# Configure folder structure
set_target_properties(${LIBNAME} PROPERTIES FOLDER Src)
source_group(${PUBLIC_FOLDER} FILES ${SOURCEFILES_PUBLIC})

# Expose header files
target_include_directories(${LIBNAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/${PUBLIC_FOLDER})

# Link dependencies
target_link_libraries(${LIBNAME} DiKErnel.DomainLibrary)