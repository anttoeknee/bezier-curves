#ifdef _WIN32

#include "Mem.hpp"
#include <windows.h>
#include <string>
#include <psapi.h>

std::string core::utils::getMemUsage() {

    PROCESS_MEMORY_COUNTERS_EX pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), reinterpret_cast<PROCESS_MEMORY_COUNTERS *>(&pmc), sizeof(pmc))) {
        SIZE_T physMemUsed = pmc.WorkingSetSize;
        physMemUsed /= (1024 * 1024); // Convert bytes to MB
        return std::to_string(physMemUsed) + " MB";
    }
    return "N/A";
}

#endif