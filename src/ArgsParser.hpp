#pragma once
#include <cstring>
#include <optional>
#include <iostream>

class ArgsParser {
private:
  int m_argc;
  char **m_argv;

  std::optional<const char *> read_flag(const char *flag) {
    int i;
    for (i = 0; i < m_argc; i++) {
      if (strcmp(m_argv[i], flag) == 0) {
        if ((i + 1) < m_argc) {
          return m_argv[i + 1];
        }
      }
    }

    return {};
  }

  bool read_optional_flag(const char *flag) {
    int i;
    for (i = 0; i < m_argc; i++) {
      if (strcmp(m_argv[i], flag) == 0) {
        return true;
      }
    }

    return false;
  }  

public:
  ArgsParser(int argc, char **argv) : m_argc(argc), m_argv(argv) {}

  std::optional<int> Int(const char *flag) {
    auto value = read_flag(flag);
    if (!value) {
      return {};
    }

    return std::atoi(*value);
  }

  std::optional<std::string> String(const char *flag) {
    auto value = read_flag(flag);   
    if (!value) {
      return {};
    }

    return std::string{*value};
  }

  bool Bool(const char* flag) {
    return read_optional_flag(flag);
  }
};