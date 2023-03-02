#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//传入指针给函数
void test(int *p)
{
    *p += 1;
}

//返回指针的函数：指针函数
char *strlong(char *str1, char *str2)
{
    printf("str1 len=%d str2 len=%d\n", strlen(str1), strlen(str2));
    if (strlen(str1) >= strlen(str2))
    {
        return str1;
    }
    else
    {
        return str2;
    }
}
int *retArr()
{
    static int arr[10]; //static 让数据空间再静态数据区分配
    int i;
    for (i = 0; i < 10; i++)
    {
        arr[i] = rand();
    }
    return arr;
}

int main(void)
{
    int i;
    int num = 90;
    int *p = &num;
    test(p);
    printf("main num=%d\n", num); //91
    test(p);
    printf("main num=%d\n", num); //92

    //---------------------------------------------------------
    char str1[30], str2[30], *str;
    printf("input str1:\n");
    gets(str1);
    printf("input str2:\n");
    gets(str2);
    str = strlong(str1, str2);
    printf("longer string:%s\n", str);

    int *pArr;
    pArr = retArr();
    printf("%d", pArr);
    for (i = 0; i < 10; i++)
    {
        printf("%d\n", *(pArr + i));
    }

    return 0;
}