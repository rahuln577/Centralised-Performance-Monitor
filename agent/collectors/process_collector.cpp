#include"process_collector.h"
#include<filesystem>
#include<string>
#include<iostream>
#include<cctype>
#include<sstream>
#include<vector>
#include<fstream>
#include<algorithm>

using namespace std;

bool isDigitString(string value)
{
    for(auto i:value)
    {
        if(!isdigit(i))return false;
    }
    return true;
}

//Trim the beggining of the string until it encounters first ")"
string removeLeadingProcName(string &val)
{
    string res;
    size_t pos = val.rfind(')');

    if(pos == string::npos)
    {
        return "";
    }

    return val.substr(pos+1);
}

vector<ProcessInfo> ProcessCollector::collectProcesses()
{
    vector<ProcessInfo> procList;
    for(const auto& dir:filesystem::directory_iterator("/proc"))
    {
        ProcessInfo procInfo;
        bool res = false;
        if(isDigitString(dir.path().filename().string()))
        {
            istringstream filename(dir.path().filename().string());
            pid_t pid;
            filename>>pid;
            if(!(res = readProcessStatus(pid,procInfo)))
            {
                cout<<"Error in reading process status"<<endl;
            }
        }
        if(res)
        {
            procList.push_back(procInfo);
        }
    }
    return procList;
}


bool ProcessCollector::readProcessStatus(pid_t pid,ProcessInfo& processInfo)
{
    string pname = "/proc/"+to_string(pid)+"/status";
    ifstream file(pname);

    if(!file.is_open())
    {
        cout<<"Error in reading the process stats with PID "<<pid<<endl;
        return false;
    }

    string line;
    while(getline(file,line))
    {
        istringstream field(line);
        string label;
        field>>label;
        
        if(label == "Pid:")
        {
            field>>processInfo.pid;
        }
        else if(label == "PPid:")
        {
            field>>processInfo.ppid;
        }
        else if(label == "Name:")
        {
            field>>processInfo.name;
        }
        else if(label == "State:")
        {
            field>>processInfo.state;
        }
        else if(label == "Threads:")
        {
            field>>processInfo.threads;
        }
        else if(label == "VmRSS:")
        {
            field>>processInfo.vmRSSKb;
        }
        else if(label == "VmSize:")
        {
            field>>processInfo.vmSizeKb;
        }

        string temp;
        while(!field.eof())field>>temp;
    }
    
    if(!readProcessTime(pid,processInfo))return false;

    return true;
}

bool ProcessCollector::readProcessTime(pid_t pid,ProcessInfo& procInfo)
{
    ifstream filestat("/proc/"+to_string(pid)+"/stat");

    if(!filestat.is_open())
    {
        cout<<"Error opening /proc/stat for pid "<<pid<<endl;
        return false;
    }
    long ticksPerSecond = sysconf(_SC_CLK_TCK);
    string procStat;
    if(!getline(filestat,procStat))
    {
        cout<<"Error in getline of /proc/stat of PID "<<pid<<endl;
        return false;
    }

    procStat = removeLeadingProcName(procStat);
    int ind = 0;
    string temp;
    istringstream stat(procStat);
    stat>>temp;

    for(int i=0;i<=11;i++)
    {
        uint64_t val;
        if(!stat>>val)
        {
            cout<<"String stream extraction error in stat"<<endl;
            return false;
        }
        if(ind == 10)
        {
            procInfo.utime = val/ticksPerSecond;
        }
        if(ind == 11)
        {
            procInfo.ktime = val/ticksPerSecond;
            break;
        }
        ind++;
    }

    return true;
}