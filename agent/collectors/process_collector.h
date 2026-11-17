#ifndef PROCESS_COLLECTOR_H
#define PROCESS_COLLECTOR_H
#include<cstdint>
#include<string>
#include<vector>
#include<sys/types.h>

using namespace std;

struct ProcessInfo 
{
    pid_t pid;
    pid_t ppid;

    string name;
    string state;

    unsigned int threads;

    uint64_t vmSizeKb;
    uint64_t vmRSSKb;

    uint64_t utime; //user space execution time
    uint64_t ktime; //Kernel space execution time
};

class ProcessCollector 
{
    public:
        vector<ProcessInfo> collectProcesses();
        bool readProcessTime(pid_t pid,ProcessInfo& procInfo);
    private:
        bool readProcessStatus(pid_t pid,ProcessInfo& processInfo);
};

#endif