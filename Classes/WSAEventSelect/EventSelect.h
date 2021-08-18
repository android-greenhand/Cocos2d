#pragma once
#include <stdio.h>
#include "../SocketInit/SocketInit.h"
#include "timestamp.hpp"

#include"ThreadRecv.h"
class EventSelect
{
private:
	SocketInit m_init;//异常分支的时候直接调用析构函数
	SOCKET m_sserver;
	int m_threadcount;
	ThreadRecv *m_thread;
	HANDLE m_hsserverevent;
	HANDLE m_clientcountthread;
	Timestamp m_timestamp;
public:
	EventSelect();
	EventSelect(int threadcount);
	void CreateSocket();
	void BindSocket(short ht, char *ip);
	void CreateBindEvent();
	void AcceptClient();
	static	DWORD WINAPI ClientCountThread(LPVOID lp);
	~EventSelect();
private:
	void AssignToThread(SOCKET sclient, sockaddr_in cadd);
};

