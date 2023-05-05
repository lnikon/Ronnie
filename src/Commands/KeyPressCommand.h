#pragma once

#include <memory>

#include "ICommand.h"
#include "KeyType.h"
#include "../Camera/CameraDirection.h"

CameraDirection KeyTypeToCameraDirection(const KeyType);

class ICamera;

class KeyPressCommand final: public ICommand {
public:
	KeyPressCommand(const KeyType keyType);

	KeyPressCommand() = delete;
	KeyPressCommand(const KeyPressCommand&) = default;
	KeyPressCommand(KeyPressCommand&&) noexcept = default;
	KeyPressCommand& operator=(const KeyPressCommand&) = default;
	KeyPressCommand& operator=(KeyPressCommand&&) noexcept = default;
	~KeyPressCommand() = default;

	void Execute() override;
	CommandType Type() const override;

	KeyType GetKeyType() const;

private:
	const KeyType m_keyType;
};
