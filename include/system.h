#ifndef SYSTEM_H
#define SYSTEM_H

#include <windows.h>

// Function to get CPU usage percentage
double getCpuUsage();

// Function to get available RAM (in MB)
SIZE_T getAvailableRAM();

#endif // SYSTEM_H
