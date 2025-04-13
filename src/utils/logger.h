#pragma once

#include <string>

class Logger {
public:
    static void init();
    static void info(const std::string& message);
    static void error(const std::string& message);
    static void debug(const std::string& message);
};
// Placeholder for src/utils/logger.h
