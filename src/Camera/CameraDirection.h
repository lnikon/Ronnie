#pragma once

#include <string>

enum CameraDirection {
	Unkown = 0,

	Up,
	Left,
	Down,
	Right,
	Forward,
	Backward
};

std::string ToString(const CameraDirection);

