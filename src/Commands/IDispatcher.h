#pragma once

#include <vector>
#include <memory>

#include "CommandTypes.h"

class ICommand;

class IDispatcher {
public:
  virtual bool CanDispatch(const CommandType cmd) const = 0;
  virtual void Dispatch(std::shared_ptr<ICommand> pCommand) = 0;
  virtual std::vector<CommandType> SupportedCommands() const = 0;
};
