#include <iostream>

#include "Camera/ICamera.h"
#include "MoveCameraCommand.h"

MoveCameraCommand::MoveCameraCommand(const CameraDirection direction,
                                     std::shared_ptr<ICamera> pCamera)
    : m_direction{direction}, m_pCamera{pCamera} {}

void MoveCameraCommand::Execute() {
  std::cout << "my direction is: " << ToString(m_direction) << std::endl;
  m_pCamera->Update(shared_from_this());
  // m_pCamera->Update(std::make_shared<MoveCameraCommand>(CameraDirection::Backward,
  // m_pCamera));
}

CommandType MoveCameraCommand::Type() const {
  return CommandType::MoveCameraCommand;
}

CameraDirection MoveCameraCommand::GetDirection() const { return m_direction; }
