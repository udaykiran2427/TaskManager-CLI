#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>
#include <iostream>
#include <iomanip>

// Function to list all running processes along with their memory usage
void listProcesses()
{
    // Take a snapshot of all processes in the system
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE)
    {
        std::cerr << "Failed to take process snapshot." << std::endl;
        return;
    }

    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    // Print table headers
    std::wcout << std::left << std::setw(10) << L"PID"
               << std::setw(30) << L"Process Name"
               << std::setw(15) << L"Memory Usage (KB)" << std::endl;
    std::wcout << L"------------------------------------------------------\n";

    // Retrieve information about the first process in the snapshot
    if (Process32First(hSnapshot, &pe32))
    {
        do
        {
            // Open the process to retrieve its memory usage
            HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pe32.th32ProcessID);
            SIZE_T memoryUsage = 0;

            if (hProcess)
            {
                PROCESS_MEMORY_COUNTERS pmc;
                if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc)))
                {
                    memoryUsage = pmc.WorkingSetSize / 1024; // Convert bytes to KB
                }
                CloseHandle(hProcess);
            }

            // Print process details
            std::wcout << std::left << std::setw(10) << pe32.th32ProcessID
                       << std::setw(30) << pe32.szExeFile
                       << std::setw(15) << memoryUsage << std::endl;
        } while (Process32Next(hSnapshot, &pe32)); // Iterate through all processes
    }
    else
    {
        std::cerr << "Failed to retrieve processes" << std::endl;
    }

    CloseHandle(hSnapshot); // Release the snapshot handle
}

// Function to terminate a process by its PID
bool killProcess(DWORD pid)
{
    // Open the process with termination rights
    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
    if (!hProcess)
    {
        std::cerr << "Failed to open process " << pid << std::endl;
        return false;
    }

    // Attempt to terminate the process
    if (!TerminateProcess(hProcess, 0))
    {
        std::cerr << "Failed to terminate process " << pid << std::endl;
        CloseHandle(hProcess);
        return false;
    }

    CloseHandle(hProcess); // Close process handle
    std::cout << "Successfully terminated process " << pid << std::endl;
    return true;
}
