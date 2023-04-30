// Ronnie.cpp : Defines the entry point for the application.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ImGui/Bindings/imgui_impl_glfw.h"
#include "ImGui/Bindings/imgui_impl_opengl3.h"
#include <imgui.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdio.h>

#include "Ronnie.h"
#include "ArrayBuffer.h"
#include "InputHandler.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include "Window.h"

int main() {
  auto window{std::make_shared<Window>(600, 800, "Ronnie")};
  auto inputHandler = InputHandler{};

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

  // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
  // GL ES 2.0 + GLSL 100
  const char *glsl_version = "#version 100";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
  // GL 3.2 + GLSL 150
  const char *glsl_version = "#version 150";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // Required on Mac
#else
  // GL 3.0 + GLSL 130
  const char *glsl_version = "#version 130";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+
  // only glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // 3.0+ only
#endif

  ImGui_ImplGlfw_InitForOpenGL(window->GetGLFWWindow(), true);
  ImGui_ImplOpenGL3_Init(glsl_version);

  std::vector<float> vertices = {
      // Positions		// Colors			// Texture
      // coords
      0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // bottom right
      0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom left
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // top
      -0.5f, 0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, //
  };

  std::vector<unsigned int> indices = {0, 1, 3, 1, 2, 3};

  Texture texture1{
      "./resources/textures/bricks2.jpg"};
  Texture texture2{
      "./resources/textures/container.jpg"};

  VertexArray vao1;
  vao1.Bind();

  Buffer<float> vbo1{BufferType::ARRAY_BUFFER, vertices};
  Buffer<unsigned int> ebo1{BufferType::ELEMENT_BUFFER, indices};

  vao1.AddAttribute(ValueType::FLOAT, 3);
  vao1.AddAttribute(ValueType::FLOAT, 3);
  vao1.AddAttribute(ValueType::FLOAT, 2);
  vao1.EnableAttribute();

  ShaderProgramm shaderProgramm;
  auto vertexShader { shaderProgramm.AddShader(
      std::move(Shader{"./resources/shaders/vertex_shader.glsl", ShaderType::VERTEX})) };

  auto fragmentShader { shaderProgramm.AddShader(std::move(
      Shader{"./resources/shaders/fragment_shader.glsl", ShaderType::FRAGMENT})) };

  shaderProgramm.Create();
  shaderProgramm.Use();

glm::mat4 trans = glm::mat4(1.0f);
  while (!window->ShouldClose()) {
    inputHandler.HandleInput(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Start new ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

	trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
	//trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

    shaderProgramm.Use();
	shaderProgramm.SetMat4f("transform", trans);

    texture1.Bind();
    vao1.Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    window->Sync();
  }

  return 0;
}
