#include <stdio.h>

const int MAX = 3;
int main(void)
{
    //指针加减运算
    int var[3] = {10, 100, 200};
    int *ptr = var;
    ptr += 2;

    printf("var[2]=%d var[2]address=%p ptr=%p ptr->=%d\n", var[2], &var[2], ptr, *ptr);
    //var[2]=200 var[2]address=000000000064FE14 ptr=000000000064FE14 ptr->=200

    //--------------------------------------------------
    //指针数组
    // 数据类型 *指针数组名[size]
    int *ptrArr[3];
    int var2[3] = {10, 100, 200};
    int i;
    for (i = 0; i < MAX; i++)
    {
        ptrArr[i] = &var2[i];
    }
    //赋值
    for (i = 0; i < MAX; i++)
    {
        printf("value of var2[%d]  ptrArr address=%p\n", *ptrArr[i], &ptrArr[i]);
    }

    //定义一个指针数组，该数组的每个元素，指向的是一个字符串
    char *books[] = {
        "sanguoyanyi",
        "xiyouji",
        "hongloumeng",
        "shuihuchuan",
    };
    int j;
    int len = 4;
    for (j = 0; j < len; j++)
    {
        printf("books[%d] : %s \n", j, books[j]);
    }

    return 0;
}