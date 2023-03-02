#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

void show()
{
    MessageBoxA(0, "123", "456", 0);
}

void go()
{
    printf("%s\n", "this is func");
}

void main()
{
    //函数指针
    void (*p)() = show;
    p();

    p = go;
    p();

    system("pause");
}