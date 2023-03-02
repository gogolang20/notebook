#include <stdio.h>

//定义结构体 方式一
struct Stu
{
    char *name;
    int age;
    char *addr;
};

//定义结构体 方式二
struct Stu2
{
    char *name;
    int age;
    char *addr;
} stu01, stu02;

//定义结构体 方式三：匿名结构体
struct
{
    char *name;
    int age;
    char *addr;
} stu001, stu002;

char *say(struct Stu stu)
{
    static char info[50];
    sprintf(info, "name=%s age=%d addr=%s", stu.name, stu.age, stu.addr);
    return info;
}

int main(void)
{
    struct Stu stu1;
    stu1.name = "jack";
    stu1.age = 18;
    stu1.addr = "beijing";

    struct Stu stu2 = {
        name : "tom",
        age : 20,
        addr : "shanghai",
    };

    printf("%s, %d, %s\n", stu1.name, stu1.age, stu1.addr);
    printf("%s, %d, %s\n", stu2.name, stu2.age, stu2.addr);

    char *info = NULL;
    info = say(stu2);
    printf("%s", info);

    printf("%d\n", sizeof(stu1));

    return 0;
}
