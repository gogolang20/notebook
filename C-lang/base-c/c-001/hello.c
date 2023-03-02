#include <stdio.h>

int main(void)
{
    //转义字符
    printf("hello world\n");
    printf("hello \tworld\n");
    printf("hello \\world\n");
    printf("hello \"world\n");
    printf("hello \'world\n");
    printf("hello world\r123");
    printf("\n");

    int num;
    scanf("%d", &num);

    printf("%d\n", num);
    return 0;
}