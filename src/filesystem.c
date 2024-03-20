#include "filesystem.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

char *slurp_file(const char *file_path)
{
    char *buf = NULL;
    FILE *f = NULL;

    f = fopen(file_path, "r");
    if(f == NULL) goto defer;
    if(fseek(f, 0, SEEK_END) < 0) goto defer;

    long size = ftell(f);
    if(size < 0) goto defer;

    // size should be equal to the files length
    buf = malloc(size + 1);
    if(buf == NULL) goto defer;

    if(fseek(f, 0, SEEK_SET) < 0) goto defer;

    fread(buf, 1, size, f);
    if(ferror(f)) goto defer;

    buf[size] = '\0';

    if(f) {
        fclose(f);
        errno = 0;
    }
    return buf;

defer:
    if(f) {
        int serr = errno;
        fclose(f);
        errno = serr;
    }
    if(buf) {
        free(buf);
    }

    return NULL;
}

