#include "SocketInit.h"
#pragma comment(lib, "Ws2_32.lib")

SocketInit::SocketInit()
{
	//���ض�̬���ӿ�
	WORD version = MAKEWORD(2, 2);
	WSADATA data;
	WSAStartup(version, &data);
}


SocketInit::~SocketInit()
{
	//����������ٵ�ʱ�� ֱ�ӵ��õ�������
	WSACleanup();
}
