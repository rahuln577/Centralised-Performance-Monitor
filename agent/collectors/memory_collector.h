#ifndef MEMORY_COLLECTOR_H
#define MEMORY_COLLECTOR_H

#include<stdint.h>

struct MemoryInfo {
    uint64_t total;
    uint64_t available;
    double usagePercent;
};

class MemoryCollector {
    public:
        bool readMemoryInfo(MemoryInfo& memInfo);
};

#endif