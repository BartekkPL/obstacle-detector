find_package(GTest REQUIRED)

set(TEST_SOURCE_DIR ${CMAKE_SOURCE_DIR}/test/src/)
file(GLOB TEST_SOURCES ${TEST_SOURCE_DIR}/*.cpp)

add_executable(${PROJECT_NAME}_test ${TEST_SOURCES})

target_link_libraries(${PROJECT_NAME}_test
    ${PROJECT_NAME}
    GTest::GTest
    GTest::Main
    )

include_directories("${PROJECT_BINARY_DIR}")
