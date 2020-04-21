#include"ThreadCache.h"
//�����ڴ�
void* ThreadCache::Alloc(size_t size)
{
	//�ȸ�������Ĵ�С����λ����������±�index
	size_t index = SizeClass::ListIndex(size);
	//Ȼ�������������ҵ����ڴ�С�Ķ���ȡ�ڴ�
	FreeList& freelist = _freelists[index];
	if (!freelist.Empty())//1�������������Ķ��������ڴ棬��ֱ����,����ȡ�����ڴ�
	{
		return freelist.Pop();
	}
	else//2�������������Ķ���Ϊ�գ���ô��Ҫȥ��һ��Central Cacheȥ��,����ȡ�����ڴ�
	{
		return FetchFromCentralCache(size);
	}	
}

//�ͷ��ڴ�
void ThreadCache::Dellocte(void* ptr, size_t size)
{
	//�ȸ�������Ĵ�С����λ����������±�index
	size_t index = SizeClass::ListIndex(size);
	//Ȼ�������������ҵ����ڴ�С�Ķ���ȡ�ڴ�
	FreeList& freelist = _freelists[index];
	//��ֱ�ӻ���Thread Cache
	freelist.Push(ptr);

	//���ThreadCache�ж�Ӧ��С�Ķ��󳬹�һ��������ô���仹�����Ļ���CentralCache

}

//�����Ļ���ȥ�ÿռ�
void* ThreadCache::FetchFromCentralCache(size_t index)
{
	int num = 20;

	size_t size = (index + 1) * 8;//�����Ӧ�����£������ڴ���С
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

//�������������ĳ�����󳬹�һ��������ô���仹�����Ļ���CentralCache
void ThreadCache::ListTooLong(FreeList& freelist, size_t num, size_t size)
{

}