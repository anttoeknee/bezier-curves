#ifdef _WIN32
#include <Foundation/Foundation.h>
#include "../../includes/utils/Mem.h"

std::string core::utils::getMemUsage() {
    return "Windows";
}

#endif