#include "Room.h"
room::room()
{
	mclientlast = NULL;
}
void room::EnterRoom(ClientObj* c)
{
	if (mclientlast == NULL)
	{
		mclientlast = c;
	}
	else if (mmap.find(c) == mmap.end())
	{
		mmap[mclientlast] = c;
		mmap[c] = mclientlast;
		mclientlast=NULL;
	}
	return;
}

ClientObj* room::FindCompetitor(ClientObj* c)
{
	if (mmap.find(c) != mmap.end())
		return mmap[c];
}


room::~room()
{
	
}
