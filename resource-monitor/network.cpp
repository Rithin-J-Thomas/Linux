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



// // // int GetCurrentSpeed(int newSpeed, int oldSpeed)
// // // {
// // //         return   newSpeed  - oldSpeed  ;
// // // }

std::string NetworkBox::Download()
{
        int totalDataReceivedBytes = 0, newtotalDataReceivedBytes = 0; // //stores the total received data
        std::string netInterfacePath = "/sys/class/net/";
        std::string networkInterface = GetDirList(netInterfacePath);

        std::string totalDataReceivedPath = "/sys/class/net/" + networkInterface + "/statistics/rx_bytes";

        totalDataReceivedBytes = GetData(totalDataReceivedPath);

        std::string data = MyConversion(totalDataReceivedBytes);
        return data;
        // // // myCustomSleep(1);
        // // // newtotalDataReceivedBytes = GetData(totalDataReceivedPath);

        // // // int currentSpeed = GetCurrentSpeed(newtotalDataReceivedBytes, totalDataReceivedBytes);
        // // // // std::cout << totalDataReceivedBytes << "\t"<< newtotalDataReceivedBytes << "\n";
        // // // std::cout << currentSpeed/1024 << "\n";
}

 std::string NetworkBox::Upload()
{
        int totalDataUploaded = 0; // //stores the total transmitted or uploaded  data
        std::string netInterfacePath = "/sys/class/net/";
        std::string networkInterface = GetDirList(netInterfacePath);
        // std::cout<<networkInterface<<"\n";
        std::string totalDataUploadedPath = "/sys/class/net/" + networkInterface + "/statistics/tx_bytes";

        totalDataUploaded = GetData(totalDataUploadedPath);
                
         std::string data = MyConversion(totalDataUploaded);

        return data;
}