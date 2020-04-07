// CMakeProject1.cpp: 定义应用程序的入口点。
//

#include    "pipe.h"
using namespace std;
#include<iostream>
#include<windows.h>
#include<ctime>
using namespace std;


int main()
{
    pipeClient* myClient = new pipeClient();
    while (true)
    {
        myClient->send();
        Sleep(1000);
    }
    return 0;
    
    
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
        Sleep(1000);
        //DWORD rlen = 0;
        //if (ReadFile(hPipe, buf, 256, &rlen, NULL) == FALSE)//读取管道中的内容（管道是一种特殊的文件）
        //{
        //    CloseHandle(hPipe);//关闭管道
        //    //connectStatus = false;
        //    return  false;
        //}
        //else
        //{
        //    cout << "Rcv:" << buf << endl;
        //}
    }
    return 1;
}

