#include "Mem.hpp"
#include <string>

#if defined(_WIN32)
#include <windows.h>
#include <psapi.h>

std::string core::utils::getMemUsage() {
    PROCESS_MEMORY_COUNTERS_EX pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), reinterpret_cast<PROCESS_MEMORY_COUNTERS *>(&pmc), sizeof(pmc))) {
        SIZE_T physMemUsed = pmc.WorkingSetSize;
        physMemUsed /= (1024 * 1024);
        return std::to_string(physMemUsed) + " MB";
    }
    return "N/A";
}

#elif defined(__linux__)
#include <fstream>

std::string core::utils::getMemUsage() {
    std::ifstream status("/proc/self/status");
    std::string line;
    while (std::getline(status, line)) {
        if (line.find("VmRSS:") == 0) {
            long kb = std::stol(line.substr(6));
            return std::to_string(kb / 1024) + " MB";
        }
    }
    return "N/A";
}

#endif