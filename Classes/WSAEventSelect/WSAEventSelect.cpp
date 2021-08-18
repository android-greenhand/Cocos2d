#include <stdio.h>
#include "../SocketInit/SocketInit.h"
#include"ThreadRecv.h"
#include "EventSelect.h"



int main()
{
	EventSelect eventselect(1);
	eventselect.CreateSocket();
	eventselect.BindSocket(12306, "192.168.6.1");
	eventselect.CreateBindEvent();
	eventselect.AcceptClient();
	return 0;
}