#include "logger.h"

int main(void)
{
    logger_init("test.log", LEVEL_FATAL);

    log_info("this is not it %s", "sike");

    logger_close();
}
