#pragma once
#include <array>
#include <iostream>

struct CommandResult {
  std::string output;
  int exitstatus;
};

class Command {
public:
  /**
   * Execute system command and get STDOUT result.
   * Like system() but gives back exit status and stdout.
   * @param command system command to execute
   * @return CommandResult containing STDOUT (not stderr) output & exitstatus
   * of command. Empty if command failed (or has no output). If you want stderr,
   * use shell redirection (2&>1).
   */
  static CommandResult exec(const std::string &command) {
    int exitcode = 255;
    std::array<char, 1048576> buffer{};
    std::string result;

    FILE *pipe = popen(command.c_str(), "r");
    if (pipe == nullptr) {
      throw std::runtime_error("popen() failed!");
    }
    try {
      std::size_t bytesread;
      while ((bytesread = fread(buffer.data(), sizeof(buffer.at(0)),
                                sizeof(buffer), pipe)) != 0) {
        result += std::string(buffer.data(), bytesread);
      }
    } catch (...) {
      pclose(pipe);
      throw;
    }
    exitcode = WEXITSTATUS(pclose(pipe));
    return CommandResult{result, exitcode};
  }
};