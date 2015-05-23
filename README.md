# MiniCRT
《程序员的自我修养》运行库：MiniCRT实现。

编译：
进入make目录，执行./make.sh，将会打印使用说明，其中：

target有minicrt、main以及clean三个选项:
minicrt: 该项编译出minicrt.a静态库；
main: 该项编译出运行的main程序；
clean: 清除掉所有库、目标.o文件以及main程序。

使用步骤：
1) ./make.sh clean     // 清除所有多余文件；

2) ./make.sh minicrt   // 编译生成minicrt.a静态库；

3) ./make.sh main      // 编译生成main执行程序；
