#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    if(argc != 2){
        // 2 is fd(standard error info)
        fprintf(2, "Usage: pause for a user-specified number of ticks...\n");
        exit(1);
}
    int i = atoi(argv[1]);
    sleep(i);
    exit(0);
}