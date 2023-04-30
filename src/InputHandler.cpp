#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "InputHandler.h"
#include "Window.h"

InputHandler::InputHandler()
{
}

InputHandler::~InputHandler()
{
}

void InputHandler::HandleInput(std::shared_ptr<Window> pWindow) const
{
	if (glfwGetKey(pWindow->GetGLFWWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		handleInputInternal(pWindow, GLFW_KEY_ESCAPE);
	}
}

void InputHandler::handleInputInternal(std::shared_ptr<Window> pWindow, const int32_t glfwKey) const
{
	if (glfwKey == GLFW_KEY_ESCAPE) {
		pWindow->Close();
	}
	else {
		std::cerr << "(InputHandler::handleInputInternal): Unkown key pressed. glfwKey=" << glfwKey << std::endl;
	}
}
