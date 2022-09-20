# Set library name
set(LIBNAME DiKErnel.Util.TestUtil)

# Set folder names
set(HELPERS_FOLDER Helpers)

# Define sources
set(SOURCEFILES
  EventAssertHelper.cpp
  EventAssertHelper.h
  EventRegistryTestHelper.cpp
  EventRegistryTestHelper.h
  ValidatorAssertHelper.h
)

set(SOURCEFILES_HELPERS
  ${HELPERS_FOLDER}/Base.cpp
  ${HELPERS_FOLDER}/Base.h
  ${HELPERS_FOLDER}/Derived1.cpp
  ${HELPERS_FOLDER}/Derived1.h
  ${HELPERS_FOLDER}/Derived2.cpp
  ${HELPERS_FOLDER}/Derived2.h
)

# Add library
add_library(${LIBNAME}
  ${SOURCEFILES}
  ${SOURCEFILES_HELPERS}
)

# Configure folder structure
set_target_properties(${LIBNAME} PROPERTIES FOLDER Test)
source_group("" FILES ${SOURCEFILES})
source_group(${HELPERS_FOLDER} FILES ${SOURCEFILES_HELPERS})

# Expose header files
target_include_directories(${LIBNAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/${PUBLIC_HELPERS_FOLDER}
)

# Link dependencies
target_link_libraries(${LIBNAME}
  DiKErnel.Util
  gmock
)