cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 23)

project(
  ${CMAKE_PROJECT_NAME}Test
  DESCRIPTION
    "Creates unit test executable to run all unit tests. For this it includes Google test and mock framework and all dependent submodules."
  LANGUAGES C CXX ASM)

# Include compiler settings
include(cmake/compiler-settings.cmake)

# Include GoogleTest
add_subdirectory(testrunner)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

# Add all test files to the executable and call it UnitTestExecutable. Test
# files have to be in folder <ModuleFolder>/test/src or a subfolder.
file(
  GLOB_RECURSE module_tests
  RELATIVE ${PROJECT_SOURCE_DIR}
  "src/*.cpp")
add_executable(UnitTestExecutable ${module_tests})

# Add all submodule directories to run CMake file which builds corresponding
# submodule mock libraries.
foreach(LIBRARY ${USED_LIBRARIES})
  add_subdirectory("submodules/${LIBRARY}")
endforeach()

# Link all needed libraries to the executable
target_link_libraries(UnitTestExecutable gtest gtest_main gmock gmock_main)
target_link_libraries(UnitTestExecutable "I${CMAKE_PROJECT_NAME}")
# Link all submodule mock libraries which are used by this module
foreach(LIBRARY ${USED_LIBRARIES})
  target_link_libraries(UnitTestExecutable I${LIBRARY}Mock)
endforeach()

