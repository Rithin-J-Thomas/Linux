#pragma once

#include "raylib.h"
#include "cpu.hpp"
#include "proc.hpp"
#include "network.hpp"


void DrawCpuGraph(const std::deque<int>& history, int startX, int startY, int width, int height, Color color);
void CpuSectionRaylib(CpuBox& cpuBoxObj);
void ProcessSectionRaylib(ProcBox &procBoxObj);
void NetworkSectionRaylib();
void TerminateSectionRaylib();