#pragma once

#include <cstddef>
#include <string>
#include <memory>

void defaultFramebufferSizeCallback(GLFWwindow* window, int width, int height);

struct GLFWwidowUniqueDeleter {
	void operator()(GLFWwindow* window);
};

class Window {
public:
	Window(const std::size_t width, const std::size_t height, const std::string& title, GLFWframebuffersizefun framebufferSizeCallback = defaultFramebufferSizeCallback);
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	Window(Window&&) = delete;
	Window& operator=(Window&&) = delete;
	~Window();

	void SetFramebufferSizeCallback(GLFWframebuffersizefun framebufferSizeCallback);
	
	void MakeCurrentContext();

	bool ShouldClose() const;
	void Close();

	void Sync() const;

	std::size_t GetWidth() const;
	std::size_t GetHeight() const;
	std::string GetTitle() const;
	GLFWwindow* GetGLFWWindow() const;

private:
	const std::size_t m_width;
	const std::size_t m_height;
	const std::string m_title;

	std::unique_ptr<GLFWwindow, GLFWwidowUniqueDeleter> m_pWindow;
	GLFWframebuffersizefun m_framebufferSizeCallback;
};