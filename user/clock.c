#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"

int
main(void)
{
    printf("%d\n", clock() / 1000000000);
    return 0;
}