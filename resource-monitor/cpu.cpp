#include "cpu.hpp"

std::vector<std::string> strUptimeFromFileVector;

void CpuBox::SystemUptime() // // gets System uptime time in seconds (uptime & idle time)
{
        std::string uptime;
        std::ifstream uptimeFile("/proc/uptime"); // // gets file
        while (getline(uptimeFile, uptime))       // // gets file's contents
        {
                // // std::string fileuptimetext = uptime;
                // // std::cout << fileuptimetext << "\n";

                std::stringstream ss(uptime);

                while (getline(ss, uptime, ' '))
                {
                        strUptimeFromFileVector.push_back(uptime); // // separate each floating points  using space
                }
        }

        uptimeFile.close();
}

void CpuBox::UptimeSecToMin_Hour()
{
        SystemUptime();

        std::string strUptime = strUptimeFromFileVector.front(); // // takes only System's uptime time in seconds

        int intUptime = std::stoi(strUptime);

        int hour = 0, minutes = 0, remainingTime = 0;

        minutes = intUptime / 60;
        hour = minutes / 60;
        remainingTime = minutes % 60;

        int second = (intUptime % 3600) % 60;

        std::cout << "System Uptime " << std::setw(2) << std::setfill('0') << hour << ":"
                  << std::setw(2) << std::setfill('0') << remainingTime << ":"
                  << std::setw(2) << std::setfill('0') << second << " \n";
}

void CpuBox::BatteryPercentage()
{
        std::string path = "/sys/class/power_supply/BAT0/capacity"; // // path of directory for Battery Percentage

        std::vector<std::string> batteryDataVector = GetData(path); // // Data stored in a Vector from shared.cpp file's function

        for (std::string i : batteryDataVector)
        {
                std::cout << "BATTERY percentage " << i << "%\n";
        }
}

// std::vector<std::string> CpuBox::CpuInfoDataMethod()
// {
//         std::vector<std::string> cpuInfoVector;

        

//         return cpuInfoVector;




// }

// for (std::string time : strUptimeFromFileVector)
// {
//         std::cout << time << "\n";
// }