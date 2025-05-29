#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid) {
    Process::pid_ = pid;
}    

// TODO: Return this process's ID
int Process::Pid() { return Process::pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {
	vector<string> values = LinuxParser::CpuUtilization(pid_);
    long uptime = LinuxParser::UpTime();

    long utime, stime, cutime, cstime, starttime, total_time;

    if (values.size() >= 22){

        utime = stol(values[13]);
        stime = stol(values[14]);
        cutime = stol(values[15]);
        cstime = stol(values[16]);
        starttime = stol(values[21]);

        total_time = utime + stime + cutime + cstime;

        float seconds = uptime - (starttime / sysconf(_SC_CLK_TCK));
        if (!seconds) {return 0.0;}
        float cpu_usage = (total_time / sysconf(_SC_CLK_TCK)) / seconds;
        return cpu_usage;
    }
    return 0.0;
}

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(Process::pid_); }

// TODO: Return this process's memory utilization
string Process::Ram() { 
	std::string ram = LinuxParser::Ram(pid_); 
    // Convert from KB to MB
    return std::to_string(stoi(ram) / 1000); 
}

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(Process::pid_); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(Process::pid_); }


bool Process::operator<(Process& a) {  
    return CpuUtilization() > a.CpuUtilization();
}
