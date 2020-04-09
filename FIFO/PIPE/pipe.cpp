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
        CloseHandle(hPipe);//�رչܵ�
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
    if (ReadFile(hPipe, buf, 256, &rlen, NULL) == FALSE)//��ȡ�ܵ��е����ݣ��ܵ���һ��������ļ���
    {
        //CloseHandle(hPipe);//�رչܵ�
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
        cout << "���ͳɹ���" << endl;
    }
    else
    {
        return  false;
        cout << "����ʧ�ܣ�" << endl;
    }
    
    return  true;
}

pipeClient::pipeClient()
{
    //hPipe = CreateNamedPipe(this->pipe_name, PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT
    //    , PIPE_UNLIMITED_INSTANCES, 0, 0, NMPWAIT_NOWAIT, 0);//������һ�������ܵ�
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
        CloseHandle(hPipe);//�رչܵ�
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
    if (ReadFile(hPipe, buf, 256, &rlen, NULL) == FALSE)//��ȡ�ܵ��е����ݣ��ܵ���һ��������ļ���
    {
        //CloseHandle(hPipe);//�رչܵ�
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
        , PIPE_UNLIMITED_INSTANCES, 0, 0, NMPWAIT_NOWAIT, 0);//������һ�������ܵ�
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
        , PIPE_UNLIMITED_INSTANCES, 0, 0, NMPWAIT_WAIT_FOREVER, 0);//������һ�������ܵ�
    if (ConnectNamedPipe(hPipe, NULL) == TRUE)//һֱ�ȴ���ֱ��ͬ���Ĺܵ�������
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