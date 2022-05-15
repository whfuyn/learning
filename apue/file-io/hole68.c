#include "../fy.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

const char buf1[] = "abcdefghij";
const char buf2[] = "ABCDEFGHIJ";

const char buf3[16384] = "abcdefghij";


int main() {
    int fd1 = open("file.hole", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if(fd1 == -1) {
        panic("cannot create file.hole");
    }

    if(write(fd1, buf1, 10) == -1) {
        panic("cannot write file.hole init");
    }

    if(lseek(fd1, 16384, SEEK_SET) == -1) {
        panic("cannot lseek");
    }

    if(write(fd1, buf2, 10) == -1) {
        panic("cannot write file.hole end");
    }

    int fd2 = open("file.nohole", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if(write(fd2, buf3, sizeof(buf3)) == -1) {
        panic("cannot write file.nohole head");
    }
    if(write(fd2, buf2, 10) == -1) {
        panic("cannot write file.nohole end");
    }
}
