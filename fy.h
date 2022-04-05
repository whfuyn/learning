#ifndef FY_HEADER_H
#define FY_HEADER_H

#include <stdio.h>
#include <stdlib.h>

void panic(const char *msg) {
    perror(msg);
    exit(-1);
}

#endif // FY_HEADER_H
