#include "DataLibrary.h"
#pragma comment(lib,"E:\\MySQL Server 5.7\\lib\\libmysql.lib")
#include <string>
#include <iostream>
using namespace std;

void DataLibrary::ConnectDataLibrary()
{ 
	const char user[] = "root";
	const char pswd[] = "1111";
	const char host[] = "localhost";
	const char table[] = "chinesechess";
	unsigned int port = 3306;
	mysql_init(&mmysql);
	if (mysql_real_connect(&mmysql, host, user, pswd, table, port, NULL, 0))
	{
		printf("���ݿ����ӳɹ�������\n");
	}
	else
	{
		printf("���ݿ�����ʧ�ܣ�����\n");
	}
}

bool DataLibrary::CheckInfo(char *name, char * ps)
{
	//select count(*) into n from info where admin = ad and pd = passwd;
	char* m = name;
	char* n = ps;
	string q1 = "select * from info where username = '";
	string q2 = m;
	string q3 = "'and userpassword = '";
	string q4 = n;
	string q5 = "'";
	string cc = q1 + q2 + q3 + q4 + q5;
	const char *pp = cc.c_str();
	//���ݿ��ѯ��¼��Ϣ
	int res;
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	res = mysql_query(&mmysql, pp);
	if (!res)
	{
		result = mysql_store_result(&mmysql);
		if (result)
		{
			while (sql_row = mysql_fetch_row(result))//��ȡ���������
			{
				return true;
			}
		}
	}
	else
	{
		printf("��ѯʧ�ܣ���\n");
		return false;
	}
	return false;
	
}