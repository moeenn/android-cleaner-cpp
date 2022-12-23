#pragma once
#include <functional>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>

namespace PackageFile {
void process_file(std::ifstream &file,
                  std::function<void(const std::string &)>);
std::string extract_package_name(const std::string &line);
} // namespace PackageFile