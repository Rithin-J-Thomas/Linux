#include "shared.hpp"

// // FUnction for getting data or pharsing data from a file
std::vector<std::string> GetData(std::string filePath)
{

        std::string data;
        std::vector<std::string> dataVector;
        std::ifstream dataFile(filePath);
        while (getline(dataFile, data))
        {
                std::stringstream ss(data);
                while (getline(ss, data, ' '))
                {
                        dataVector.push_back(data); // // separate each using space
                }
        }

        dataFile.close();

        return dataVector;
}