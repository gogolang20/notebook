#include <stdio.h>
#include <stdlib.h>

//malloc: memory allocation
//动态内存
// (void *) 是一个纯地址，不指向任何数据空间

//常用关于动态分配内存函数：malloc  free  calloc  realloc

int main(void)
{
    void check(int *); //声明一个函数
    int *p, i;
    p = (int *)malloc(5 * sizeof(int)); //动态分配内存 (int *)是强制转换 (void *)数据类型
    for (i = 0; i < 5; i++)
    {
        scanf("%d", p + i);
    }
    check(p);
    free(p); //释放分配的内存

    return 0;
}

void check(int *p)
{
    int i;
    printf("not pass:\n");
    for (i = 0; i < 5; i++)
    {
        if (p[i] < 60)
        {
            printf("%d ", p[i]);
        }
    }
}