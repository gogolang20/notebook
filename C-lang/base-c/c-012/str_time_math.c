#include <stdio.h>
//字符串函数
#include <string.h>
//日期函数
#include <time.h>
//数学函数
#include <math.h>

void testTime(void)
{
    int i = 0;
    int sum = 0;
    for (i = 0; i < 1000000000; i++)
    {
        sum += i;
    }
    return;
}
int main(void)
{
    char src[50] = "1324", dest[50];
    char *str = "abcdff";
    //得到字符串长度
    printf("str len = %d\n", strlen(str));
    //拷贝字符串，会将原来的内容覆盖
    strcpy(src, "hello");
    printf("src=%s\n", src);
    strcpy(dest, "world");
    printf("dest=%s\n", dest);

    //字符串连接,将src 连接到 dest后面
    strcat(dest, src);
    printf("final str=%s\n", dest); //final str=worldhello

    //获取当前时间
    time_t curtime; //time_t 一个结构体
    time(&curtime);
    printf("current time=%s\n", ctime(&curtime));

    //统计函数执行的时间
    time_t start_t, end_t;
    double diff_t; //存放时间差
    printf("start testTime \n");
    time(&start_t);
    testTime();
    time(&end_t);

    diff_t = difftime(end_t, start_t);
    printf("diff_t=%.2f \n", diff_t);

    //1 返回 e 的 x 次幂的值
    double exp(double x);
    //2 返回 x 的自然对数（基数为 e 的对数）
    double log(double x);
    //3 返回 x 的 y 次幂
    double pow(double x, double y);
    //4 返回 x 的平方根
    double sqrt(double x);
    //5 返回 x 的绝对值
    double fabs(double x);
}
