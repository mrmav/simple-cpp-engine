cmake_minimum_required(VERSION 3.22..3.26)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_PREFIX_PATH "external/easy_profiler/lib/cmake/easy_profiler")

project(simple-cpp-engine)

# options
option(BUILD_TESTS "Build the sample tests that show case the engine usage." ON)

find_package(easy_profiler REQUIRED)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCE})

#specifies that we also have work to do on this directory
add_subdirectory(src)
add_subdirectory(src/OpenGL)
add_subdirectory(src/Render)
add_subdirectory(src/Input)
add_subdirectory(src/Utils)
add_subdirectory(src/Systems)

# build librarires
add_subdirectory(external)
add_subdirectory(external/glfw)
add_subdirectory(external/glm)

if(BUILD_TESTS)
    add_subdirectory(engine-test)
endif(BUILD_TESTS)

target_include_directories(${PROJECT_NAME}
    PUBLIC external/glfw/include
    PUBLIC external/glm
    PUBLIC external/imgui
    PUBLIC external/json
    PUBLIC external/easy_profiler/include
    PUBLIC external
    PUBLIC src
)

target_link_directories(${PROJECT_NAME} PRIVATE external/glfw/src PRIVATE external/imgui)

target_link_libraries(${PROJECT_NAME} glfw imgui easy_profiler)
