#include<iostream>
#include<thread>
#include<unistd.h>
#include "cpu_collector.h"
#include "memory_collector.h"
#include "process_collector.h"

using namespace std;

int main()
{
    CpuCollector ccol;
    MemoryCollector mcol;
    MemoryInfo memi;
    CpuTimes prev, cur;
    ProcessCollector pc;
    vector<ProcessInfo> procList(pc.collectProcesses());

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


    cout<<"---- Per process Info ------"<<endl;
    for(auto pr:procList)
    {
        cout<<"Pid: "<<pr.pid<<endl;
        cout<<"Ppid: "<<pr.ppid<<endl;
        cout<<"Name: "<<pr.name<<endl;
        cout<<"State: "<<pr.state<<endl;
        cout<<"Threads: "<<pr.threads<<endl;
        cout<<"vmSizeKb: "<<pr.vmSizeKb<<" kb"<<endl;
        cout<<"vmRSSKb: "<<pr.vmRSSKb<<" kb"<<endl;
        ProcessInfo prev,cur;
        pc.readProcessTime(pr.pid,prev);
        sleep(2);
        pc.readProcessTime(pr.pid,cur);
        uint64_t totalTime = ((cur.utime+cur.ktime) - (prev.utime+prev.ktime));
        cout<<"Total CPU load in 1 sec: "<<totalTime<<endl;
        cout<<"-----------------------------"<<endl;
        cout<<endl;
    }
    return 0;
}