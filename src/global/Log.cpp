#include "global/Log.hpp"

const char* Log::getLogPrefix(LogLevel level)
{
    switch(level) {
    case Log::LOG_LEVEL_INFO:
        return "\e[36m[INF] ";
    case Log::LOG_LEVEL_DEBUG:
        return "\e[32m[DBG] ";
    case Log::LOG_LEVEL_WARNING:
        return "\e[33m[WRN] ";
    case Log::LOG_LEVEL_ERROR:
        return "\e[33m[ERR] ";
    default:
        return "\e[31m[FTL] ";
    }
}

void Log::log(const char* file, int line, LogLevel level, const char* message)
{
    const char* prefix = getLogPrefix(level);
    std::cerr << prefix << file << ":" << line << "\t\t" << message << "\e[0m" << std::endl;
}
