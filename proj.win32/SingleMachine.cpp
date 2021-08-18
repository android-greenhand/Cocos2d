
#include "proj.win32\SigleMachine.h"
SigleMachine::SigleMachine(ChessBoard * Pthis)
{
	c = Pthis;
}
void SigleMachine::InitGradeArry()
{
	memset(GameGrade, 0, sizeof(int)* 10 * 9);
	for (int k = 0; k < 16; k++)
	{
		if (c->m_stone[k]->s->isVisible())
		{
			GameGrade[c->m_stone[k]->m_From.first][c->m_stone[k]->m_From.second] = c->m_stone[k]->value;
		}
	}
	for (int k = 16; k < 32; k++)
	{
		if (c->m_stone[k]->s->isVisible())
		{
			GameGrade[c->m_stone[k]->m_From.first][c->m_stone[k]->m_From.second] = -c->m_stone[k]->value;
		}
	}
}
int  SigleMachine::CalculateNowGrade()
{
	int grade = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			grade += GameGrade[i][j];
		}
	}
	return grade;
}

void SigleMachine::InitGameProssArry()
{
	memcpy(GamePross, c->m_GamePross,sizeof(int)*90);
	/*for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			GamePross[i][j] = c->m_GamePross[i][j];
		}
	}*/
}

void SigleMachine::CanMoveStone()
{
	for (int k = 0; k < 16; k++)
	{
		if (c->m_stone[k]->s->isVisible())
		{
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					if (k == 8 && i == 0 && j == 8)
					{
						int aaaa=0;
					}
					if ((c->m_GamePross[i][j] > 7 || c->m_GamePross[i][j] == 0) && c->m_stone[k]->gular(c->m_GamePross, pair<int, int>(i, j)))
					{
						int max = -1500, flagi = -1, flagj = -1;
						InitGameProssArry();
						InitGradeArry();
						GamePross[c->m_stone[k]->m_From.first][c->m_stone[k]->m_From.second] = 0;
						GamePross[i][j] = c->m_stone[k]->m_k;

						GameGrade[c->m_stone[k]->m_From.first][c->m_stone[k]->m_From.second] = 0;
						GameGrade[i][j] = c->m_stone[k]->value;



						int temp = CompetitorCanMoveStone();
						if (temp >= max)
						{
							max = temp;
							flagi = i;
							flagj = j;
							if (max == 0)
							{
								int dddd = 0;
							}
						}

						if (-1 != flagi&&-1 != flagj)
						{
							StoneStep *ss = new StoneStep(k, flagi, flagj, max);
							pq.push(ss);
						}

					}

				}
			}


		}

	}
}
int  SigleMachine::CompetitorCanMoveStone()
{
	int min = 1500; //机器走了一步，计算玩家走一步的分数，把最小分数返回去
	for (int k = 16; k < 32; k++)
	{
		if (c->m_stone[k]->s->isVisible())
		{
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					if ( GamePross[i][j] <21 && c->m_stone[k]->gular(GamePross, pair<int, int>(i, j)))
					{
						int temp = GameGrade[i][j];
						GameGrade[i][j] = 0;
						int tem = CalculateNowGrade();
					
						if (tem <= min)
						{
							min = tem;
						}
						GameGrade[i][j] = temp;
					}
				}
			}
		}
	}
	return  min;
}


void SigleMachine::getresult()
{

	InitGradeArry();
	CanMoveStone();

	
	StoneStep *ss = pq.top();
	if (c->m_GamePross[ss->i][ss->j] >= 16)
	{
		int i = 16;
		for (; i < 32; i++)
		{
			if (c->m_stone[i]->m_From.first == ss->i&&c->m_stone[i]->m_From.second == ss->j)
				break;
		}
		c->SetData(i, ss->k, ss->i, ss->j);
	}
	else
	{
		c->SetData(-1, ss->k, ss->i, ss->j);
	}
	while (pq.empty())
	{
		StoneStep *ss = pq.top();
		delete ss;
		pq.pop();
	}
}