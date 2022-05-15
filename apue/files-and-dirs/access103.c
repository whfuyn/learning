#include "../fy.h"
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if(argc != 2) {
        puts("Usage: access <path>");
    }
    const char* path = argv[1];
    if(access(path, R_OK) < 0) {
        printf("access error for %s\n", path);
        perror("");
    } else {
        printf("read access of %s is OK\n", path);
    }
    if(open(path, O_RDONLY) < 0) {
        printf("open error for %s\n", path);
        perror("");
        exit(-1);
    } else {
        printf("open for reading OK\n");
    }

}
