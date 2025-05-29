#include <unistd.h>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <thread>
#include <chrono>

#include "processor.h"
#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;


// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
	auto cpu1 = LinuxParser::CpuUtilization();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    auto cpu2 = LinuxParser::CpuUtilization();

    if (cpu1.size() < 8 || cpu2.size() < 8) return 0.0;

    unsigned long long idle1 = std::stol(cpu1[3]) + std::stol(cpu1[4]);
    unsigned long long idle2 = std::stol(cpu2[3]) + std::stol(cpu2[4]);

    unsigned long long total1 = 0.0, total2 = 0.0;
    for (int i = 0; i < 8; ++i) {
        total1 += std::stol(cpu1[i]);
        total2 += std::stol(cpu2[i]);
    }

    float total_delta = total2 - total1;
    float idle_delta = idle2 - idle1;

    if (total_delta == 0) return 0.0;
  
  	float cpu_usage = (total_delta - idle_delta) / total_delta;
  
    return cpu_usage;
}