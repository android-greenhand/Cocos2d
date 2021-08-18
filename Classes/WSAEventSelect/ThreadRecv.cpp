#include "ThreadRecv.h"

#include "../MsgType/MsgType.hpp"

#include "Room.h"
#include "DataLibrary.h"

DWORD WINAPI ThreadRecv::ThreadPro(LPVOID lp)
{
	ThreadRecv* th = (ThreadRecv *)lp;
	while (1)
	{
		int ClientCount = th->m_client.size();
		DWORD index = WSAWaitForMultipleEvents(th->m_client.size() + 1, th->m_events, false, INFINITE, 0);
		if (index == WSA_WAIT_FAILED)
		{
			printf("%d\n", WSAGetLastError());
		}
		for (int i = index; i <th->m_client.size() + 1; i++)
		{
			DWORD dw = WSAWaitForMultipleEvents(1, &(th->m_events[i]), true, 0, 0);
			if (dw == WAIT_OBJECT_0)
			{
				ResetEvent(th->m_events[i]);//有信号设置为无信号
				if (i == 0)
				{
					EnterCriticalSection(&(th->m_sec));
					int s = th->m_clientbuffer.size();
					for (int j = 0; j < s; j++)
					{
						th->m_client.push_back(th->m_clientbuffer[j]);
					}
					th->m_clientbuffer.clear();
					LeaveCriticalSection(&(th->m_sec));


					s = th->m_client.size();
					for (int j = 0; j < s; j++)
					{
						th->m_events[j + 1] = th->m_client[j]->cevent;
					}
					break;
				}
				WSANETWORKEVENTS networkevent;
				WSAEnumNetworkEvents(th->m_client[i - 1]->csocket, th->m_events[i], &networkevent);
				if (networkevent.lNetworkEvents&FD_READ)
				{
					if (networkevent.iErrorCode[FD_READ_BIT] != 0)
					{
						printf("接受数据错误：%d\n", networkevent.iErrorCode[FD_READ_BIT]);
					}
					ClientObj *t = th->m_client[i - 1];
					int n = recv(t->csocket,t->buff+t->lastpos, 1024, 0);
					if (n > 0)
					{
						th->MsgProc(t, n);
					}
					else
					{
						printf("其他错误\n");
						closesocket(th->m_client[i - 1]->csocket);
						WSACloseEvent(th->m_client[i - 1]->cevent);
						//delete th->m_client[i - 1];
						ThreadRecv::operator delete(&(th->m_client[i - 1]));
						th->m_client.erase(th->m_client.begin() + i - 1);		
						SetEvent(th->m_events[0]);//设置有信号
						break;
					}	
				}
				if (networkevent.lNetworkEvents&FD_CLOSE)
				{
					if (networkevent.iErrorCode[FD_CLOSE_BIT] != 0)
					{
						/*printf("关闭客户端错误：%d\n", networkevent.iErrorCode[FD_READ_BIT]);*/
					
					}
					printf("客户端已关闭\n");
					
					WSACloseEvent(th->m_client[i - 1]->cevent);
					closesocket(th->m_client[i - 1]->csocket);
					//delete th->m_client[i - 1];
					
					ThreadRecv::operator delete(&(th->m_client[i - 1]));
					th->m_client.erase(th->m_client.begin() + i - 1);
				
					SetEvent(th->m_events[0]);//设置有信号
					break;
				}
				
			}
			/*else
			{
				printf("%d\n", GetLastError());
			}*/
		}
	}
}

ThreadRecv::ThreadRecv()
{
	InitializeCriticalSection(&m_sec);
	m_events[0] = WSACreateEvent();
	m_handle = CreateThread(0, 0, ThreadPro, this, 0, 0);
	m_room = new room();
}
int ThreadRecv::getclientsize()
{
	return m_client.size();
}
void ThreadRecv::pushclient(SOCKET sclient, sockaddr_in cadd)
{
 	ClientObj *client = (ClientObj *)ThreadRecv::operator new(sizeof(ClientObj));
	client->csocket = sclient;
	client->addr = cadd;
	client->lastpos = 0;
	client->heartbeat = 0;
	HANDLE clientevent = WSACreateEvent();
	client->cevent = clientevent;
	WSAEventSelect(client->csocket, clientevent, FD_READ | FD_CLOSE);

	EnterCriticalSection(&m_sec);
	m_clientbuffer.push_back(client);
	SetEvent(m_events[0]);
	LeaveCriticalSection(&m_sec);
}
int ThreadRecv::MsgProc(ClientObj *client, int ncount) //处理粘包问题
{
	int ntotal = client->lastpos + ncount;
	char *t = client->buff;
	MsgHead *head=NULL;
	while (ntotal >= sizeof(head))
	{
		head = (MsgHead*)t;
		if (ntotal >=head->msglength)
		{
			OnMsg(client,(char *) head);
			t += head->msglength;
			ntotal -= head->msglength;
		}
		else
		{
			break;
		}
	}
	memcmp(client->buff, t, ntotal);
	client->lastpos = ntotal;
	return 0;
}
void ThreadRecv::OnMsg(ClientObj * client, char *buff)
{
	MsgHead *msg = (MsgHead *)buff;
	switch (msg->msgtype)
	{
	case e_MsgLogin:
	{
					   MsgLogin *msglogin = (MsgLogin*)msg;
					   //可以与数据库进行比对
					   printf("用户名：%s,密码：%s\n", msglogin->name, msglogin->password);

					   DataLibrary d;
					   d.ConnectDataLibrary();
					   if (d.CheckInfo(msglogin->name, msglogin->password))
					   {
						   MsgLoginReplay msgloginreplay;
						   msgloginreplay.res = 1;
						   send(client->csocket, (char *)&msgloginreplay, msgloginreplay.msglength, 0);
					   }
					   
					   break;
	}
	case e_MsgTalking:
	{
				MsgTalking *msgtalking = (MsgTalking *)msg;
				send(m_room->FindCompetitor(client)->csocket, (const char *)msgtalking, msgtalking->msglength, 0);
				break;
	}
	case e_MsgStone:
	{
					MsgStone *msgstone = (MsgStone*)msg;
					send(m_room->FindCompetitor(client)->csocket, (const char *)msgstone, msgstone->msglength, 0);
					break;
	}
	case e_MsgRegretStone:
	{
				    MsgRegretStone msgregretstone;
					send(m_room->FindCompetitor(client)->csocket, (const char *)&msgregretstone, msgregretstone.msglength, 0);
					break;
	}
	case e_MsgStoneColor:
	{
					MsgStoneColor  *msgstonecolor = (MsgStoneColor *)msg;;
					send(m_room->FindCompetitor(client)->csocket, (const char *)msgstonecolor, msgstonecolor->msglength, 0);
					break;
	}
	case e_MsgisDouble:
	{
					m_room->EnterRoom(client);
					break;
	}
	case e_MsgRose:
	{
					  MsgRose  *msgrose = (MsgRose *)msg;;
					  send(m_room->FindCompetitor(client)->csocket, (const char *)msgrose, msgrose->msglength, 0);
		break;
	}
	case e_MsgHeartBeat:
	{
				  client->heartbeat = 0;
					  
					  break;
	}

	case  e_MsgLoginReply:break;
	default:
		#ifdef _DEBUG
		OutputDebugString(TEXT("消息解析失败\n"));
		#endif
		break;
	}
}


ThreadRecv::~ThreadRecv()
{
	WSAWaitForMultipleEvents(m_client.size(), &m_handle, true, INFINITE, 0);
	CloseHandle(m_handle);
	WSACloseEvent(m_client[0]);
	for (int i = 0; i < m_client.size(); i++)
	{
		closesocket(m_client[i]->csocket);
		WSACloseEvent(m_client[i]->cevent);
		//delete m_client[i];

		ThreadRecv::operator delete(&m_client[i]);
	}
	m_client.clear();
	DeleteCriticalSection(&m_sec);
}


void * ThreadRecv::operator new(size_t p)
{
	return MemoryManager::Getinstance()->MallocMemoryPool(p);
};

void  ThreadRecv::operator delete(void * p)
{
	return MemoryManager::Getinstance()->FreeMemoryPool(p);
};