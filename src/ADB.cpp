#include "ADB.hpp"

bool ADB::is_installed() {
  CommandResult result = Command::exec("which adb");
  return result.exitstatus == 0;
}

bool ADB::disable_package(const std::string& pkg_name) {
  // CommandResult result = Command::exec("adb shell pm disable-user " + pkg_name);
  // return result.exitstatus == 0;

  return true;
}