#include "logger.h"

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "string_builder.h"

void debug_log(LOG_LEVEL level, const char *fmt, ...)
{
    const char *log_string[] = {
        "[FATAL]: ", "[ERROR]: ", "[WARN]: ",
        "[INFO]: ", "[TRACE]: ",
    };

    va_list args;
    String_Builder log_msg = {0};
    char *msg;
    size_t msg_len;

    sb_append_cstr(&log_msg, log_string[level]);

    va_start(args, fmt);
        msg_len = vsnprintf(0, 0, fmt, args);
    va_end(args);

    msg = malloc(msg_len + 1);
    if(msg == NULL) {
        fprintf(stderr, "[ERROR]: failed to allocate memory: %s", strerror(errno));
        return;
    }

    va_start(args, fmt);
        vsnprintf(msg, msg_len + 1, fmt, args);
    va_end(args);

    sb_append_cstr(&log_msg, msg);
    sb_append_cstr(&log_msg, "\n");
    free(msg);

    fprintf(stderr, SB_Fmt, SB_Arg(log_msg));
}
