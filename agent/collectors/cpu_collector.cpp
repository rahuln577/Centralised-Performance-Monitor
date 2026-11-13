#include<fcntl.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<unistd.h>
#include "cpu_collector.h"
#define CPU_INFO "/proc/stat"

using namespace std;

bool CpuCollector::readCpuTimes(CpuTimes& times){
    ifstream cpuFd(CPU_INFO);
    if(!cpuFd.is_open())
    {
        cout<<"Error opening /proc/stat"<<endl;
        return false;
    }
    string valueBuffer;
    if(!getline(cpuFd,valueBuffer))
    {
        cout<<"Error reading /proc/stat"<<endl;
        return false;
    }
    istringstream ss(valueBuffer);
    int tot = 0;
    int idle = 0;
    int cnt = 0;
    int temp;
    string cpuLabel;
    ss>>cpuLabel;
    while(ss>>temp)
    {
        tot += temp;
        if(cnt == 3 || cnt == 4)
        {
            idle += temp;
        }
        cnt++;
    }
    times.total = tot;
    times.idle = idle;
    return true;
}

double CpuCollector::calcCpuValues(const CpuTimes& prev, const CpuTimes& cur){
    int tot = cur.total - prev.total;
    int idle = cur.idle - prev.idle;
    double cpuUsage = (static_cast<double>(tot - idle)/tot)*100;
    return cpuUsage;
}