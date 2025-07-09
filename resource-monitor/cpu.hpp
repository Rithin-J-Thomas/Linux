#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <iomanip>


#include "shared.hpp"

class CpuBox
{
public:
        void SystemUptime();
        void UptimeSecToMin_Hour();
        void BatteryPercentage();
        std::vector<std::string> CpuInfoDataMethod();
};
