#include "minicrt.h"

#ifdef WIN32

#include <Windows.h>

#endif


extern int main(int arge, char *argv[]);
void exit(int);


static void crt_fatal_error(const char *msg)
{
    printf("fatal error: %s", msg);
    exit(1);
}


void mini_crt_entry(void)
{
    int ret = 0;

#ifdef WIN32
    int flag = 0;
    int argc = 0;
    char *argv[16];  // 最多支持16个参数
    char *cl = GetCommandLine(); // Windows提供该API获取进程的命令行参数
    
    // 解析命令行
    argv[0] = cl;
    argc++;
    while (*cl)
    {
        if (*cl == '\"' && flag == 0)
        {
            flag = 1;
        }
        else if (*cl == ' ' && flag == 0)
        {
            if (*(cl + 1))
            {
                argv[argc] = cl + 1;
                argc++;
            }
            *cl = '\0';
        }

        cl++;
    }
    
#else
    int argc = 0;
    char **argv;

    char *ebp_reg = NULL;
    asm("movq %%rbp, %0  \n" : "=r"(ebp_reg));
    
    argc = *(int *)(ebp_reg + 8);
    argv = (char **)(ebp_reg + 16);
#endif

    if (!mini_crt_heap_init())
    {
        crt_fatal_error("Heap Initialize Failed!\n");
    }

    if (!mini_crt_io_init())
    {
        crt_fatal_error("IO Initialize Failed!\n");
    }
    
    // 初始化部分
    ret = main(argc, argv);

    // 结束部分
    exit(ret);
}


void exit(int exitCode)
{
    // mini_crt_call_exit_routine();

#ifdef WIN32
    ExitProcess(exitCode);
#else
    asm( "movl %0, %%ebx \n\t"
         "movl $1, %%eax \n\t"
         "int $0x80      \n\t"
         "hlt            \n\t"::"m"(exitCode));

#endif

}




