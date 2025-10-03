#pragma once

#include "shared.hpp"


#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>

std::string GetDirList(std::string dirPath);
int GetData(std::string Path);
// // //int GetCurrentSpeed(std::string Path);


class NetworkBox
{
public:
// //shows total data received , top speed hit , current speed
std::string  Download();
// //shows total data uploaded , top speed hit for upload , current speed
 std::string Upload();
};