#include<iostream>
#include<thread>
#include<unistd.h>
#include "cpu_collector.h"
#include "memory_collector.h"

using namespace std;

int main()
{
    CpuCollector ccol;
    MemoryCollector mcol;
    MemoryInfo memi;
    CpuTimes prev, cur;
    ccol.readCpuTimes(prev);
    mcol.readMemoryInfo(memi);
    sleep(1);
    ccol.readCpuTimes(cur);
    double cpuUsage = ccol.calcCpuValues(prev,cur);
    cout<<"CPU usage: "<<cpuUsage<<"%"<<endl;
    cout<<"CPU Idle Time: "<<cur.idle<<endl;
    cout<<"CPU Running Time: "<<cur.total<<endl;
    cout<<"Memory Total: "<<(memi.total/1000)<<" mb"<<endl;
    cout<<"Memory Available: "<<(memi.available/1000)<<" mb"<<endl;
    cout<<"Memory Usage: "<<memi.usagePercent<<"%"<<endl;
    return 0;
}