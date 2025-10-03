#include "shared.hpp"

//  // //std::cout <<  << "\n";
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

std::string GetEntireLineOfUid(std::string filePath, char customDelimiter, char dataLookFrom)
{
        std::string data, user = "", foundUid;

        std::ifstream dataFile(filePath);
        while (getline(dataFile, data, customDelimiter))
        {
                if (data.find(dataLookFrom) != std::string::npos)
                {
                        foundUid = data;
                }

        } // std::cout << foundUid << "\t founded uid\n";
        for (int i = 5; i <= 8; i++)
        {
                user += foundUid[i];
        }
        dataFile.close();

        int intUserId = std::stoi(user);
        std::string userName = getlogin(); // // // for finding regular user's name
        // std::cout << userName << "\t user\n";

        if (intUserId == 0)
        {
                return "Root";
        }
        else if (intUserId >= 1 && intUserId <= 999)
        {
                return "System";
        }
        else
        {
                return userName;
        }
        return " ";
}

// // // to make things wait
void myCustomSleep(int sleepTime)
{
        std::this_thread::sleep_for(std::chrono::seconds(sleepTime));
}

// ftxui::Color DetermineColor(int percentage)

// {
        // ftxui::Color graphColor ;
        // if (percentage < 15)
        // {
        //         graphColor = ftxui::Color::Green1;
        // }
        // else if (percentage < 30)
        // {
        //         graphColor = ftxui::Color::Green;
        // }
        // else if (percentage < 70)
        // {
        //         graphColor = ftxui::Color::Yellow1;
        // }
        // else if (percentage < 85)
        // {
        //         graphColor = ftxui::Color::Orange1;
        // }
        // else if (percentage < 100)
        // {
        //         graphColor = ftxui::Color::Red;
        // }
        // return graphColor;
// }



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
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << GB; 
        return oss.str() + " GB"; 
        }
        return "";
}