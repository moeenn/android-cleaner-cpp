#include "PackageFile.hpp"

/**
 *  iterate through the file, one line at a time
 *
 */
void PackageFile::process_file(
    std::ifstream &file,
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
std::string PackageFile::extract_package_name(const std::string &line) {
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
