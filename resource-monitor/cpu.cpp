#include "cpu.hpp"

std::vector<std::string> strUptimeFromFileVector;

void CpuBox::SystemUptime() // // gets System uptime time in seconds (uptime & idle time)
{

        std::string path = "/proc/uptime";
        char customDelimiter = ' ';
        strUptimeFromFileVector = GetData(path, customDelimiter);
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
        char customDelimiter = ' ';
        std::vector<std::string> batteryDataVector = GetData(path, customDelimiter); // // Data stored in a Vector from shared.cpp file's function

        for (std::string i : batteryDataVector)
        {
                std::cout << "BATTERY percentage " << i << "%\n";
        }
}

void CpuBox::CpuInfoDataMethod()
{

        std::string path = "/proc/cpuinfo";
        char customDelimiter = ':';
        std::vector<std::string> thisDataLineVector;

        thisDataLineVector = GetData(path, customDelimiter);

        int vectorCount = 0;

        for (auto element : thisDataLineVector)
        {

                if (element == "model name	")
                {
                        std::cout << "model name" << thisDataLineVector[vectorCount + 1] << "\n ";
                        break;
                }
                vectorCount++;
                // // //std::cout << vectorCount << "\n";
        }
}
