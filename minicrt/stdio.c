#include "minicrt.h"

int mini_crt_io_init()
{
    return 1;
}

#ifdef WIN32
#include <Windows.h>






#else

static long open(const char *pathname, int flags, int mode)
{
    long fd = 0;
    asm("movl $5, %%eax   \n\t"
        "movl %1, %%ebx   \n\t"
        "movl %2, %%ecx   \n\t"
        "movl %3, %%edx   \n\t"
        "int $0x80   \n\t"
        "movl %%eax, %0   \n\t" :
        "=m"(fd) : "m"(pathname), "m"(flags), "m"(mode));
}

static long read(long fd, void *buffer, unsigned size)
{
    long ret = 0;
    asm("movl $3, %%eax   \n\t"
        "movl %1, %%ebx   \n\t"
        "movl %2, %%ecx   \n\t"
        "movl %3, %%edx   \n\t"
        "int $0x80   \n\t"
        "movl %%eax, %0   \n\t" :
        "=m"(ret) : "m"(fd), "m"(buffer), "m"(size));
    return ret;
}

static long write(long fd, const void *buffer, unsigned size)
{
    long ret = 0;
    asm("movl $4, %%eax   \n\t"
        "movl %1, %%ebx   \n\t"
        "movl %2, %%ecx   \n\t"
        "movl %3, %%edx   \n\t"
        "int $0x80   \n\t"
        "mov %%eax, %0   \n\t" :
        "=m"(ret) : "m"(fd), "m"(buffer), "m"(size));
    return ret;
}

static long close(long fd)
{
    long ret = 0;
    asm("movl $6, %%eax   \n\t"
        "movl %1, %%ebx   \n\t"
        "int $0x80   \n\t"
        "movl %%eax, %0   \n\t" :
        "=m"(ret) : "m"(fd));
    return ret;
}

static int seek(long fd, int offset, int mode)
{
    int ret = 0;
    asm("movl $19, %%eax   \n\t"
        "movl %1, %%ebx   \n\t"
        "movl %2, %%ecx   \n\t"
        "movl %3, %%edx   \n\t"
        "int $0x80   \n\t"
        "movl %%eax, %0   \n\t" :
        "=m"(ret) : "m"(fd), "m"(offset), "m"(mode));
    return ret;
}

FILE *fopen(const char *filename, const char *mode)
{
    long fd = -1; 
    long flags = 0;
    long access = 00700; // 创建文件的权限

// 来自于 /usr/include/bit/fcntl.h
// 注意: 以0开始的数字是八进制的
#define  O_RDONLY  00
#define  O_WRONLY  01
#define  O_RDWR    02
#define  O_CREAT   0100
#define  O_TRUNC   01000
#define  O_APPEND  02000

    if (strcmp(mode, "w") == 0)
    {
        flags |= O_CREAT | O_WRONLY | O_TRUNC;
    }

    if (strcmp(mode, "w+") == 0)
    {
        flags |= O_CREAT | O_RDWR | O_TRUNC;
    }

    if (strcmp(mode, "r") == 0)
    {
        flags |= O_WRONLY;
    }

    if (strcmp(mode, "r+") == 0)
    {
        flags |= O_CREAT | O_RDWR;
    }

    fd = open(filename, flags, access);

    return (FILE *)fd;
}

long fread(void *buffer, long size, long count, FILE *stream)
{
    return read((long)stream, buffer, size * count);
}

long fwrite(void *buffer, long size, long count, FILE *stream)
{
    return write((long)stream, buffer, size * count);
}

long fclose(FILE *fp)
{
    return close((long)fp);
}

long fseek(FILE *fp, long offset, long set)
{
    return seek((long)fp, offset, set);
}


#endif






