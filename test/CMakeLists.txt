set(PROJECT_TEST_NAME ${PROJECT_NAME}_test)

set(TEST_SOURCE_DIR ${CMAKE_SOURCE_DIR}/test/src/)
file(GLOB TEST_SOURCES ${TEST_SOURCE_DIR}/*.cpp)

message(STATUS ${GTEST_LIBS_DIR})

include_directories(${GTEST_INCLUDE_DIRS})

add_executable(${PROJECT_TEST_NAME} ${TEST_SOURCES})

add_dependencies(${PROJECT_TEST_NAME} googletest)

target_link_libraries(${PROJECT_TEST_NAME}
    ${PROJECT_NAME}
    ${GTEST_LIBS_DIR}/libgtest.a
    ${GTEST_LIBS_DIR}/libgtest_main.a
    pthread
    )

include_directories("${PROJECT_BINARY_DIR}")
