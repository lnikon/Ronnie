cmake_minimum_required (VERSION 3.22)
project(LearnOpenGL)

# Language specific configs
set(CMAKE_CXX_STANDARD 20) # this does nothing for MSVC, use target_compile_options below
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# Find required packages
find_package(imgui REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glad REQUIRED)

# Bindings for ImGui
set(
    IMGUI_BINDINGS_SOURCES
    ${CMAKE_SOURCE_DIR}/src/ImGui/Bindings/imgui_impl_glfw.h
    ${CMAKE_SOURCE_DIR}/src/ImGui/Bindings/imgui_impl_glfw.cpp
    ${CMAKE_SOURCE_DIR}/src/ImGui/Bindings/imgui_impl_opengl3.h
    ${CMAKE_SOURCE_DIR}/src/ImGui/Bindings/imgui_impl_opengl3.cpp
    ${CMAKE_SOURCE_DIR}/src/ImGui/Bindings/imgui_impl_opengl3_loader.h
    )

add_library(IMGUI_BINDINGS_LIB STATIC ${IMGUI_BINDINGS_SOURCES})
target_link_libraries(
    IMGUI_BINDINGS_LIB
    imgui::imgui
    glfw
    glad::glad
    )

# stb_image as a lib
set(
    STB_IMAGE_SOURCES
    ${CMAKE_SOURCE_DIR}/src/stb_image/stb_image.cpp
    ${CMAKE_SOURCE_DIR}/src/stb_image/stb_image.h
    )

add_library(
    STB_IMAGE_LIB
    STATIC
    ${STB_IMAGE_SOURCES}
)

# Main executable of the engine: Ronnie
set(
    RONNIE_SOURCES
    "${CMAKE_SOURCE_DIR}/src/ArrayBuffer.cpp"
    "${CMAKE_SOURCE_DIR}/src/ArrayBuffer.h"
    "${CMAKE_SOURCE_DIR}/src/ElementArray.cpp"
    "${CMAKE_SOURCE_DIR}/src/ElementArray.h"
    "${CMAKE_SOURCE_DIR}/src/InputHandler.cpp"
    "${CMAKE_SOURCE_DIR}/src/InputHandler.h"
    "${CMAKE_SOURCE_DIR}/src/Shader.cpp"
    "${CMAKE_SOURCE_DIR}/src/Shader.h"
    "${CMAKE_SOURCE_DIR}/src/Texture.cpp"
    "${CMAKE_SOURCE_DIR}/src/Texture.h"
    "${CMAKE_SOURCE_DIR}/src/VertexArray.cpp"
    "${CMAKE_SOURCE_DIR}/src/VertexArray.h"
    "${CMAKE_SOURCE_DIR}/src/Window.cpp"
    "${CMAKE_SOURCE_DIR}/src/Window.h"
    "${CMAKE_SOURCE_DIR}/src/Ronnie.h"
    "${CMAKE_SOURCE_DIR}/src/Ronnie.cpp"
    )

add_executable(
    Ronnie
    ${RONNIE_SOURCES}
    )

target_include_directories(
    Ronnie
    PUBLIC
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/stb_image
)

target_link_libraries(
    Ronnie
    imgui::imgui
    glfw
    glad::glad
    IMGUI_BINDINGS_LIB
    STB_IMAGE_LIB
    )

# Copy resources into build directory

add_custom_command(
	TARGET
	Ronnie	
	POST_BUILD
	COMMAND
		${CMAKE_COMMAND} -E copy_directory
			${CMAKE_SOURCE_DIR}/resources
			${PROJECT_BINARY_DIR}/resources
	)

