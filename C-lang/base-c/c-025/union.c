#include <stdio.h>

//共用体：所有成员占用同一段内存
union data //声明一个共用体
{
    int n;
    char ch;
    short m
};

int main(void)
{
    union data a;                                     //定义
    printf("%d %d\n", sizeof(a), sizeof(union data)); //4 4

    a.n = 0x40;
    printf("%d, %c, %d\n", a.n, a.ch, a.m); //64, @, 64
    a.ch = '9';
    printf("%d, %c, %d\n", a.n, a.ch, a.m); //57, 9, 57
    a.m = 0x2059;
    printf("%d, %c, %d\n", a.n, a.ch, a.m); //8281, Y, 8281

    return 0;
}