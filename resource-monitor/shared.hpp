#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <chrono>
#include <thread>
#include <algorithm>
#include <unistd.h>
#include <iomanip>
//#include <ftxui/screen/color.hpp>



std::vector<std::string> GetDataFromFile(std::string filePath, char customDelimiter);
std::string GetDataFromFile(std::string filePath);
std::string GetEntireLineOfUid(std::string filePath, char takeDataFrom ,char dataLookFrom);
void myCustomSleep(int sleepTime);
std::string MyConversion(int value);
//ftxui::Color DetermineColor(int percentage);

