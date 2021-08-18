#ifndef _MEMORY_H
#define _MEMORY_H

#include "MemoryPool.h"


void * operator new(unsigned int p)
{
	return MemoryManager::Getinstance()->MallocMemoryPool(p);
};
void  operator delete(void * p)
{
	return MemoryManager::Getinstance()->FreeMemoryPool(p);
};
void * operator new[](unsigned int p)
{
	return MemoryManager::Getinstance()->MallocMemoryPool(p);
};
void  operator delete[](void *p)
{
	return MemoryManager::Getinstance()->FreeMemoryPool(p);
};
#endif