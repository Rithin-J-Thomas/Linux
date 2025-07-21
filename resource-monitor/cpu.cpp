#include "cpu.hpp"

std::vector<std::string> strUptimeFromFileVector, initialCpuUsageDataVector, finalCpuUsageDataVector;

// // std::cout<< " " ;

std::vector<std::string> getCpuDataByLines() // //
{
        std::vector<std::string> dataVector;
        std::string line;
        std::ifstream dataFile("/proc/stat");

        while (getline(dataFile, line))
        {
                if (line.find("cpu") != std::string::npos)
                {

                        // std::cout << line;
                        std::stringstream ss(line);
                        while (getline(ss, line, ' '))
                        {
                                if (line != "")
                                {
                                        dataVector.emplace_back(line);
                                }
                        }
                        break;
                }
        }
        dataFile.close();
        return dataVector;
}

void CpuBox::SystemUptime() // // gets System uptime time in seconds (uptime & idle time)
{

        std::string path = "/proc/uptime";
        char customDelimiter = ' ';
        strUptimeFromFileVector = GetDataFromFile(path, customDelimiter);
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
        std::vector<std::string> batteryDataVector = GetDataFromFile(path, customDelimiter); // // Data stored in a Vector from shared.cpp file's function

        for (std::string i : batteryDataVector)
        {
                std::cout << "BATTERY percentage " << i << "%\n";
        }
}

void CpuBox::CpuModelName()
{

        std::string path = "/proc/cpuinfo";
        char customDelimiter = ':';
        std::vector<std::string> thisDataLineVector;

        thisDataLineVector = GetDataFromFile(path, customDelimiter);

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

void CpuBox::FullCpuUsage()
{
        std::vector<std::string> cpuLineVector; // //
        double totalCpuUsage = 0;
        long long int Total_1st_CpuUsage = 0, Total_2nd_CpuUsage = 0, addedCpuUsage = 0;
        long long int idle_1st_Time = 0, idle_2nd_Time = 0, totalIdleTime = 0;

        cpuLineVector = getCpuDataByLines();
        for (int i = 1; i <= 8; i++)
        {
                Total_1st_CpuUsage += std::stoi(cpuLineVector[i]);
        }
        idle_1st_Time = std::stol(cpuLineVector[4]) + std::stoi(cpuLineVector[5]);

        myCustomSleep(1);

        cpuLineVector = getCpuDataByLines();
        for (int i = 1; i <= 8; i++)
        {
                Total_2nd_CpuUsage += std::stoi(cpuLineVector[i]);
                // std::cout << cpuLineVector[i] << "\n";
        }

        idle_2nd_Time = std::stol(cpuLineVector[4]) + std::stoi(cpuLineVector[5]);

        addedCpuUsage = Total_2nd_CpuUsage - Total_1st_CpuUsage;
        totalIdleTime = idle_2nd_Time - idle_1st_Time;

        // //std::cout << Total_1st_CpuUsage << "\t"<<Total_2nd_CpuUsage << "\n";
        std::cout << addedCpuUsage << "\t" << totalIdleTime << "\n";

        // std::cout << idle_1st_Time << "\t" << idle_2nd_Time << "\n";
      //     totalCpuUsage = (addedCpuUsage - totalIdleTime) / addedCpuUsage;

double usedCpu = static_cast<double>(addedCpuUsage - totalIdleTime);
totalCpuUsage = usedCpu / static_cast<double>(addedCpuUsage);


        std::cout<< totalCpuUsage*100 << "%\n";
}