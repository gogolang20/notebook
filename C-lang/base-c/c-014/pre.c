#if _WIN32
#include <windows.h>
#elif _linux_
#include <unistd.h>
#endif

int main(void)
{
#if _WIN32
    Sleep(5000);
#elif _linux_
        sleep(5);
#endif
    puts("after 5 second");
    return 0;
}