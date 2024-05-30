#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#define MAXARG 32

// 这个lab理解不是很到位，感觉得再看grep.c学

/*在xv6中运行如下命令得到如下输出则为正确
    $ sh < xargstest.sh
    $ $ $ $ $ $ hello
    hello
    hello
    $ $
*/
void main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(2, "usage: xargs command\n");
        exit(1);
    }
    else
    {
        int i = 0;
        int j = argc - 1;
        int start = 0;
        char buf[512];
        char *myargv[MAXARG];
        for(int i = 0; i < argc - 1; i++)
        {
            myargv[i] = argv[i + 1];
            // printf("myargv[%d]: %s\n", i, myargv[i]);
        }
        while(read(0, buf + i, 1) != 0)
        {
            // printf("buf[%d]: %c\n", i, buf[i]);
            if(buf[i] == ' ' || buf[i] == '\n'){
                // printf("im here\n");
                buf[i] = '\0';
                myargv[j] = buf + start;
                // printf("myargv[%d]: %s\n", j, myargv[j]);
                j++;
                start = i + 1;
            }
            i++;
        }
        exec(argv[1], myargv);
    }
    exit(0);
}