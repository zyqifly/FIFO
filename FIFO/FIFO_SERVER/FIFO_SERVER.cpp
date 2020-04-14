// CMakeProject1.cpp: 定义应用程序的入口点。
//

#include "pipe.h"


#include<iostream>
#include<windows.h>
#include<ctime>
#include <thread>
using namespace std;

int main()
{
    //pipeServer* myServer = new   pipeServer();
    
    while (true)
    {
        cout << "输入一个数，1开始，或者退出！" << endl;
        int value = 0;
        cin >> value;
        if (value!=1)
        {
            break;
        }
        pipeServer* myServer = new   pipeServer();
        thread t(&pipeServer::connect, myServer);
        while (myServer->connectStatus)
        {
            char    data[256] = "hello pipe!";
            myServer->read(data);
            char data1[256] = "recieved!";
            myServer->send(data1);
        }
        myServer->close();
    }
    cout << "已经退出！" << endl;
    return 0;
}


