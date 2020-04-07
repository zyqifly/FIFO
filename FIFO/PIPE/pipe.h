#pragma once
#include	<iostream>
using	namespace std;
#include<iostream>
#include<windows.h>
#include<ctime>
class pipeServer
{
public:
	pipeServer();
	~pipeServer();
	pipeServer(LPCWSTR pipe_name);
	LPCWSTR pipe_name = TEXT("\\\\.\\Pipe\\mypipe");
	void	closeServer();
	bool	read();
	bool	send();
	bool	connectStatus = false;

private:
	HANDLE hPipe = NULL;
	
};



class pipeClient
{
public:
	pipeClient();
	~pipeClient();
	pipeClient(LPCWSTR pipe_name);
	LPCWSTR pipe_name = TEXT("\\\\.\\Pipe\\mypipe");
	void	closeClient();
	bool	read();
	bool	send();
	bool	connectStatus = false;

private:
	HANDLE hPipe = NULL;

};

