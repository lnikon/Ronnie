#pragma once

#include <memory>

class ICommand;

class ICamera: public std::enable_shared_from_this<ICamera> {
public:
  virtual void Update(std::shared_ptr<ICommand> pCommand) = 0;
};
