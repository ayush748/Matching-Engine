#pragma once
#include <fstream>
#include <mutex>
#include <string>

class Logger {
private:
    std::mutex mtx;
    std::ofstream logFile;
public:
    Logger(const std::string& filename) {
        logFile.open(filename, std::ios::app);
    }
    ~Logger() {
        logFile.close();
    }
    void log(const std::string& msg) {
        std::lock_guard<std::mutex> lock(mtx);
        logFile << msg << std::endl;
    }
};
