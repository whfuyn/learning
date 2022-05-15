#include "../fy.h"
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    struct stat st;

    for(int i = 1; i < argc; i++) {
        const char* path = argv[i];
        int ret = lstat(path, &st);
        if(ret < 0) {
            panic("failed to read file stat");
        }
        
        mode_t ty = st.st_mode;

        if(S_ISREG(ty)) {
            printf("\"%s\" is a regular file.", path);
        }
        if(S_ISDIR(ty)) {
            printf("\"%s\" is a directory.", path);
        }
        if(S_ISCHR(ty)) {
            printf("\"%s\" is a char special file.", path);
        }
        if(S_ISBLK(ty)) {
            printf("\"%s\" is a block special file.", path);
        }
        if(S_ISFIFO(ty)) {
            printf("\"%s\" is a pipe or FIFO.", path);
        }
        if(S_ISLNK(ty)) {
            printf("\"%s\" is a symbolic link.", path);
        }
        if(S_ISSOCK(ty)) {
            printf("\"%s\" is a socket.", path);
        }
        if(ty & S_ISUID) {
            printf("\"%s\" is a set-user-id file.", path);
        }
        if(ty & S_ISGID) {
            printf("\"%s\" is a set-group-id file.", path);
        }
        if(S_TYPEISMQ(&st)) {
            printf("\"%s\" is a message queue.", path);
        }
        if(S_TYPEISSEM(&st)) {
            printf("\"%s\" is a semaphore.", path);
        }
        if(S_TYPEISSHM(&st)) {
            printf("\"%s\" is a shared memory object.", path);
        }
        puts("");
    }
    puts("done!");
}



