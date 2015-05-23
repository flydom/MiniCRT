#include "minicrt.h"

int main(int argc, char *argv[])
{
	printf("********** Welcome to MiniCRT! **********\n";)

#if 0
    int i;
    FILE *fp;
    long *len = malloc(sizeof(long));
    char **v = malloc(argc * sizeof(char *));
    for (i = 0; i < argc; ++i)
    {
        v[i] = malloc(strlen(argv[i]) + 1);
        strcpy(v[i], argv[i]);
    }

    fp = fopen("test.txt", "w");
    for (i = 0; i < argc; ++i)
    {
        // long len = strlen(v[i]);
        *len = strlen(v[i]);
        fwrite(len, 1, sizeof(long), fp);
        fwrite(v[i], 1, *len, fp);
    }
    fclose(fp);

    fp = fopen("test.txt", "r");  
    for (i = 0; i < argc; ++i)
    {
        // long len = 0;
        char *buf;
        fread(len, 1, sizeof(long), fp);
        buf = malloc(*len + 1);
        fread(buf, 1, *len, fp);
        buf[*len] = '\0';
        printf("%d %s\n", *len, buf);
        free(buf);
        free(v[i]);
    }
    fclose(fp);
#endif

    printf("Hello World For Fun!\n");

    return 0;
}



