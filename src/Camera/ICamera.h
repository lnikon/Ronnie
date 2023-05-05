#pragma once

#include <memory>

class ICommand;

class ICamera {
public:
  virtual void Update(std::shared_ptr<ICommand> pCommand) = 0;
};
