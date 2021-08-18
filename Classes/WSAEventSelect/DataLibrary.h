#pragma once
#include <iostream>
#include <winsock2.h>
#include <windows.h>

#include <Windows.h>
#include <mysql.h>



class DataLibrary
{
	MYSQL mmysql;
public:
	void ConnectDataLibrary();
	bool CheckInfo(char *name, char * ps);
};