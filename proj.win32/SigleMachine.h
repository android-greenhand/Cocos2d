#include "ChessBoard.h"
#include <queue>
struct StoneStep
{
	int k;
	int i;
	int j;
	int max;
	StoneStep(int k, int i, int j, int max) :k(k), i(i), j(j), max(max){};
};
struct compare
{
	bool operator ()(const StoneStep *a, const StoneStep *b)
	{
		return a->max<b->max;
	}
};
class SigleMachine 
{
public:
	ChessBoard * c;
	priority_queue<StoneStep *, vector<StoneStep *>, compare> pq;
	int GamePross[10][9];
	int GameGrade[10][9];
	
	SigleMachine(ChessBoard * Pthis);
	int mnowgrade;
	int CalculateNowGrade();
	void CanMoveStone();
	int CalculateGrade();
	int  CompetitorCanMoveStone();
	void getresult();
	void InitGradeArry();
	void InitGameProssArry();

};