#include <stdio.h>

//static
//静态局部变量存储于进程的静态存储区（全局性质）
//只会被初始一次，即使函数返回，他的值也会保持不变
void fn_static(void)
{
    static int n = 10;
    printf("n=%d\n", n);
    n++;
    printf("++ n=%d\n", n);
}

//extern
//引入其他文件的普通全局变量
//无法引用到其他文件的 static全局变量
extern int num;

//static 静态函数
void func_static(void);
//只能在声明的文件中使用
//不可以使用extern引入 静态函数

int main(void)
{
    static int a;
    printf("a=%d\n", a); //a=0

    fn_static();
    printf("---------------\n");
    fn_static();
    /*
    输出结果：
    n=10
    ++ n=11
    ---------------
    n=11
    ++ n=12
    */

    printf("num=%d\n", num);

    return 0;
}