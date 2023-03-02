#include <stdio.h>
#include <string.h>

int main(void)
{
    int i = 1;
    while (i <= 100)
    {
        if (i % 3 == 0)
        {
            printf("%d\n", i);
        }
        i++;
    }

    char name[20];
    while (strcmp(name, "exit") != 0)
    {
        printf("please input name:\n");
        scanf("\n%s", &name);
    }
    //----------------------- do while -----------------------
    int x = 1;
    do //至少执行一次
    {
        printf("this is %d\n", x);
        x++;
    } while (x <= 5);

    return 0;
}