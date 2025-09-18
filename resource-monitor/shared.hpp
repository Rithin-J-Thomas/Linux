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

std::vector<std::string> GetDataFromFile(std::string filePath, char customDelimiter);
std::string GetDataFromFile(std::string filePath);
std::string GetEntireLineOfUid(std::string filePath, char takeDataFrom ,char dataLookFrom);
void myCustomSleep(int sleepTime);
