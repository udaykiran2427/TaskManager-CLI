#include "system.h"
#include <windows.h>
#include <iostream>
#include <pdh.h>
#include <pdhmsg.h>

// Function to get CPU usage percentage using PDH (Performance Data Helper)
double getCpuUsage()
{
    PDH_HQUERY cpuQuery;
    PDH_HCOUNTER cpuTotal;
    PDH_FMT_COUNTERVALUE counterVal;

    // Open a PDH query to retrieve CPU usage data
    if (PdhOpenQueryW(NULL, 0, &cpuQuery) != ERROR_SUCCESS)
    {
        std::cerr << "Error: Failed to open PDH query.\n";
        return -1;
    }

    // Add a counter for total CPU usage
    if (PdhAddCounterW(cpuQuery, L"\\Processor Information(_Total)\\% Processor Utility", 0, &cpuTotal) != ERROR_SUCCESS)
    {
        std::cerr << "Error: Failed to add PDH counter.\n";
        PdhCloseQuery(cpuQuery);
        return -1;
    }

    // First sample (needed for initialization)
    PdhCollectQueryData(cpuQuery);
    Sleep(1000); // Minimum 1-second delay for accurate reading

    // Second sample (used for calculation)
    PdhCollectQueryData(cpuQuery);
    if (PdhGetFormattedCounterValue(cpuTotal, PDH_FMT_DOUBLE, NULL, &counterVal) != ERROR_SUCCESS)
    {
        std::cerr << "Error: Failed to retrieve CPU usage data.\n";
        PdhCloseQuery(cpuQuery);
        return -1;
    }

    PdhCloseQuery(cpuQuery); // Close the PDH query
    return counterVal.doubleValue;
}

// Function to get available physical RAM in MB
SIZE_T getAvailableRAM()
{
    MEMORYSTATUSEX memStatus;
    memStatus.dwLength = sizeof(memStatus);

    // Retrieve system memory status
    if (GlobalMemoryStatusEx(&memStatus))
    {
        return memStatus.ullAvailPhys / (1024 * 1024); // Convert bytes to MB
    }

    std::cerr << "Error: Failed to retrieve memory status.\n";
    return 0;
}
