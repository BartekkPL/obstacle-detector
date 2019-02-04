#-------------------------------------------------------------------------------
# PROJECT SETTINGS
#-------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.5)
project(SelfLocalizator VERSION 0.1.0)

enable_language(C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -std=c++17")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g")

message(STATUS "Start of execution CMake for Self Localizator library in"
                " version ${PROJECT_VERSION}"
                )

set(EASYLOGGING_CONFIG_FILE_PATH
    "${CMAKE_SOURCE_DIR}/easylogging++.config"
    )

#-------------------------------------------------------------------------------
# LIBRARY SOURCES SETTING
#-------------------------------------------------------------------------------
set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB PROJECT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${PROJECT_INCLUDE_DIR}
    )

#-------------------------------------------------------------------------------
# EXTERNAL MODULES
#-------------------------------------------------------------------------------
find_package(OpenCV 4.0.0 REQUIRED)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

set (EASYLOGGING_CONFIG_FILE_PATH
    "${CMAKE_SOURCE_DIR}/easylogging++.config"
    )

set(EXT_PROJECTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/modules)

#-------------------------------------------------------------------------------
# TESTS
#-------------------------------------------------------------------------------
add_subdirectory(${EXT_PROJECTS_DIR}/googletest)

set(GOOGLETEST_ROOT ${EXT_PROJECTS_DIR}/googletest
    CACHE STRING "Google Test source root")

message(STATUS "GOOGLETEST_ROOT set to ${GOOGLETEST_ROOT}")

add_subdirectory(test)

#-------------------------------------------------------------------------------
# CONFIGURATION FILE
#-------------------------------------------------------------------------------
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.hpp.in
    ${PROJECT_BINARY_DIR}/config.hpp
    )

include_directories("${PROJECT_BINARY_DIR}")

#-------------------------------------------------------------------------------
# MY MAIN TEST EXECUTABLE
#-------------------------------------------------------------------------------
add_executable(main ${PROJECT_SOURCE_DIR}/main.cpp)
target_link_libraries(main
    ${OpenCV_LIBS}
    ${PROJECT_NAME}
    )
