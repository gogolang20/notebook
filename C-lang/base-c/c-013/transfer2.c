#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    //sprintf
    char str1[20];
    char str2[20];
    char str3[20];
    int a = 20984;
    int b = 40984;
    double d = 14.309948;
    sprintf(str1, "%d %d", a, b);
    sprintf(str2, "%.2f", d);
    sprintf(str3, "%8.2f", d); //%8.2f 一共8微，小数点占两位
    printf("str1=%s str2=%s str3=%s \n", str1, str2, str3);
    //str1=20984 40984 str2=14.31 str3=   14.31

    //atoi atof
    char str01[10] = "123456";
    char str02[10] = "12.67423";
    char str03[2] = "a";
    char str04[4] = "111";

    int num1 = atoi(str01);
    short s1 = atoi(str04);
    double x = atof(str02);
    char c = str03[0];
    printf("num1=%d x=%f c=%c s1=%d\n", num1, x, c, s1);
    //num1=123456 x=12.674230 c=a s1=111

    return 0;
}