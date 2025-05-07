
#ifdef __APPLE__
#include <Foundation/Foundation.h>
#include "../../includes/platform/platform.h"

std::string getMemUsage() {

    // Get the current process's task info
    task_basic_info_data_t info;
    mach_msg_type_number_t infoCount = TASK_BASIC_INFO_COUNT;
    kern_return_t kr = task_info(mach_task_self(), TASK_BASIC_INFO, (task_info_t)&info, &infoCount);

    if (kr != KERN_SUCCESS) {
        return "Error retrieving memory info.";
    }

    // Memory usage in bytes, convert to MB
    uint64_t memoryUsed = info.resident_size / (1024 * 1024);
    return std::to_string(memoryUsed) + " MB";
}

#endif

