#include <stdio.h>

int main(void)
{
    char name[20];
    int age;
    printf("Name:");
    scanf("%s", &name);
    printf("Age:");
    scanf("%d", &age);

    if (age > 18)
    {
        printf("adult!\n");
    }
    else if (age > 0 && age <= 18)
    {
        printf("not adult!\n");
    }
    else
    {
        printf("error\n");
    }

    printf("\nName:%s \nAge:%d", name, age);

    int i, j;
    for (i = 0, j = 0; i < 8; i++, j++)
    {
        printf("\n%d %d", i, j);
    }
    printf("\nafter loop: %d %d", i, j);

    return 0;
}