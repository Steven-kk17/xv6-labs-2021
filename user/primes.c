#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void primes(int fd){
    int received_num = 0;
    int is_firstnum = 0;
    int first_num = 0;
    int p[2];
    pipe(p);

    while(read(fd, &received_num, 4) != 0){
        // 保存第一个读到的数，作为要输出的素数
        if(!is_firstnum){
            first_num = received_num;
            is_firstnum = !is_firstnum;
            if(first_num == 0){
                exit(0);
            }
            else printf("prime %d\n", first_num);
        }
    
        if(received_num % first_num != 0){
            // 不整除第一个数，要被pass到下一个进程，所以写入pipe
            write(p[1], &received_num, 4);
        }
    }
    int pid = fork();
    if(pid == 0){
        close(p[1]);
        primes(p[0]);
    } else{
        close(p[0]);
        close(p[1]);
        wait(0);
        exit(0);
    }

}

void
main(){
    int p[2];
    pipe(p);
    for(int i = 2; i <= 35; i++){
        write(p[1], &i, 4);
    }
    close(p[1]);
    primes(p[0]);
    close(p[0]);
    exit(0);
}