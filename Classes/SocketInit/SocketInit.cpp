#include "SocketInit.h"
#pragma comment(lib, "Ws2_32.lib")

SocketInit::SocketInit()
{
	//加载动态链接库
	WORD version = MAKEWORD(2, 2);
	WSADATA data;
	WSAStartup(version, &data);
}


SocketInit::~SocketInit()
{
	//定义对象，销毁的时候 直接调用调用析构
	WSACleanup();
}
