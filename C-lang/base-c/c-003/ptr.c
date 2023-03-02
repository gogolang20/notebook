#include <stdio.h>

int main(void)
{
    //指针
    int num = 100;
    int *ptr = &num;
    printf("%d %p %p\n", num, &num, ptr);
    printf("%d\n", *ptr); //相当与打印num
    printf("%p\n", &ptr); //指针的地址
    *ptr = 50;            //num = 50
    printf("值：%d\n", num);
    printf("%d \n", sizeof(ptr));

    //基本类型都有对应的指针类型  例如：int *
    //还有 指向数组的指针 指向结构体的指针 指向共用体的指针 多级指针 等

    return 0;
}