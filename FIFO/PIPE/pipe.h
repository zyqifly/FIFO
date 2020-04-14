#pragma once
#include	<iostream>
using	namespace std;
#include<iostream>
#include<windows.h>
#include<ctime>
class pipeBase
{
public:
	pipeBase();
	~pipeBase();
	virtual	bool	read(char	buf[]);
	virtual	bool	send(char	buf[]);
	virtual	void	close();
	virtual	void	connect();
	bool	connectStatus = false;
	LPCWSTR pipe_name = TEXT("\\\\.\\Pipe\\mypipe");
	HANDLE hPipe = NULL;

};


class pipeServer : public	pipeBase
{
public:
	pipeServer();
	~pipeServer();
	pipeServer(LPCWSTR pipe_name);
	void	connect();
	
};



class pipeClient: public	pipeBase
{
public:
	pipeClient();
	~pipeClient();
	pipeClient(LPCWSTR pipe_name);
	void	connect();

};



