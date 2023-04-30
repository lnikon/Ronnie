﻿// Ronnie.cpp : Defines the entry point for the application.
//

#include <glad/glad.h>
#include <imgui.h>
#include "ImGui/Bindings/imgui_impl_glfw.h"
#include "ImGui/Bindings/imgui_impl_opengl3.h"
#include <stdio.h>
#include <GLFW/glfw3.h>

#define GLFW_EXPOSE_NATIVE_EGL

#include "Ronnie.h"
#include "Window.h"
#include "InputHandler.h"
#include "ArrayBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

using namespace std;

int main()
{
	auto window{ std::make_shared<Window>(600, 800, "Ronnie") };
	auto inputHandler = InputHandler{};

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    ImGui_ImplGlfw_InitForOpenGL(window->GetGLFWWindow(), true);
    ImGui_ImplOpenGL3_Init(glsl_version);

	std::vector<float> vertices = {
		// Positions		// Colors			// Texture coords
		 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,	1.0f, 1.0f,	// bottom right
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,	1.0f, 0.0f,	// bottom left
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,	0.0f, 0.0f,	// top
		-0.5f, 0.5f, 0.0f,  0.0f, 0.0f, 1.0f,	0.0f, 1.0f,	// 
	};

	std::vector<unsigned int> indices = {
		0, 1, 3,
		1, 2, 3
	};

	Texture texture1{ "C:/Users/nikon/source/repos/Ronnie/resources/textures/bricks2.jpg" };
	Texture texture2{"C:/Users/nikon/source/repos/Ronnie/resources/textures/container.jpg"};

	VertexArray vao1;
	vao1.Bind();

	Buffer<float> vbo1{ BufferType::ARRAY_BUFFER, vertices };
	Buffer<unsigned int> ebo1{ BufferType::ELEMENT_BUFFER, indices };

	vao1.AddAttribute(ValueType::FLOAT, 3);
	vao1.AddAttribute(ValueType::FLOAT, 3);
	vao1.AddAttribute(ValueType::FLOAT, 2);
	vao1.EnableAttribute();

	ShaderProgramm shaderProgramm;
	shaderProgramm.AddShader(std::move(Shader{ "C:/Users/nikon/source/repos/Ronnie/resources/vertex_shader.glsl", ShaderType::VERTEX }));
	shaderProgramm.AddShader(std::move(Shader{ "C:/Users/nikon/source/repos/Ronnie/resources/fragment_shader.glsl", ShaderType::FRAGMENT }));
	shaderProgramm.Create();
	shaderProgramm.Use();

	while (!window->ShouldClose()) {
		inputHandler.HandleInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

        // Start new ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

		shaderProgramm.Use();

		texture1.Bind();
		vao1.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        ImGui::Begin("Demo window");
        ImGui::Button("Hello");
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		window->Sync();
	}

	return 0;
}
