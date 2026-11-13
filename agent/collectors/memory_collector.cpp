#include"memory_collector.h"
#include<sstream>
#include<fstream>
#include<iostream>
#define MEM_INFO_PATH "/proc/meminfo"

using namespace std;

bool MemoryCollector::readMemoryInfo(MemoryInfo& memInfo){
    ifstream memFile(MEM_INFO_PATH);
    if(!memFile.is_open())
    {
        cout<<"Error Opening /proc/meminfo"<<endl;
        return false;
    }
    string line;
    while(getline(memFile,line))
    {
        string label;
        uint64_t value;
        string kb;
        istringstream ss(line);
        ss>>label;
        ss>>value;
        ss>>kb;
        if(label == "MemTotal:")
        {
            memInfo.total = value;
        }
        if(label == "MemAvailable:")
        {
            memInfo.available = value;
        }
    }
    memInfo.usagePercent = (static_cast<double>(memInfo.total - memInfo.available)/memInfo.total) * 100;
    return true;
}