#include "logger.h"
#include <time.h>
#include <stdarg.h>

static struct logger libchow_logger;
static volatile int logger_initalized = 0;

/*
 * Initialize the logger struct with the given filename and logging level
 *
 * @param filename    the filename to open for writing
 * @param log_level   the maxmium logging level
 * @return LOG_RC_SUCCESS if successful, error code otherwise
*/
enum logger_rc logger_init(const char *filename, enum log_level log_level)
{
    if (logger_initalized) {
        return LOG_RC_SUCCESS;
    }

    FILE *fp = fopen(filename, "a");
    if (fp == NULL) {
        return LOG_RC_ERR_FILE_NOT_OPEN;
    }

    if (log_level <= UNKNOWN_LEVEL || log_level >= NUM_LOG_LEVEL) {
        fclose(fp);
        return LOG_RC_ERR_INVALID_LVL;
    }

    libchow_logger.fp = fp;
    libchow_logger.lvl_log = log_level;
    logger_initalized = 1;

    return LOG_RC_SUCCESS;
}

/*
 * Set log level of the libchow_logger
 *
 * @param log_level   the maxmium logging level
 * @return LOG_RC_SUCCESS if successful, error code otherwise
*/
enum logger_rc logger_set_level(enum log_level log_level)
{
    if (log_level <= UNKNOWN_LEVEL || log_level >= NUM_LOG_LEVEL) {
        return LOG_RC_ERR_INVALID_LVL;
    }

    libchow_logger.lvl_log = log_level;

    return LOG_RC_SUCCESS;
}
static void get_timestamp(char *buffer, int buf_size)
{
    time_t curr_time = time(NULL);
    struct tm *curr_tm = localtime(&curr_time);
    strftime(buffer, buf_size, "%c", curr_tm);

    return;
}

static char *log_level_to_str(enum log_level log_level)
{
    switch (log_level) {
        case LEVEL_TRACE:
            return "TRACE";
        case LEVEL_DEBUG:
            return "DEBUG";
        case LEVEL_INFO:
            return "INFO";
        case LEVEL_WARN:
            return "WARN";
        case LEVEL_ERROR:
            return "ERROR";
        case LEVEL_FATAL:
            return "FATAL";
        default:
            return "UNKNOWN";
    }
}

/*
 * Insert log message to file stream
 *
 * @param log_level   the maxmium logging level
 * @param fmt         the format string
 * @param ...         optional arguments for fmt
 * @return LOG_RC_SUCCESS if successful, error code otherwise
*/
#define MAX_TIMESTAMP 100
#define MAX_LOG_MSG 2048
#define MAX_LOG_OUTPUT 4096
enum logger_rc logger_log(enum log_level log_level, const char *fmt, ...)
{
    if (!logger_initalized) {
        return LOG_RC_ERR_UNINITIALIZED;
    }
    if (log_level <= UNKNOWN_LEVEL || log_level > libchow_logger.lvl_log) {
        return LOG_RC_ERR_INVALID_LVL;
    }

    va_list v_args;
    char output_msg[MAX_LOG_OUTPUT];
    char log_msg[MAX_LOG_MSG];
    size_t written;

    char timestamp[MAX_TIMESTAMP];
    get_timestamp(timestamp, MAX_TIMESTAMP);

    va_start(v_args, fmt);
    vsnprintf(log_msg, sizeof(log_msg), fmt, v_args);
    va_end(v_args);

    written = snprintf(output_msg, sizeof(output_msg), "[%s] - [%s] : %s\n", timestamp, log_level_to_str(log_level), log_msg);
    fwrite(output_msg, 1, written, libchow_logger.fp);
    fflush(libchow_logger.fp);

    return LOG_RC_SUCCESS;
}

/*
 * Cleanup struct logger
*/
void logger_close()
{
    if (!logger_initalized) {
        return;
    }

    if (libchow_logger.fp != NULL) {
        fclose(libchow_logger.fp);
    }
    libchow_logger.lvl_log = UNKNOWN_LEVEL;

    return;
}
