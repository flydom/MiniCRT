#ifndef __MINI_CRT_H__
#define __MINI_CRT_H__

#ifdef __cplusplus
extern "C" {
#endif


// malloc
#ifndef NULL
#define NULL (0)
#endif

void free(void *ptr);
void *malloc(unsigned size);
static long brk(void *end_data_segment);
int mini_crt_heap_init();


// ×Ö·û´®
char* itoa(long n, char* str, long radix);
char* strcpy(char *dst, const char *src);
long strcmp(const char* src, const char* dst);
unsigned strlen(const char *str);



// ÎÄ¼þÓëIO
typedef long FILE;
#define EOF (-1)

#if WIN32


#else
#define  stdin   ((FILE *)0)
#define  stdout  ((FILE *)1)
#define  stderr  ((FILE *)2)

#endif

int mini_crt_io_init();
FILE *fopen(const char *filename, const char *mode);
long fread(void *buffer, long size, long count, FILE *stream);
long fwrite(void *buffer, long size, long count, FILE *stream);
long fclose(FILE *fp);
long fseek(FILE *fp, long offset, long set);


// printf
long fputc(char c, FILE *stream);
long fputs(const char *str, FILE *stream);
long printf(const char* format, ...);
long fprintf(FILE *stream, const char* format, ...);


// internal
void do_global_ctors();
void mini_crt_call_exit_routine();


// atexit
typedef void (*atexit_func_t)(void);
int atexit(atexit_func_t func);



#ifdef __cplusplus
}
#endif

#endif // __MINI_CRT_H__
