#include "types.h"
#include "user.h"
#include "mystdio.h"

int main(int argc, char *argv[]) {
    printf(1, "hello world\n");


    FILE *fp = myfopen("test.txt", 'w');
    printf(1, "no errors in myfopen\n");

    if (fp == NULL) {
        printf(1, "error in myfopen\n");
        exit();
    }

    myfprintf(fp, "Hello, world!");
    printf(1, "no errors in myfprintf\n");

    myfclose(fp);
    printf(1, "no errors in myfclose\n");

    exit();
}