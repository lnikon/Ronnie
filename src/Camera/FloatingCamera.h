#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <memory>

#include "../Window.h"
#include "Commands/IDispatcher.h"
#include "ICamera.h"

class ShaderProgramm;

class FloatingCamera : public ICamera, public IDispatcher, public std::enable_shared_from_this<FloatingCamera> {
public:
  FloatingCamera(std::shared_ptr<Window> pWindow,
                 std::shared_ptr<ShaderProgramm> pShaderProgramm);

  void Update(std::shared_ptr<ICommand> pCommand) override;

  bool CanDispatch(const CommandType cmd) const override;
  void Dispatch(std::shared_ptr<ICommand> pCommand) override;
  std::vector<CommandType> SupportedCommands() const override;

private:
  void dispatchInternal(std::shared_ptr<ICommand> pCommand);

private:
  std::shared_ptr<Window> m_pWindow{nullptr};
  std::shared_ptr<ShaderProgramm> m_pShaderProgramm{nullptr};

  float m_deltaTime{0.0f};
  float m_lastFrame{0.0f};

  glm::vec3 m_cameraPos{glm::vec3(0.0f, 0.0f, 3.0f)};
  glm::vec3 m_cameraFront{glm::vec3(0.0f, 0.0f, -1.0f)};
  glm::vec3 m_cameraUp{glm::vec3(0.0f, 1.0f, 0.0f)};

  glm::mat4 m_projection{glm::perspective(
      glm::radians(45.0f),
      static_cast<float>(m_pWindow->GetWidth() / m_pWindow->GetHeight()), 0.1f, 100.0f)};
  glm::mat4 m_model = glm::mat4(1.0f);
  glm::mat4 m_view{
      glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp)};
};
