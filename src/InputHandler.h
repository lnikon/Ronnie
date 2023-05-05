#pragma once

#include <memory>

class Window;
class ICommand;

class InputHandler {
public:
	InputHandler();
	InputHandler(const InputHandler&) = delete;
	InputHandler& operator=(const InputHandler&) = delete;
	InputHandler(InputHandler&&) = delete;
	InputHandler& operator=(InputHandler&&) = delete;
	~InputHandler();

	std::shared_ptr<ICommand> HandleInput(std::shared_ptr<Window> pWindow) const;

	// TODO: Another implementation for Camera
	//void HandleInput(std::shared_ptr<Camera> pWindow) const;

private:
	void handleInputInternal(std::shared_ptr<Window> pWindow, const int32_t glfwKey) const;
};
