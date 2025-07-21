#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <string>
#include <iomanip>

#include "shared.hpp"

std::vector<std::string>CpuDataByLines();

class CpuBox
{
public:
        void SystemUptime();        // // for getting System Uptime (uptime & idle time)
        void UptimeSecToMin_Hour(); // // display only uptime
        void BatteryPercentage();   // // for Battery Percentage
        void CpuModelName();        // // display Cpu Model Name
        void FullCpuUsage();
};
