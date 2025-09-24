#pragma once

#include "shared.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <dirent.h>
#include <cstdio>
#include <stdexcept>
#include <tuple>
#include <filesystem>
#include <unistd.h>
#include <sys/stat.h>

void SingleProcessDetails(int pid);
std::string GetEntireLine(std::string filePath, char customDelimiter, std::string dataLookFrom);
std::string KBtoMB(std::string MEMString);
// // // std::vector<std::string> SingleCpuUsage(std::string filePath, char delimiter);
// // // std::vector<std::string> GetCpuUsage(std::string filePath_ForStatFile);
// // // std::vector<std::string> EveryCpuUStimeUsage(char path);

class ProcBox
{
public:
        void ProcessCollection();
};
