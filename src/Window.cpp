#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Window.h"

void GLFWwidowUniqueDeleter::operator()(GLFWwindow* window) {
	glfwDestroyWindow(window);
}

Window::Window(const std::size_t width, const std::size_t height, const std::string& title, GLFWframebuffersizefun framebufferSizeCallback)
	: m_width(width), m_height(height), m_title(title), m_framebufferSizeCallback(framebufferSizeCallback)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_pWindow.reset(glfwCreateWindow(GetWidth(), GetHeight(), GetTitle().data(), NULL, NULL));
	if (m_pWindow == nullptr) {
		std::cerr << "Failed to create a GLFW windows" << std::endl;
		glfwTerminate();
	}

	MakeCurrentContext();

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
	}
	
	glViewport(0, 0, GetWidth(), GetHeight());
	glfwSetFramebufferSizeCallback(m_pWindow.get(), m_framebufferSizeCallback);
}

Window::~Window()
{
	glfwTerminate();
}

inline void Window::SetFramebufferSizeCallback(GLFWframebuffersizefun framebufferSizeCallback) {
	m_framebufferSizeCallback = framebufferSizeCallback;
	glfwSetFramebufferSizeCallback(m_pWindow.get(), m_framebufferSizeCallback);
}

void Window::MakeCurrentContext()
{
	glfwMakeContextCurrent(m_pWindow.get());
}

bool Window::ShouldClose() const
{
	return glfwWindowShouldClose(m_pWindow.get());
}

void Window::Close()
{
	glfwSetWindowShouldClose(m_pWindow.get(), true);
}

void Window::Sync() const
{
	glfwSwapBuffers(m_pWindow.get());
	glfwPollEvents();
}

std::size_t Window::GetWidth() const
{
	return m_width;
}

std::size_t Window::GetHeight() const
{
	return m_height;
}

std::string Window::GetTitle() const
{
	return m_title;
}

GLFWwindow* Window::GetGLFWWindow() const
{
	return m_pWindow.get();
}

void defaultFramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
