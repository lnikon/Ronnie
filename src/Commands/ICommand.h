#pragma once

#include <memory>
#include <utility>

#include "CommandTypes.h"

class ICommand: public std::enable_shared_from_this<ICommand> {

public:
	virtual void Execute() = 0;
	virtual CommandType Type() const = 0;
};
