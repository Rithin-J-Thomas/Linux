#include "network.hpp"

std::string GetDirList(std::string dirPath)
{
        for (const auto &entry : std::filesystem::directory_iterator(dirPath))
        {
                std::string currentDIR = "";
                currentDIR = entry.path();
                // if(currentDIR != "/sys/class/net")
                // {
                //         std::cout<<currentDIR<<"\n";
                // }
                int dirPosition = currentDIR.find_last_of('/');
                currentDIR = currentDIR.substr(dirPosition + 1);
                //  std::cout<<currentDIR<<"\n";

                if (currentDIR != "lo")
                {
                        return currentDIR;
                }
        }
        return "";
}

int GetData(std::string Path)
{
        std::string dataStr;
        std::ifstream file(Path);

        while (getline(file, dataStr))
        {
                return std::stoi(dataStr);
        }

        return 0;
}

std::string MyConversion(int value)
{

        int MB = value / 1048576; // //converts into bytes to MB

        if (MB < 1024)
        {
                return std::to_string(MB) + " MB";
        }
        else
        {
                double GB = MB / 1024.0; 
                 return std::to_string(GB) + " GB"; 
        }
        return "";
}

// // // int GetCurrentSpeed(int newSpeed, int oldSpeed)
// // // {
// // //         return   newSpeed  - oldSpeed  ;
// // // }

void NetworkBox::Download()
{
        int totalDataReceivedBytes = 0, newtotalDataReceivedBytes = 0; // //stores the total received data
        std::string netInterfacePath = "/sys/class/net/";
        std::string networkInterface = GetDirList(netInterfacePath);
        // //std::cout<<networkInterface<<"\n";
        std::string totalDataReceivedPath = "/sys/class/net/" + networkInterface + "/statistics/rx_bytes";

        totalDataReceivedBytes = GetData(totalDataReceivedPath);

        std::string data = MyConversion(totalDataReceivedBytes);
        std::cout << data << " \n";
        // // // myCustomSleep(1);
        // // // newtotalDataReceivedBytes = GetData(totalDataReceivedPath);

        // // // int currentSpeed = GetCurrentSpeed(newtotalDataReceivedBytes, totalDataReceivedBytes);
        // // // // std::cout << totalDataReceivedBytes << "\t"<< newtotalDataReceivedBytes << "\n";
        // // // std::cout << currentSpeed/1024 << "\n";
}

void NetworkBox::Upload()
{
        int totalDataUploaded = 0; // //stores the total transmitted or uploaded  data
        std::string netInterfacePath = "/sys/class/net/";
        std::string networkInterface = GetDirList(netInterfacePath);
        // std::cout<<networkInterface<<"\n";
        std::string totalDataUploadedPath = "/sys/class/net/" + networkInterface + "/statistics/tx_bytes";

        totalDataUploaded = GetData(totalDataUploadedPath);
        std::cout << totalDataUploaded << "\n";

        totalDataUploaded = totalDataUploaded / 1048576; // //converts into bytes to MB
        std::cout << totalDataUploaded << " MB\n";
}