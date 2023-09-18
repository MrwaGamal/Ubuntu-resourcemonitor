#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/statvfs.h>
#include <sys/sysinfo.h>
#include <iomanip>
#include <sstream>
#include <cstring>
#include <ctime>

// Function to get CPU usage percentage
double getCPUUsage() {
    double total = 0.0, idle = 0.0;
    std::ifstream stat("/proc/stat");
    std::string line;

    if (std::getline(stat, line)) {
        std::istringstream ss(line);
        ss.ignore(5);  // Skip "cpu" prefix
        for (double val; ss >> val;)
            total += val;
        idle = total;  // Initial idle value
        idle -= total; // New idle value
    }

    stat.close();
    return 100.0 - (idle / total * 100.0);
}

// Function to get memory usage
double getMemoryUsage() {
    struct sysinfo info;
    sysinfo(&info);
    long long totalram = info.totalram;
    totalram *= info.mem_unit;
    long long freeram = info.freeram;
    freeram *= info.mem_unit;
    return static_cast<double>(totalram - freeram) / totalram * 100.0;
}

// Function to get disk usage percentage
double getDiskUsage(const std::string& path) {
    struct statvfs data;
    if (statvfs(path.c_str(), &data) != 0)
        return -1.0; // Error

    long long total = static_cast<long long>(data.f_blocks) * data.f_frsize;
    long long free = static_cast<long long>(data.f_bfree) * data.f_frsize;
    return static_cast<double>(total - free) / total * 100.0;
}

int main() {
    while (true) {
        // Get current date and time
        std::time_t t = std::time(nullptr);
        std::tm* timePtr = std::localtime(&t);

        // Print date and time
        std::cout << "Date and Time: ";
        std::cout << std::put_time(timePtr, "%Y-%m-%d %H:%M:%S") << std::endl;

        // Get and print CPU usage
        double cpuUsage = getCPUUsage();
        std::cout << "CPU Usage: " << std::fixed << std::setprecision(2) << cpuUsage << "%" << std::endl;

        // Get and print memory usage
        double memoryUsage = getMemoryUsage();
        std::cout << "Memory Usage: " << std::fixed << std::setprecision(2) << memoryUsage << "%" << std::endl;

        // Specify the disk path you want to monitor (e.g., "/")
        std::string diskPath = "/";
        double diskUsage = getDiskUsage(diskPath);
        if (diskUsage >= 0.0) {
            std::cout << "Disk Usage (" << diskPath << "): " << std::fixed << std::setprecision(2) << diskUsage << "%" << std::endl;
        } else {
            std::cout << "Failed to retrieve disk usage information." << std::endl;
        }

        // Sleep for a few seconds before checking again
        sleep(5); // Sleep for 5 seconds (adjust as needed)
    }

    return 0;
}
