#include "CommandTypes.h"

std::string ToString(const CommandType cmd) {
  switch (cmd) {
  case CommandType::Unkown:
    return "Unkown";
  case CommandType::MoveCameraCommand:
    return "MoveCameraCommand";
  case CommandType::CommandType_EnumSize:
    return "CommandType_EnumSize";
  default:
    return "";
  }
}
