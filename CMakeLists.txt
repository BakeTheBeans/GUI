cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project("Draw")

#enable_testing()


if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(warnings "-Wall -Wextra -Werror")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(warnings "/W4 /WX /EHsc")
endif()
if (NOT CONFIGURED_ONCE)
    set(CMAKE_CXX_FLAGS "${warnings}"
        CACHE STRING "Flags used by the compiler during all build types." FORCE)
    set(CMAKE_C_FLAGS   "${warnings}"
        CACHE STRING "Flags used by the compiler during all build types." FORCE)
endif()

set(CMAKE_CXX_FLAGS "-g -std=c++0x")

set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for libraries")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(CMarkup)

add_executable(ButtonTest Utility.cpp buttonicons.cpp buttontypes.cpp  Properties.cpp  button.cpp unittest.cpp Test.cpp)
target_link_libraries(ButtonTest Markup sfml-system sfml-window sfml-graphics)

#add_test(toDoTest toDo)


set(CONFIGURED_ONCE TRUE CACHE INTERNAL
    "A flag showing that CMake has configured at least once.")