#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <map>
#include <sstream>
#include <string>
#include <iomanip>
#include <thread>
#include <deque>
#include "raylib.h"

#include "shared.hpp"

std::vector<std::string> CpuDataByLines(std::string searchWord);

class CpuBox
{
public:
        void SystemUptime();               // // for getting System Uptime (uptime & idle time)
        std::string UptimeSecToMin_Hour(); // // display only uptime
        std::string BatteryPercentage();   // // for Battery Percentage
        std::string CpuModelName();        // // display Cpu Model Name
        int FullCpuUsage();                // // display full Cpu usage
        std::vector<int> PerCoreUsage();   // // display per core's usage
        void LoadAvg();
        void UpdateHistory();
        void DrawHistoryGraph(int x, int y, int width, int height);

        std::deque<int> fullCpuHistory;
        std::vector<std::deque<int>> perCoreHistory;

        CpuBox();
};
