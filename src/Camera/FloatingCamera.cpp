#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>

#include "../Shader.h"
#include "Commands/CommandTypes.h"
#include "Commands/ICommand.h"
#include "Commands/KeyPressCommand.h"
#include "Commands/MoveCameraCommand.h"
#include "FloatingCamera.h"

// TODO: Use CameraConfig to map KeyType to MoveDirection

CameraDirection KeyTypeToCameraDirection(const KeyType keyType) {
  switch (keyType) {
  case KeyType::W:
    return CameraDirection::Forward;
  case KeyType::A:
    return CameraDirection::Left;
  case KeyType::S:
    return CameraDirection::Backward;
  case KeyType::D:
    return CameraDirection::Right;
  default:
    return CameraDirection::Unkown;
  }
}

FloatingCamera::FloatingCamera(std::shared_ptr<Window> pWindow,
                               std::shared_ptr<ShaderProgramm> pShaderProgramm)
    : m_pWindow{pWindow}, m_pShaderProgramm{pShaderProgramm} {
  m_pShaderProgramm->SetMat4f("projection", m_projection);
}

void FloatingCamera::Update(std::shared_ptr<ICommand> pCommand) {
  //float currentFrame = glfwGetTime();
  //m_deltaTime = currentFrame - m_lastFrame;
  //m_lastFrame = currentFrame;

  if (!pCommand) {
    std::cerr << "(FloatingCamera::Update): null pcommand" << std::endl;
    return;
  }

  if (pCommand->Type() != CommandType::MoveCameraCommand) {
    std::cerr << "(FloatingCamera::Update): Cant handle "
              << ToString(pCommand->Type()) << std::endl;
    return;
  }

  auto pMoveCommand{std::dynamic_pointer_cast<MoveCameraCommand>(pCommand)};
  const float cameraSpeed = 2.5f * m_deltaTime;
  std::cout << "*** [VAGAG]: cameraSpeed=" << cameraSpeed << std::endl;
  switch (pMoveCommand->GetDirection()) {
  case CameraDirection::Forward: {
    std::cout << "Forward" << std::endl;
    m_cameraPos += cameraSpeed * m_cameraFront;
    break;
  }
  case CameraDirection::Left: {
    std::cout << "Left" << std::endl;
    m_cameraPos -=
        glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * cameraSpeed;
    break;
  }
  case CameraDirection::Backward: {
    std::cout << "Backward" << std::endl;
    m_cameraPos -= cameraSpeed * m_cameraFront;
    break;
  }
  case CameraDirection::Right: {
    std::cout << "Right" << std::endl;
    m_cameraPos +=
        glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * cameraSpeed;
    break;
  }
  default: {
    std::cerr << "(FloatingCamera::Update): cant handle direction "
              << ToString(pMoveCommand->GetDirection()) << std::endl;
    assert(false);
  }
  }

  // std::cout << m_cameraPos[0] << " " << m_cameraPos[1] << " " <<
  // m_cameraPos[2]
  //           << std::endl;
  //
  m_view = glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);
  for (int rowIdx = 0; rowIdx < m_view.length(); rowIdx++) {
    for (int colIdx = 0; colIdx < m_view[rowIdx].length(); colIdx++) {
      std::cout << m_view[rowIdx][colIdx] << ' ';
    }
    std::cout << std::endl;
  }
  m_pShaderProgramm->SetMat4f("view", m_view);

  std::cout << "Here" << std::endl;
}

bool FloatingCamera::CanDispatch(const CommandType cmd) const {
  const auto cmds{SupportedCommands()};
  return std::find(std::begin(cmds), std::end(cmds), cmd) != std::end(cmds);
}

void FloatingCamera::Dispatch(std::shared_ptr<ICommand> pCommand) {
  float currentFrame = glfwGetTime();
  m_deltaTime = currentFrame - m_lastFrame;
  m_lastFrame = currentFrame;

  if (!pCommand) {
    std::cerr << "(FloatingCamera::Dispatch): null pcommand" << std::endl;
    return;
  }

  if (!CanDispatch(pCommand->Type())) {
    std::cerr << "(FloatingCamera::Dispatch): Unable to dispatch the command "
              << ToString(pCommand->Type()) << std::endl;
    return;
  }

  std::shared_ptr<MoveCameraCommand> pMoveCameraCmd{nullptr};
  if (pCommand->Type() == CommandType::KeyPressCommand) {
    std::cout << "(FloatingCamera::Dispatch): Handling KeyPressCommand" << std::endl;
  
    auto keyPressCmd{std::dynamic_pointer_cast<KeyPressCommand>(pCommand)};
    pMoveCameraCmd = std::make_shared<MoveCameraCommand>(KeyTypeToCameraDirection(keyPressCmd->GetKeyType()), shared_from_this());
  } else if (pCommand->Type() == CommandType::MoveCameraCommand) {
    std::cout << "(FloatingCamera::Dispatch): Handling MoveCameraCommand"
              << std::endl;
    pMoveCameraCmd = std::dynamic_pointer_cast<MoveCameraCommand>(pCommand);
  } else {
    std::cerr << "(FloatingCamera::Dispatch): unkown command type "
              << ToString(pCommand->Type()) << " to dispatch" << std::endl;
    assert(false);
  }

  pMoveCameraCmd->Execute();
}

std::vector<CommandType> FloatingCamera::SupportedCommands() const {
  return {CommandType::MoveCameraCommand, CommandType::KeyPressCommand};
}
