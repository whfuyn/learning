#include "../fy.h"
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    if (lseek(STDIN_FILENO, SEEK_CUR, 0) == -1) {
        puts("cannot seek");
    }
    else {
        puts("seek ok");
    }
}
