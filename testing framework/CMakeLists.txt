cmake_minimum_required(VERSION 3.22)
project(TestingFramework CXX)

include(SourceList.cmake)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

find_package(Vulkan REQUIRED)

set(Includes
        ${PROJECT_SOURCE_DIR}/src
        ${Vulkan_INCLUDE_DIR}
        ${DEV_LIBS}/glfw/include
        ${CMAKE_SOURCE_DIR}/engine/src
        ${DEV_LIBS}/spdlog/include)

set(Libraries ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/engine.lib)

target_include_directories(${PROJECT_NAME} PRIVATE ${Includes})
target_link_libraries(${PROJECT_NAME} ${Libraries})