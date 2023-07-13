#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

enum logger_rc {
    LOG_RC_ERR_INVALID_LVL,
    LOG_RC_ERR_FILE_NOT_OPEN,
    LOG_RC_ERR_UNINITIALIZED,
    LOG_RC_SUCCESS,
};

enum log_level {
    UNKNOWN_LEVEL,
    LEVEL_TRACE,
    LEVEL_DEBUG,
    LEVEL_INFO,
    LEVEL_WARN,
    LEVEL_ERROR,
    LEVEL_FATAL,

    NUM_LOG_LEVEL,
};

struct logger {
    FILE *fp;
    enum log_level lvl_log;
};

#define log_trace(fmt, ...) logger_log(LEVEL_TRACE, fmt, ##__VA_ARGS__)
#define log_debug(fmt, ...) logger_log(LEVEL_DEBUG, fmt, ##__VA_ARGS__)
#define log_info(fmt, ...)  logger_log(LEVEL_INFO, fmt, ##__VA_ARGS__)
#define log_warn(fmt, ...)  logger_log(LEVEL_WARN, fmt, ##__VA_ARGS__)
#define log_error(fmt, ...) logger_log(LEVEL_ERROR, fmt, ##__VA_ARGS__)
#define log_fatal(fmt, ...) logger_log(LEVEL_FATAL, fmt, ##__VA_ARGS__)

enum logger_rc logger_init(const char *filename, enum log_level log_level);
enum logger_rc logger_set_level(enum log_level log_level);
enum logger_rc logger_log(enum log_level log_level, const char *fmt, ...);
void logger_close();

#endif
