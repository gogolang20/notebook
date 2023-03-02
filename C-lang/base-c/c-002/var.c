#include <stdio.h>

//宏定义
#define Bool int
#define true 1
#define false 0

void main()
{
    //变量三要素：变量名  值  数据类型
    //1 声明
    //2 赋值
    //3 使用

    //整型 short int long
    //浮点型 float double
    //字符类型 char

    //构造类型：数组 结构体struct 共用体union 枚举类型enum
    //指针类型
    //空类型 void

    int a = 3;
    float b = 4.0f;
    double c = 5.0;

    //char存储：字符'a' --> ascII(97) --> 二进制(110 0001) --> 存储
    char d = 'w';
    char dd = 98;
    char ddd = '\"';
    char e[] = "hello c language";

    unsigned int f = 90; //无符号
    signed int g = -80;  //有符号
    long long h;
    long double i;

    double j = 5.12e2;  //512.000
    double k = 5.12e-2; //512.000

    printf("a = %d \n", a);
    printf("%d %ld %lld %ld\n", sizeof(a), sizeof(unsigned long), sizeof(long long), sizeof(long double));

    printf("b = %.2f \n", b);
    printf("c = %.2f \n", c);
    printf("d = %c dd = %c ddd = %c \n", d, dd, ddd);
    printf("e = %s \n", e);
    printf("j = %f k = %f \n", j, k);
    printf("%d %d %d\n", sizeof(b), sizeof(float), sizeof(double));

    //c语言没有布尔类型，0表示false，非0表示true
    //可以使用 宏 定义
    Bool isOk = true; //等价 int isOk = 1
    if (isOk)
    {
        printf("ok \n");
    }

    //将控制台停留
    getchar();
}
