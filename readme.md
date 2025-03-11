# Task Manager CLI

A simple command-line-based Task Manager for Windows that allows users to list processes, terminate processes by PID, and monitor CPU & RAM usage.

## Features
- List all running processes along with their memory usage.
- Kill a process by entering its PID.
- Display real-time CPU and available RAM usage.

## Requirements
- Windows OS
- **MinGW with psapi & pdh libraries** or **Microsoft Visual Studio**
- g++ compiler (for MinGW)

## Installation
1. Clone this repository:
   ```sh
   https://github.com/udaykiran2427/TaskManager-CLI.git
   cd TaskManager-CLI
   ```
2. Compile the project using g++ (MinGW) or Visual Studio:
   ```sh
   g++ -Iinclude src/main.cpp src/process.cpp src/system.cpp -o taskmgr.exe -std=c++20 -lpsapi -lpdh
   ```

## Usage
Run the compiled executable:
```sh
./taskmgr.exe
```
### Menu Options:
1. **List Processes** - Displays all running processes with their PID and memory usage.
2. **Kill a Process** - Prompts for a PID and attempts to terminate the process.
3. **Show CPU & RAM Usage** - Displays current CPU usage percentage and available RAM in MB.
4. **Exit** - Exits the program.

## Notes
- Requires administrator privileges to terminate certain processes.
- Uses Windows APIs such as `CreateToolhelp32Snapshot` and `PdhOpenQueryW` for process monitoring.

## License
MIT License.

