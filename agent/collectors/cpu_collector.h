#ifndef CPU_COLLECTOR_H
#define CPU_COLLECTOR_H

#include<stdint.h>

struct CpuTimes
{
    uint64_t total;
    uint64_t idle;
};

class CpuCollector {
    public:
        bool readCpuTimes(CpuTimes& times);
        double calcCpuValues(const CpuTimes& prev, const CpuTimes& cur);
};

#endif
