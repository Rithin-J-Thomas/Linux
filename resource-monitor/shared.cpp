#include "shared.hpp"

// // FUnction for getting data or parsing data from a file
std::vector<std::string> GetDataFromFile(std::string filePath, char customDelimiter)
{

        std::string data;

        std::vector<std::string> dataVector; // // store data in this vector and return it
        std::ifstream dataFile(filePath);
        while (getline(dataFile, data))
        {
                std::stringstream ss(data); // // gets data as objs and pass it as line like std::cin
                while (getline(ss, data, customDelimiter))
                {
                        if (data != "")
                        {
                                dataVector.emplace_back(data); // // separates each using space or colon or semi-colon or whatever and store data in vector
                        }
                }
        }

        dataFile.close();

        return dataVector;
}

// //method overloading for contents with 1 lined file
std::string GetDataFromFile(std::string filePath)
{

        std::string data;
        std::ifstream dataFile(filePath);
        getline(dataFile, data);

        dataFile.close();

        return data;
}

std::string GetEntireLine(std::string filePath, char customDelimiter)
{
        std::string data;


        //std::ifstream dataFile(filePath);
        // while (getline(dataFile, data))
        // {
        //         std::stringstream ss(data); 
        //         getline(ss, data, customDelimiter);


        // }

        // dataFile.close();

         return data;
}

// // // to make things wait
void myCustomSleep(int sleepTime)
{
        std::this_thread::sleep_for(std::chrono::seconds(sleepTime));
}