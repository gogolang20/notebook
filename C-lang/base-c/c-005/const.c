#include <stdio.h>

//常量：定义后不能修改
//0x 十六进制
//0 八进制

// #define 常量名 常量值
#define PI 3.14
#undef PI //取消 PI 的定义
#define PI 3.1415

//const 数据类型 常量名 = 常量值；
const double Pie = 3.1415;

int main(void)
{
#ifdef PI
    printf("if def \n");
#endif
#ifndef PI
    printf("if no def \n");
#endif

    //整数常量可以带后缀 u 无符号整数 l 表示长整数
    30u;  //(unsigned int)30U
    30l;  //(long)30L
    30ul; // (unsigned long)30UL

    128;
    int n1 = 0200; // (int)128
    int n2 = 0x80; // (int)128
    int res = n1 + n2;
    printf("%d\n", res);

    char string[20] = "this is string";
    char str[] = "hello \
world ";
    printf("%s\n", str);
    printf("%s\n", string);

    //定义常量的两种方式
    // 使用 define 预处理器：
    //1 编译的预处理阶段起作用
    //2 #define 就是一个简单的替换，简单的字符串替换会出现边界效应
    // 使用 const 关键字：
    //1 编译运行时起作用
    //2 const 常量可以进行调试的，define是不能进行调式的，主要是预编译阶段就已经替换掉了，调式的时候就没有它了
    //3 const不能重定义，不可以定义两个一样的，而define 通过undef取消某个符号的定义，在重新定义
    // define可以配合 #ifdef #inndef #endif 来使用

    return 0;
}