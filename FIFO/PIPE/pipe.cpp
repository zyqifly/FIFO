#include	"pipe.h"
template<class T>
int length(T& arr)
{
	//cout << sizeof(arr[0]) << endl;
	//cout << sizeof(arr) << endl;
	return sizeof(arr) / sizeof(arr[0]);
}
pipeBase::pipeBase()
{
}

pipeBase::~pipeBase()
{
    this->close();
}
pipeServer::pipeServer()
{
}

pipeServer::~pipeServer()
{
}
pipeServer::pipeServer(LPCWSTR pipe_name)
{
    this->pipe_name = pipe_name;
    
}

bool	pipeServer::connect()
{
    //由于是个死循环，可以放到另一个线程
    while (WaitNamedPipe(pipe_name, NMPWAIT_WAIT_FOREVER) == FALSE)
    {
        //cout << "wait。。。。。" << endl;
    }
    
    this->hPipe = CreateFile(pipe_name, GENERIC_READ | GENERIC_WRITE, 0,
        NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (this->hPipe != NULL)
    {
        connectStatus = true;
        //this->pipe_name = pipe_name;
    }
    cout << "pipe Server connected!" << endl;
    return true;
}




pipeClient::pipeClient()
{
    
}

pipeClient::~pipeClient()
{
}



bool	pipeClient::connect()
{
    hPipe = CreateNamedPipe(this->pipe_name, PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT
        , PIPE_UNLIMITED_INSTANCES, 0, 0, NMPWAIT_NOWAIT, 0);//创建了一个命名管道
    //如果Server不存在，上条指令会一直等待，所以把这个函数要放在另外一个线程中
    if (ConnectNamedPipe(this->hPipe, NULL) == TRUE)//
    {
        cout << "Connected!" << endl;
        this->connectStatus = true;
    }
    else
    {
        cout << "Connected failed!" << endl;
        this->connectStatus = false;
    }
    return  true;
}
pipeClient::pipeClient(LPCWSTR pipe_name)
{
    this->pipe_name = pipe_name;
    
}

bool	pipeBase::read(char buf[], DWORD	len)//接收数据，并计数
{
    if (!this->connectStatus)
    {
        return  false;
    }
    //char buf[256] = "Hello Pipe";
    DWORD rlen = 0;
    if (ReadFile(hPipe, buf, len, &rlen, NULL) == FALSE)//读取管道中的内容（管道是一种特殊的文件）
    {
        CloseHandle(hPipe);//关闭管道
        connectStatus = false;
        cout << "读失败，关闭！" << endl;
        return  false;
    }
    else
    {
        cout << "Rcv:" << buf << endl;
    }

    return  true;
}
bool	pipeBase::send(char buf[], DWORD	len)//数组里面的数据全发送
{
    if (!connectStatus)
    {
        return  false;
    }
    DWORD   wlen = 0;
    bool    ret = false;
    ret = WriteFile(hPipe, buf, len, &wlen, 0);
    if (!ret)
    {
        //CloseHandle(hPipe);//关闭管道
        connectStatus = false;
        cout << "写失败，关闭！" << endl;
        return  false;
    }
    cout << "Send:" << buf << endl;
    return  true;
}
void	pipeBase::close()
{
    if (connectStatus)
    {
        //CloseHandle(this->hPipe);//关闭管道
        connectStatus = false;
        cout << "已经关闭!" << endl;
    }
}
bool	pipeBase::connect()
{
    return false;
}