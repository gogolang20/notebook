#include <stdio.h>

int main(void)
{
    //二维数组
    int arr[3][5];
    int i, j;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 5; j++)
        {
            arr[i][j] = 0;
        }
    }

    //遍历二维数组
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 5; j++)
        {
            printf("%d", arr[i][j]);
        }
        printf("\n");
    }
    /*
    遍历结果
    00000
    00000
    00000
    */
    printf("%p\n", arr);        //000000000064FDD0
    printf("%p\n", arr[0]);     //000000000064FDD0
    printf("%p\n", &arr[0][0]); //000000000064FDD0
    printf("%p\n", arr[1]);     //000000000064FDE4

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 5; j++)
        {
            printf("%p ", &arr[i][j]);
        }
        printf("\n");
    }

    int map[3][3] = {{1, 2, 3},
                     {4, 5, 6},
                     {7, 8, 9}};
    int row = sizeof(map) / sizeof(map[0]);  //行数
    int clow = sizeof(map[0]) / sizeof(int); //列数
    printf("%d %d", row, clow);

    return 0;
}