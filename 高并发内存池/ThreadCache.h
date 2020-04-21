#pragma once
#include"Common.h"

class ThreadCache
{
public:
	//申请内存
	void* Alloc(size_t size);

	//释放内存
	void Dellocte(void* ptr, size_t size);

	//从中心缓存去拿空间
	void* FetchFromCentralCache(size_t index);

	//如果自由链表中某个对象超过一定长度那么将其还给中心缓存CentralCache
	void ListTooLong(FreeList& freelist, size_t num, size_t size);

private:
	FreeList _freelists[NFREELIST];//顶一个自由链表
};