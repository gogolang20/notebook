#include <stdio.h>

//指针

const int MAX = 3;

int main(void)
{
    int var[] = {10, 100, 200};
    int i, *ptr;

    ptr = var;

    for (i = 0; i < MAX; i++)
    {
        printf("var[%d] addr=%p\n", i, ptr);
        printf("value:var[%d]=%d\n", i, *ptr);
        ptr++; //指针的算术运算
    }
    /*
    var[0] addr=000000000064FE04
    value:var[0]=10
    var[1] addr=000000000064FE08
    value:var[1]=100
    var[2] addr=000000000064FE0C
    value:var[2]=200
    */
    int *ptr2 = &var[MAX - 1];
    for (i = MAX; i > 0; i--)
    {
        printf("var[%d] addr=%p\n", i - 1, ptr2);
        printf("value:var[%d]=%d\n", i - 1, *ptr2);
        ptr2--; //指针的算术运算
    }

    return 0;
}