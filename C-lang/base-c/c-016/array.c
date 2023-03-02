
#include <stdio.h>
#include <string.h>

//数组传递的是地址
void fn(int arr[4])
{
    arr[0] += 1;
}

int main(void)
{
    double balls[6];
    balls[0] = 5.0;
    balls[1] = 5.0;
    balls[2] = 5.0;
    balls[3] = 5.0;
    balls[4] = 5.0;
    balls[5] = 5.0;
    int arrlen = sizeof(balls) / sizeof(double);
    printf("arrlen = %d\n", arrlen);

    int arr[10];
    //arr[0] = 9;
    printf("arr=%p %p\n", &arr, &arr[1]);

    int arr2[4] = {1, 2, 3, 5};
    int arr3[] = {1, 2, 3, 5, 6};

    fn(arr2);
    int i;
    for (i = 0; i < 4; i++)
    {
        printf("%d %d\n", i, arr2[i]);
    }

    char ch[3] = "abc";
    char str[4] = {'A', 'B', 'C', '\0'}; //最后一个元素 '\0' 表示 结束
    char str2[4] = "ABC";
    printf("%s %c\n", ch, ch[2]);
    printf("%s \n", str);
    printf("%s \n", str2);

    char str3[] = "hello";
    printf("%d \n", sizeof(str3)); // 6，'\0' 表示NULL 不显示
    printf("%d \n", strlen(str3)); // 5

    //字符指针变量
    char *pStr = "hello world";
    printf("%s \n", pStr);
    printf("%p \n", pStr);  //pStr指向的地址 //0000000000404023
    printf("%p \n", &pStr); //pStr本身的地址 //000000000064FDA0

    printf("%d \n", sizeof(pStr)); // 8
    printf("%d \n", strlen(pStr)); // 11

    pStr = "99 81";
    printf("%s \n", pStr);
    printf("%p \n", pStr);  //pStr指向的地址 //0000000000404034
    printf("%p \n", &pStr); //pStr本身的地址 //000000000064FDA0

    return 0;
}
