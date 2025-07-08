#include "common.hpp"

std::vector<std::string> strUptimeFromFileVector;

void SystemUptime() // // gets System uptime time in seconds (uptime & idle time)
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
                        strUptimeFromFileVector.push_back(uptime);  // // separate each floating points  using space
                }
        }

        uptimeFile.close();
}

void UptimeSecToMin_Hour()
{
        SystemUptime();

        std::string strUptime = strUptimeFromFileVector.front();        // // takes only System's uptime time in seconds

        int intUptime = std::stoi(strUptime);

        int hour = 0, minutes = 0, remainingTime = 0;

        minutes = intUptime / 60;
        hour = minutes / 60;
        remainingTime = minutes % 60;

        int second = (intUptime % 3600) % 60;   

        std::cout << std::setw(2) << std::setfill('0') << hour << ":"
                  << std::setw(2) << std::setfill('0') << remainingTime << ":"
                  << std::setw(2) << std::setfill('0') << second << " \n";
}

// for (std::string time : strUptimeFromFileVector)
// {
//         std::cout << time << "\n";
// }