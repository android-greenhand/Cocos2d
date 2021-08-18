#include "MemoryPool.h"

void MemoryPool::InitMemoryPool(int s, int c)
{
	msize = s;
	mcount = c;
	buff = (char*)malloc((msize + sizeof(MemoryBlock))*c);
	phead = (MemoryBlock*)buff;
	MemoryBlock *tmp = phead;
	for (int i = 0; i < mcount - 1; i++)
	{
		tmp->ip = i;
		tmp->flag = 1;
		tmp->pnext = (MemoryBlock*)(buff + (msize + sizeof(MemoryBlock))*(i + 1));
		tmp->pparent = this;
		tmp = tmp->pnext;
	}
	tmp->ip = mcount - 1;
	tmp->flag = 1;
	tmp->pnext = NULL;
	tmp->pparent = this;
}
void * MemoryPool::MallocMemoryBlock()
{
	MemoryBlock *tmp = phead;
	if (tmp)
	{
		phead = tmp->pnext;
	}
	else
	{
		tmp = (MemoryBlock*)malloc((msize + sizeof(MemoryBlock)));
		tmp->ip = -1;
		tmp->flag = 0;
		tmp->pnext = NULL;
	}
	return tmp + 1;
}
void MemoryPool::FreeMemoryBlock(void * p)
{
	MemoryBlock *tmp = (MemoryBlock *)p-1;
	if (tmp->flag)
	{
		tmp->pnext = phead;
		phead = tmp;
	}
	else
	{
		free(tmp);
	}
}

MemoryPool::~MemoryPool()
{
	free(phead);
}

MemoryManager* MemoryManager::pMemoryManager = NULL;
MemoryManager::MemoryManager()
{
	p64.InitMemoryPool(256, 1000);
	p128.InitMemoryPool(512, 1000);
}
MemoryManager* MemoryManager::Getinstance()
{
	static MemoryManager m;
	return &m;
}
void * MemoryManager::MallocMemoryPool(size_t s)
{
	if (s < 256)
	{
	return p64.MallocMemoryBlock();
	}
	else if (s < 512)
	{
		return p128.MallocMemoryBlock();
	}
	else
	{
		MemoryBlock*tmp = (MemoryBlock*)malloc(s + sizeof(MemoryBlock));
		tmp->ip = -1;
		tmp->flag = 0;
		tmp->pnext = NULL;
		return tmp + 1;
	}

}
void MemoryManager::FreeMemoryPool(void * p)
{
	MemoryBlock*tmp = (MemoryBlock*)p-1;
	if (tmp->flag)
	{
		tmp->pparent->FreeMemoryBlock(p);
	}
	else
	{
		free(p);
	}
	
}

MemoryManager::~MemoryManager()
{
}
