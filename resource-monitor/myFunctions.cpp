#include "myFunctions.hpp"

void DrawCpuGraph(const std::deque<int> &history, int startX, int startY, int width, int height, Color color)
{
    int size = history.size();
    float stepX = (float)width / size;

    for (int i = 0; i < size; i++)
    {
        int usage = history[i]; // value 0–100
        float dotY = startY + height - (usage / 100.0f * height);
        DrawCircle(startX + i * stepX, dotY, 2, color);
    }
}

void CpuSectionRaylib(CpuBox &cpuBoxObj)
{
    Rectangle cpuSection = {30, 30, 1870, 400};
    int borderThickness = 4;

    // // // section's style colors
    Color backgroundClr = {0, 0, 0, 255}, sectionBorderColor = {16, 82, 28, 255};

    DrawRectangleRec(cpuSection, backgroundClr);

    cpuBoxObj.UpdateHistory();

    DrawRectangleLinesEx(cpuSection, borderThickness, sectionBorderColor);

    std::string uptimeText = cpuBoxObj.UptimeSecToMin_Hour(); // //displays only uptime
    DrawText(uptimeText.c_str(), 80, 370, 20, RAYWHITE);

    std::string batteryPercentText = cpuBoxObj.BatteryPercentage(); // //for Battery Percentage
    DrawText(batteryPercentText.c_str(), 300, 370, 20, RAYWHITE);

    std::string cpuModelNameText = cpuBoxObj.CpuModelName(); // //for display only Cpu Model Name
    DrawText(cpuModelNameText.c_str(), 400, 370, 20, RAYWHITE);

    int fullCpuUsageInt = cpuBoxObj.FullCpuUsage();
    std::string fullCpuUsageText = std::to_string(fullCpuUsageInt) + "  CPU";
    DrawText(fullCpuUsageText.c_str(), 950, 370, 20, RAYWHITE);

    std::vector<int> perCoreUsageVector = cpuBoxObj.PerCoreUsage();
    int gap = 50;
    for (auto core : perCoreUsageVector)
    {
        DrawText(std::to_string(core).c_str(), 1150 + gap, 370, 20, RAYWHITE);
        gap += 50;
    }
    cpuBoxObj.DrawHistoryGraph(50, 50, 400, 100);

    // per-core small graphs
    int yOffset = 270;
    int coreIndex = 0;
    for (auto &coreHist : cpuBoxObj.perCoreHistory)
    {
        DrawCpuGraph(coreHist, 900, yOffset-200, 800, 40, SKYBLUE);
        yOffset += 50;
        if (++coreIndex >= 4)
            break; // only first 4 cores shown
    }
}

void ProcessSectionRaylib(ProcBox &procBoxObj)
{
    Rectangle processSection = {730, 460, 1170, 550};

    int borderThickness = 4;

    // // // section's style colors
    Color backgroundClr = {0, 0, 0, 255}, sectionBorderColor = {135, 103, 38, 255};

    DrawRectangleRec(processSection, backgroundClr);
    DrawRectangleLinesEx(processSection, borderThickness, sectionBorderColor);

    int lineHeight = 20;
    int maxVisible = processSection.height / lineHeight;

    float wheel = GetMouseWheelMove();
    if (wheel != 0) procBoxObj.scrollOffset -= (int)wheel * 3;
    if (IsKeyDown(KEY_DOWN)) procBoxObj.scrollOffset += 2;
    if (IsKeyDown(KEY_UP)) procBoxObj.scrollOffset -= 2;


    std::vector<ProcessInfo> localCopy;
    {
        std::lock_guard<std::mutex> lock(procBoxObj.procMutex);
        localCopy = procBoxObj.processes;
    }


    if (procBoxObj.scrollOffset < 0) procBoxObj.scrollOffset = 0;
    if (procBoxObj.scrollOffset > (int)localCopy.size() - maxVisible)
        procBoxObj.scrollOffset = std::max(0, (int)localCopy.size() - maxVisible);


    int y = processSection.y + 10;
    for (int i = procBoxObj.scrollOffset;
         i < localCopy.size() && i < procBoxObj.scrollOffset + maxVisible; i++) {
        std::string line = std::to_string(localCopy[i].pid) + " \t " +
                           localCopy[i].processName + " \t " +
                           localCopy[i].processCommand + "\t  " +
                           localCopy[i].currentProcessMEMString;

        DrawText(line.c_str(), processSection.x + 10, y, 25, RAYWHITE);
        y += lineHeight;
    }
}
void NetworkSectionRaylib()
{
    Rectangle networkSection = {30, 30, 400, 400};
    int borderThickness = 4;
    // // // section's style colors
    Color backgroundClr = {0, 0, 0, 255}, sectionBorderColor = {158, 168, 5, 255};

    DrawRectangleRec(networkSection, backgroundClr);
    DrawRectangleLinesEx(networkSection, borderThickness, sectionBorderColor);
}
void TerminateSectionRaylib()
{
    Rectangle TerminateSection = {30, 700, 470, 400};
    int borderThickness = 4;

    // // // section's style colors
    Color backgroundClr = {0, 0, 0, 255}, sectionBorderColor = {73, 14, 125, 255};

    DrawRectangleRec(TerminateSection, backgroundClr);
    DrawRectangleLinesEx(TerminateSection, borderThickness, sectionBorderColor);
}