#include <stdio.h>
#include <stdarg.h>
//#include "myfunc.h" //查询vscode配置头文件路径方法

//函数
int add1(int a, int b)
{
    return a + b;
}

int add2(int num, ...)
{
    int sum = 0;
    int i = 0;
    va_list v1;
    va_start(v1, num);

    for (i = 0; i < num; i++)
    {
        int val = va_arg(v1, int);
        sum += val;
    }
    va_end(v1);
    return sum;
}

int main(void)
{
    // int res = mine(5, 3);
    // printf("%d\n", res);

    int res1 = add1(5, 3);
    //输入多个参数
    int res2 = add2(5, 3, 6, 7, 3, 9);

    printf("%d\n", res1);
    printf("%d\n", res2);

    return 0;
}