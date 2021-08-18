#pragma once
#include <vector>
#include <stdio.h>
#include <WinSock2.h>
#include <winsock.h>

#include "MemoryPool\MemoryPool.h"
using namespace std;
class room;
struct ClientObj
{
#define _BUFFER_MAX_SIZE 256
	WSAEVENT cevent;
	SOCKET  csocket;
	sockaddr_in addr;
	int lastpos;
	char buff[_BUFFER_MAX_SIZE];
	int heartbeat;//心跳检测
};
class ThreadRecv
{ 
	#define max_event 64
	HANDLE m_handle;
	vector<ClientObj*>  m_clientbuffer;
	room * m_room;


	static void * operator new(size_t p);

	
	
public:
	WSAEVENT m_events[max_event];
	vector<ClientObj*>  m_client;
	CRITICAL_SECTION m_sec;
	ThreadRecv();
	static DWORD WINAPI ThreadPro(LPVOID lp);
	int getclientsize();
	void pushclient(SOCKET sclient, sockaddr_in cadd);
	int  MsgProc(ClientObj *client, int ncount); //处理粘包问题
	void OnMsg(ClientObj * client, char *buff);

	static void  operator delete(void * p);
	~ThreadRecv();
 

	//void * operator new(size_t p)
	///*{
	//	return MemoryManager::Getinstance()->MallocMemoryPool(p);
	//}*/;
	//void  operator delete(void * p)
	//{
	//	return MemoryManager::Getinstance()->FreeMemoryPool(p);
	//};
	void * operator new[](size_t p)
	{
		return MemoryManager::Getinstance()->MallocMemoryPool(p);
	};
	void  operator delete[](void *p)
	{
		return MemoryManager::Getinstance()->FreeMemoryPool(p);
	};
};


