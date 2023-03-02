#include <stdio.h>

//宏定义
// #define 宏名 字符串
//字符串的简单替换
//字符串的公式需要添加小括号，否则会导致不可预知的错误
#define N (100 * 180)
//宏可以层层嵌套，宏名一般用大写

//宏定义可以表示数据类型
#define UNIT unsigned int

//带参数的宏定义
// #define 宏名(形参列表)字符串
//(a, b) 形参
//(a > b) ? a : b 是带参数的宏对应字符串，该字符串中可以使用形参
#define MAX(a, b) (a > b) ? a : b

//字符串内的形参通常要用小括号括起来
#define SQ(y) (y) * (y)

int main(void)
{
    int res = N + 20;
    printf("res = %d \n", res);

#undef N //取消定义 N

    UNIT a = 7;
    unsigned int b = 8;
    printf("a = %d b = %d \n", a, b);

    int x, y, max;
    printf("input two numbers\n");
    scanf("%d %d", &x, &y);
    //调用
    max = MAX(x, y);
    printf("max = %d\n");

    int c = 9;
    int res3 = SQ(c);
    printf("res3 = %d \n", res3);

    return 0;
}