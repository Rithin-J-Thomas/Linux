#include "proc.hpp"

//  // //std::cout <<  << "\n";

//  // //function for get all process's details (pid , name , command , threads , user , mem , cpu% )
void SingleProcessDetails(int pid)
{
        std::string filePath_Name = "/proc/" + std::to_string(pid) + "/comm";       // // file path for Process Name
        std::string filePath_Command = "/proc/" + std::to_string(pid) + "/cmdline"; // //  file path for Process Command
        std::string filePath_Threads = "/proc/" + std::to_string(pid) + "/task";    // //  file path for Process Threads
        std::string filePath_UID = "/proc/" + std::to_string(pid) +"/status";    // //  file path for Process UID (user id)

        std::string processName = GetDataFromFile(filePath_Name); // //  gets  Process Name

        std::vector<std::string> processCommand = GetDataFromFile(filePath_Command, ' ');
        processCommand.emplace_back(" "); // // adds a empty string to avoid empty vectors


        const char *char_filePath_Threads = filePath_Threads.c_str();

        int processThreads = 0;

        for (const auto &directories : std::filesystem::directory_iterator(char_filePath_Threads))
        {
                if (std::filesystem::is_directory(directories))
                {
                        processThreads++;
                }
        }








        std::tuple<int, std::string, std::string, int> processDetailsTuple = std::make_tuple(pid, processName, processCommand[0], processThreads); // // stores pid , name , command , threads , user , mem , cpu%

        // std::cout << std::get<0>(processDetailsTuple) << "\t" << std::get<1>(processDetailsTuple) << "\t" << "\n"; // // not printing 'command' yet
       // std::cout << std::get<0>(processDetailsTuple) << "\t" << std::get<1>(processDetailsTuple) << "\t" << std::get<3>(processDetailsTuple) << "\n";
}

void ProcBox::ProcessCollection()
{
        DIR *process; // // directory

        const char *path = "/proc"; // // char for opendir()

        process = opendir(path);

        struct dirent *files;

        if (process == NULL)
        {
                perror("Failed opening directory");
                return;
        }

        while ((files = readdir(process)) != NULL)
        {
                int processID = 0;
                try
                {
                        processID = std::stoi(files->d_name);
                        //  // //std::cout << processID << "\n";
                }
                catch (const std::invalid_argument &e)
                {
                        continue;
                }

                SingleProcessDetails(processID);
        }

        closedir(process);
}