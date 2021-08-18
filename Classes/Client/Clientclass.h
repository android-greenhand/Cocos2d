#pragma once
#include"../SocketInit/SocketInit.h"
#include "SelectStone\SelectStone.h"
#include "timestamp.hpp"
class ChessBoard;
class Clientclass
{
	HANDLE m_recvthread;
	HANDLE m_sendthread;
	SocketInit m_init;//异常分支的时候直接调用析构函数
	SOCKET m_sclient;
	ChessBoard *m_chessboard;
	Timestamp   m_heartbeat;
	static Clientclass *m_pInstance;

	Clientclass();
public:
	SelectStone *m_SelectStone;
	static Clientclass * GetInstance();
	void SetChessBoard(ChessBoard * Pthis);
	void CreateSocket();
	void ConnectServer(int port, char *ip);
	
	void SendData(const char *s);
	
	
	static DWORD WINAPI Sendthread(LPVOID lp);  ///心跳检测
	static DWORD WINAPI Recvthread(LPVOID lp);
	~Clientclass();


	bool mloginreplay;
};

