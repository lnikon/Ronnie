#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <iostream>

#include "InputHandler.h"
#include "Window.h"
#include "Commands/KeyPressCommand.h"

InputHandler::InputHandler()
{
}

InputHandler::~InputHandler()
{
}

std::shared_ptr<ICommand> InputHandler::HandleInput(std::shared_ptr<Window> pWindow) const
{
	if (glfwGetKey(pWindow->GetGLFWWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		// TODO: Use command factory/builder instead
		return std::make_shared<KeyPressCommand>(KeyType::Escape);
	} else if (glfwGetKey(pWindow->GetGLFWWindow(), GLFW_KEY_W) == GLFW_PRESS) {
		return std::make_shared<KeyPressCommand>(KeyType::W);
	} else if (glfwGetKey(pWindow->GetGLFWWindow(), GLFW_KEY_A) == GLFW_PRESS) {
		return std::make_shared<KeyPressCommand>(KeyType::A);
	} else if (glfwGetKey(pWindow->GetGLFWWindow(), GLFW_KEY_S) == GLFW_PRESS) {
		return std::make_shared<KeyPressCommand>(KeyType::S);
	} else if (glfwGetKey(pWindow->GetGLFWWindow(), GLFW_KEY_D) == GLFW_PRESS) {
		return std::make_shared<KeyPressCommand>(KeyType::D);
	}

	return nullptr;
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
