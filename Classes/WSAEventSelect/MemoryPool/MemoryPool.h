#include <stdio.h>
#include <stdlib.h>

class MemoryManager;
class MemoryPool;
struct MemoryBlock
{
	int flag;//记录是不是内存池
	int ip; //标记第几块
	MemoryBlock *pnext;
	MemoryPool * pparent;
};

class MemoryPool
{
private:
	int msize;
	int mcount;
	char * buff;
	MemoryBlock *phead;

public:
	void InitMemoryPool(int s, int c);
	void * MallocMemoryBlock();
	void FreeMemoryBlock(void * p);
	~MemoryPool();

};

class MemoryManager
{
private:
	MemoryPool p64;
	MemoryPool p128;
	MemoryManager();
	static  MemoryManager *pMemoryManager;
public:
	static MemoryManager * Getinstance();
	void * MallocMemoryPool(size_t s);
	void FreeMemoryPool(void * p);
	~MemoryManager();
};



