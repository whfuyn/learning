#include "../fy.h"
#include <sys/stat.h>
#include <unistd.h>

char buf1[] = "abcdefghij";
char buf2[] = "1234567890";

int main() {
    int fd = open("ex36.test", O_RDWR | O_CREAT | O_TRUNC | O_APPEND, S_IRUSR | S_IWUSR);
    if(fd == -1) panic("cannot create file");

    if(write(fd, buf1, 10) != 10) panic("failed to write data");

    if(lseek(fd, 0, SEEK_SET) == -1) panic("failed to lseek");

    // notice that \0
    char buf[6] = {0};
    if(read(fd, buf, 5) != 5) panic("failed to read");
    printf("read 0..5: %s\n", buf);

    // This lseek is unneccessary, but to answer the question
    if(lseek(fd, 5, SEEK_SET) == -1) panic("failed to lseek");
    if(write(fd, buf2, 5) != 5) panic("failed to write");

    if(lseek(fd, 5, SEEK_SET) == -1) panic("failed to lseek");
    if(read(fd, buf, 5) != 5) panic("failed to read");
    printf("read 5..10: %s\n", buf);

    if(lseek(fd, -5, SEEK_END) == -1) panic("failed to lseek");
    if(read(fd, buf, 5) != 5) panic("failed to read");
    printf("read 10..15: %s\n", buf);

    // read 0..5: abcde
    // read 5..10: fghij
    // read 10..15: 12345
}
