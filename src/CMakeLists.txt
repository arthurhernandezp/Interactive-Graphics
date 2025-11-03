set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(DEBUG_BIN_DIRECTORY ${CMAKE_BINARY_DIR}/bin/Debug)
set(RELEASE_BIN_DIRECTORY ${CMAKE_BINARY_DIR}/bin/Release)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${DEBUG_BIN_DIRECTORY}/${PROJECT_NAME})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${RELEASE_BIN_DIRECTORY}/${PROJECT_NAME})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${DEBUG_BIN_DIRECTORY}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${RELEASE_BIN_DIRECTORY}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${DEBUG_BIN_DIRECTORY}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${RELEASE_BIN_DIRECTORY}/lib)

file(GLOB_RECURSE SOURCES ${SRC_DIR}/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${SRC_DIR})

# External dependencies includes
target_include_directories(${PROJECT_NAME} PRIVATE
    ${GLAD_ROOT_DIR}/include
    ${GLFW_ROOT_DIR}/include
    ${GLM_ROOT_DIR}/include
    ${STB_IMAGE_ROOT_DIR}
)

# External dependencies libs
target_link_libraries(${PROJECT_NAME} PRIVATE
    glad
    glfw
    glm
    stb_image
)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/shaders
            $<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders
)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/resources
            $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
)
