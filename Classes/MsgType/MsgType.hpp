#pragma once
#include<Windows.h>
#include<stdio.h>
enum MsgType
{
	e_MsgLogin,
	e_MsgLoginReply,
	e_MsgEnterTalking,
	e_MsgTalking,
	e_MsgLeaveTaking,
	e_MsgStone,
	e_MsgRegretStone,
	e_MsgStoneColor,
	e_MsgisDouble,
	e_MsgRose,
	e_MsgHeartBeat,
	
};
struct MsgHead
{
	unsigned short msgtype;
	unsigned short msglength;
};
struct MsgLogin :public MsgHead
{
	MsgLogin()
	{
		msgtype = e_MsgLogin;
		msglength = sizeof(MsgLogin);
	}
	char name[12];
	char password[12];
	void SetUserName(const char *buff)
	{
		if (buff == NULL || sizeof(buff) > 12)
		{
#ifdef _DEBUG
			OutputDebugString(TEXT("用户名输入错误"));
#endif
			return;
		}
		strcpy(name, buff);

	}


	void SetUserPassword(const char *buff)
	{
		if (buff == NULL || sizeof(buff) > 12)
		{
#ifdef _DEBUG
			OutputDebugString(TEXT("密码输入错误"));
#endif
			return;
		}
		strcpy(password, buff);

	}
};
struct MsgLoginReplay :public MsgHead
{
	MsgLoginReplay()
	{
		msgtype = e_MsgLoginReply;
		msglength = sizeof(MsgLoginReplay);
	}
	int res;
};
struct MsgStone :public MsgHead
{
	MsgStone()
	{
		msgtype = e_MsgStone;
		msglength = sizeof(MsgStone);
	}
	int now_stone;
	int last_stone;
	int i, j;
};
struct MsgTalking :public MsgHead
{
#define _BUFFER_MAX_SIZE 128
	MsgTalking()
	{
		msgtype = e_MsgTalking;
		msglength = sizeof(MsgTalking);
	}
	char buff[_BUFFER_MAX_SIZE];

	void SetText(const char *buff)
	{
		if (buff == NULL || sizeof(buff) >128)
		{
#ifdef _DEBUG
			OutputDebugString(TEXT("文本输入有误"));
#endif
			return;
		}
		strcpy(this->buff, buff);

	}
};

struct MsgRegretStone :public MsgHead
{
	MsgRegretStone()
	{
		msgtype = e_MsgRegretStone;
		msglength = sizeof(MsgRegretStone);
	}
};

struct MsgStoneColor :public MsgHead
{
	MsgStoneColor()
	{
		msgtype = e_MsgStoneColor;
		msglength = sizeof(MsgStone);
	}
	bool red;
	
};

struct MsgisDouble :public MsgHead
{
	MsgisDouble()
	{
		msgtype = e_MsgisDouble;
		msglength = sizeof(MsgisDouble);
	}
	double ll = 10;
};


struct MsgRose :public MsgHead
{
	MsgRose()
	{
		msgtype = e_MsgRose;
		msglength = sizeof(MsgRose);
	}
};


struct MsgHeartBeat :public MsgHead
{
	MsgHeartBeat()
	{
		msgtype = e_MsgHeartBeat;
		msglength = sizeof(MsgHeartBeat);
	}
};