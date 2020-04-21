#include"ThreadCache.h"
//申请内存
void* ThreadCache::Alloc(size_t size)
{
	//先根据申请的大小，定位自由链表的下标index
	size_t index = SizeClass::ListIndex(size);
	//然后到自由链表中找到对于大小的对象，取内存
	FreeList& freelist = _freelists[index];
	if (!freelist.Empty())//1、如果自由链表的对象中有内存，则直接拿,返回取到的内存
	{
		return freelist.Pop();
	}
	else//2、如果自由链表的对象为空，那么就要去上一级Central Cache去拿,返回取到的内存
	{
		return FetchFromCentralCache(size);
	}	
}

//释放内存
void ThreadCache::Dellocte(void* ptr, size_t size)
{
	//先根据申请的大小，定位自由链表的下标index
	size_t index = SizeClass::ListIndex(size);
	//然后到自由链表中找到对于大小的对象，取内存
	FreeList& freelist = _freelists[index];
	//先直接还给Thread Cache
	freelist.Push(ptr);

	//如果ThreadCache中对应大小的对象超过一定长度那么将其还给中心缓存CentralCache

}

//从中心缓存去拿空间
void* ThreadCache::FetchFromCentralCache(size_t index)
{
	int num = 20;

	size_t size = (index + 1) * 8;//算出对应对象下，挂载内存块大小
	char* start = (char*)malloc(num*size);
	char* cur = start;

	for (int i = 0; i < num - 1; i++)
	{
		char* next = cur + size;
		NextObj(cur) = next;
		cur = next;
	}
	NextObj(cur) = nullptr;

	void* head = NextObj(start);
	void* tail = cur;

	_freelists[index].PushRange(head, tail);
	
	return start;
}

//如果自由链表中某个对象超过一定长度那么将其还给中心缓存CentralCache
void ThreadCache::ListTooLong(FreeList& freelist, size_t num, size_t size)
{

}