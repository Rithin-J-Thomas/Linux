#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <chrono>
#include <thread>

std::vector<std::string> GetDataFromFile(std::string filePath, char customDelimiter);
void myCustomSleep(int sleepTime);
