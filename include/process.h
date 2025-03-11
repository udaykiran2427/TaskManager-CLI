#ifndef PROCESS_H
#define PROCESS_H

#include <windows.h>

// Function to list running processes
void listProcesses();

// Function to kill a process by PID
bool killProcess(DWORD pid);

#endif // PROCESS_H
