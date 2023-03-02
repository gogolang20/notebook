#include <stdio.h>

int main(void)
{
    // a%b =a-a/b*b
    int res1 = 10 % 3;
    int res2 = -10 % 3;
    int res3 = 10 % -3;
    int res4 = -10 % -3;

    printf("%d %d %d %d\n", res1, res2, res3, res4); //1 -1 1 -1

    int i = 3;
    int j = i++;
    int k = 6;
    int t = ++k;
    printf("%d %d \n", i, j); //4 3
    printf("%d %d \n", k, t); //7 7

    //三元运算符
    // 条件表达式 ? 表达式1 ： 表达式2 ；
    int x = 3;
    int y = 2;
    int res = x > y ? ++x : --y;
    printf("res=%d\n", res);

    //运算符优先级：算术运算符 > 关系运算符 > 逻辑运算符(!除外) > 赋值运算符 > 逗号运算符

    return 0;
}