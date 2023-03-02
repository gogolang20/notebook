#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int max(int a, int b)
{
    return a > b ? a : b;
}
//回调函数
// 1 函数指针变量可以作为某个函数的参数来使用的，回调函数就是一个
// 通过函数指针调用的函数
// 2 回调函数是由别人的函数执行时调用你传入的函数（通过函数指针完成）
void initArr(int *array, int arraySize, int (*f)(void))
{
    int i;
    for (i = 0; i < arraySize; i++)
    {
        array[i] = f();
    }
}

//获取随机值
int getNextRandomValue(void)
{
    srand((unsigned)time(NULL));
    return rand();
}

int main(void)
{
    //函数指针
    int x, y;
    //定义函数指针
    //returnType (*pointerName)(param list)
    int (*pmax)(int, int) = max;

    printf("input two numbers:");
    scanf("%d %d", &x, &y);
    //调用
    int maxVal = (*pmax)(x, y);
    printf("Max value:%d pmax=%p &pmax=%p\n", maxVal, pmax, &pmax);

    //callback function
    int myarray[10];
    initArr(myarray, 10, getNextRandomValue);
    int i;
    for (i = 0; i < 10; i++)
    {
        printf("%d\n", myarray);
    }

    int *p = NULL; //空指针
    int num = 86;
    p = &num;
    printf("p=%d\n", *p);

    return 0;
}