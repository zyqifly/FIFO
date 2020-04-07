// CMakeProject1.cpp: 定义应用程序的入口点。
//

#include "pipe.h"


#include<iostream>
#include<windows.h>
#include<ctime>
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
        LPCWSTR NAME = TEXT("\\\\.\\Pipe\\mypipe");
        pipeServer* myServer = new   pipeServer(NAME);
        while (myServer->connectStatus)
        {
            myServer->read();
            //myServer->send();
        }
        myServer->closeServer();
    }
    cout << "已经退出！" << endl;
    return 0;
}


