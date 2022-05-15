#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

void err_sys(const char* x) 
{ 
    perror(x); 
    exit(1); 
}

#define read_lock(fd, offset, whence, len) \
    lock_reg((fd), F_SETLK, F_RDLCK, (offset), (whence), (len))
#define readw_lock(fd, offset, whence, len) \
    lock_reg((fd), F_SETLKW, F_RDLCK, (offset), (whence), (len))
#define write_lock(fd, offset, whence, len) \
    lock_reg((fd), F_SETLK, F_WRLCK, (offset), (whence), (len))
#define writew_lock(fd, offset, whence, len) \
    lock_reg((fd), F_SETLKW, F_WRLCK, (offset), (whence), (len))
#define unlock(fd, offset, whence, len) \
    lock_reg((fd), F_SETLK, F_UNLCK, (offset), (whence), (len))

int lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len)
{
    struct flock lock;
    lock.l_type = type;
    lock.l_start = offset;
    lock.l_whence = whence;
    lock.l_len = len;

    return fcntl(fd, cmd, &lock);
}

pid_t lock_test(int fd, int type, off_t offset, int whence, off_t len) {
    struct flock lock;
    lock.l_type = type;
    lock.l_start = offset;
    lock.l_whence = whence;
    lock.l_len = len;

    if(fcntl(fd, F_GETLK, &lock) < 0) {
        err_sys("fcntl error");
    }
    if(lock.l_type == F_UNLCK) {
        puts("no lock");
        return 0;
    }

    return lock.l_pid;
}

int main() {
    int fd = open("test.txt", O_RDONLY);
    int res = lock_test(fd, O_RDONLY, 0, SEEK_SET, 100);

    printf("lock_test: %d\n", res);
    
}
