#include "KeyPressCommand.h"

KeyPressCommand::KeyPressCommand(const KeyType keyType) : m_keyType{keyType} {}

void KeyPressCommand::Execute() {}

CommandType KeyPressCommand::Type() const {
  return CommandType::KeyPressCommand;
}

KeyType KeyPressCommand::GetKeyType() const {
	return m_keyType;
}
