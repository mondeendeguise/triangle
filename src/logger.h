#ifndef LOGGER_H_
#define LOGGER_H_

// Uncomment any of the following to mute respective logger output:

//#define LOG_SILENCE_FATAL
//#define LOG_SILENCE_ERROR
//#define LOG_SILENCE_WARN
//#define LOG_SILENCE_INFO
//#define LOG_SILENCE_TRACE

#ifdef _BUILD_RELEASE

    #ifndef LOG_SILENCE_INFO
    #define LOG_SILENCE_INFO
    #endif // LOG_SILENCE_INFO
    
    #ifndef LOG_SILENCE_TRACE
    #define LOG_SILENCE_TRACE
    #endif // LOG_SILENCE_TRACE

#endif // _BUILD_RELEASE

typedef enum {
    LOG_LEVEL_FATAL = 0,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_WARN,
    LOG_LEVEL_INFO,
    LOG_LEVEL_TRACE,
} LOG_LEVEL;

void debug_log(LOG_LEVEL level, const char *fmt, ...);

#ifdef LOG_SILENCE_FATAL
#define LOG_FATAL(fmt, ...)
#else
#define LOG_FATAL(fmt, ...) debug_log(LOG_LEVEL_FATAL, fmt, ##__VA_ARGS__)
#endif

#ifdef LOG_SILENCE_ERROR
#define LOG_ERROR(fmt, ...)
#else
#define LOG_ERROR(fmt, ...) debug_log(LOG_LEVEL_ERROR, fmt, ##__VA_ARGS__)
#endif

#ifdef LOG_SILENCE_WARN
#define LOG_WARN(fmt, ...)
#else
#define LOG_WARN(fmt, ...) debug_log(LOG_LEVEL_WARN, fmt, ##__VA_ARGS__)
#endif

#ifdef LOG_SILENCE_INFO
#define LOG_INFO(fmt, ...)
#else
#define LOG_INFO(fmt, ...) debug_log(LOG_LEVEL_INFO, fmt, ##__VA_ARGS__)
#endif

#ifdef LOG_SILENCE_TRACE
#define LOG_TRACE(fmt, ...)
#else
#define LOG_TRACE(fmt, ...) debug_log(LOG_LEVEL_TRACE, fmt, ##__VA_ARGS__)
#endif

#endif // LOGGER_H_
