# Add sources to parent scope
set(CORETESTFILES ${CORETESTFILES}
  ${CMAKE_CURRENT_SOURCE_DIR}/CalculatorTest.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ControllerTest.cpp
  PARENT_SCOPE
)