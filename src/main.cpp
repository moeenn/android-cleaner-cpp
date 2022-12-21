#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

/**
 *  function prototypes
 *
 */
void report(const char *message);
void process_file(std::ifstream &file,
                  std::function<void(const std::string &)>);
std::string extract_package_name(const std::string &line);

int main() {
  const char *path = "./packages.txt";
  std::ifstream file{path};
  if (!file) {
    report("failed to open file");
  }

  process_file(file, [](const std::string &line) {
    /* line starts with the matching pattern */
    if (line.rfind("package:", 0) == 0) {
      std::string pkg_name = extract_package_name(line);
      if (pkg_name.empty()) {
        return;
      }

      std::cout << pkg_name << '\n';
    }
  });

  file.close();
}

/**
 *  write to stderr and exit with failure status code
 *
 */
void report(const char *message) {
  std::cerr << "[error] " << message << '\n';
  std::exit(EXIT_FAILURE);
}

/**
 *  iterate through the file, one line at a time
 *
 */
void process_file(std::ifstream &file,
                  std::function<void(const std::string &)> line_processor) {
  std::string line;

  while (file) {
    std::getline(file, line);
    line_processor(line);
  }
}

/**
 *  extract package name from provided line
 *
 */
std::string extract_package_name(const std::string &line) {
  std::stringstream ss{line};
  std::string piece;
  uint i = 0;

  while (ss.good() && i < 2) {
    std::getline(ss, piece, ':');
    if (i == 1)
      break;
    i++;
  }

  return piece;
}
