#include <stdio.h>

void main()
{
    //数据类型自动转换
    //c程序在进行赋值或者运算时，精度小的类型自动转换位精度大的数据类型
    //这就是自动类型转换
    char c = 'E';
    int num = c;
    double d = num;
    printf("%c \t %d \t %.2lf\n", c, num, d);

    //数据类型强制转换
    //将精度高的数据类型转换为精度小的数据类型，同时加上强制转换符 ()
    double t = 10.864651649;
    int x = (int)t;
    printf("%.10lf %d\n", t, x);
    printf("%d %d %d\n", sizeof(double), sizeof(t), sizeof(x));

    int y = (int)1.5 * 10;
    printf("%d\n", y); //10

    getchar();
}