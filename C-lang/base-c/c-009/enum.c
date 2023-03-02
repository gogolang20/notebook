#include <stdio.h>

//枚举
int main(void)
{
    enum DAY
    {
        MON = 1,
        TUE = 2,
        WEN = 3,
        THU = 4,
        FRI = 5,
        SAT = 6,
        SUN = 7
    };
    enum DAY day;
    day = MON;
    printf("MON=%d\n", day);

    //枚举遍历
    for (day = MON; day <= SUN; day++)
    {
        printf("%d\n", day);
    }

    //使用switch
    enum DAY days;
    scanf("%d", &days);
    switch (days)
    {
    case MON:
        printf("today is mon\n");
        break;
    case TUE:
        printf("today is tue\n");
        break;
    case WEN:
        printf("today is wen\n");
        break;
    case THU:
        printf("today is thu\n");
        break;
    case FRI:
        printf("today is fri\n");
        break;
    case SAT:
        printf("today is sat\n");
        break;
    case SUN:
        printf("you like sunday\n");
        break;
    default:
        break;
    }
    //将 整数 类型转换成 枚举 类型
    enum DAY dd;
    int n = 10;
    dd = (enum DAY)n;
    printf("%d\n", dd);
    return 0;
}