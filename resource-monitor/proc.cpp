#include "proc.hpp"

//  // //std::cout <<  << "\n";

//  // //function for get all process's details (pid , name , command , threads , user , mem , cpu% )
void SingleProcessDetails(int pid)
{
        std::string filePath_Name = "/proc/" + std::to_string(pid) + "/comm";            // // file path for Process Name
        std::string filePath_Command = "/proc/" + std::to_string(pid) + "/cmdline";      // //  file path for Process Command
        std::string filePath_Threads = "/proc/" + std::to_string(pid) + "/task";         // //  file path for Process Threads
        std::string filePath_ForStatusFile = "/proc/" + std::to_string(pid) + "/status"; // //  file path for Process UID (user id) and MEM

        std::string processName = GetDataFromFile(filePath_Name); // //  gets  Process Name

        std::vector<std::string> processCommand = GetDataFromFile(filePath_Command, ' ');
        processCommand.emplace_back(" "); // // adds a empty string to avoid empty vectors

        const char *char_filePath_Threads = filePath_Threads.c_str(); // //  gets  Process threads

        int processThreads = 0;

        for (const auto &directories : std::filesystem::directory_iterator(char_filePath_Threads))
        {
                if (std::filesystem::is_directory(directories))
                {
                        processThreads++;
                }
        }

        std::string pidPath = "/proc/" + std::to_string(pid);
        //         const char *pidPathPointer = pidPath.c_str() ;
        // std::cout << pidPath<< "\t"<< *pidPathPointer << "\n";
        //    int stat(*pidPathPointer,)
        const char *takeDataFromForUid = "Uid:";
        std::string takeDataOfVmRSS = "VmRSS:";

        std::string userNameFromUid = GetEntireLineOfUid(filePath_ForStatusFile, '\n', *takeDataFromForUid);

        std::string currentProcessMEMString = GetEntireLine(filePath_ForStatusFile, '\n', takeDataOfVmRSS);
        //  std::cout << currentProcessMEMString<<"\n";

        currentProcessMEMString = KBtoMB(currentProcessMEMString);

        std::tuple<int, std::string, std::string, int, std::string, std::string> processDetailsTuple = std::make_tuple(pid, processName, processCommand[0], processThreads, userNameFromUid, currentProcessMEMString); // // stores pid , name , command , threads , user , mem , cpu%

       std::cout << std::get<0>(processDetailsTuple) << "\t" << std::get<1>(processDetailsTuple) << "\t" << std::get<5>(processDetailsTuple) << "\n";
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

std::string GetEntireLine(std::string filePath, char customDelimiter, std::string dataLookFrom) //  // //Function for take a single line which looking or passed
{
        std::string data, dataWanted;
        std::ifstream dataFile(filePath);

        while (getline(dataFile, data, customDelimiter))
        {
                if (data.find(dataLookFrom) != std::string::npos)
                {
                       //   std::cout << data << "\n";
                        return data;
                }
        }
        return " ";
}

std::string KBtoMB(std::string MEMString)
{
        if (MEMString == " ")
        {
                return "0B";
        }

        else
        {
                std::size_t intFirstPosition = MEMString.find_first_of("0123456789");
                std::size_t intLastPosition = MEMString.find_first_not_of("0123456789", intFirstPosition);

                if (intFirstPosition != std::string::npos)
                {
                        MEMString = MEMString.substr(intFirstPosition, intLastPosition - intFirstPosition);
                }
                int MEMDouble = stoi(MEMString) / 1024;

             //   std::cout<<MEMDouble<<"\n";

                return std::to_string(MEMDouble) + " MB";
        }
}