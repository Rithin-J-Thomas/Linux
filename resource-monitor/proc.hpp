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

void SingleProcessDetails(int  pid);
std::string GetEntireLine(std::string filePath,char customDelimiter , std::string  dataLookFrom);
std::string KBtoMB(std::string MEMString);


class ProcBox
{
public:
        void ProcessCollection();

};
