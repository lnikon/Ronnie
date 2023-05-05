#pragma once

#include <memory>

#include "Camera/FloatingCamera.h"
#include "ICommand.h"
#include "../Camera/CameraDirection.h"

class ICamera;

class MoveCameraCommand final: public ICommand {
public:
	MoveCameraCommand(const CameraDirection direction, std::shared_ptr<ICamera> pCamera);

	MoveCameraCommand() = delete;
	MoveCameraCommand(const MoveCameraCommand&) = default;
	MoveCameraCommand(MoveCameraCommand&&) noexcept = delete;
	~MoveCameraCommand() = default;

	void Execute() override;
	CommandType Type() const override;
	CameraDirection GetDirection() const;

private:
	const CameraDirection m_direction;
	std::shared_ptr<ICamera> m_pCamera{nullptr};
};
