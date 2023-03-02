#include <stdio.h>

#define TOTAL 2

struct Person
{
    char name[20];
    int num;
    char sex;
    char profession; //输入 s 或者 t
    union
    {
        double score;
        char course[20];
    } sc;
};

int main(void)
{
    int i;
    struct Person persons[TOTAL];
    for (i = 0; i < TOTAL; i++)
    {
        printf("Input info:\n");
        scanf("%s %d %c %c", persons[i].name, &(persons[i].num), &(persons[i].sex), &(persons[i].profession));
        if (persons[i].profession == 's')
        {
            printf("Please input Stu info:");
            scanf("%f", persons[i].sc.score);
            // getchar();
        }
        else
        {
            printf("Please input Tea info:");
            scanf("%s", persons[i].sc.course);
        }
        fflush(stdin);
    }

    //打印
    for (i = 0; i < TOTAL; i++)
    {
        if (persons[i].profession == 's')
        {
            printf("%s %d %c %c %.2f \n", persons[i].name, persons[i].num, persons[i].sex, persons[i].profession, persons[i].sc.score);
        }
        else
        {
            printf("%s %d %c %c %s \n", persons[i].name, persons[i].num, persons[i].sex, persons[i].profession, persons[i].sc.course);
        }
    }

    return 0;
}