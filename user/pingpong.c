#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
/*Write a program that uses UNIX system calls to ''ping-pong'' a byte between two processes
over a pair of pipes, one for each direction. 
The parent should send a byte to the child; 
the child should print "<pid>: received ping", 
where <pid> is its process ID, write the byte on the pipe to the parent, and exit;
the parent should read the byte from the child, print "<pid>: received pong", and exit. 
Your solution should be in the file user/pingpong.c.*/

void
main(){
    int p_f2s[2], p_s2f[2];
    pipe(p_f2s);
    pipe(p_s2f);
    char buf[128];
    int id;
    int pid = fork();
    if(pid == 0){
    // child process
        char send[5] = "pong\n";
        id = getpid();
        close(p_s2f[0]);
        close(p_f2s[1]);
        write(p_s2f[1], send, sizeof(send));
        read(p_f2s[0],buf, sizeof(buf));
        close(p_s2f[1]);
        close(p_f2s[0]);
        printf("%d: received %s", id, buf);
        exit(0);
    } else{
        // parent process
        // printf("%d %d %d %d\n", p_f2s[0], p_f2s[1], p_s2f[0], p_s2f[1]);
        char send[5] = "ping\n";
        id = getpid();
        close(p_f2s[0]);
        close(p_s2f[1]);
        write(p_f2s[1], send, sizeof(send));
        read(p_s2f[0], buf, sizeof(buf));
        wait(0);
        close(p_f2s[1]);
        close(p_s2f[0]);
        printf("%d: received %s", id, buf);
        exit(0);
    }
}