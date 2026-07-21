cmake_minimum_required(VERSION 3.20)
project(
    ArenaShooter
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

add_executable(${CMAKE_PROJECT_NAME}
    "src/main.cpp"
    "src/application.cpp"
    "src/game.cpp"

    "src/gameplay/camera.cpp"
    "src/gameplay/player.cpp"

    "src/graphics/mesh.cpp"
    "src/graphics/shader.cpp"

    "src/physics/collision.cpp"

    "src/platform/error_handling.cpp"
    "src/platform/system_info.cpp"
    "src/platform/window.cpp"

    "src/external/gl.c"
    "src/external/stb_image.cpp"
    "src/external/tinyfiledialogs.c"
)

target_include_directories(${CMAKE_PROJECT_NAME}
    PRIVATE
        "include/"
        "external/"
)

if(MINGW)
    target_link_options(${CMAKE_PROJECT_NAME}
        PRIVATE
            -static
            -static-libgcc
            -static-libstdc++
    )
endif()

target_link_libraries(${CMAKE_PROJECT_NAME}
    PRIVATE
        OpenGL::GL
        glfw
        glm::glm
)
