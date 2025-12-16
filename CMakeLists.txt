cmake_minimum_required(VERSION 3.16)
project(cubez VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(LIBS)

include(FetchContent)

# sdl3
FetchContent_Declare(
    SDL
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG 3.2.28
)
FetchContent_MakeAvailable(SDL)
list(APPEND LIBS SDL3::SDL3)

# vulkan
find_package(Vulkan REQUIRED)
list(APPEND LIBS Vulkan::Vulkan)


add_executable(${PROJECT_NAME}
    src/main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBS})