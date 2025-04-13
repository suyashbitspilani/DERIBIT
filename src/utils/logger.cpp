#include "logger.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <mutex>

namespace {
    std::mutex logMutex;
    std::ofstream logFile;
}

void Logger::init() {
    logFile.open("deribot.log", std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "⚠️ Failed to open log file!" << std::endl;
    }
}

void Logger::info(const std::string& message) {
    std::lock_guard<std::mutex> lock(logMutex);
    std::time_t now = std::time(nullptr);
    std::cout << "[INFO] " << std::ctime(&now) << ": " << message << std::endl;
    if (logFile.is_open()) {
        logFile << "[INFO] " << std::ctime(&now) << ": " << message << std::endl;
    }
}

void Logger::error(const std::string& message) {
    std::lock_guard<std::mutex> lock(logMutex);
    std::time_t now = std::time(nullptr);
    std::cerr << "[ERROR] " << std::ctime(&now) << ": " << message << std::endl;
    if (logFile.is_open()) {
        logFile << "[ERROR] " << std::ctime(&now) << ": " << message << std::endl;
    }
}

void Logger::debug(const std::string& message) {
#ifdef DEBUG
    std::lock_guard<std::mutex> lock(logMutex);
    std::time_t now = std::time(nullptr);
    std::cout << "[DEBUG] " << std::ctime(&now) << ": " << message << std::endl;
    if (logFile.is_open()) {
        logFile << "[DEBUG] " << std::ctime(&now) << ": " << message << std::endl;
    }
#endif
}
