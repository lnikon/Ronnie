#include "CameraDirection.h"

std::string ToString(const CameraDirection direction) {
  switch (direction) {
  case CameraDirection::Up:
    return "Up";
  case CameraDirection::Left:
    return "Left";
  case CameraDirection::Down:
    return "Down";
  case CameraDirection::Right:
    return "Right";
  case CameraDirection::Forward:
    return "Forward";
  case CameraDirection::Backward:
    return "Backward";
  default:
    return "";
  }
}
