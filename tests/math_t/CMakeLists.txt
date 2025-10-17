set(TEST_NAME gtest_math_t)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE SOURCES ${SRC_DIR}/*.cpp ${CMAKE_SOURCE_DIR}/src/math/*cpp)

enable_testing()

add_executable(${TEST_NAME} ${SOURCES})

target_include_directories(${TEST_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

target_include_directories(${TEST_NAME} PRIVATE ${SRC_DIR})

# Linka com GoogleTest via FetchContent
target_link_libraries(${TEST_NAME}
    gtest
    gtest_main
    pthread
)

add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
