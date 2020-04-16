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
    //thread t(&pipeClient::connect, myClient);//此函数将连接的动作发送到另一个线程
    myClient->connect();//
    while (true)
    {
        int a = 0;
        cout << "输入数字继续，0退出、1自动运行、2停止、3读取状态。。。" << endl;
        cin >> a;
        if (a==0)
        {
            myClient->close();
            return  0;
        }
        if (!myClient->connectStatus)//如果一开始没连接上，那就一直等待
        {
            myClient->connect();
            continue;
        }
        else
        {
            if (a==1)
            {
                char    data[] = ":auto";
                myClient->send(data, sizeof(data));
                //continue;
            }
            else if (a==2)
            {
                char    data[] = ":stop";
                myClient->send(data, sizeof(data));
                //continue;
            }
            else  if (a==3)
            {
                char    data[] = ":req";
                myClient->send(data, sizeof(data));
                Sleep(1000);
                char    data1[256] = {};
                myClient->read(data1, sizeof(data1));
                //continue;
            }
            /*else
            {
                char    data[] = "hello";
                myClient->send(data, sizeof(data));
                Sleep(1000);
                char    data1[256] = {};
                myClient->read(data1, sizeof(data1));
                continue;
            }*/
            
            
        }
       
        if (!myClient->connectStatus)
        {
            cout << "连接已经断开，自动重连。。。。" << endl;
            myClient->connect();
        }
        
    }
    cout << "退出" << endl;
    return 0;
}

