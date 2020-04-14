// CMakeProject1.cpp: 定义应用程序的入口点。
//

#include    "pipe.h"
using namespace std;
#include<iostream>
#include<windows.h>
#include<ctime>
using namespace std;
#include <thread>


int main()
{
    pipeClient* myClient = new   pipeClient();/* = new pipeClient(TEXT("\\\\.\\Pipe\\mypipe"));*/
    thread t(&pipeClient::connect, myClient);
    while (true)
    {
        int a = 0;
        cout << "输入1继续。。。" << endl;
        cin >> a;
        if (a!=1)
        {
            myClient->close();
            break;
        }
        if (!myClient->connectStatus)//如果一开始没连接上，那就一直等待
        {
            continue;
        }
        char    data[] = "hello Pipe!";
        myClient->send(data);
        Sleep(1000);
        char    data1[256] = {};
        myClient->read(data1);
        if (!myClient->connectStatus)
        {
            cout << "连接已经断开，自动重连。。。。" << endl;
            myClient->connect();
        }
        
    }
    cout << "退出" << endl;
    return 0;
}

