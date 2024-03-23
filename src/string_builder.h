#ifndef STRING_BUILDER_H_
#define STRING_BUILDER_H_

#include <stddef.h>
#include <string.h>

#include "dynamic_array.h"

typedef struct {
    char *items;
    size_t count;
    size_t capacity;
} String_Builder;

#define SB_Fmt "%.*s"
#define SB_Arg(sb) (int) (sb).count, (sb).items

#define sb_append_buf da_append_many
#define sb_append_cstr(sb, cstr) \
    do {                         \
        const char *s = (cstr);  \
        size_t n = strlen(s);    \
        sb_append_buf(sb, s, n); \
    } while(0)

#endif // STRING_BUILDER_H_
