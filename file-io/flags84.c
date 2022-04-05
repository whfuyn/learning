#include "../fy.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

void print_flag(int fd) {
    int fd_flag = fcntl(fd, F_GETFD);
    if(fd_flag == -1) panic("cannot get fd");
    
    printf("fd: %d\n", fd);
    printf("fd flag is 0%o\n", fd_flag);

    if(fd_flag & FD_CLOEXEC) {
        puts("close on exec");
    }

    int file_flag = fcntl(fd, F_GETFL);
    if(file_flag == -1) panic("cannot get file flag");
    printf("file flag is 0%o\n", file_flag);

    int access_mode = file_flag & O_ACCMODE;

    switch(access_mode) {
        case O_RDONLY:
            puts("read only");
            break;
        case O_WRONLY:
            puts("write only");
            break;
        case O_RDWR:
            puts("read write");
            break;
        default:
            panic("unexpected file flag");
    }

    if(file_flag & O_APPEND) {
        puts("append mode");
    }
    if(file_flag & O_SYNC) {
        puts("synchronouse writes");
    }

    puts("------------");
}

int dup_cloexec(int fd) {
    // hmm, seems that F_DUPFD_CLOEXEC is not defined on WSL2
    // fcntl(fd, F_DUPFD_CLOEXEC, 0);

    int fd2 = fcntl(fd, F_DUPFD, 0);
    if(fd2 == -1) panic("cannot dup fd");
    int prev_flag = fcntl(fd2, F_GETFD);
    if(prev_flag == -1) panic("cannot get fd flag");

    if(fcntl(fd2, F_SETFD, prev_flag | FD_CLOEXEC) == -1) {
        panic("cannot set CLOEXEC");
    };
    return fd2;
}

void clean_append_and_cloexec(int fd) {
    int prev_fd_flag = fcntl(fd, F_GETFD);
    int prev_file_flag = fcntl(fd, F_GETFL);

    if(prev_fd_flag == -1 || prev_file_flag == -1) panic("cannot get fd flag or file flag");

    // &~ IS NOT xor, because xor will turn on the bit flags if it's already off.
    if(fcntl(fd, F_SETFD, prev_fd_flag & ~FD_CLOEXEC) == -1) {
        panic("cannot set fd flag");
    };

    if(fcntl(fd, F_SETFL, prev_file_flag & ~O_APPEND) == -1) {
        panic("cannot set file flag");
    };
}

int main(){
    int fd1 = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, S_IRUSR | S_IWUSR);
    if(fd1 == -1) panic("cannot open fd1");
    int fd2 = dup(fd1);
    if(fd2 == -1) panic("cannot open fd2");
    int fd3 = dup_cloexec(fd2);

    print_flag(STDIN_FILENO);
    print_flag(STDOUT_FILENO);
    print_flag(STDERR_FILENO);

    print_flag(fd1);
    print_flag(fd2);
    print_flag(fd3);
    clean_append_and_cloexec(fd3);
    puts("after clean append and cloexec for the last fd");
    print_flag(fd3);
}
