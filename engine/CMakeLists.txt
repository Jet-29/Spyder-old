cmake_minimum_required(VERSION 3.22)
project(engine CXX)

include(SourceList.cmake)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

find_package(Vulkan REQUIRED)

set(Includes
        ${PROJECT_SOURCE_DIR}/src
        ${Vulkan_INCLUDE_DIR}
        ${DEV_LIBS}/glfw/include
        ${DEV_LIBS}/spdlog/include)

set(Libraries "${Vulkan_LIBRARIES} ${DEV_LIBS}/glfw/lib/glfw3.lib ${DEV_LIBS}/shaderc/${CMAKE_BUILD_TYPE}/lib/shaderc_combined.lib")

set(CMAKE_STATIC_LINKER_FLAGS ${Libraries})

target_include_directories(${PROJECT_NAME} PRIVATE ${Includes})
target_precompile_headers(${PROJECT_NAME} PRIVATE ${PrecompiledHeaders})