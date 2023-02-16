#ifndef MYSTDIO_H
#define MYSTDIO_H

#define BUFF_SIZE 4096
#define NULL 0L

typedef struct FILE {
    int fd;
    char mode;
    long long pos;
    char buffer[BUFF_SIZE];
} FILE;

// extern FILE * mystdout;

FILE * myfopen(const char *path, char mode);
void myfclose(FILE *fp);
void myfprintf(FILE *fp, const char* s, ...);

#endif