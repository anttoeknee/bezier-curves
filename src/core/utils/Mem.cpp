#ifdef _WIN32

#include "Mem.hpp"

#include <string>

std::string core::utils::getMemUsage() {
    return "Windows";
}

#endif