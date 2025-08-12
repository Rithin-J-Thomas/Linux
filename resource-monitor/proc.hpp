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

void SingleProcessDetails(int  pid);

class ProcBox
{
public:
        void ProcessCollection();
};
