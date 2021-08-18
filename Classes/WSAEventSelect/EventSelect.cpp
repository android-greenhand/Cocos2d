#include "EventSelect.h"

EventSelect::EventSelect()
{
	m_sserver = SOCKET_ERROR;
	m_threadcount = 1;
	m_thread = new ThreadRecv[m_threadcount];
	m_clientcountthread = CreateThread(0, 0,ClientCountThread, this, 0, 0);
}

EventSelect::EventSelect(int threadcount)
{
	m_sserver = SOCKET_ERROR;
	m_threadcount = threadcount;
	m_thread = new ThreadRecv[m_threadcount];
	m_clientcountthread = CreateThread(0, 0, ClientCountThread, this, 0, 0);
}
void EventSelect::CreateSocket()
{
	m_sserver = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_sserver == -1)
	{
		printf("服务器套接字创建失败\n");
		return ;
	}
	else
	{
		printf("服务器套接字创建成功\n");
	}
}
void EventSelect::BindSocket(short ht,char *ip)
{
	sockaddr_in sadd;
	sadd.sin_family = AF_INET;
	sadd.sin_port = htons(ht);
	sadd.sin_addr.S_un.S_addr = inet_addr(ip);
	if (bind(m_sserver, (const sockaddr *)&sadd, sizeof(sockaddr_in)) != 0)
	{
		printf("绑定失败\n");
	}
	else
	{
		printf("绑定成功\n");
	}

	listen(m_sserver, 100);
}
void EventSelect::CreateBindEvent()
{
	m_hsserverevent = WSACreateEvent();//手动 无信号
	WSAEventSelect(m_sserver, m_hsserverevent, FD_ACCEPT | FD_CLOSE);
}
     
void EventSelect::AcceptClient()
{
	while (1)
	{
		DWORD dw = WaitForSingleObject(m_hsserverevent, INFINITE);
		if (dw == 0)
		{
			ResetEvent(m_hsserverevent);
			sockaddr_in cadd = { 0 };
			int size = sizeof(sockaddr_in);
			SOCKET sclient = accept(m_sserver, (sockaddr *)&cadd, &size);
			if (sclient == SOCKET_ERROR)
			{
				printf("客户端连接失败\n");
			}
			else
			{
				printf("客户端连接成功\n");
				printf("客户端ip: %s\n", inet_ntoa(cadd.sin_addr));
				AssignToThread(sclient,cadd);
			}
		}
		else
		{
			printf("出现错误 %d", WSAGetLastError());
		}
		

	}
}
void EventSelect::AssignToThread(SOCKET sclient, sockaddr_in cadd)
{
	int min = m_thread[0].getclientsize();
	int flag = 0;
	for (int i = 1; i < m_threadcount; i++)
	{
		if (min>m_thread[i].getclientsize())
		{
			min = m_thread[i].getclientsize();
			flag = i;
		}
	}
	if (min >= 63)
	{
		printf("服务器已达到最大容量\n");
		return;
	}
	m_thread[flag].pushclient(sclient, cadd);
}
DWORD WINAPI EventSelect::ClientCountThread(LPVOID lp)
{
	EventSelect* th = (EventSelect *) lp;
	while (1)
	{
		if (th->m_timestamp.getElapsedTimeInMicroSec()>= 1)
		{
			int n = 0;
			for (int i = 0; i < th->m_threadcount; i++)
			{
				EnterCriticalSection(&(th->m_thread[i].m_sec));
				n += th->m_thread[i].getclientsize();
				
				for (int j = 0; j < th->m_thread[i].getclientsize(); j++)
				{
					th->m_thread[i].m_client[j]->heartbeat++;
					if (th->m_thread[i].m_client[j]->heartbeat >= 20)
					{
						WSACloseEvent(th->m_thread[i].m_client[j]->cevent);
						closesocket(th->m_thread[i].m_client[j]->csocket);
						//delete  th->m_thread[i].m_client[j];

						ThreadRecv::operator delete(&(th->m_thread[i].m_client[j]));
						th->m_thread[i].m_client.erase(th->m_thread[i].m_client.begin() + j);
						SetEvent(th->m_thread[i].m_events[0]);//
					}
				}
				LeaveCriticalSection(&(th->m_thread[i].m_sec));
			}
			printf("已连接的客户端数量： %d\n", n);
			th->m_timestamp.update();
			Sleep(1000);
		}
		
	}
}
EventSelect::~EventSelect()
{
	WaitForSingleObject(m_clientcountthread, INFINITE);
	CloseHandle(m_clientcountthread);
	closesocket(m_sserver);
	delete[]m_thread;
	CloseHandle(m_hsserverevent);
}
