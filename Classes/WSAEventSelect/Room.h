#include "ThreadRecv.h"
#include <unordered_map>
class room
{
	ClientObj*  mclientlast;
	unordered_map<ClientObj*, ClientObj*> mmap;
	
public:
	room();
	~room();
	void EnterRoom(ClientObj* c);
	ClientObj* FindCompetitor(ClientObj* c);//’“µΩ∂‘ ÷
};