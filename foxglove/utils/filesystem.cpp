#include "filesystem.hpp"

#include <fstream>
#include <sstream>

namespace foxglove::utils {
    std::string ReadTextFile(const std::string& path) {
        std::ifstream file(path);
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }
}
