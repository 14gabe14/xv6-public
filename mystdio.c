#include "mystdio.h"
#include "types.h"
#include "user.h"

// FILE *mystdout = NULL;

static void myputc(FILE *fp, char c);

static void myfflush(FILE *fp);

static void myprintint(FILE* fp, int xx, int base, int sgn);

FILE * myfopen(const char *path, char mode) {
    int fd = open(path, mode);

    if (fd < 0) {
        return NULL;
    }

    //Create a FILE structure
    FILE * fp = (FILE *) malloc(sizeof(FILE));

    if (fp == NULL) {
        return NULL;
    }

    fp->fd = fd;
    fp->mode = mode;
    fp->pos = 0;

    return fp;
}

void myfclose(FILE *fp) {
    myfflush(fp);
    close(fp->fd);
    free(fp);
}

void myfprintf(FILE *fp, const char* s, ...) {
    char *str;
    int c, i, state;
    uint *ap;

    state = 0;
    ap = (uint*)(void*)&s + 1;
    for(i = 0; s[i]; i++){
        c = s[i] & 0xff;
        if(state == 0){
        if(c == '%'){
            state = '%';
        } else {
            myputc(fp, c);
        }
        } else if(state == '%'){
        if(c == 'd'){
            myprintint(fp, *ap, 10, 1);
            ap++;
        } else if(c == 'x' || c == 'p'){
            myprintint(fp, *ap, 16, 0);
            ap++;
        } else if(c == 's'){
            str = (char*)*ap;
            ap++;
            if(str == 0)
            str = "(null)";
            while(*str != 0){
            myputc(fp, *str);
            str++;
            }
        } else if(c == 'c'){
            myputc(fp, *ap);
            ap++;
        } else if(c == '%'){
            myputc(fp, c);
        } else {
            // Unknown % sequence.  Print it to draw attention.
            myputc(fp, '%');
            myputc(fp, c);
        }
        state = 0;
        }
    }

    myfflush(fp);
}

static void myputc(FILE *fp, char c)
{
    printf(1, "no errors so far line 89\n");
    fp->buffer[fp->pos] = c;
    printf(1, "no errors so far line 90\n");
    fp->pos++;
    printf(1, "no errors so far line 92\n");
    if (fp->pos == BUFF_SIZE) {
        printf(1, "no errors so far line 94\n");
        myfflush(fp);
        printf(1, "no errors so far line 96\n");
    }

    write(fp->fd, &c, 1);
    printf(1, "no errors so far line 100\n");
}

static void myfflush(FILE *fp) {
    write(fp->fd, fp->buffer, fp->pos);
    fp->pos = 0;
}


static void myprintint(FILE* fp, int xx, int base, int sgn)
{
    static char digits[] = "0123456789ABCDEF";
    char buf[16];
    int i, neg;
    uint x;

    neg = 0;
    if(sgn && xx < 0){
        neg = 1;
        x = -xx;
    } else {
        x = xx;
    }

    i = 0;
    do{
        buf[i++] = digits[x % base];
    } while((x /= base) != 0);
    if(neg)
        buf[i++] = '-';

    while(--i >= 0)
        myputc(fp, buf[i]);
}