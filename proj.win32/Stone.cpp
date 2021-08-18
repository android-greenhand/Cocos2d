#include "Stone.h"

Stone::Stone(int a,int i, int j, cocos2d::Sprite * s,int v)
{
		m_k = a;
		m_Init.first = i;
		m_Init.second = j;
		m_From = m_Init;
		m_GameArry.push_back(m_Init);
		if (a < 20)
		{
			m_IsRed = false;
		}
		else
		{
			m_IsRed = true;
		}
		this->s=s;
		value = v;
}
bool Stone::gular(int game_arr[10][9], pair<int, int> To)
{
	return true;
}
Stone::~Stone()
{
}
bool ChessCarStone::gular(int game_arr[10][9], pair<int, int> To)
 {
	int x0 = m_From.first;
	int y0 = m_From.second;
	int x1 = To.first;
	int y1 = To.second;
	if (x0 == x1&&y0 == y1)
	{
		return false;
	}
	if (x0 != x1&&y0 != y1)
	{
		return false;
	}
	if (x0 == x1)
	{
		int max = y0 > y1 ? y0 : y1;
		int min = y0 < y1 ? y0 : y1;
		for (int j = min + 1; j< max; j++)
		{
			if (game_arr[x0][j])
			{
				return false;
			}
		}
	}
	else
	{
		int max = x0 > x1 ? x0 : x1;
		int min = x0 < x1 ? x0 : x1;
		for (int i = min + 1; i< max; i++)
		{
			if (game_arr[i][y0])
			{
				return false;
			}
		}
	}
	return true;
}

bool ChessHorseStone::gular(int game_arr[10][9], pair<int, int> To)
{
	int x0 = m_From.first;
	int y0 = m_From.second;
	int x1 = To.first;
	int y1 = To.second;
	if ((abs(x0 - x1) + abs(y0 - y1)) != 3)
	{
		return false;
	}
	if (x0 == x1||y0 ==y1)
	{
		return false;
	}

	if (y1 - y0 == 2 && game_arr[x0][y0+1])
	{
		return false;
	}
	if (y1 - y0 == -2 && game_arr[x0][y0-1])
	{
		return false;
	}
	if (x1 - x0 == 2 && game_arr[x0+1][y0])
	{
		return false;
	}
	if (x1 - x0 == -2 && game_arr[x0-1][y0])
	{
		return false;
	}
	return true;
}

bool ChessElephantStone::gular(int game_arr[10][9], pair<int, int> To)
{

	int x0 = m_From.first;
	int y0 = m_From.second;
	int x1 = To.first;
	int y1 = To.second;
	//走的是不是对的点
	if ((abs(x0 - x1) + abs(y0 - y1)) != 4 || (abs(x0 - x1)) != 2 || (abs(y0 - y1)) != 2)
	{
		return false;
	}
	//象不能过河
	if (game_arr[x0][y0] == 3)
	{
		if (x1 >5)
		{
			return false;
		}
	}
	else
	{
		if (x1 <5)
		{
			return false;
		}
	}

	//不能瘪腿
	if (x1 - x0 == 2)
	{
		if (y1 - y0 == 2 && game_arr[x0 + 1][y0 + 1])
		{
			return false;
		}
		else if (y1 - y0 == -2 && game_arr[x0 +1][y0 - 1])
		{
			return false;
		}
	}
	else if (x1 - x0 == -2)
	{
		if (y1 - y0 == 2 && game_arr[x0 - 1][y0 + 1])
		{
			return false;
		}
		else if (y1 - y0 == -2 && game_arr[x0 - 1][y0 - 1])
		{
			return false;
		}
	}
	return true;
}
//士的规则
bool ChessSoldierStone::gular(int game_arr[10][9], pair<int, int> To)
{
	int x0 = m_From.first;
	int y0 = m_From.second;
	int x1 = To.first;
	int y1 = To.second;
	if (y1 > 2 && y1 < 6)
	{
		if (x1 < 3 || x1>6)
		{
			if ((abs(x0 - x1) + abs(y0 - y1)) == 2 && x0 != x1&&y0 != y1)
			{
				return true;
			}
		}
	}
	return false;
}
bool ChessGeneralStone::gular(int game_arr[10][9], pair<int, int> To)
{
	int x0 = m_From.first;
	int y0 = m_From.second;
	int x1 = To.first;
	int y1 = To.second;
	int enemy_x = -1;
	int enemy_y = -1;
	if (game_arr[x0][y0] == 5)
	{
		for (int i = 0; i < 10; i++)//****
		{
			for (int j = 0; j < 9; j++)
			{
				if (game_arr[i][j] == 25)
				{
					//得到对方将的的位置
					enemy_x = i;
					enemy_y = j;
				}
			}
		}
	}
	else if (game_arr[x0][y0] == 25)
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (game_arr[i][j] == 5)
				{
					//得到对方将的的位置
					enemy_x = i;
					enemy_y = j;
				}
			}
		}
	}
	int n = 0;
	if (y1 == enemy_y)
	{
		int min = x0 < enemy_x ? x0 + 1 : enemy_x + 1;
		int max = x0> enemy_x ? x0 : enemy_x;
		for (int i = min; i<max; i++)
		{
			if (game_arr[i][y1])
			{
				n++;
			}
		}
		if (n == 0)
		{
			return false;
		}
	}

	if (y1 > 2 && y1 < 6)
	{
		if (x1 < 3 || x1>6)
		{
			if ((abs(x0 - x1) + abs(y0 - y1)) == 1)
			{
				return true;
			}

		}
	}
	return false;
}
//炮的规则
bool ChessCannonStone::gular(int game_arr[10][9], pair<int, int> To)
{
	int x0 = m_From.first;
	int y0 = m_From.second;
	int x1 = To.first;
	int y1 = To.second;
	if (x0 == x1&&y0 == y1)
	{
		return false;
	}
	if (x0 != x1&&y0 != y1)
	{
		return false;
	}
	int n = 0;

	if (x0 == x1)
	{
		int max = y0 > y1 ? y0 : y1;
		int min = y0 < y1 ? y0 : y1;
		for (int j = min + 1; j< max; j++)
		{
			if (game_arr[x0][j])
			{
				n++;
			}
		}
	}
	else
	{
		int max = x0 > x1 ? x0 : x1;
		int min = x0 < x1 ? x0 : x1;
		for (int i = min + 1; i< max; i++)
		{
			if (game_arr[i][y0])
			{
				n++;
			}
		}
	}
	if (n == 0 && game_arr[x1][y1])
	{
		return false;
	}
	if (n > 1)
	{
		return false;
	}
	if (n == 1 && game_arr[x1][y1] == 0)
	{
		return false;
	}
	return true;
}
//卒兵规则
bool ChessObiitStone::gular(int game_arr[10][9], pair<int, int> To)
{
	int x0 = m_From.first;
	int y0 = m_From.second;
	int x1 = To.first;
	int y1 = To.second;
	if ((abs(x0 - x1) + abs(y0 - y1)) != 1)
	{
		return false;
	}

	if (game_arr[x0][y0] == 7)
	{
		if (x0 < 5 && x1 == x0)
		{
			return false;
		}
		if (x1 < x0)
		{
			return false;
		}
	}
	else
	{
		if (x0 >4 && x1 == x0)
		{
			return false;
		}
		if (x1 > x0)
		{
			return false;
		}
	}
	return true;
}

