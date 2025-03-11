#include <iostream>
#include "process.h"
#include "system.h"

int main()
{
    int choice;
    DWORD pid;

    while (true)
    {
        std::cout << "\nTask Manager CLI\n";
        std::cout << "1. List Processes\n";
        std::cout << "2. Kill a Process\n";
        std::cout << "3. Show CPU & RAM Usage\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            listProcesses();
            break;
        case 2:
            std::cout << "Enter PID to kill: ";
            std::cin >> pid;
            killProcess(pid);
            break;
        case 3:
            std::cout << "CPU Usage: " << getCpuUsage() << "%\n";
            std::cout << "Available RAM: " << getAvailableRAM() << " MB\n";
            break;
        case 4:
            return 0;
        default:
            std::cout << "Invalid choice, try again!\n";
        }
    }

    return 0;
}
