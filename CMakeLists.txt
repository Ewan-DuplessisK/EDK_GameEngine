cmake_minimum_required(VERSION 3.28)
project(EDK_GameEngine)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} WIN32 main.cpp
        Vectors.h
        Vectors.cpp
        Matrices.cpp
        Matrices.h
        MessageBus.cpp
        MessageBus.h
        ISystem.h
        ConsoleSystem.cpp
        ConsoleSystem.h
        imgui_impl_opengl3.h
        imgui_impl_opengl3.cpp
        Map.cpp
        Map.h
        EventsStructs.h
        EventsStructs.h
        RendererOGL.cpp
        RendererOGL.h
        Shader.h
        Shader.cpp
        Assets.h
        Assets.cpp
        Texture.h
        Mesh.h
        Mesh.cpp
        Texture.cpp
        VertexArray.h
        VertexArray.cpp
        Sprite.cpp
        Sprite.h
        imgui_impl_sdl2.h
        imgui_impl_sdl2.cpp)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(GLEW CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(RapidJSON CONFIG REQUIRED)
find_package(tinyobjloader CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME}  SDL2::SDL2 SDL2_image::SDL2_image GLEW::glew imgui::imgui rapidjson tinyobjloader::tinyobjloader)