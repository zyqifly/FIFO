#include	"pipe.h"
pipeServer::pipeServer()
{
    while (WaitNamedPipe(this->pipe_name, NMPWAIT_WAIT_FOREVER) == FALSE)
    {
        
    }
    cout << "pipe Server connected!"<<endl;
    hPipe = CreateFile(this->pipe_name, GENERIC_READ | GENERIC_WRITE, 0,
        NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hPipe!=NULL)
    {
        connectStatus = true;
    }
}

pipeServer::~pipeServer()
{
}
pipeServer::pipeServer(LPCWSTR pipe_name)
{
    while (WaitNamedPipe(pipe_name, NMPWAIT_WAIT_FOREVER) == FALSE)
    {
   
    }
    cout << "pipe Server connected!" << endl;
    hPipe = CreateFile(pipe_name, GENERIC_READ | GENERIC_WRITE, 0,
        NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hPipe!=NULL)
    {
        connectStatus = true;
        this->pipe_name = pipe_name;
    }
    
}
void	pipeServer::closeServer()
{
    if (connectStatus)
    {
        CloseHandle(hPipe);//关闭管道
        connectStatus = false;
    }
}
bool	pipeServer::read()
{
    if (!connectStatus)
    {
        return  false;
    }
    char buf[256];
    DWORD rlen = 0;
    if (ReadFile(hPipe, buf, 256, &rlen, NULL) == FALSE)//读取管道中的内容（管道是一种特殊的文件）
    {
        //CloseHandle(hPipe);//关闭管道
        //connectStatus = false;
        return  false;
    }
    else
    {
        cout << "Rcv:" << buf << endl;
    }
    return  true;
}
bool	pipeServer::send()
{
    if (!this->connectStatus)
    {
        return  false;
    }
    char buf[] = "read ok!";
    DWORD   wlen = 0;
    bool    ret = WriteFile(hPipe, buf, sizeof(buf), &wlen, 0);
    if (ret)
    {
        cout << "发送成功！" << endl;
    }
    else
    {
        return  false;
        cout << "发送失败！" << endl;
    }
    
    return  true;
}

pipeClient::pipeClient()
{
    //hPipe = CreateNamedPipe(this->pipe_name, PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT
    //    , PIPE_UNLIMITED_INSTANCES, 0, 0, NMPWAIT_NOWAIT, 0);//创建了一个命名管道
    //if (ConnectNamedPipe(hPipe, NULL) == TRUE)//
    //{
    //    cout << "Connected!" << endl;
    //    this->connectStatus = true;
    //}
    //else
    //{
    //    cout << "Connected failed!" << endl;
    //    this->connectStatus = false;
    //}
}

pipeClient::~pipeClient()
{
}
void	pipeClient::closeClient()
{
    if (connectStatus)
    {
        CloseHandle(hPipe);//关闭管道
        connectStatus = false;
    }
}
bool	pipeClient::read()
{
    if (!this->connectStatus)
    {
        return  false;
    }
    char buf[256] = "Hello Pipe";
    DWORD rlen = 0;
    if (ReadFile(hPipe, buf, 256, &rlen, NULL) == FALSE)//读取管道中的内容（管道是一种特殊的文件）
    {
        //CloseHandle(hPipe);//关闭管道
        //connectStatus = false;
        //return  false;
    }
    else
    {
        cout << "Rcv:" << buf << endl;
    }
          
    return  true;
}
bool	pipeClient::send()
{
    if (!connectStatus)
    {
        return  false;
    }
    char buf[256] = "Hello Pipe";
    DWORD wlen = 0;
    bool    ret = false;
    ret = WriteFile(hPipe, buf, sizeof(buf), &wlen, 0);
    cout << "Send:" << buf << endl;
    return  true;
}
void	pipeClient::connect()
{
    hPipe = CreateNamedPipe(this->pipe_name, PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT
        , PIPE_UNLIMITED_INSTANCES, 0, 0, NMPWAIT_NOWAIT, 0);//创建了一个命名管道
    if (ConnectNamedPipe(hPipe, NULL) == TRUE)//
    {
        cout << "Connected!" << endl;
        this->connectStatus = true;
    }
    else
    {
        cout << "Connected failed!" << endl;
        this->connectStatus = false;
    }
}
pipeClient::pipeClient(LPCWSTR pipe_name)
{
    hPipe = CreateNamedPipe(pipe_name, PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT
        , PIPE_UNLIMITED_INSTANCES, 0, 0, NMPWAIT_WAIT_FOREVER, 0);//创建了一个命名管道
    if (ConnectNamedPipe(hPipe, NULL) == TRUE)//一直等待，直到同名的管道创建。
    {
        cout << "Connected!" << endl;
        this->pipe_name = pipe_name;
        this->connectStatus = true;
    }
    else
    {
        cout << "Connected failed!" << endl;
        this->connectStatus = false;
    }
    
}