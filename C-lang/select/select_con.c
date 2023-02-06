#include <sys/select.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

// select + 并发
typedef struct fdinfo
{
    int fd;
    int *maxfd;
    fd_set* rdset;
} PDInfo;

void* acceptConn(void* arg)
{
    PDInfo* info = (PDInfo*)arg;
    int cfd = accept(info->fd, NULL, NULL);
    FD_SET(cfd, info->rdset);
    *info->maxfd = cfd > *info->maxfd ? cfd : *info->maxfd;

    return NULL;
}

void* communication(void* arg)
{
    PDInfo* info = (PDInfo*)arg;
   
    char buf[1024] = {0};
    int len = read(info->fd, buf, sizeof(buf));

    if(len == 0)
    {
        printf("客户端关闭了连接...\n");
        FD_CLR(info->fd, info->rdset);
        close(info->fd);
        return NULL;
    }
    else if(len > 0)
    {
        // 收到了数据
        // 发送数据
        write(info->fd, buf, strlen(buf)+1);
        printf("server buf: %s\n", buf);
    }
    else
    {
        free(info);
        perror("read");
        return NULL;
    }
    free(info);
    return NULL;
}

int main()
{
    // 1. 创建监听的fd
    int lfd = socket(AF_INET, SOCK_STREAM, 0);

    // 2. 绑定
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9999);
    addr.sin_addr.s_addr = INADDR_ANY;
    bind(lfd, (struct sockaddr*)&addr, sizeof(addr));

    // 3. 设置监听
    listen(lfd, 128);

    // 将监听的fd的状态检测委托给内核检测
    int maxfd = lfd;
    // 初始化检测的读集合
    fd_set rdset;
    fd_set rdtemp;
    // 清零
    FD_ZERO(&rdset);
    // 将监听的lfd设置到检测的读集合中
    FD_SET(lfd, &rdset);
    // 通过select委托内核检测读集合中的文件描述符状态, 检测read缓冲区有没有数据
    // 如果有数据, select解除阻塞返回
    // 应该让内核持续检测
    while(1)
    {
        // 默认阻塞
        // rdset 中是委托内核检测的所有的文件描述符
        rdtemp = rdset;
        int num = select(maxfd+1, &rdtemp, NULL, NULL, NULL);
        // rdset中的数据被内核改写了, 只保留了发生变化的文件描述的标志位上的1, 没变化的改为0
        // 只要rdset中的fd对应的标志位为1 -> 缓冲区有数据了
        // 判断
        // 有没有新连接
        if(FD_ISSET(lfd, &rdtemp))
        {
            pthread_t tid;
            PDInfo* info = (PDInfo*)malloc(sizeof(PDInfo));
            info->fd = lfd;
            info->maxfd = &maxfd;
            info->rdset = &rdset;
            pthread_create(&tid, NULL, acceptConn, info);
            pthread_detach(tid);
        }

        // 没有新连接, 通信
        for(int i=0; i<maxfd+1; ++i)
        {
			// 判断从监听的文件描述符之后到maxfd这个范围内的文件描述符是否读缓冲区有数据
            if(i != lfd && FD_ISSET(i, &rdtemp))
            {
                pthread_t tid;
                PDInfo* info = (PDInfo*)malloc(sizeof(PDInfo));
                info->fd = i;
                info->rdset = &rdset;
                pthread_create(&tid, NULL, communication, info);
                pthread_detach(tid);
            }
        }
    }

    return 0;
}
