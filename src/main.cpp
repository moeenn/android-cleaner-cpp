#include "ADB.hpp"
#include "ArgsParser.hpp"
#include "PackageFile.hpp"
#include <fstream>
#include <iostream>
#include <string>

void report(const char *message) {
  std::cerr << "[error] " << message << '\n';
  std::exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
  ArgsParser parser{argc, argv};

  auto path = parser.String("-file");
  if (!path) {
    std::cout << "usage: android-cleaner -file /path/to/packages.txt\n";
    return 1;
  }

  bool isInstalled = ADB::is_installed();
  if (!isInstalled) {
    report("adb not installed");
  }

  std::ifstream file{*path};
  if (!file) {
    report("failed to open file");
  }

  PackageFile::process_file(file, [](const std::string &line) {
    /* line starts with the matching pattern */
    if (line.rfind("package:", 0) == 0) {
      std::string pkg_name = PackageFile::extract_package_name(line);
      if (pkg_name.empty()) {
        return;
      }

      bool result = ADB::disable_package(pkg_name);
      std::cout << (result ? "[x] " : "[ ] ") << pkg_name << '\n';
    }
  });

  file.close();
}
