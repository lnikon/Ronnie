#pragma once

#include <string>

enum class CommandType {
  Unkown = 0,

  MoveCameraCommand,
  KeyPressCommand,

  CommandType_EnumSize
};

std::string ToString(const CommandType cmd);
