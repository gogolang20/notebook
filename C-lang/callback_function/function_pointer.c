#include <stdio.h>

int Callback_1(int a)   ///< 回调函数1
{
    printf("Hello, this is Callback_1: a = %d ", a);
    return 0;
}

int Callback_2(int b)  ///< 回调函数2
{
    printf("Hello, this is Callback_2: b = %d ", b);
    return 0;
}

int Callback_3(int c)   ///< 回调函数3
{
    printf("Hello, this is Callback_3: c = %d ", c);
    return 0;
}

int Handle(int x, int (*Callback)(int)) ///< 注意这里用到的函数指针定义
{
    Callback(x);
}

int main()
{
    Handle(4, Callback_1);
    Handle(5, Callback_2);
    Handle(6, Callback_3);
    return 0;
}
