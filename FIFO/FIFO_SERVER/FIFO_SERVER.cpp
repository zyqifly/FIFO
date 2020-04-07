// CMakeProject1.cpp: 定义应用程序的入口点。
//

#include "FIFO_SERVER.h"

using namespace std;

#include<iostream>
#include<windows.h>
#include<ctime>
using namespace std;

int main()
{
    while (WaitNamedPipe(TEXT("\\\\.\\Pipe\\mypipe"), NMPWAIT_WAIT_FOREVER) == FALSE)
    {

    }

    HANDLE hPipe = CreateFile(TEXT("\\\\.\\Pipe\\mypipe"), GENERIC_READ | GENERIC_WRITE, 0,
        NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    char buf[256];
    DWORD rlen = 0;
    while (1)
    {
        if (ReadFile(hPipe, buf, 256, &rlen, NULL) == FALSE)//读取管道中的内容（管道是一种特殊的文件）
        {
            CloseHandle(hPipe);//关闭管道
            break;
        }
        else
        {
            cout << "Rcv:" << buf << endl;
        }
    }
    return 0;
}


