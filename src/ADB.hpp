#pragma once
#include <iostream>
#include "Command.hpp"

namespace ADB {
  bool is_installed();
  bool disable_package(const std::string& pkg_name);
};