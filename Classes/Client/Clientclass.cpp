#include "Clientclass.h"
#include <stdio.h>
#include "../MsgType/MsgType.hpp"
#include "ChessBoard.h"


Clientclass * Clientclass::m_pInstance = NULL;
Clientclass *Clientclass::GetInstance()
{
	        if (m_pInstance == NULL) //�ж��Ƿ��һ�ε���
				m_pInstance = new Clientclass();
	       return m_pInstance;
}
Clientclass::Clientclass()
{
	m_chessboard = NULL;
	m_sclient = INVALID_SOCKET;
	CreateSocket();
	ConnectServer(12306, "192.168.6.1");

	mloginreplay = false;//��½�ظ�
}
void Clientclass::SetChessBoard(ChessBoard * Pthis)
{
	m_chessboard = Pthis;
}
void Clientclass::CreateSocket()
{
		m_sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (m_sclient == -1)
		{
			printf("�ͻ����׽��ִ���ʧ��\n");
		}
		else
		{
			printf("�ͻ����׽��ִ����ɹ�\n");
		}
}
void Clientclass::ConnectServer(int port,char *ip)
{
		sockaddr_in cadd = {0};
		cadd.sin_family = AF_INET;
		cadd.sin_port = htons(port);
		cadd.sin_addr.S_un.S_addr = inet_addr(ip);//�п������ⲻ��
		if (::connect(m_sclient, (sockaddr *)&cadd, sizeof(sockaddr_in)) != 0)
		{
			printf("����������ʧ��:%d\n",WSAGetLastError());
			closesocket(m_sclient);
		}
		else
		{
			printf("���������ӳɹ�\n");
		}
		Sleep(1);
		m_recvthread = CreateThread(NULL, 0, Recvthread, this, 0, 0);
		m_sendthread = CreateThread(NULL, 0, Sendthread, this, 0, 0);
}
DWORD WINAPI Clientclass::Sendthread(LPVOID lp)
{
	Clientclass *pthis = (Clientclass *)lp;
	while (1)
	{
		if (pthis->m_heartbeat.getElapsedTimeInMicroSec() >= 1)
		{
			MsgHeartBeat msg;
			send(pthis->m_sclient, (const char *)&msg, msg.msglength, 0);
		}
		pthis->m_heartbeat.update();
		Sleep(3000);
		
			
	}
}
 DWORD WINAPI Clientclass::Recvthread(LPVOID lp)
 {
	 Clientclass *cli = (Clientclass *)lp;
	 while (1)
	 {
		
		 char buff[1024] = { 0 };
		 int n = recv(cli->m_sclient, buff, 1024, 0);

			 if (n > 0)
			 {
				 MsgHead *msg = (MsgHead *)buff;
				 switch (msg->msgtype)
				 {
				 case  e_MsgLoginReply:
				 {
										  MsgLoginReplay *msgloginreplay = (MsgLoginReplay*)msg;
										  if (msgloginreplay->res == 1)
										  {
											  printf("��¼�ɹ�\n");
											  cli->mloginreplay = true;
										  }
										  break;
				 }
				 case e_MsgStone:
				 {
									MsgStone *msgstone = (MsgStone *)msg;
									cli->m_chessboard->SetData(msgstone->last_stone,msgstone->now_stone,msgstone->i,msgstone->j);
									break;
				 }

				 case e_MsgTalking:
				 {
									  MsgTalking *msgtalking = (MsgTalking *)msg;
									  cli->m_chessboard->SetText(msgtalking->buff);
									  break;
				 }
				 case e_MsgRegretStone:
				{
										  cli->m_chessboard->RegretStone();
										  break;
				}
				 case e_MsgStoneColor:
				 {
										 MsgStoneColor  msgstonecolor;
	
											 cli->m_SelectStone->SelectStoneColor(msgstonecolor.red);
										 break;
				 }
				 case e_MsgRose:
					 {
								   cli->m_chessboard->PlayRose();
						 break;
					 }
				 default:

					 OutputDebugString(TEXT("��Ϣ����ʧ��\n"));

					 break;
				 }
		 }
	 }
		
 }

 void Clientclass::SendData(const char *s)
 {
	 MsgHead *msg = (MsgHead*)s;
	 send(m_sclient, (const char *)msg, msg->msglength, 0);

 }


Clientclass::~Clientclass()
{
	WaitForSingleObject(m_sendthread, INFINITE);
	WaitForSingleObject(Recvthread, INFINITE);
	closesocket(m_sclient);
	CloseHandle(m_sendthread);
	CloseHandle(m_recvthread);
}
