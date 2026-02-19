cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 23)

set(MODULE_NAME RingBuffer)

set(USED_LIBRARIES GeLib AbstractionLayer)

project(
  ${MODULE_NAME}
  DESCRIPTION
    "Creates library of this module. If top level project is this CMake file then it adds and includes everything for building unit test executable, otherwise it creates mock library of this module."
  LANGUAGES C CXX ASM)

# If top level project is this CMake file then it adds and includes everything
# for building unit test executable.
if("${CMAKE_PROJECT_NAME}" STREQUAL "${MODULE_NAME}")
  include(${PROJECT_SOURCE_DIR}/cmake/compiler-options.cmake)
  
  # Add test directory to build unit test executable and all mocks of used
  # libraries.
  add_subdirectory(test)

  # link gcov library required for code coverage
  add_compile_options("-lgcov")
  link_libraries("-lgcov")  
elseif("${PROJECT_TYPE}" STREQUAL "EXECUTABLE")

else()
  # Create a mock library of this module.
  set(MOCK_NAME ${MODULE_NAME}Mock)
  file(
    GLOB_RECURSE mock_files
    RELATIVE ${PROJECT_SOURCE_DIR}
    "inc/${MODULE_NAME}/*.h" "mock/*.h" "mock/*.cpp")
  add_library(${MOCK_NAME} OBJECT ${mock_files})
  target_include_directories(${MOCK_NAME} PRIVATE inc inc/${MODULE_NAME} src)

  # Add include directories of all used libraries.
  foreach(LIBRARY ${USED_LIBRARIES})
    target_include_directories(${MOCK_NAME} PRIVATE ../${LIBRARY}/inc)
  endforeach()

  # Add mock interface library which is used by other modules to include this
  # module for unit tests.
  set(MOCK_INTERFACE_NAME I${MOCK_NAME})
  project(${MOCK_INTERFACE_NAME})
  add_library(${MOCK_INTERFACE_NAME} INTERFACE)
  target_include_directories(${MOCK_INTERFACE_NAME} INTERFACE inc mock)
  target_link_libraries(
    ${MOCK_INTERFACE_NAME} INTERFACE ${MOCK_NAME} 
                                     $<TARGET_OBJECTS:${MOCK_NAME}>)
endif()

if(NOT DEFINED MOCK_NAME)
  # Create library of this module.
  file(
    GLOB_RECURSE src_files
    RELATIVE ${PROJECT_SOURCE_DIR}
    "inc/${MODULE_NAME}/*.h" "src/*.hpp" "src/*.h" "src/*.cpp" "src/*.c")
  add_library(${MODULE_NAME} OBJECT ${src_files})
  target_include_directories(${MODULE_NAME} PRIVATE inc inc/${MODULE_NAME} src)

  # Link all libraries which are needed for this module.
  foreach(LIBRARY ${USED_LIBRARIES})
    if("${PROJECT_TYPE}" STREQUAL "EXECUTABLE")
      target_link_libraries(${MODULE_NAME} PUBLIC I${LIBRARY})
    else()
      target_link_libraries(${MODULE_NAME} PUBLIC I${LIBRARY}Mock)
    endif()
  endforeach()

  # Add interface library which is used by other modules to include this module.
  set(MODULE_INTERFACE_NAME I${MODULE_NAME})
  project(${MODULE_INTERFACE_NAME})
  add_library(${MODULE_INTERFACE_NAME} INTERFACE)
  target_include_directories(${MODULE_INTERFACE_NAME} INTERFACE inc)
  target_link_libraries(${MODULE_INTERFACE_NAME}
                        INTERFACE ${MODULE_NAME} $<TARGET_OBJECTS:${MODULE_NAME}>)
endif()