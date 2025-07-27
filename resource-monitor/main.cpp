#include <iostream>

#include "cpu.hpp"

int main()
{

        CpuBox cpuBoxObj; // // cpu section's class obj

        while (true)
        {
                std::cout << "\033[2J\033[1;1H";

                // cpuBoxObj.UptimeSecToMin_Hour(); // //displays only uptime

                // cpuBoxObj.BatteryPercentage(); // //for Battery Percentage
                // cpuBoxObj.CpuModelName();      // //for display only Cpu Model Name
                //  cpuBoxObj.FullCpuUsage();

                cpuBoxObj.PerCoreUsage();
                // myCustomSleep(2);
        }

        return 0;
}