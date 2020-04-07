// CMakeProject1.cpp: 定义应用程序的入口点。
//

#include "FIFO_CLIENT.h"

using namespace std;
#include<iostream>
#include<windows.h>
#include<ctime>
using namespace std;


int main()
{
    HANDLE hPipe = CreateNamedPipe(TEXT("\\\\.\\Pipe\\mypipe"), PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT
        , PIPE_UNLIMITED_INSTANCES, 0, 0, NMPWAIT_WAIT_FOREVER, 0);//创建了一个命名管道
    if (ConnectNamedPipe(hPipe, NULL) == TRUE)//
    {
        cout << "Connected!" << endl;
    }

    char buf[256] = "Hello Pipe";
    DWORD wlen = 0;

    while (1)
    {
        WriteFile(hPipe, buf, sizeof(buf), &wlen, 0);
        cout << "Send:" << buf << endl;
        _sleep(1000);
    }
    return 1;
}

