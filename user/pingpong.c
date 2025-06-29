#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int p_f[2]; // 父进程管道
    pipe(p_f);
    int p_c[2]; // 子进程管道
    pipe(p_c);

    int pid = fork();
    
    // 父进程
    if(pid > 0) {
        char buf_p[16] = {0};
        write(p_f[1], "parent", 6);
        close(p_f[1]);
        wait(0);
        read(p_c[0], buf_p, sizeof(buf_p));
        close(p_c[0]);
        printf("%d: received pong\n", getpid());
    }
    // 子进程 
    else if(pid == 0) {
        char buf_c[16] = {0};
        write(p_c[1], "child", 5);
        close(p_c[1]);
        read(p_f[0], buf_c, sizeof(buf_c));
        close(p_f[0]);
        printf("%d: received ping\n", getpid());
    } 
    else {
        printf("fork error\n");
    }
    exit(0);
}