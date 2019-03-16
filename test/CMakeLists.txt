set(PROJECT_TEST_NAME ${PROJECT_NAME}_test)

set(TEST_SOURCE_DIR ${CMAKE_SOURCE_DIR}/test/src/)
file(GLOB TEST_SOURCES ${TEST_SOURCE_DIR}/*.cpp)

find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

add_executable(${PROJECT_TEST_NAME} ${TEST_SOURCES})

target_link_libraries(${PROJECT_TEST_NAME}
    ${PROJECT_NAME}
    ${GTEST_BOTH_LIBRARIES}
    )

include_directories("${PROJECT_BINARY_DIR}")
