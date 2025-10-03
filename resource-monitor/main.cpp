#include <iostream>
#include "raylib.h"
#include <cstdlib>
#include <csignal>

#include "cpu.hpp"
#include "proc.hpp"
#include "network.hpp"
#include "myFunctions.hpp"

// int main()
// {

//     CpuBox cpuBoxObj;      // // cpu section's class obj
//     ProcBox procBoxObj;    // // process section's class obj
//     NetworkBox networkObj; // // network section's class obj

//     while (true)
//     {
//         // // //  ==========cpu section==========

//
//
//

//         // // // ========== process section==========
//         std::vector<ProcessInfo> test = procBoxObj.ProcessCollection();

//         // // //  ==========network section==========
//         std::string download = networkObj.Download();
//         std::string upload = networkObj.Upload();

//         myCustomSleep(1);
//     }

//     return 0;
// }
void TerminateProcessByPID(int pid)
{
    if (pid > 0)
    {
        int result = kill(pid, SIGTERM);
        if (result == 0)
            printf("Process %d terminated successfully\n", pid);
        else
            printf("Failed to terminate process %d\n", pid);
    }
}

int main()
{
    CpuBox cpuBoxObj;      // // cpu section's class obj
    ProcBox procBoxObj;    // // process section's class obj
    NetworkBox networkObj; // // network section's class obj
    procBoxObj.StartUpdating();

    InitWindow(1920, 1080, "Hello world");

    // // // section's style colors
    Color backgroundClr = {0, 0, 0, 255};
    SetTargetFPS(60);

    std::string pidInput = "";
    bool enterPressed = false;

    while (!WindowShouldClose())
    {

        int key = GetCharPressed();
        while (key > 0)
        {
            if (key >= '0' && key <= '9')
            {
                pidInput.push_back((char)key);
            }
            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE) && !pidInput.empty())
        {
            pidInput.pop_back();
        }

        if (IsKeyPressed(KEY_BACKSPACE) && !pidInput.empty())
        {
            pidInput.pop_back();
        }

        if ((IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER)) && !pidInput.empty())
        {
            // int pid = std::stoi(pidInput);
            // TerminateProcessByPID(pid);
            // pidInput.clear();
                printf("ENTER pressed, input = '%s'\n", pidInput.c_str());
    int pid = std::stoi(pidInput);
    printf("Trying to terminate PID %d\n", pid);
    TerminateProcessByPID(pid);
    pidInput.clear();
        }

        BeginDrawing();
        ClearBackground(backgroundClr);

        CpuSectionRaylib(cpuBoxObj);

        ProcessSectionRaylib(procBoxObj);
        // NetworkSectionRaylib();

        // TerminateSectionRaylib();

        DrawRectangle(50, 600, 300, 40, LIGHTGRAY);
        DrawText(pidInput.c_str(), 60, 610, 20, BLACK);
        DrawText("Enter PID to terminate:", 50, 570, 20, RAYWHITE);

        EndDrawing();
    }
    procBoxObj.StopUpdating();

    CloseWindow();
    return 0;
}

// int main()
// {

// 	CpuBox cpuBoxObj;   // // cpu section's class obj
// 	ProcBox procBoxObj; // // process section's class obj
// 	NetworkBox networkObj;

// 	while (true)
// 	{
// 		std::cout << "\033[2J\033[1;1H";

// 		cpuBoxObj.UptimeSecToMin_Hour(); // //displays only uptime

// 		cpuBoxObj.BatteryPercentage(); // //for Battery Percentage
// 		cpuBoxObj.CpuModelName();      // //for display only Cpu Model Name
// 		cpuBoxObj.FullCpuUsage();

// 		cpuBoxObj.PerCoreUsage();
// 		procBoxObj.ProcessCollection();
// 		networkObj.Download();

//         int pid  ;
//         std::cin >> pid;
//         TerminateProcessByPID(pid);

// 		myCustomSleep(1);
// 	}

// 	return 0;
// }