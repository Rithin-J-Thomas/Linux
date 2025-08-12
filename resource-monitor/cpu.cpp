#include "cpu.hpp"

std::vector<std::string> strUptimeFromFileVector, initialCpuUsageDataVector, finalCpuUsageDataVector;

// // std::cout<< " " ;

std::vector<std::string> getCpuDataByLines(std::string searchWord) // //
{
        std::vector<std::string> dataVector;
        std::string line;
        std::ifstream dataFile("/proc/stat");

        while (getline(dataFile, line))
        {
                if (line.find(searchWord) != std::string::npos)
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

std::tuple<std::vector<int>, std::vector<int>> perCoreUsage_and_IdleFunction()
{
        int findAllCpuReference = 0, trackCpuReference = 0, totalCores = 0, total_IdleTime = 0;
        std::vector<std::string> perCoreUsageLineVector;
        std::vector<int> vectorForEachCoreTotal, vectorForTotal_IdleTime;
        std::string statFilePath = "/proc/stat";
        int TotalSingleCoreUsage = 0;

        perCoreUsageLineVector = GetDataFromFile(statFilePath, ' '); // //takes entire stat file as individual elements

        for (int i = 0; i < perCoreUsageLineVector.size(); i++) // // this loop is to find how many times cpu appeared in stat's vector its 13(in my system's case) including cpu(full usage's field) cpu0, etc...
        {

                findAllCpuReference = perCoreUsageLineVector[i].find("cpu"); // //if cpu found it return 0 else -1
                // // std::cout<<findAllCpuReference<<"\n";
                if (findAllCpuReference == 0)
                {
                        trackCpuReference++;
                }
        }
        // // std::cout << trackCpuReference << "\n";
        totalCores = trackCpuReference - 1; // // line to find correct cores present in system

        for (int i = 0; i < totalCores; i++) // // this loop is to get every core's usage
        {

                std::string currentCore = "cpu";
                std::vector<std::string> percpuLineVector, singleCore;

                currentCore = currentCore + std::to_string(i); // //convert it like "cpu"+1 = cpu1 etc
                // std::cout << currentCore << "\n";

                percpuLineVector = getCpuDataByLines(currentCore); // //takes only current per core's usage all 10 fields

                for (int trackElements = 0; trackElements < percpuLineVector.size(); trackElements++) // // this loop is to find total usage of a single core only
                {
                        if (trackElements > 0 && trackElements < 10) // //condition for adding only required fields , skips core's name and guest field and so on
                        {
                                TotalSingleCoreUsage += std::stoi(percpuLineVector[trackElements]); // // adding required fields
                                //       std::cout << i << " first \n";
                        }

                        //  std::cout << TotalSingleCoreUsage << " last \n";
                }
                vectorForTotal_IdleTime.emplace_back(std::stoi(percpuLineVector[4]) + std::stoi(percpuLineVector[5])); //  //     insert this as current core's idle time
                vectorForEachCoreTotal.emplace_back(TotalSingleCoreUsage);                                             //   //     insert this 1st total into vector

                TotalSingleCoreUsage = 0; //   //  reseting this to 0

                //  std::cout << vectorForEachCoreTotal.size() << " size \n";
        }
        return std::make_tuple(vectorForEachCoreTotal, vectorForTotal_IdleTime);
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
        std::vector<std::string> cpuLineVector;                                          // //Vector for store the all cpu's resource line
        double totalCpuUsage = 0;                                                        // // variable for storing final result
        long long int Total_1st_CpuUsage = 0, Total_2nd_CpuUsage = 0, addedCpuUsage = 0; // // variable for storing both Total Cpu Usage from 1 second apart
        long long int idle_1st_Time = 0, idle_2nd_Time = 0, totalIdleTime = 0;           // //   same but for idle Time

        cpuLineVector = getCpuDataByLines("cpu");
        for (int i = 1; i <= 8; i++)
        {
                Total_1st_CpuUsage += std::stoi(cpuLineVector[i]); // // adds all field's values from user , nice , system till upto steal
        }
        idle_1st_Time = std::stol(cpuLineVector[4]) + std::stoi(cpuLineVector[5]); // // adds  field idle & iowait

        myCustomSleep(1); // // Sleeps

        cpuLineVector = getCpuDataByLines("cpu");
        for (int i = 1; i <= 8; i++)
        {
                Total_2nd_CpuUsage += std::stoi(cpuLineVector[i]); // // adds all field's values from user , nice , system till upto steal but after 1 second
                // std::cout << cpuLineVector[i] << "\n";
        }

        idle_2nd_Time = std::stol(cpuLineVector[4]) + std::stoi(cpuLineVector[5]); // // adds all field idle & iowait

        addedCpuUsage = Total_2nd_CpuUsage - Total_1st_CpuUsage;
        totalIdleTime = idle_2nd_Time - idle_1st_Time;

        // //std::cout << Total_1st_CpuUsage << "\t"<<Total_2nd_CpuUsage << "\n";
        // std::cout << addedCpuUsage << "\t" << totalIdleTime << "\n";

        // std::cout << idle_1st_Time << "\t" << idle_2nd_Time << "\n";
        //     totalCpuUsage = (addedCpuUsage - totalIdleTime) / addedCpuUsage;

        double usedCpu = static_cast<double>(addedCpuUsage - totalIdleTime); // //static_cast<double> for keep division between integers as floating point
        totalCpuUsage = usedCpu / static_cast<double>(addedCpuUsage);

        std::cout << int(totalCpuUsage * 100) << "%\n"; // //turns into 100%
}

void CpuBox::PerCoreUsage()
{
        // // taking values of core from stat file before 1sec
        std::tuple<std::vector<int>, std::vector<int>> firstCoreUsage_and_IdleTime = perCoreUsage_and_IdleFunction(); // // returns tuple with 2 vectors
        std::vector<int> totalVectorForEachCore_1st = std::get<0>(firstCoreUsage_and_IdleTime);                       // // Vector for every core's total usages
        std::vector<int> total_IdleTimeVector_1st = std::get<1>(firstCoreUsage_and_IdleTime);                         // // Vector for every core's total idle time(idle + iowait)

        myCustomSleep(1); // // waits to get difference between 2 values

        // // taking values of core from stat file after 1sec   (same thing as above)
        std::tuple<std::vector<int>, std::vector<int>> secondCoreUsage_and_IdleTime = perCoreUsage_and_IdleFunction();
        std::vector<int> totalVectorForEachCore_2nd = std::get<0>(secondCoreUsage_and_IdleTime);
        std::vector<int> total_IdleTimeVector_2nd = std::get<1>(secondCoreUsage_and_IdleTime);

        for (int currentCore = 0; currentCore < totalVectorForEachCore_1st.size(); currentCore++) // // loop for getting single core's usage
        {
                double totalCoreUsage = 0;
                long long int addedCoreUsage = totalVectorForEachCore_1st[currentCore] - totalVectorForEachCore_2nd[currentCore];
                long long int totalCoreIdleTime = total_IdleTimeVector_1st[currentCore] - total_IdleTimeVector_2nd[currentCore];

                double usedCore = static_cast<double>(addedCoreUsage - totalCoreIdleTime);
                totalCoreUsage = usedCore / static_cast<double>(addedCoreUsage);

                std::cout << int(totalCoreUsage * 100) << "% " << "  C" << currentCore << "\n"; // //turns into 100%
        }
}


void CpuBox::LoadAvg()
{
        
}