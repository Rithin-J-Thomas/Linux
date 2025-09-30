#include <iostream>

#include "cpu.hpp"
#include "proc.hpp"
#include "network.hpp"

int main()
{

	CpuBox cpuBoxObj;   // // cpu section's class obj
	ProcBox procBoxObj; // // process section's class obj
	NetworkBox networkObj;

	while (true)
	{
		std::cout << "\033[2J\033[1;1H";

		cpuBoxObj.UptimeSecToMin_Hour(); // //displays only uptime

		cpuBoxObj.BatteryPercentage(); // //for Battery Percentage
		cpuBoxObj.CpuModelName();      // //for display only Cpu Model Name
		cpuBoxObj.FullCpuUsage();

		cpuBoxObj.PerCoreUsage();
		procBoxObj.ProcessCollection();
		networkObj.Download();
		myCustomSleep(1);
	}

	return 0;
}