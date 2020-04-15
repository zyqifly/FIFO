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
    //�����Ǹ���ѭ�������Էŵ���һ���߳�
    while (WaitNamedPipe(pipe_name, NMPWAIT_WAIT_FOREVER) == FALSE)
    {
        //cout << "wait����������" << endl;
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
    return  true;
}
pipeClient::pipeClient(LPCWSTR pipe_name)
{
    this->pipe_name = pipe_name;
    
}

bool	pipeBase::read(char buf[], DWORD	len)//�������ݣ�������
{
    if (!this->connectStatus)
    {
        return  false;
    }
    //char buf[256] = "Hello Pipe";
    DWORD rlen = 0;
    if (ReadFile(hPipe, buf, len, &rlen, NULL) == FALSE)//��ȡ�ܵ��е����ݣ��ܵ���һ��������ļ���
    {
        CloseHandle(hPipe);//�رչܵ�
        connectStatus = false;
        cout << "��ʧ�ܣ��رգ�" << endl;
        return  false;
    }
    else
    {
        cout << "Rcv:" << buf << endl;
    }

    return  true;
}
bool	pipeBase::send(char buf[], DWORD	len)//�������������ȫ����
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
        //CloseHandle(hPipe);//�رչܵ�
        connectStatus = false;
        cout << "дʧ�ܣ��رգ�" << endl;
        return  false;
    }
    cout << "Send:" << buf << endl;
    return  true;
}
void	pipeBase::close()
{
    if (connectStatus)
    {
        //CloseHandle(this->hPipe);//�رչܵ�
        connectStatus = false;
        cout << "�Ѿ��ر�!" << endl;
    }
}
bool	pipeBase::connect()
{
    return false;
}