#include	"pipe.h"
pipeBase::pipeBase()
{
}

pipeBase::~pipeBase()
{
    this->close();
}
pipeServer::pipeServer()
{
    while (WaitNamedPipe(this->pipe_name, NMPWAIT_WAIT_FOREVER) == FALSE)
    {
        
    }
    cout << "pipe Server connected!"<<endl;
    this->hPipe = CreateFile(this->pipe_name, GENERIC_READ | GENERIC_WRITE, 0,
        NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    
    if (this->hPipe!=NULL)
    {
        connectStatus = true;
    }
}

pipeServer::~pipeServer()
{
}
pipeServer::pipeServer(LPCWSTR pipe_name)
{
    this->pipe_name = pipe_name;
    
}

void	pipeServer::connect()
{
    //�����Ǹ���ѭ�������Էŵ���һ���߳�
    while (WaitNamedPipe(pipe_name, NMPWAIT_WAIT_FOREVER) == FALSE)
    {

    }
    cout << "pipe Server connected!" << endl;
    this->hPipe = CreateFile(pipe_name, GENERIC_READ | GENERIC_WRITE, 0,
        NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (this->hPipe != NULL)
    {
        connectStatus = true;
        this->pipe_name = pipe_name;
    }
}




pipeClient::pipeClient()
{
    
}

pipeClient::~pipeClient()
{
}



void	pipeClient::connect()
{
    hPipe = CreateNamedPipe(this->pipe_name, PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT
        , PIPE_UNLIMITED_INSTANCES, 0, 0, NMPWAIT_NOWAIT, 0);//������һ�������ܵ�
    //���Server�����ڣ�����ָ���һֱ�ȴ������԰��������Ҫ��������һ���߳���
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
}
pipeClient::pipeClient(LPCWSTR pipe_name)
{
    this->pipe_name = pipe_name;
    
}

bool	pipeBase::read(char buf[])//�������ݣ�������
{
    if (!this->connectStatus)
    {
        return  false;
    }
    //char buf[256] = "Hello Pipe";
    DWORD rlen = 0;
    if (ReadFile(hPipe, buf, 256, &rlen, NULL) == FALSE)//��ȡ�ܵ��е����ݣ��ܵ���һ��������ļ���
    {
        CloseHandle(hPipe);//�رչܵ�
        connectStatus = false;
        return  false;
    }
    else
    {
        cout << "Rcv:" << buf << endl;
    }

    return  true;
}
bool	pipeBase::send(char buf[])//�������������ȫ����
{
    if (!connectStatus)
    {
        return  false;
    }
    DWORD   wlen = 0;
    bool    ret = false;
    ret = WriteFile(hPipe, buf, sizeof(buf), &wlen, 0);
    if (!ret)
    {
        CloseHandle(hPipe);//�رչܵ�
        connectStatus = false;
        return  false;
    }
    cout << "Send:" << buf << endl;
    return  true;
}
void	pipeBase::close()
{
    if (connectStatus)
    {
        CloseHandle(this->hPipe);//�رչܵ�
        connectStatus = false;
        cout << "�Ѿ��ر�!" << endl;
    }
}
void	pipeBase::connect()
{
    return;
}