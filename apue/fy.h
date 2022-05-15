#ifndef FY_HEADER_H
#define FY_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

void panic(const char *msg) {
    perror(msg);
    exit(-1);
}

int dbg(int v) {
    printf("%o\n", v);
    return v;
}

// caveat: cannot change O_SYNC O_DSYNC
void set_fl(int fd, int flag) {
    int prev_fl = fcntl(fd, F_GETFL);
    if(prev_fl == -1) {
        printf("cannot get previous flag of `%d` for set_fl `%o`: ", fd, flag);
        panic("");
    }

    if(fcntl(fd, F_SETFL, prev_fl | flag) == -1) {
        printf("cannot set flag of `%d` for set_fl `%o`", fd, flag);
        panic("");
    }
}

void clr_fl(int fd, int flag) {
    int prev_fl = fcntl(fd, F_GETFL);
    if(prev_fl == -1) {
        printf("cannot get previous flag of `%d` for set_fl `%o`: ", fd, flag);
        panic("");
    }

    if(fcntl(fd, F_SETFL, prev_fl & ~flag) == -1) {
        printf("cannot set flag of `%d` for set_fl `%o`", fd, flag);
        panic("");
    }
}

#endif // FY_HEADER_H
