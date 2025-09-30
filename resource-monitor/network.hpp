#pragma once

#include "shared.hpp"


#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>

std::string GetDirList(std::string dirPath);
int GetData(std::string Path);
// // //int GetCurrentSpeed(std::string Path);
std::string MyConversion(int value);

class NetworkBox
{
public:
// //shows total data received , top speed hit , current speed
void Download();
// //shows total data uploaded , top speed hit for upload , current speed
void Upload();
};